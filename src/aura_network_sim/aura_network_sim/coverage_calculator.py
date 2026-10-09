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
        
        # Compute coverage for each grid cell
        for iy, y in enumerate(self.grid_y):
            for ix, x in enumerate(self.grid_x):
                ground_pos = np.array([x, y, self.ground_height])
                
                best_rssi = -200.0
                best_rate = 0.0
                best_drone_id = -1
                
                # Find best serving drone
                for drone_id, drone in drones.items():
                    distance = np.linalg.norm(ground_pos - drone.position)
                    
                    # Compute RSSI using D2G propagation. tx_id + rx_xy
                    # select this drone's shadowing field at this cell, so
                    # shadowing varies across the ground instead of offsetting
                    # the whole footprint by one cached value.
                    rssi = self.propagation.compute_rssi(
                        distance,
                        tx_power_dbm=drone.tx_power_dbm,
                        tx_id=drone_id,
                        rx_xy=(x, y),
                    )
                    
                    # Apply dead zone signal attenuation
                    if dead_zones:
                        for zone in dead_zones:
                            dz_dx = x - zone['cx']
                            dz_dy = y - zone['cy']
                            dist_to_zone = np.sqrt(dz_dx*dz_dx + dz_dy*dz_dy)
                            if dist_to_zone < zone['radius']:
                                rssi -= zone['attenuation_db']
                    
                    if rssi > best_rssi:
                        best_rssi = rssi
                        best_drone_id = drone_id
                        
                        if rssi > self.config.rx_sensitivity_dbm:
                            snr = self.propagation.compute_snr(rssi)
                            best_rate = self.propagation.get_data_rate(snr)
                        else:
                            best_rate = 0.0
                
                signal_map[iy, ix] = best_rssi
                throughput_map[iy, ix] = best_rate
                serving_map[iy, ix] = best_drone_id
        
        return self._build_result(signal_map, throughput_map, serving_map)
    
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
