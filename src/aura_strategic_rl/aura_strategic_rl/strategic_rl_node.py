#!/usr/bin/env python3
"""
Strategic RL Node

Executes trained RL policy to determine optimal drone positions
for coverage optimization. Publishes CoverageGoal messages to
trajectory planner.
"""

import rclpy
from rclpy.node import Node
import numpy as np
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass
import torch
import torch.nn as nn
from .policy import MLPPolicy, PolicyCheckpoint
from .spaces import ObservationBuilder as TrainedObsBuilder, ObservationConfig

from geometry_msgs.msg import Point
from aura_msgs.msg import (
    DroneState, SwarmState, NetworkMetrics, 
    CoverageMap, CoverageGoal, WeatherZone
)


@dataclass
class RLConfig:
    """RL policy configuration"""
    # Observation space
    num_drones: int = 5
    grid_size: int = 20  # Coverage grid cells per dimension
    max_neighbors: int = 4
    
    # Action space
    action_type: str = 'continuous'  # 'continuous' or 'discrete'
    max_move_distance: float = 10.0  # meters per step
    
    # Policy parameters
    hidden_dim: int = 256
    num_layers: int = 3
    
    # Reward weights
    reward_coverage: float = 1.0
    reward_network_quality: float = 0.5
    reward_energy: float = 0.1
    reward_connectivity: float = 2.0  # Penalty for disconnected mesh
    
    # Deployment
    action_rate_hz: float = 1.0  # How often to compute new goals
    min_altitude: float = 10.0
    max_altitude: float = 50.0


class PolicyNetwork(nn.Module):
    """
    Actor network for strategic positioning policy.
    
    Input: Flattened observation (drone states, coverage map, network metrics)
    Output: Delta positions for each drone (continuous) or goal selection (discrete)
    """
    
    def __init__(self, obs_dim: int, action_dim: int, config: RLConfig):
        super().__init__()
        
        self.config = config
        
        # Build MLP
        layers = []
        in_dim = obs_dim
        for _ in range(config.num_layers - 1):
            layers.extend([
                nn.Linear(in_dim, config.hidden_dim),
                nn.ReLU(),
                nn.LayerNorm(config.hidden_dim),
            ])
            in_dim = config.hidden_dim
        
        self.feature_net = nn.Sequential(*layers)
        
        # Action head
        self.action_mean = nn.Linear(config.hidden_dim, action_dim)
        self.action_log_std = nn.Parameter(torch.zeros(action_dim))
        
    def forward(self, obs: torch.Tensor) -> Tuple[torch.Tensor, torch.Tensor]:
        """
        Forward pass.
        
        Returns:
            action_mean: Mean of action distribution
            action_std: Standard deviation of action distribution
        """
        features = self.feature_net(obs)
        action_mean = self.action_mean(features)
        action_std = torch.exp(self.action_log_std)
        return action_mean, action_std
    
    def get_action(self, obs: torch.Tensor, deterministic: bool = False) -> torch.Tensor:
        """Sample action from policy"""
        mean, std = self.forward(obs)
        
        if deterministic:
            return mean
        
        # Sample from Gaussian
        noise = torch.randn_like(mean)
        action = mean + std * noise
        
        return action


class ObservationBuilder:
    """
    Builds observation vector from ROS messages.
    """
    
    def __init__(self, config: RLConfig):
        self.config = config
        
        # Compute observation dimension
        drone_obs_dim = 7  # x, y, z, vx, vy, vz, battery
        coverage_dim = config.grid_size * config.grid_size
        network_dim = config.num_drones * (config.max_neighbors + 3)  # neighbors + metrics
        
        self.obs_dim = (config.num_drones * drone_obs_dim + 
                        coverage_dim + 
                        network_dim)
    
    def build(self, 
              swarm_state: SwarmState,
              coverage_map: CoverageMap,
              network_metrics: NetworkMetrics) -> np.ndarray:
        """Build observation vector from current state"""
        obs_parts = []
        
        # Drone states (padded to num_drones)
        drone_obs = np.zeros((self.config.num_drones, 7))
        for i, drone in enumerate(swarm_state.drones[:self.config.num_drones]):
            drone_obs[i] = [
                drone.position.x / 100.0,  # Normalize
                drone.position.y / 100.0,
                drone.position.z / 50.0,
                drone.velocity.x / 3.0,
                drone.velocity.y / 3.0,
                drone.velocity.z / 3.0,
                drone.battery_percent / 100.0
            ]
        obs_parts.append(drone_obs.flatten())
        
        # Coverage map (downsampled to grid_size)
        if coverage_map.is_covered:
            coverage = np.array(coverage_map.is_covered).astype(float)
            # Reshape and downsample
            try:
                coverage = coverage.reshape(
                    coverage_map.grid_size_y, 
                    coverage_map.grid_size_x
                )
                # Simple downsampling by averaging
                step_y = max(1, coverage_map.grid_size_y // self.config.grid_size)
                step_x = max(1, coverage_map.grid_size_x // self.config.grid_size)
                coverage = coverage[::step_y, ::step_x]
                coverage = coverage[:self.config.grid_size, :self.config.grid_size]
            except:
                coverage = np.zeros((self.config.grid_size, self.config.grid_size))
        else:
            coverage = np.zeros((self.config.grid_size, self.config.grid_size))
        
        # Pad if needed
        padded_coverage = np.zeros((self.config.grid_size, self.config.grid_size))
        h, w = coverage.shape
        padded_coverage[:h, :w] = coverage
        obs_parts.append(padded_coverage.flatten())
        
        # Network metrics per drone
        network_obs = np.zeros((self.config.num_drones, self.config.max_neighbors + 3))
        for i, drone in enumerate(swarm_state.drones[:self.config.num_drones]):
            network_obs[i, 0] = drone.throughput_mbps / 50.0
            network_obs[i, 1] = drone.latency_ms / 100.0
            network_obs[i, 2] = drone.connected_neighbors / self.config.max_neighbors
        obs_parts.append(network_obs.flatten())
        
        return np.concatenate(obs_parts).astype(np.float32)


class StrategicRLNode(Node):
    """
    Strategic RL policy execution node.
    
    Computes optimal drone positions based on:
    - Current coverage map
    - Network metrics
    - Weather conditions
    - Battery states
    """
    
    def __init__(self):
        super().__init__('strategic_rl')
        
        # Parameters
        self.declare_parameter('num_drones', 5)
        self.declare_parameter('action_rate_hz', 1.0)
        self.declare_parameter('model_path', '')
        self.declare_parameter('use_baseline', True)  # Use HHO baseline if no trained model
        self.declare_parameter('deterministic', True)
        
        num_drones = self.get_parameter('num_drones').value
        action_rate = self.get_parameter('action_rate_hz').value
        model_path = self.get_parameter('model_path').value
        self.use_baseline = self.get_parameter('use_baseline').value
        self.deterministic = self.get_parameter('deterministic').value
        
        # Configuration
        self.config = RLConfig(num_drones=num_drones)
        
        # Observation builder — use the trained spaces when loading a trained policy
        if model_path and not self.use_baseline:
            obs_config = ObservationConfig(num_drones=num_drones)
            self.obs_builder = TrainedObsBuilder(obs_config)
            self.obs_builder.obs_dim = obs_config.total_obs_dim  # compatibility
            self.get_logger().info(f'Using trained observation space (dim={obs_config.total_obs_dim})')
        else:
            self.obs_builder = ObservationBuilder(self.config)
        
        # Policy network
        action_dim = num_drones * 3  # dx, dy, dz per drone
        self.policy = None
        
        # Load trained model if available
        if model_path:
            try:
                self.policy, meta = PolicyCheckpoint.load(model_path, device='cpu')
                self.use_baseline = False
                self.get_logger().info(
                    f'Loaded trained policy from {model_path} '
                    f'(obs={meta.get("obs_dim")}, act={meta.get("action_dim")}, '
                    f'reward={meta.get("eval_reward", "?"):.1f})')
            except Exception as e:
                self.get_logger().warn(f'Failed to load model: {e}. Using baseline.')
                self.use_baseline = True
        
        # Fallback to old PolicyNetwork if no trained model
        if self.policy is None and not self.use_baseline:
            self.policy = PolicyNetwork(
                self.obs_builder.obs_dim, action_dim, self.config)
        
        # State
        self.latest_swarm: Optional[SwarmState] = None
        self.latest_coverage: Optional[CoverageMap] = None
        self.latest_network: Optional[NetworkMetrics] = None
        self.weather_zones: List[WeatherZone] = []
        
        # Subscribers
        self.swarm_sub = self.create_subscription(
            SwarmState, '/swarm/state',
            self.swarm_callback, 10
        )
        
        self.coverage_sub = self.create_subscription(
            CoverageMap, '/network/coverage_map',
            self.coverage_callback, 10
        )
        
        self.network_sub = self.create_subscription(
            NetworkMetrics, '/network/metrics',
            self.network_callback, 10
        )
        
        self.weather_sub = self.create_subscription(
            WeatherZone, '/weather/zones',
            self.weather_callback, 10
        )
        
        # Publishers - one per drone
        self.goal_pubs: Dict[int, rclpy.publisher.Publisher] = {}
        for i in range(num_drones):
            pub = self.create_publisher(
                CoverageGoal, 
                f'/drone_{i}/coverage_goal', 
                10
            )
            self.goal_pubs[i] = pub
        
        # Action timer
        self.action_timer = self.create_timer(
            1.0 / action_rate,
            self.compute_and_publish_goals
        )
        
        self.get_logger().info(
            f'Strategic RL node started (drones: {num_drones}, '
            f'baseline: {self.use_baseline})'
        )
    
    def swarm_callback(self, msg: SwarmState):
        self.latest_swarm = msg
    
    def coverage_callback(self, msg: CoverageMap):
        self.latest_coverage = msg
    
    def network_callback(self, msg: NetworkMetrics):
        self.latest_network = msg
    
    def weather_callback(self, msg: WeatherZone):
        # Update or add weather zone
        for i, zone in enumerate(self.weather_zones):
            if zone.zone_id == msg.zone_id:
                self.weather_zones[i] = msg
                return
        self.weather_zones.append(msg)
    
    def compute_and_publish_goals(self):
        """Compute optimal positions and publish goals"""
        if self.latest_swarm is None:
            return
        
        if len(self.latest_swarm.drones) == 0:
            return
        
        if self.use_baseline:
            goals = self._compute_baseline_goals()
        else:
            goals = self._compute_rl_goals()
        
        # Publish goals
        for drone_id, goal_pos in goals.items():
            if drone_id in self.goal_pubs:
                msg = CoverageGoal()
                msg.timestamp = self.get_clock().now().to_msg()
                msg.drone_id = drone_id
                msg.position.x = goal_pos[0]
                msg.position.y = goal_pos[1]
                msg.position.z = goal_pos[2]
                msg.priority = 1.0
                msg.min_altitude = self.config.min_altitude
                msg.max_altitude = self.config.max_altitude
                
                self.goal_pubs[drone_id].publish(msg)
    
    def _compute_rl_goals(self) -> Dict[int, np.ndarray]:
        """Compute goals using trained RL policy"""
        # Build observation
        if self.latest_coverage is None:
            self.latest_coverage = CoverageMap()
        if self.latest_network is None:
            self.latest_network = NetworkMetrics()
        
        # Use appropriate observation builder
        if hasattr(self.obs_builder, 'build_from_ros'):
            obs = self.obs_builder.build_from_ros(
                self.latest_swarm,
                self.latest_network,
                self.weather_zones
            )
        else:
            obs = self.obs_builder.build(
                self.latest_swarm,
                self.latest_coverage,
                self.latest_network
            )
        
        # Run policy
        with torch.no_grad():
            obs_tensor = torch.FloatTensor(obs).unsqueeze(0)
            actions = self.policy.get_action(obs_tensor, self.deterministic)
            actions = actions.squeeze(0).numpy()
        
        # Convert actions to goal positions
        goals = {}
        for i, drone in enumerate(self.latest_swarm.drones[:self.config.num_drones]):
            delta = actions[i*3:(i+1)*3] * self.config.max_move_distance
            
            current_pos = np.array([
                drone.position.x,
                drone.position.y,
                drone.position.z
            ])
            
            goal_pos = current_pos + delta
            
            # Clamp altitude
            goal_pos[2] = np.clip(
                goal_pos[2],
                self.config.min_altitude,
                self.config.max_altitude
            )
            
            goals[drone.drone_id] = goal_pos
        
        return goals
    
    def _compute_baseline_goals(self) -> Dict[int, np.ndarray]:
        """
        Compute goals using simple baseline strategy.
        Spreads drones out to maximize coverage area.
        """
        goals = {}
        num_drones = len(self.latest_swarm.drones)
        
        if num_drones == 0:
            return goals
        
        # Simple grid formation
        # Compute centroid of current positions
        positions = []
        for drone in self.latest_swarm.drones:
            positions.append([
                drone.position.x,
                drone.position.y,
                drone.position.z
            ])
        positions = np.array(positions)
        centroid = np.mean(positions, axis=0)
        
        # Spread in a circle around centroid
        radius = 50.0  # meters
        altitude = 25.0  # meters
        
        for i, drone in enumerate(self.latest_swarm.drones):
            angle = 2 * np.pi * i / num_drones
            
            goal_x = centroid[0] + radius * np.cos(angle)
            goal_y = centroid[1] + radius * np.sin(angle)
            goal_z = altitude
            
            # Avoid weather zones
            for zone in self.weather_zones:
                if zone.no_fly and zone.is_active:
                    zone_pos = np.array([zone.center.x, zone.center.y])
                    goal_pos = np.array([goal_x, goal_y])
                    
                    dist = np.linalg.norm(goal_pos - zone_pos)
                    if dist < zone.radius_meters:
                        # Push away from zone
                        direction = goal_pos - zone_pos
                        if np.linalg.norm(direction) > 0:
                            direction = direction / np.linalg.norm(direction)
                        else:
                            direction = np.array([1, 0])
                        
                        goal_x = zone.center.x + direction[0] * (zone.radius_meters + 10)
                        goal_y = zone.center.y + direction[1] * (zone.radius_meters + 10)
            
            goals[drone.drone_id] = np.array([goal_x, goal_y, goal_z])
        
        return goals


def main(args=None):
    rclpy.init(args=args)
    node = StrategicRLNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
