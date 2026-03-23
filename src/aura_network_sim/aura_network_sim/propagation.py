"""
Radio Propagation Models for A.U.R.A.

Implements log-distance path loss model with shadowing for:
- Drone-to-Drone (D2D): 5 GHz, free-space-like propagation
- Drone-to-Ground (D2G): 2.4 GHz, air-to-ground model

Parameters are configurable via ROS 2 YAML (network_sim_params.yaml).
"""

import numpy as np
from dataclasses import dataclass, field
from typing import Dict, Tuple, Optional


@dataclass
class RadioConfig:
    """Radio configuration for a specific link type"""
    
    # Transmit power (dBm)
    tx_power_dbm: float = 20.0
    
    # Receiver sensitivity (dBm) - derived from noise_floor + min_snr
    rx_sensitivity_dbm: float = -85.0
    
    # Frequency (GHz)
    frequency_ghz: float = 5.8
    
    # Path loss exponent (2.0 = free space, 2.7 = mixed, 3.5 = urban)
    path_loss_exponent: float = 2.7
    
    # Reference distance for path loss model (meters)
    reference_distance_m: float = 1.0
    
    # Reference loss at reference distance (dB)
    # Computed from free space: 20*log10(4*pi*d*f/c)
    # At 5.8 GHz, 1m: ~46.4 dB
    reference_loss_db: float = 46.4
    
    # Shadow fading / signal noise standard deviation (dB)
    shadow_fading_std: float = 2.0
    
    # Antenna gain (dBi) - applied to both TX and RX
    antenna_gain_dbi: float = 3.0
    
    # Noise floor (dBm)
    noise_floor_dbm: float = -100.0
    
    # Minimum SNR for connectivity (dB)
    min_snr_db: float = 10.0
    
    # Maximum mesh distance (meters) - hard cutoff
    max_mesh_distance_m: float = 150.0
    
    # MCS table: SNR threshold (dB) -> Data rate (Mbps)
    # Simplified 802.11ax rates
    mcs_thresholds: Dict[float, float] = field(default_factory=lambda: {
        4.0: 8.6,    # MCS 0
        7.0: 17.2,   # MCS 1
        10.0: 25.8,  # MCS 2
        13.0: 34.4,  # MCS 3
        16.0: 51.6,  # MCS 4
        19.0: 68.8,  # MCS 5
        22.0: 77.4,  # MCS 6
        25.0: 86.0,  # MCS 7
        28.0: 103.2, # MCS 8
        31.0: 114.7, # MCS 9
    })
    
    @classmethod
    def from_ros_params(cls, 
                        tx_power_dbm: float = 20.0,
                        noise_floor_dbm: float = -100.0,
                        path_loss_exponent: float = 2.7,
                        reference_distance_m: float = 1.0,
                        max_mesh_distance_m: float = 150.0,
                        min_snr_db: float = 10.0,
                        signal_noise_std_db: float = 2.0,
                        frequency_ghz: float = 5.8) -> 'RadioConfig':
        """Create RadioConfig from ROS parameters"""
        # Compute reference loss using free space formula at reference distance
        # FSPL = 20*log10(d) + 20*log10(f_GHz) + 32.44
        reference_loss_db = (20 * np.log10(max(0.1, reference_distance_m)) + 
                            20 * np.log10(frequency_ghz) + 32.44)
        
        # Receiver sensitivity = noise_floor + min_snr
        rx_sensitivity_dbm = noise_floor_dbm + min_snr_db
        
        return cls(
            tx_power_dbm=tx_power_dbm,
            rx_sensitivity_dbm=rx_sensitivity_dbm,
            frequency_ghz=frequency_ghz,
            path_loss_exponent=path_loss_exponent,
            reference_distance_m=reference_distance_m,
            reference_loss_db=reference_loss_db,
            shadow_fading_std=signal_noise_std_db,
            noise_floor_dbm=noise_floor_dbm,
            min_snr_db=min_snr_db,
            max_mesh_distance_m=max_mesh_distance_m,
        )


# Pre-configured radio profiles (defaults, can be overridden by YAML)
D2D_CONFIG = RadioConfig(
    tx_power_dbm=20.0,
    rx_sensitivity_dbm=-90.0,  # noise_floor (-100) + min_snr (10)
    frequency_ghz=5.8,
    path_loss_exponent=2.7,
    reference_distance_m=1.0,
    reference_loss_db=47.7,  # Free space at 5.8 GHz, 1m
    shadow_fading_std=2.0,
    antenna_gain_dbi=3.0,
    noise_floor_dbm=-100.0,
    min_snr_db=10.0,
    max_mesh_distance_m=150.0,
)

D2G_CONFIG = RadioConfig(
    tx_power_dbm=20.0,
    rx_sensitivity_dbm=-85.0,  # Phone sensitivity (stricter)
    frequency_ghz=2.4,
    path_loss_exponent=2.8,  # Air-to-ground with some obstruction
    reference_distance_m=1.0,
    reference_loss_db=40.0,
    shadow_fading_std=3.0,
    antenna_gain_dbi=2.0,
    noise_floor_dbm=-100.0,
    min_snr_db=10.0,
    max_mesh_distance_m=200.0,
)


class PropagationModel:
    """
    Log-distance propagation model with shadow fading.
    
    Path Loss: PL(d) = PL0 + 10 * n * log10(d) + X_sigma
    
    Where:
    - PL0 = reference loss at 1 meter
    - n = path loss exponent
    - X_sigma = shadow fading (log-normal, zero-mean Gaussian in dB)
    """
    
    def __init__(self, config: RadioConfig, seed: Optional[int] = None):
        self.config = config
        self.rng = np.random.default_rng(seed)
        
        # Cache shadow fading values for link consistency
        self._shadow_cache: Dict[Tuple[int, int], float] = {}
    
    def compute_free_space_loss(self, distance_m: float) -> float:
        """
        Compute free space path loss (Friis formula).
        
        FSPL = 20*log10(d) + 20*log10(f) + 32.44
        Where d is in meters, f is in GHz
        """
        if distance_m < 0.1:
            distance_m = 0.1
        
        fspl = (20 * np.log10(distance_m) + 
                20 * np.log10(self.config.frequency_ghz) + 
                32.44)
        return fspl
    
    def compute_path_loss(self, distance_m: float, 
                          link_id: Optional[Tuple[int, int]] = None,
                          include_shadow: bool = True) -> float:
        """
        Compute path loss using log-distance model.
        
        Args:
            distance_m: Distance between transmitter and receiver
            link_id: Optional tuple (tx_id, rx_id) for consistent shadowing
            include_shadow: Whether to include shadow fading
            
        Returns:
            Path loss in dB
        """
        if distance_m < 1.0:
            distance_m = 1.0
        
        # Log-distance path loss
        pl = (self.config.reference_loss_db + 
              10 * self.config.path_loss_exponent * np.log10(distance_m))
        
        # Add shadow fading
        if include_shadow:
            if link_id is not None:
                # Use cached value for consistent shadowing per link
                if link_id not in self._shadow_cache:
                    self._shadow_cache[link_id] = self.rng.normal(
                        0, self.config.shadow_fading_std
                    )
                pl += self._shadow_cache[link_id]
            else:
                # Random shadowing
                pl += self.rng.normal(0, self.config.shadow_fading_std)
        
        return pl
    
    def compute_rssi(self, distance_m: float,
                     link_id: Optional[Tuple[int, int]] = None,
                     tx_power_dbm: Optional[float] = None) -> float:
        """
        Compute received signal strength indicator (RSSI).
        
        RSSI = Tx_power + Antenna_gain - Path_loss
        """
        if tx_power_dbm is None:
            tx_power_dbm = self.config.tx_power_dbm
        
        path_loss = self.compute_path_loss(distance_m, link_id)
        antenna_gain = 2 * self.config.antenna_gain_dbi  # TX + RX
        
        rssi = tx_power_dbm + antenna_gain - path_loss
        return rssi
    
    def compute_snr(self, rssi_dbm: float) -> float:
        """Compute signal-to-noise ratio in dB"""
        return rssi_dbm - self.config.noise_floor_dbm
    
    def is_connected(self, rssi_dbm: float, distance_m: float = 0.0) -> bool:
        """Check if link is connected (RSSI above sensitivity and within max distance)"""
        if distance_m > 0 and distance_m > self.config.max_mesh_distance_m:
            return False
        return rssi_dbm > self.config.rx_sensitivity_dbm
    
    def get_data_rate(self, snr_db: float) -> float:
        """
        Get achievable data rate from SNR.
        Returns highest rate where SNR exceeds threshold.
        """
        rate = 0.0
        for snr_thresh, data_rate in sorted(self.config.mcs_thresholds.items()):
            if snr_db >= snr_thresh:
                rate = data_rate
            else:
                break
        return rate
    
    def compute_link_metrics(self, distance_m: float,
                             link_id: Optional[Tuple[int, int]] = None
                             ) -> Dict[str, float]:
        """
        Compute all link metrics at once.
        
        Returns dict with: rssi_dbm, snr_db, rate_mbps, connected
        """
        rssi = self.compute_rssi(distance_m, link_id)
        snr = self.compute_snr(rssi)
        rate = self.get_data_rate(snr)
        connected = self.is_connected(rssi, distance_m)
        
        return {
            'rssi_dbm': rssi,
            'snr_db': snr,
            'rate_mbps': rate,
            'connected': connected,
            'distance_m': distance_m,
        }
    
    def compute_max_range(self) -> float:
        """
        Compute maximum communication range (where RSSI = sensitivity).
        """
        # At max range: tx_power + antenna_gain - path_loss = rx_sensitivity
        # path_loss = tx_power + antenna_gain - rx_sensitivity
        max_path_loss = (self.config.tx_power_dbm + 
                         2 * self.config.antenna_gain_dbi - 
                         self.config.rx_sensitivity_dbm)
        
        # Solve: path_loss = PL0 + 10*n*log10(d)
        # d = 10^((path_loss - PL0) / (10*n))
        exponent = (max_path_loss - self.config.reference_loss_db) / (
            10 * self.config.path_loss_exponent
        )
        max_range = 10 ** exponent
        
        return max_range
    
    def clear_shadow_cache(self):
        """Clear cached shadow fading values"""
        self._shadow_cache.clear()
