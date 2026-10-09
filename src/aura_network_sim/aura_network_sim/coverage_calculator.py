"""
Ground Coverage Calculator for A.U.R.A.

Calculates WiFi coverage from drone swarm to ground users:
- Signal strength map
- Data rate map
- Coverage percentage
"""

import numpy as np
from dataclasses import dataclass
from typing import Dict, List, Tuple, Optional

from .propagation import PropagationModel, D2G_CONFIG, RadioConfig
from .mesh_simulator import DroneNetworkState


@dataclass
class CoverageResult:
    """Results from coverage calculation"""
    
    # Grid dimensions
    grid_size_x: int
    grid_size_y: int
    cell_size_m: float
    origin_x: float
    origin_y: float
    
    # Coverage maps (2D arrays)
    signal_strength: np.ndarray  # dBm
    throughput: np.ndarray       # Mbps
    coverage_mask: np.ndarray    # Boolean
    serving_drone: np.ndarray    # Drone ID providing best signal
    
    # Statistics
    coverage_percent: float
    avg_signal_dbm: float
    avg_throughput_mbps: float
    min_signal_dbm: float
    max_signal_dbm: float


@dataclass
class CoverageReliability:
    """Coverage measured over many shadowing realizations.

    A single run against a random channel is one draw, and its coverage
    percentage is a sample, not a property of the swarm. This aggregates
    `realizations` draws into the two numbers that mean different things:

    - `mean_coverage_percent`: the expected fraction of locations covered.
      Shadowing tends to *raise* this relative to the deterministic median
      channel, because a ground user attaches to the best drone and the
      maximum over partly-independent fades is biased upward. That is a real
      macro-diversity gain, and quoting it alone makes a disaster relay look
      better than it is.
    - `reliable_coverage_percent`: the fraction of locations covered in at
      least `reliability` of realizations. This is what a responder standing
      on a given street cares about, and shadowing lowers it sharply.

    `marginal_percent` is the area that is sometimes covered and sometimes
    not. The deterministic model reports a crisp coverage boundary; this is
    how much of the map that boundary was hiding.
    """

    realizations: int
    reliability: float
    #: Per-cell probability of being covered, shape (grid_size_y, grid_size_x).
    coverage_probability: np.ndarray
    mean_coverage_percent: float
    reliable_coverage_percent: float
    marginal_percent: float
    #: Coverage percentage of each individual realization.
    per_realization_percent: np.ndarray

    @property
    def spread_percent(self) -> float:
        """Standard deviation across realizations, in percentage points."""
        return float(np.std(self.per_realization_percent))


class CoverageCalculator:
    """
    Calculates ground coverage from drone positions.
    
    Uses 2.4 GHz AP configuration for ground coverage
    (better penetration and phone compatibility).
    """
    
    def __init__(self, 
                 config: Optional[RadioConfig] = None,
                 area_bounds: Tuple[float, float, float, float] = (-100, -100, 100, 100),
                 resolution_m: float = 10.0,
                 ground_height: float = 0.0,
                 seed: Optional[int] = None):
        """
        Args:
            config: Radio configuration (defaults to D2G_CONFIG)
            area_bounds: (x_min, y_min, x_max, y_max) in meters
            resolution_m: Grid cell size in meters
            ground_height: Height of ground users (meters)
            seed: Seeds the shadowing realization; None draws a fresh one
        """
        self.config = config or D2G_CONFIG
        # The grid bounds are also the shadowing bounds. Without them the
        # model falls back to one cached draw per (drone, ground) pair, which
        # is identical for every cell — a per-drone RSSI offset, not
        # shadowing. See PropagationModel's docstring.
        self.propagation = PropagationModel(self.config, seed=seed,
                                            shadow_bounds=area_bounds)
        
        self.bounds = area_bounds
        self.resolution = resolution_m
        self.ground_height = ground_height
        
        # Create grid
        x_min, y_min, x_max, y_max = area_bounds
        self.grid_x = np.arange(x_min, x_max, resolution_m)
        self.grid_y = np.arange(y_min, y_max, resolution_m)
        self.grid_size_x = len(self.grid_x)
        self.grid_size_y = len(self.grid_y)
    
    def compute_coverage(self, 
                         drones: Dict[int, DroneNetworkState],
                         dead_zones: list = None
                         ) -> CoverageResult:
        """
        Compute coverage map from current drone positions.
        
        Args:
            drones: Dictionary of drone states
            
        Returns:
            CoverageResult with all coverage data
        """
        # Initialize arrays
        signal_map = np.full((self.grid_size_y, self.grid_size_x), -200.0)
        throughput_map = np.zeros((self.grid_size_y, self.grid_size_x))
        serving_map = np.full((self.grid_size_y, self.grid_size_x), -1, dtype=int)

        if not drones:
            return self._build_result(signal_map, throughput_map, serving_map)
        
        # One vectorized pass over the whole grid.
        #
        # This was three nested Python loops (cells x cells x drones), which
        # cost ~194 ms per update on a 40x40 grid — the node is configured for
        # 10 Hz, so it had been silently running at about half that, and any
        # larger grid made it worse. The arithmetic is unchanged;
        # test_coverage_vectorization.py asserts this agrees with the scalar
        # formulation cell for cell.
        cfg = self.config
        grid_x, grid_y = np.meshgrid(self.grid_x, self.grid_y)   # (ny, nx)

        # Dead zone attenuation depends on the cell, not the drone, so it is
        # computed once and applied to every drone's RSSI.
        attenuation = None
        if dead_zones:
            attenuation = np.zeros_like(grid_x)
            for zone in dead_zones:
                dz_dx = grid_x - zone['cx']
                dz_dy = grid_y - zone['cy']
                inside = (dz_dx * dz_dx + dz_dy * dz_dy
                          < zone['radius'] * zone['radius'])
                attenuation[inside] += zone['attenuation_db']

        # Drone ids in iteration order, so argmax's first-wins tie-breaking
        # matches the strict `>` the scalar version used.
        drone_ids = list(drones.keys())
        rssi_stack = np.empty((len(drone_ids),) + grid_x.shape, dtype=float)
        antenna_gain = 2 * cfg.antenna_gain_dbi

        for index, drone_id in enumerate(drone_ids):
            drone = drones[drone_id]
            dx = grid_x - drone.position[0]
            dy = grid_y - drone.position[1]
            dz = self.ground_height - drone.position[2]
            distance = np.sqrt(dx * dx + dy * dy + dz * dz)
            # compute_path_loss clamps to 1 m; keep that, or a cell directly
            # under a drone would give a negative log.
            np.maximum(distance, 1.0, out=distance)

            path_loss = (cfg.reference_loss_db
                         + 10 * cfg.path_loss_exponent * np.log10(distance))
            path_loss += self.propagation.shadow_map(drone_id, grid_x, grid_y)

            rssi = drone.tx_power_dbm + antenna_gain - path_loss
            if attenuation is not None:
                rssi -= attenuation
            rssi_stack[index] = rssi

        best = np.argmax(rssi_stack, axis=0)
        best_rssi = np.take_along_axis(rssi_stack, best[None], axis=0)[0]

        # A cell with no drone above the -200 dBm floor stays uncovered and
        # unserved, exactly as the scalar version's strict `>` left it.
        served = best_rssi > -200.0
        signal_map = np.where(served, best_rssi, -200.0)
        serving_map = np.where(served, np.asarray(drone_ids)[best], -1
                               ).astype(int)
        throughput_map = self._data_rate_map(signal_map)

        return self._build_result(signal_map, throughput_map, serving_map)

    def _data_rate_map(self, signal_map: np.ndarray) -> np.ndarray:
        """MCS lookup over a whole grid.

        The table is sorted and its rates increase with their SNR threshold,
        so the highest rate whose threshold the SNR clears is a binary search
        rather than the linear scan `get_data_rate` does per cell.
        """
        cfg = self.config
        thresholds = np.array(sorted(cfg.mcs_thresholds))
        rates = np.array([cfg.mcs_thresholds[t] for t in thresholds])

        snr = signal_map - cfg.noise_floor_dbm
        rung = np.searchsorted(thresholds, snr, side='right') - 1
        rate = np.where(rung >= 0, rates[np.clip(rung, 0, None)], 0.0)

        # Rate is only meaningful where the cell is actually covered.
        return np.where(signal_map > cfg.rx_sensitivity_dbm, rate, 0.0)
    
    def compute_coverage_reliability(self,
                                     drones: Dict[int, DroneNetworkState],
                                     dead_zones: list = None,
                                     realizations: int = 100,
                                     reliability: float = 0.9,
                                     seed: int = 0) -> CoverageReliability:
        """Coverage over repeated shadowing draws, for the same drone positions.

        Reports expected coverage and coverage at a reliability target; see
        CoverageReliability for why both are needed. With shadowing disabled
        every realization is identical and the two numbers coincide, which is
        the honest answer for a deterministic channel rather than an error.
        """
        if realizations < 1:
            raise ValueError(f'realizations must be >= 1, got {realizations}')
        if not 0.0 < reliability <= 1.0:
            raise ValueError(f'reliability must be in (0, 1], got {reliability}')

        masks = np.empty((realizations, self.grid_size_y, self.grid_size_x),
                         dtype=bool)
        per_realization = np.empty(realizations, dtype=float)

        for i in range(realizations):
            # Reseed rather than reuse: a fresh realization per draw is the
            # point, and seeding from (seed, i) keeps the set reproducible.
            self.propagation.regenerate_shadowing(seed=seed + i)
            result = self.compute_coverage(drones, dead_zones)
            masks[i] = result.coverage_mask
            per_realization[i] = result.coverage_percent

        probability = masks.mean(axis=0)
        cells = probability.size

        return CoverageReliability(
            realizations=realizations,
            reliability=reliability,
            coverage_probability=probability,
            mean_coverage_percent=float(100.0 * probability.mean()),
            reliable_coverage_percent=float(
                100.0 * np.count_nonzero(probability >= reliability) / cells),
            marginal_percent=float(
                100.0 * np.count_nonzero((probability > 0.0)
                                         & (probability < 1.0)) / cells),
            per_realization_percent=per_realization,
        )

    def _build_result(self, signal_map: np.ndarray, 
                      throughput_map: np.ndarray,
                      serving_map: np.ndarray) -> CoverageResult:
        """Build CoverageResult from computed maps"""
        
        # Coverage mask: where signal exceeds sensitivity
        coverage_mask = signal_map > self.config.rx_sensitivity_dbm
        
        # Statistics
        coverage_percent = 100.0 * np.mean(coverage_mask)
        
        if np.any(coverage_mask):
            covered_signals = signal_map[coverage_mask]
            covered_throughputs = throughput_map[coverage_mask]
            
            avg_signal = float(np.mean(covered_signals))
            avg_throughput = float(np.mean(covered_throughputs))
            min_signal = float(np.min(covered_signals))
            max_signal = float(np.max(covered_signals))
        else:
            avg_signal = -200.0
            avg_throughput = 0.0
            min_signal = -200.0
            max_signal = -200.0
        
        return CoverageResult(
            grid_size_x=self.grid_size_x,
            grid_size_y=self.grid_size_y,
            cell_size_m=self.resolution,
            origin_x=float(self.bounds[0]),
            origin_y=float(self.bounds[1]),
            signal_strength=signal_map,
            throughput=throughput_map,
            coverage_mask=coverage_mask,
            serving_drone=serving_map,
            coverage_percent=coverage_percent,
            avg_signal_dbm=avg_signal,
            avg_throughput_mbps=avg_throughput,
            min_signal_dbm=min_signal,
            max_signal_dbm=max_signal,
        )
    
    def get_coverage_at_point(self, x: float, y: float,
                              drones: Dict[int, DroneNetworkState]
                              ) -> Dict:
        """Get coverage info at a specific point"""
        ground_pos = np.array([x, y, self.ground_height])
        
        best_rssi = -200.0
        best_rate = 0.0
        best_drone_id = -1
        best_distance = 0.0
        
        for drone_id, drone in drones.items():
            distance = np.linalg.norm(ground_pos - drone.position)
            rssi = self.propagation.compute_rssi(
                distance, tx_id=drone_id, rx_xy=(x, y))
            
            if rssi > best_rssi:
                best_rssi = rssi
                best_drone_id = drone_id
                best_distance = distance
                
                if rssi > self.config.rx_sensitivity_dbm:
                    snr = self.propagation.compute_snr(rssi)
                    best_rate = self.propagation.get_data_rate(snr)
                else:
                    best_rate = 0.0
        
        return {
            'x': x,
            'y': y,
            'rssi_dbm': best_rssi,
            'throughput_mbps': best_rate,
            'connected': best_rssi > self.config.rx_sensitivity_dbm,
            'serving_drone': best_drone_id,
            'distance_m': best_distance,
        }
