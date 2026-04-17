"""
Gymnasium Environment for A.U.R.A. Swarm Training

Provides a standalone training environment that simulates:
- Drone swarm dynamics
- Network coverage (using log-distance path loss model)
- Mesh connectivity
- Weather effects
- Reward computation

Can run without ROS for faster training, then deploy trained
policy via strategic_rl_node.
"""

import math
import numpy as np
from typing import Dict, List, Tuple, Optional, Any
from dataclasses import dataclass

try:
    import gymnasium as gym
    from gymnasium import spaces
    GYM_AVAILABLE = True
except ImportError:
    GYM_AVAILABLE = False

    class _StubEnv:
        pass

    class gym:  # type: ignore[no-redef]
        Env = _StubEnv

from .spaces import ObservationConfig, ActionConfig, ObservationBuilder, ActionProcessor
from .rewards import RewardConfig, RewardCalculator


@dataclass
class EnvConfig:
    """Environment configuration"""

    # Simulation
    num_drones: int = 5
    max_steps: int = 200
    dt: float = 0.5  # Time step (seconds)

    # Area
    area_size: float = 200.0
    grid_resolution: float = 10.0

    # Drone dynamics
    max_velocity: float = 5.0   # m/s
    max_acceleration: float = 2.0  # m/s^2

    # Initial formation
    initial_radius: float = 30.0
    initial_altitude: float = 30.0

    # Network simulation (log-distance path loss)
    tx_power_dbm: float = 20.0
    noise_floor_dbm: float = -100.0
    path_loss_exponent: float = 2.7
    reference_distance_m: float = 1.0
    reference_loss_db: float = 46.7  # Free-space loss at 1m for 2.4 GHz
    coverage_threshold_dbm: float = -80.0
    max_mesh_distance: float = 150.0

    # Randomization
    randomize_initial_positions: bool = True
    randomize_weather: bool = False
    weather_probability: float = 0.3


class DroneState:
    """State of a single drone in simulation"""

    def __init__(self, drone_id: int, position: np.ndarray):
        self.drone_id = drone_id
        self.position = position.copy()
        self.velocity = np.zeros(3)
        self.battery = 100.0
        self.is_hub = (drone_id == 0)

        # Network state
        self.signal_strength_dbm = -70.0
        self.throughput_mbps = 50.0
        self.latency_ms = 10.0
        self.neighbors: List[int] = []


class WeatherZone:
    """Simulated weather zone"""

    def __init__(self, x: float, y: float, radius: float, attenuation_db: float):
        self.center = np.array([x, y])
        self.radius = radius
        self.attenuation_db = attenuation_db
        self.is_active = True


class SwarmGymEnv(gym.Env if GYM_AVAILABLE else object):
    """
    Gymnasium environment for A.U.R.A. swarm training.

    Observation: ~184-dimensional vector (see spaces.py)
    Action: num_drones * 3 position deltas
    Reward: Multi-objective (coverage + network + safety)
    """

    metadata = {'render_modes': ['human', 'rgb_array']}

    def __init__(self, config: EnvConfig = None, render_mode: str = None):
        super().__init__()

        self.config = config or EnvConfig()
        self.render_mode = render_mode

        # Create configs
        self.obs_config = ObservationConfig(num_drones=self.config.num_drones)
        self.action_config = ActionConfig(num_drones=self.config.num_drones)
        self.reward_config = RewardConfig()

        # Create helpers
        self.obs_builder = ObservationBuilder(self.obs_config)
        self.action_processor = ActionProcessor(self.action_config)
        self.reward_calculator = RewardCalculator(self.reward_config)

        # Define spaces
        if GYM_AVAILABLE:
            self.observation_space = spaces.Box(
                low=-np.inf,
                high=np.inf,
                shape=(self.obs_config.total_obs_dim,),
                dtype=np.float32
            )

            self.action_space = spaces.Box(
                low=-1.0,
                high=1.0,
                shape=(self.action_config.action_dim,),
                dtype=np.float32
            )

        # State
        self.drones: List[DroneState] = []
        self.weather_zones: List[WeatherZone] = []
        self.step_count = 0
        self.coverage_history: List[float] = []

        # Coverage grid
        self._init_coverage_grid()

    def _init_coverage_grid(self):
        """Initialize coverage grid for simulation"""
        size = int(2 * self.config.area_size / self.config.grid_resolution)
        self.grid_size = size
        self.coverage_grid = np.zeros((size, size), dtype=np.float32)
        self.signal_grid = np.full((size, size), -200.0, dtype=np.float32)

    def reset(self, seed: int = None, options: Dict = None) -> Tuple[np.ndarray, Dict]:
        """Reset environment to initial state"""
        if seed is not None:
            np.random.seed(seed)

        self.step_count = 0
        self.coverage_history = []
        self.reward_calculator.reset()

        # Initialize drones
        self.drones = []
        for i in range(self.config.num_drones):
            if self.config.randomize_initial_positions:
                angle = 2 * np.pi * i / self.config.num_drones
                r = self.config.initial_radius * (0.8 + 0.4 * np.random.random())
                pos = np.array([
                    r * np.cos(angle),
                    r * np.sin(angle),
                    self.config.initial_altitude + np.random.uniform(-5, 5)
                ])
            else:
                angle = 2 * np.pi * i / self.config.num_drones
                pos = np.array([
                    self.config.initial_radius * np.cos(angle),
                    self.config.initial_radius * np.sin(angle),
                    self.config.initial_altitude
                ])

            self.drones.append(DroneState(drone_id=i, position=pos))

        # Weather zones
        self.weather_zones = []
        if self.config.randomize_weather and np.random.random() < self.config.weather_probability:
            wx = np.random.uniform(-100, 100)
            wy = np.random.uniform(-100, 100)
            wr = np.random.uniform(30, 80)
            wa = np.random.uniform(5, 15)
            self.weather_zones.append(WeatherZone(wx, wy, wr, wa))

        # Compute initial state
        self._update_network()
        obs = self._get_observation()
        info = self._get_info()

        return obs, info

    def step(self, action: np.ndarray) -> Tuple[np.ndarray, float, bool, bool, Dict]:
        """Execute one environment step"""
        self.step_count += 1

        # Store previous positions for movement penalty
        prev_positions = [d.position.copy() for d in self.drones]

        # Process actions -> goal positions
        current_positions = [d.position for d in self.drones]
        goals = self.action_processor.process(action, current_positions)

        # Update drone positions (simplified dynamics)
        for i, drone in enumerate(self.drones):
            if i < len(goals):
                direction = goals[i] - drone.position
                dist = np.linalg.norm(direction)

                if dist > 0.1:
                    # Limit velocity
                    max_step = self.config.max_velocity * self.config.dt
                    if dist > max_step:
                        direction = direction / dist * max_step

                    drone.velocity = direction / self.config.dt
                    drone.position += direction
                else:
                    drone.velocity = np.zeros(3)

            # Battery drain (simplified)
            speed = np.linalg.norm(drone.velocity)
            drain = 0.01 + 0.005 * speed  # base + speed-dependent
            drone.battery = max(0.0, drone.battery - drain)

        # Update network simulation
        self._update_network()

        # Compute reward
        movement_magnitudes = [
            np.linalg.norm(self.drones[i].position - prev_positions[i])
            for i in range(len(self.drones))
        ]

        coverage_percent = self._compute_coverage_percent()
        mesh_connected = self._check_mesh_connected()

        reward, reward_components = self.reward_calculator.compute_reward(
            coverage_percent=coverage_percent,
            mesh_connected=mesh_connected,
            avg_signal_dbm=self._compute_avg_signal(),
            avg_throughput_mbps=self._compute_avg_throughput(),
            avg_latency_ms=self._compute_avg_latency(),
            drone_positions=[(d.position[0], d.position[1], d.position[2])
                             for d in self.drones],
            movement_magnitudes=movement_magnitudes,
        )

        self.coverage_history.append(coverage_percent)

        # Check termination
        terminated = False
        truncated = self.step_count >= self.config.max_steps

        # Terminate if all batteries depleted
        if all(d.battery <= 0 for d in self.drones):
            terminated = True

        obs = self._get_observation()
        info = self._get_info()
        info['reward_components'] = reward_components

        return obs, reward, terminated, truncated, info

    # ── Network simulation ──────────────────────────────────────

    def _update_network(self):
        """Update network metrics using log-distance path loss model"""
        self.signal_grid.fill(-200.0)
        self.coverage_grid.fill(0.0)

        half = self.config.area_size
        res = self.config.grid_resolution

        for drone in self.drones:
            # Compute signal at each grid cell
            for gy in range(self.grid_size):
                for gx in range(self.grid_size):
                    cell_x = -half + (gx + 0.5) * res
                    cell_y = -half + (gy + 0.5) * res

                    dx = cell_x - drone.position[0]
                    dy = cell_y - drone.position[1]
                    dz = -drone.position[2]  # ground level
                    dist_3d = math.sqrt(dx * dx + dy * dy + dz * dz)

                    if dist_3d < self.config.reference_distance_m:
                        dist_3d = self.config.reference_distance_m

                    # Log-distance path loss
                    path_loss = (self.config.reference_loss_db +
                                 10 * self.config.path_loss_exponent *
                                 math.log10(dist_3d / self.config.reference_distance_m))

                    # Weather attenuation
                    for wz in self.weather_zones:
                        if wz.is_active:
                            wdist = math.sqrt(
                                (cell_x - wz.center[0]) ** 2 +
                                (cell_y - wz.center[1]) ** 2
                            )
                            if wdist < wz.radius:
                                path_loss += wz.attenuation_db

                    signal = self.config.tx_power_dbm - path_loss

                    # Max signal from any drone
                    if signal > self.signal_grid[gy, gx]:
                        self.signal_grid[gy, gx] = signal

            # Update drone-to-drone links
            drone.neighbors = []
            for other in self.drones:
                if other.drone_id == drone.drone_id:
                    continue
                d = np.linalg.norm(drone.position - other.position)
                if d < self.config.max_mesh_distance:
                    drone.neighbors.append(other.drone_id)

        # Coverage mask
        self.coverage_grid = (
            self.signal_grid > self.config.coverage_threshold_dbm
        ).astype(np.float32)

        # Update per-drone network metrics
        for drone in self.drones:
            # Best signal from neighbors
            if drone.neighbors:
                signals = []
                for nid in drone.neighbors:
                    d = np.linalg.norm(drone.position - self.drones[nid].position)
                    if d < self.config.reference_distance_m:
                        d = self.config.reference_distance_m
                    pl = (self.config.reference_loss_db +
                          10 * self.config.path_loss_exponent *
                          math.log10(d / self.config.reference_distance_m))
                    signals.append(self.config.tx_power_dbm - pl)
                drone.signal_strength_dbm = max(signals)
                # Simplified throughput model (Shannon-ish)
                snr_linear = 10 ** ((drone.signal_strength_dbm -
                                     self.config.noise_floor_dbm) / 10)
                drone.throughput_mbps = min(100.0, 20.0 * math.log2(1 + snr_linear))
                drone.latency_ms = 5.0 + 2.0 * len(drone.neighbors)
            else:
                drone.signal_strength_dbm = -100.0
                drone.throughput_mbps = 0.0
                drone.latency_ms = 999.0

    def _compute_coverage_percent(self) -> float:
        """Compute percentage of area with usable coverage"""
        total_cells = self.grid_size * self.grid_size
        if total_cells == 0:
            return 0.0
        return 100.0 * np.sum(self.coverage_grid) / total_cells

    def _check_mesh_connected(self) -> bool:
        """Check if all drones form a connected mesh (BFS)"""
        if len(self.drones) <= 1:
            return True

        visited = {0}
        queue = [0]

        while queue:
            current = queue.pop(0)
            for neighbor_id in self.drones[current].neighbors:
                if neighbor_id not in visited:
                    visited.add(neighbor_id)
                    queue.append(neighbor_id)

        return len(visited) == len(self.drones)

    def _compute_avg_signal(self) -> float:
        return np.mean([d.signal_strength_dbm for d in self.drones])

    def _compute_avg_throughput(self) -> float:
        return np.mean([d.throughput_mbps for d in self.drones])

    def _compute_avg_latency(self) -> float:
        return np.mean([d.latency_ms for d in self.drones])

    # ── Observation / Info ──────────────────────────────────────

    def _get_observation(self) -> np.ndarray:
        """Build observation vector"""
        net_dict = {
            'coverage_percent': self._compute_coverage_percent(),
            'avg_signal_dbm': self._compute_avg_signal(),
            'avg_throughput_mbps': self._compute_avg_throughput(),
            'avg_latency_ms': self._compute_avg_latency(),
            'coverage_grid': self.coverage_grid,
        }

        return self.obs_builder.build_from_sim(
            drones=self.drones,
            network_metrics_dict=net_dict,
            weather_zones=self.weather_zones,
        )

    def _get_info(self) -> Dict[str, Any]:
        """Return info dictionary"""
        return {
            'coverage_percent': self._compute_coverage_percent(),
            'mesh_connected': self._check_mesh_connected(),
            'avg_signal_dbm': self._compute_avg_signal(),
            'avg_throughput_mbps': self._compute_avg_throughput(),
            'avg_latency_ms': self._compute_avg_latency(),
            'step': self.step_count,
            'drone_positions': [d.position.tolist() for d in self.drones],
            'batteries': [d.battery for d in self.drones],
        }

    def render(self):
        """Render current state (text mode)"""
        if self.render_mode != 'human':
            return

        coverage = self._compute_coverage_percent()
        connected = self._check_mesh_connected()

        print(f"\n--- Step {self.step_count} ---")
        print(f"Coverage: {coverage:.1f}% | Connected: {connected}")
        for d in self.drones:
            print(f"  Drone {d.drone_id}: pos=({d.position[0]:.1f}, "
                  f"{d.position[1]:.1f}, {d.position[2]:.1f}) "
                  f"bat={d.battery:.1f}% neighbors={d.neighbors}")

    def close(self):
        """Clean up"""
        pass


def main():
    """Test the environment"""
    if not GYM_AVAILABLE:
        print("Gymnasium not installed. Run: pip install gymnasium")
        return

    env = SwarmGymEnv(render_mode='human')
    obs, info = env.reset(seed=42)

    print(f"Observation shape: {obs.shape}")
    print(f"Action shape: {env.action_space.shape}")
    print(f"Initial info: {info}")

    total_reward = 0
    for i in range(100):
        action = env.action_space.sample()
        obs, reward, terminated, truncated, info = env.step(action)
        total_reward += reward

        if i % 20 == 0:
            env.render()

        if terminated or truncated:
            break

    print(f"\nTotal reward: {total_reward:.2f}")
    print(f"Final coverage: {info['coverage_percent']:.1f}%")

    env.close()


if __name__ == '__main__':
    main()
