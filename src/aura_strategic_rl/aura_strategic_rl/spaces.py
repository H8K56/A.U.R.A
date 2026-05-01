"""
Observation and Action Spaces for A.U.R.A. Strategic RL

Defines the observation and action spaces used by the RL policy.
Observation space is ~184-dimensional covering:
- Drone positions and states
- Network metrics
- Coverage information
- Environmental conditions

Action space provides position offsets for each drone.
"""

import numpy as np
from dataclasses import dataclass
from typing import Dict, List, Tuple, Optional


@dataclass
class ObservationConfig:
    """Configuration for observation space"""

    # Swarm
    num_drones: int = 5

    # Per-drone observation dimensions
    drone_position_dim: int = 3      # x, y, z (normalized)
    drone_velocity_dim: int = 3      # vx, vy, vz
    drone_state_dim: int = 3         # battery, signal, neighbors
    drone_network_dim: int = 4       # rssi, throughput, latency, is_hub

    # Network observation
    coverage_grid_size: int = 10     # 10x10 downsampled coverage
    network_metrics_dim: int = 4     # coverage%, avg_signal, throughput, latency

    # Environment
    num_weather_zones: int = 3       # Max weather zones to track
    weather_zone_dim: int = 5        # x, y, radius, attenuation, active

    @property
    def drone_obs_dim(self) -> int:
        """Total observation per drone"""
        return (self.drone_position_dim +
                self.drone_velocity_dim +
                self.drone_state_dim +
                self.drone_network_dim)

    @property
    def total_obs_dim(self) -> int:
        """Total observation dimension"""
        swarm_dim = self.num_drones * self.drone_obs_dim
        coverage_dim = self.coverage_grid_size ** 2
        network_dim = self.network_metrics_dim
        weather_dim = self.num_weather_zones * self.weather_zone_dim

        return swarm_dim + coverage_dim + network_dim + weather_dim


@dataclass
class ActionConfig:
    """Configuration for action space"""

    num_drones: int = 5

    # Per-drone action dimensions
    position_delta_dim: int = 3      # dx, dy, dz

    # Action scaling
    max_delta_xy: float = 2.0        # Max horizontal movement per step (m)
    max_delta_z: float = 0.8         # Max vertical movement per step (m)

    # Position bounds
    min_altitude: float = 15.0       # Minimum flight altitude (m)
    max_altitude: float = 80.0       # Maximum flight altitude (m)
    area_bound: float = 250.0        # Max distance from world center (m)

    # World center — must match ObservationBuilder constants
    world_center_x: float = 120.0
    world_center_y: float = -170.0

    @property
    def action_dim(self) -> int:
        """Total action dimension"""
        return self.num_drones * self.position_delta_dim


class ObservationBuilder:
    """
    Builds observation vectors from ROS messages or simulation state.

    Normalizes all values to roughly [-1, 1] or [0, 1] range
    for stable neural network training.
    """

    # Normalization constants
    POSITION_SCALE = 200.0       # meters
    VELOCITY_SCALE = 5.0         # m/s
    RSSI_OFFSET = 90.0           # shift so -90 dBm -> 0
    RSSI_SCALE = 40.0            # range width

    # World center — disaster zone centroid in Gazebo world frame
    WORLD_CENTER_X = 120.0
    WORLD_CENTER_Y = -170.0

    def __init__(self, config: ObservationConfig = None):
        self.config = config or ObservationConfig()

    def build_from_ros(self, swarm_state, network_metrics, weather_zones=None) -> np.ndarray:
        """
        Build observation from ROS messages.

        Args:
            swarm_state: aura_msgs/SwarmState message
            network_metrics: aura_msgs/NetworkMetrics message
            weather_zones: list of aura_msgs/WeatherZone messages

        Returns:
            Flat observation vector of shape (total_obs_dim,)
        """
        parts = []

        # 1. Drone states
        parts.append(self._build_drone_obs_ros(swarm_state))

        # 2. Downsampled coverage grid
        parts.append(self._build_coverage_obs(network_metrics))

        # 3. Global network metrics
        parts.append(self._build_network_obs(network_metrics))

        # 4. Weather zones
        parts.append(self._build_weather_obs(weather_zones or []))

        return np.concatenate(parts).astype(np.float32)

    def build_from_sim(self, drones, network_metrics_dict: dict,
                       weather_zones=None) -> np.ndarray:
        """
        Build observation from simulation state (for Gymnasium env).

        Args:
            drones: list of DroneState dataclass objects
            network_metrics_dict: dict with coverage_percent, avg_signal, etc.
            weather_zones: list of WeatherZone objects
        """
        parts = []

        # 1. Drone states
        drone_obs = np.zeros((self.config.num_drones, self.config.drone_obs_dim))
        world_center = np.array([self.WORLD_CENTER_X, self.WORLD_CENTER_Y, 0.0])
        for i, drone in enumerate(drones[:self.config.num_drones]):
            pos = (drone.position - world_center) / self.POSITION_SCALE
            vel = drone.velocity / self.VELOCITY_SCALE

            drone_obs[i, 0:3] = pos
            drone_obs[i, 3:6] = vel
            drone_obs[i, 6] = drone.battery / 100.0
            drone_obs[i, 7] = (drone.signal_strength_dbm + self.RSSI_OFFSET) / self.RSSI_SCALE
            drone_obs[i, 8] = len(drone.neighbors) / self.config.num_drones
            drone_obs[i, 9] = drone.throughput_mbps / 100.0
            drone_obs[i, 10] = drone.latency_ms / 100.0
            drone_obs[i, 11] = 0.0  # hops_to_hub placeholder
            drone_obs[i, 12] = 1.0 if drone.is_hub else 0.0

        parts.append(drone_obs.flatten())

        # 2. Coverage grid
        coverage_obs = np.zeros(self.config.coverage_grid_size ** 2)
        if 'coverage_grid' in network_metrics_dict:
            grid = network_metrics_dict['coverage_grid']
            try:
                gs = self.config.coverage_grid_size
                step_h = max(1, grid.shape[0] // gs)
                step_w = max(1, grid.shape[1] // gs)
                downsampled = grid[::step_h, ::step_w][:gs, :gs]
                coverage_obs[:downsampled.size] = downsampled.flatten()[:coverage_obs.size]
            except (ValueError, AttributeError):
                pass
        parts.append(coverage_obs)

        # 3. Network metrics
        net_obs = np.zeros(self.config.network_metrics_dim)
        net_obs[0] = network_metrics_dict.get('coverage_percent', 0.0) / 100.0
        net_obs[1] = (network_metrics_dict.get('avg_signal_dbm', -90.0) + self.RSSI_OFFSET) / self.RSSI_SCALE
        net_obs[2] = network_metrics_dict.get('avg_throughput_mbps', 0.0) / 100.0
        net_obs[3] = network_metrics_dict.get('avg_latency_ms', 0.0) / 100.0
        parts.append(net_obs)

        # 4. Weather zones
        weather_obs = np.zeros(self.config.num_weather_zones * self.config.weather_zone_dim)
        if weather_zones:
            for i, zone in enumerate(weather_zones[:self.config.num_weather_zones]):
                idx = i * self.config.weather_zone_dim
                weather_obs[idx] = (zone.center[0] - self.WORLD_CENTER_X) / self.POSITION_SCALE
                weather_obs[idx + 1] = (zone.center[1] - self.WORLD_CENTER_Y) / self.POSITION_SCALE
                weather_obs[idx + 2] = zone.radius / self.POSITION_SCALE
                weather_obs[idx + 3] = zone.attenuation_db / 20.0
                weather_obs[idx + 4] = 1.0 if zone.is_active else 0.0
        parts.append(weather_obs)

        return np.concatenate(parts).astype(np.float32)

    def _build_drone_obs_ros(self, swarm_state) -> np.ndarray:
        """Build drone observations from ROS SwarmState message"""
        obs = np.zeros((self.config.num_drones, self.config.drone_obs_dim))

        if swarm_state is None:
            return obs.flatten()

        for i, drone in enumerate(swarm_state.drones[:self.config.num_drones]):
            # Position normalized relative to world center (disaster zone)
            obs[i, 0] = (drone.position.x - self.WORLD_CENTER_X) / self.POSITION_SCALE
            obs[i, 1] = (drone.position.y - self.WORLD_CENTER_Y) / self.POSITION_SCALE
            obs[i, 2] = drone.position.z / self.POSITION_SCALE

            # Velocity
            obs[i, 3] = drone.velocity.x / self.VELOCITY_SCALE
            obs[i, 4] = drone.velocity.y / self.VELOCITY_SCALE
            obs[i, 5] = drone.velocity.z / self.VELOCITY_SCALE

            # State
            obs[i, 6] = drone.battery_percent / 100.0
            obs[i, 7] = (drone.signal_strength_dbm + self.RSSI_OFFSET) / self.RSSI_SCALE
            obs[i, 8] = drone.connected_neighbors / self.config.num_drones

            # Network
            obs[i, 9] = drone.throughput_mbps / 100.0
            obs[i, 10] = drone.latency_ms / 100.0
            obs[i, 11] = 0.0  # hops_to_hub (would need tracking)
            obs[i, 12] = 1.0 if drone.role == 1 else 0.0  # is_hub

        return obs.flatten()

    def _build_coverage_obs(self, network_metrics) -> np.ndarray:
        """Build downsampled coverage grid observation"""
        grid_size = self.config.coverage_grid_size
        obs = np.zeros(grid_size * grid_size)

        if network_metrics is None or not network_metrics.coverage_mask:
            return obs

        try:
            orig_h = network_metrics.grid_size_y
            orig_w = network_metrics.grid_size_x
            coverage = np.array(network_metrics.coverage_mask).reshape(orig_h, orig_w)

            step_h = max(1, orig_h // grid_size)
            step_w = max(1, orig_w // grid_size)

            for i in range(grid_size):
                for j in range(grid_size):
                    h_start = i * step_h
                    h_end = min((i + 1) * step_h, orig_h)
                    w_start = j * step_w
                    w_end = min((j + 1) * step_w, orig_w)
                    obs[i * grid_size + j] = np.mean(
                        coverage[h_start:h_end, w_start:w_end]
                    )
        except (ValueError, AttributeError):
            pass

        return obs

    def _build_network_obs(self, network_metrics) -> np.ndarray:
        """Build global network metrics observation"""
        obs = np.zeros(self.config.network_metrics_dim)

        if network_metrics is None:
            return obs

        obs[0] = network_metrics.total_coverage_percent / 100.0
        obs[1] = (network_metrics.avg_signal_strength_dbm + self.RSSI_OFFSET) / self.RSSI_SCALE
        obs[2] = network_metrics.avg_throughput_mbps / 100.0
        obs[3] = network_metrics.avg_latency_ms / 100.0

        return obs

    def _build_weather_obs(self, weather_zones: list) -> np.ndarray:
        """Build weather zone observations"""
        obs = np.zeros(self.config.num_weather_zones * self.config.weather_zone_dim)

        for i, zone in enumerate(weather_zones[:self.config.num_weather_zones]):
            idx = i * self.config.weather_zone_dim
            try:
                obs[idx] = (zone.center.x - self.WORLD_CENTER_X) / self.POSITION_SCALE
                obs[idx + 1] = (zone.center.y - self.WORLD_CENTER_Y) / self.POSITION_SCALE
                obs[idx + 2] = zone.radius_meters / self.POSITION_SCALE
                obs[idx + 3] = zone.signal_attenuation_db / 20.0
                obs[idx + 4] = 1.0 if zone.is_active else 0.0
            except AttributeError:
                pass

        return obs


class ActionProcessor:
    """
    Processes raw action outputs from policy network.

    Converts [-1, 1] tanh-squashed actions to bounded position deltas,
    then clips to enforce safety constraints.
    """

    def __init__(self, config: ActionConfig = None):
        self.config = config or ActionConfig()

    def process(self, raw_actions: np.ndarray,
                current_positions: List[np.ndarray]) -> List[np.ndarray]:
        """
        Convert raw policy output to position deltas.

        Args:
            raw_actions: Array of shape (action_dim,) in [-1, 1]
            current_positions: List of current drone positions

        Returns:
            List of goal position arrays, one per drone
        """
        goals = []
        nd = self.config.num_drones

        for i in range(nd):
            idx = i * self.config.position_delta_dim
            raw = raw_actions[idx:idx + self.config.position_delta_dim]

            # Scale to physical units
            delta = np.zeros(3)
            delta[0] = raw[0] * self.config.max_delta_xy
            delta[1] = raw[1] * self.config.max_delta_xy
            delta[2] = raw[2] * self.config.max_delta_z

            # Compute goal position
            if i < len(current_positions):
                goal = current_positions[i] + delta
            else:
                goal = delta

            # Circular clip relative to world center — keeps drones inside the disk
            # that the reward function enforces (avoids square-corner penalty spikes)
            cx = self.config.world_center_x
            cy = self.config.world_center_y
            bound = self.config.area_bound
            dx, dy = goal[0] - cx, goal[1] - cy
            dist_xy = np.sqrt(dx * dx + dy * dy)
            if dist_xy > bound:
                scale = bound / dist_xy
                goal[0] = cx + dx * scale
                goal[1] = cy + dy * scale
            goal[2] = np.clip(goal[2], self.config.min_altitude, self.config.max_altitude)

            goals.append(goal)

        return goals
