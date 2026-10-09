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

try:
    from aura_network_sim.propagation import CorrelatedShadowing
    SHADOWING_AVAILABLE = True
except ImportError:  # pragma: no cover - depends on the workspace overlay
    CorrelatedShadowing = None
    SHADOWING_AVAILABLE = False

from .spaces import ObservationConfig, ActionConfig, ObservationBuilder, ActionProcessor
from .rewards import RewardConfig, RewardCalculator


@dataclass
class EnvConfig:
    """Environment configuration"""

    # Simulation
    num_drones: int = 5
    max_steps: int = 500
    dt: float = 0.5  # Time step (seconds)

    # Area
    area_size: float = 200.0
    grid_resolution: float = 10.0

    # World center — disaster zone centroid in Gazebo world frame
    world_center_x: float = 120.0
    world_center_y: float = -170.0

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

    # Objective weights, forwarded to RewardConfig.
    #
    # alpha_m is the connectivity weight. At the defaults (coverage 2.0,
    # connectivity 3.0) connectivity dominates, and the trained policy holds a
    # tight cluster: a full 10-link mesh and ~40% coverage, where the
    # Hungarian baseline spreads out for ~70% coverage and 8.9 links. That is
    # not a training failure, it is the operating point the weights pick — so
    # they are exposed here, for the coverage<->connectivity Pareto sweep
    # (roadmap §10). None keeps RewardConfig's own default.
    coverage_weight: Optional[float] = None
    connectivity_weight: Optional[float] = None

    # Log-normal shadowing (roadmap §8).
    #
    # Off by default, and that default is load-bearing: the published
    # checkpoint was trained on the deterministic median channel, so enabling
    # this changes both the reported coverage and the policy that training
    # produces. Turn it on deliberately and say so alongside the numbers.
    #
    # A fresh realization is drawn every episode, which makes the channel a
    # domain-randomization axis rather than one map the policy can memorize.
    shadowing_enabled: bool = False
    shadow_sigma_db: float = 4.0
    shadow_correlation_distance_m: float = 25.0
    # Correlation between two drones' shadowing to the same ground point.
    # This decides the sign of the effect: coverage takes the best server, so
    # independent paths (0.0) hand the swarm a diversity gain and *raise*
    # coverage, while fully shared shadowing (1.0) lowers it. 0.5 is the
    # 3GPP inter-site value.
    shadow_inter_link_correlation: float = 0.5

    # Randomization
    randomize_initial_positions: bool = True
    randomize_weather: bool = True
    weather_probability: float = 0.6


class DroneState:
    """State of a single drone in simulation"""

    def __init__(self, drone_id: int, position: np.ndarray):
        self.drone_id = drone_id
        self.position = position.copy()
        self.velocity = np.zeros(3)
        self.battery = 100.0
        self.is_hub = (drone_id == 0)

        # A failed drone stays in the list so drone_id keeps matching its index
        # (BFS and the observation layout both rely on that) but stops flying,
        # stops relaying and stops contributing coverage.
        self.is_failed = False

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

    def __init__(self, config: EnvConfig = None, render_mode: str = None,
                 seed: int = None):
        super().__init__()

        self.config = config or EnvConfig()
        self.render_mode = render_mode

        # Per-instance RNG. Parallel envs must not share the global numpy
        # stream, or seeding one reseeds them all and runs stop being
        # reproducible.
        self.np_random = np.random.default_rng(seed)
        self._seed = seed

        if self.config.shadowing_enabled and not SHADOWING_AVAILABLE:
            raise ImportError(
                'shadowing_enabled=True needs aura_network_sim.propagation, '
                'which is not importable. Source the workspace overlay '
                '(install/setup.bash) or set shadowing_enabled=False. '
                'Silently training on a different channel than the one asked '
                'for is worse than failing here.')

        # Per-drone shadowing, precomputed over the coverage grid once per
        # episode. The ground grid is fixed and so is the field, so the
        # offset at each cell does not change within an episode — sampling it
        # per cell per step would cost ~8k interpolations per step for
        # nothing.
        self._shadowing: Any = None
        self._shadow_grids: List[np.ndarray] = []

        # Create configs
        self.obs_config = ObservationConfig(num_drones=self.config.num_drones)
        self.action_config = ActionConfig(
            num_drones=self.config.num_drones,
            world_center_x=self.config.world_center_x,
            world_center_y=self.config.world_center_y,
        )
        reward_overrides = {}
        if self.config.coverage_weight is not None:
            reward_overrides['coverage_weight'] = self.config.coverage_weight
        if self.config.connectivity_weight is not None:
            reward_overrides['connectivity_weight'] = \
                self.config.connectivity_weight
        self.reward_config = RewardConfig(
            world_center_x=self.config.world_center_x,
            world_center_y=self.config.world_center_y,
            **reward_overrides,
        )

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
        self.failed_drone_ids: set = set()

        # Coverage grid
        self._init_coverage_grid()

    # Disaster structure positions from earthquake_city.world (x, y in Gazebo ENU)
    _DISASTER_STRUCTURES = [
        (121, -106), (68, -88),  (45, -118), (87,  -142),   # western cluster
        (155, -228), (155, -194), (78, -216), (115, -237),  # central-south
        (291, -243), (290, -219), (290, -193), (315, -243), # eastern cluster
        (313, -218), (263, -237),
        (196, -150), (195, -240), (179, -287),              # school / police / playground
    ]

    def _init_coverage_grid(self):
        """Initialize coverage grid and importance map for disaster structures"""
        size = int(2 * self.config.area_size / self.config.grid_resolution)
        self.grid_size = size
        self.coverage_grid = np.zeros((size, size), dtype=np.float32)
        self.signal_grid = np.full((size, size), -200.0, dtype=np.float32)

        # Cell centres, as (gy, gx) grids. Built once: _update_network and
        # _reset_shadowing both index by (gy, gx) and must agree about which
        # ground point each cell is, so they share these rather than each
        # recomputing the arithmetic.
        half = self.config.area_size
        res = self.config.grid_resolution
        index = np.arange(size)
        centres_x = self.config.world_center_x - half + (index + 0.5) * res
        centres_y = self.config.world_center_y - half + (index + 0.5) * res
        self._cell_x, self._cell_y = np.meshgrid(centres_x, centres_y)

        # Build importance grid: 3× weight for cells within 50 m of a disaster
        # structure. One pass per structure over the whole grid rather than a
        # per-cell scan over every structure.
        IMPORTANCE_RADIUS = 50.0
        self.importance_grid = np.ones((size, size), dtype=np.float32)
        for sx, sy in self._DISASTER_STRUCTURES:
            dx = self._cell_x - sx
            dy = self._cell_y - sy
            near = (dx * dx + dy * dy) < IMPORTANCE_RADIUS * IMPORTANCE_RADIUS
            self.importance_grid[near] = 3.0

    def reset(self, seed: int = None, options: Dict = None) -> Tuple[np.ndarray, Dict]:
        """Reset environment to initial state"""
        if seed is not None:
            self.np_random = np.random.default_rng(seed)
            self._seed = seed

        self.step_count = 0
        self.coverage_history = []
        self.failed_drone_ids = set()
        self.reward_calculator.reset()

        # Initialize drones, in a ring around the disaster zone rather than
        # around the origin.
        #
        # The ring used to be centred on (0, 0), roughly 200 m from the area
        # the policy is rewarded for covering. That is an initial condition
        # that never occurs at inference: RL activates only in OPERATIONS,
        # after TRANSIT and FORMATION have already brought the swarm to the
        # zone. So training spent its early steps on a transit the deployed
        # policy is never asked to fly, and the deployed policy started from
        # a state training had under-sampled.
        self.drones = []
        wx = self.config.world_center_x
        wy = self.config.world_center_y
        for i in range(self.config.num_drones):
            angle = 2 * np.pi * i / self.config.num_drones
            if self.config.randomize_initial_positions:
                r = self.config.initial_radius * (0.8 + 0.4 * self.np_random.random())
                altitude = (self.config.initial_altitude
                            + self.np_random.uniform(-5, 5))
            else:
                r = self.config.initial_radius
                altitude = self.config.initial_altitude
            pos = np.array([
                wx + r * np.cos(angle),
                wy + r * np.sin(angle),
                altitude,
            ])
            self.drones.append(DroneState(drone_id=i, position=pos))

        # Shadowing realization for this episode. Only draw from np_random
        # when shadowing is on: consuming the stream unconditionally would
        # shift the initial positions and weather, and the frozen baseline
        # would stop reproducing.
        self._reset_shadowing()

        # Weather zones, placed inside the coverage grid.
        #
        # These were drawn from uniform(-100, 100) on the origin while the
        # grid sits on (120, -170), so a zone was usually outside the measured
        # area entirely and its attenuation reached nothing. Weather that
        # never attenuates anything is not a randomization axis.
        self.weather_zones = []
        if (self.config.randomize_weather
                and self.np_random.random() < self.config.weather_probability):
            half = self.config.area_size
            zone_x = wx + self.np_random.uniform(-0.5 * half, 0.5 * half)
            zone_y = wy + self.np_random.uniform(-0.5 * half, 0.5 * half)
            zone_r = self.np_random.uniform(30, 80)
            zone_attenuation = self.np_random.uniform(5, 15)
            self.weather_zones.append(
                WeatherZone(zone_x, zone_y, zone_r, zone_attenuation))

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
            if drone.is_failed:
                drone.velocity = np.zeros(3)
                continue

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

    # ── Shadowing ───────────────────────────────────────────────

    def _reset_shadowing(self) -> None:
        """Draw this episode's shadowing and bake it onto the coverage grid."""
        if not self.config.shadowing_enabled or self.config.shadow_sigma_db <= 0.0:
            self._shadowing = None
            self._shadow_grids = []
            return

        half = self.config.area_size
        wx = self.config.world_center_x
        wy = self.config.world_center_y
        bounds = (wx - half, wy - half, wx + half, wy + half)

        # The same cell centres _update_network uses, so a baked offset lands
        # on the cell it was computed for.
        grid_x, grid_y = self._cell_x, self._cell_y

        # One realization per drone, from a sub-seed of this episode's stream
        # so the whole run stays reproducible from the env seed.
        episode_seed = int(self.np_random.integers(0, 2 ** 31 - 1))

        self._shadowing = CorrelatedShadowing(
            sigma_db=self.config.shadow_sigma_db,
            correlation_distance_m=self.config.shadow_correlation_distance_m,
            bounds=bounds,
            inter_link_correlation=self.config.shadow_inter_link_correlation,
            seed=episode_seed,
        )
        self._shadow_grids = [
            np.asarray(self._shadowing.sample(drone_id, grid_x, grid_y),
                       dtype=np.float32)
            for drone_id in range(self.config.num_drones)
        ]

    def _link_shadow_db(self, tx_id: int, position: np.ndarray) -> float:
        """Shadowing on a drone-to-drone link, sampled at the far end."""
        if self._shadowing is None:
            return 0.0
        return self._shadowing.sample(
            tx_id, float(position[0]), float(position[1]))

    # ── Network simulation ──────────────────────────────────────

    def _update_network(self):
        """Update network metrics using log-distance path loss model"""
        self.signal_grid.fill(-200.0)
        self.coverage_grid.fill(0.0)

        # Weather attenuation depends on the cell, not the drone, so it is
        # computed once for the whole grid rather than per drone per cell.
        weather = None
        for wz in self.weather_zones:
            if not wz.is_active:
                continue
            if weather is None:
                weather = np.zeros_like(self._cell_x)
            wdx = self._cell_x - wz.center[0]
            wdy = self._cell_y - wz.center[1]
            inside = (wdx * wdx + wdy * wdy) < wz.radius * wz.radius
            weather[inside] += wz.attenuation_db

        # One vectorized pass per drone over the whole grid. This was a
        # cell x cell x drone Python loop and it was the training bottleneck:
        # ~54 env steps/s, so a 400k-step run took two hours and an alpha_m
        # sweep was out of reach. The arithmetic is unchanged;
        # test_env_vectorization.py asserts agreement with the scalar form.
        cfg = self.config
        for drone in self.drones:
            if drone.is_failed:
                drone.neighbors = []
                continue

            dx = self._cell_x - drone.position[0]
            dy = self._cell_y - drone.position[1]
            dz = -drone.position[2]  # ground level
            dist_3d = np.sqrt(dx * dx + dy * dy + dz * dz)
            np.maximum(dist_3d, cfg.reference_distance_m, out=dist_3d)

            path_loss = (cfg.reference_loss_db
                         + 10 * cfg.path_loss_exponent
                         * np.log10(dist_3d / cfg.reference_distance_m))
            if weather is not None:
                path_loss = path_loss + weather
            if self._shadow_grids:
                path_loss = path_loss + self._shadow_grids[drone.drone_id]

            np.maximum(self.signal_grid, cfg.tx_power_dbm - path_loss,
                       out=self.signal_grid)

            # Update drone-to-drone links
            drone.neighbors = []
            for other in self.drones:
                if other.drone_id == drone.drone_id or other.is_failed:
                    continue
                d = np.linalg.norm(drone.position - other.position)
                if d < cfg.max_mesh_distance:
                    drone.neighbors.append(other.drone_id)

        # Coverage mask
        self.coverage_grid = (
            self.signal_grid > self.config.coverage_threshold_dbm
        ).astype(np.float32)

        # Update per-drone network metrics
        for drone in self.drones:
            if drone.is_failed:
                drone.signal_strength_dbm = -100.0
                drone.throughput_mbps = 0.0
                drone.latency_ms = 999.0
                continue

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
                    pl += self._link_shadow_db(
                        drone.drone_id, self.drones[nid].position)
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
        """Compute importance-weighted coverage percentage (disaster structures count 3×)"""
        total_weight = np.sum(self.importance_grid)
        if total_weight == 0:
            return 0.0
        return 100.0 * np.sum(self.coverage_grid * self.importance_grid) / total_weight

    def _check_mesh_connected(self) -> bool:
        """Check whether every surviving drone forms one connected mesh (BFS).

        Failed drones are excluded rather than counted as unreachable: after a
        loss the question is whether the remaining swarm still holds a mesh
        together, which is the N-1 tolerance the system claims. With no
        failures this is identical to requiring all drones connected.
        """
        active = [d for d in self.drones if not d.is_failed]
        if len(active) <= 1:
            return True

        start = active[0].drone_id
        visited = {start}
        queue = [start]

        while queue:
            current = queue.pop(0)
            for neighbor_id in self.drones[current].neighbors:
                if neighbor_id not in visited and not self.drones[neighbor_id].is_failed:
                    visited.add(neighbor_id)
                    queue.append(neighbor_id)

        return len(visited) == len(active)

    def _active_drones(self) -> List[DroneState]:
        """Surviving drones. Identical to self.drones when nothing has failed."""
        return [d for d in self.drones if not d.is_failed] or list(self.drones)

    def _compute_avg_signal(self) -> float:
        return float(np.mean([d.signal_strength_dbm for d in self._active_drones()]))

    def _compute_avg_throughput(self) -> float:
        return float(np.mean([d.throughput_mbps for d in self._active_drones()]))

    def _compute_avg_latency(self) -> float:
        return float(np.mean([d.latency_ms for d in self._active_drones()]))

    def _compute_avg_snr_db(self) -> float:
        """Mean SNR over surviving drones.

        This is SNR, not SINR: the propagation model has no interference term
        (roadmap 8), so there is no I to include. Reporting it as SINR would
        overstate what the model computes.
        """
        return float(np.mean([
            d.signal_strength_dbm - self.config.noise_floor_dbm
            for d in self._active_drones()
        ]))

    # ── Fault injection ─────────────────────────────────────────

    def fail_drone(self, drone_id: int) -> None:
        """Take a drone out of service: it stops flying, relaying and covering.

        It stays in self.drones so drone_id keeps matching its list index and
        the observation keeps its fixed width — the policy sees a degraded
        neighbour rather than a resized swarm.
        """
        if not 0 <= drone_id < len(self.drones):
            raise IndexError(
                f"drone_id {drone_id} out of range for {len(self.drones)} drones")
        self.drones[drone_id].is_failed = True
        self.drones[drone_id].velocity = np.zeros(3)
        self.failed_drone_ids.add(drone_id)
        self._update_network()

    def recover_drone(self, drone_id: int) -> None:
        """Return a previously failed drone to service."""
        if not 0 <= drone_id < len(self.drones):
            raise IndexError(
                f"drone_id {drone_id} out of range for {len(self.drones)} drones")
        self.drones[drone_id].is_failed = False
        self.failed_drone_ids.discard(drone_id)
        self._update_network()

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
            'avg_snr_db': self._compute_avg_snr_db(),
            'step': self.step_count,
            'drone_positions': [d.position.tolist() for d in self.drones],
            'batteries': [d.battery for d in self.drones],
            'failed_drone_ids': sorted(self.failed_drone_ids),
            'num_active_drones': sum(1 for d in self.drones if not d.is_failed),
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
