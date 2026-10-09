"""
Radio Propagation Models for A.U.R.A.

Implements log-distance path loss model with shadowing for:
- Drone-to-Drone (D2D): 5 GHz, free-space-like propagation
- Drone-to-Ground (D2G): 2.4 GHz, air-to-ground model

Parameters are configurable via ROS 2 YAML (network_sim_params.yaml).
"""

import math
from statistics import NormalDist

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

    # Distance over which shadowing decorrelates to 1/e (meters).
    # See ShadowingConfig for why this matters: uncorrelated per-point draws
    # average out over a grid and leave mean coverage essentially unchanged.
    shadow_correlation_distance_m: float = 25.0

    # Correlation between two transmitters' shadowing to the same ground
    # point. 0.5 is the 3GPP inter-site value; see CorrelatedShadowing for
    # why this parameter decides the sign of shadowing's effect on coverage.
    shadow_inter_link_correlation: float = 0.5

    # Set False to get the deterministic median channel (useful for
    # reproducing the frozen baseline, and for unit tests that need exact
    # path-loss arithmetic).
    shadowing_enabled: bool = True
    
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
                        frequency_ghz: float = 5.8,
                        rx_sensitivity_dbm: Optional[float] = None,
                        shadow_correlation_distance_m: float = 25.0,
                        shadow_inter_link_correlation: float = 0.5,
                        shadowing_enabled: bool = True
                        ) -> 'RadioConfig':
        """Create RadioConfig from ROS parameters.

        rx_sensitivity_dbm overrides the derived value when given. Without it
        sensitivity is noise_floor + min_snr, which is the physically motivated
        default; with it, a deployment can state the coverage threshold it
        actually wants to report against. `coverage_threshold_dbm` in the YAML
        configs used to be silently ignored because there was no way to pass
        it through here.
        """
        # Compute reference loss using free space formula at reference distance
        # FSPL = 20*log10(d) + 20*log10(f_GHz) + 32.44
        reference_loss_db = (20 * np.log10(max(0.1, reference_distance_m)) + 
                            20 * np.log10(frequency_ghz) + 32.44)
        
        # Receiver sensitivity = noise_floor + min_snr unless overridden
        if rx_sensitivity_dbm is None:
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
            shadow_correlation_distance_m=shadow_correlation_distance_m,
            shadow_inter_link_correlation=shadow_inter_link_correlation,
            shadowing_enabled=shadowing_enabled,
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


@dataclass
class ShadowingConfig:
    """Log-normal shadowing settings.

    `sigma_db` is the standard deviation of the shadowing term in dB. Typical
    measured values: 2-4 dB for near-free-space air-to-air, 4-8 dB for
    air-to-ground over suburban terrain, 8-12 dB in dense urban canyons.

    `correlation_distance_m` is the distance over which shadowing decorrelates
    to 1/e. Shadowing is caused by terrain and buildings, so two points a few
    metres apart are obstructed by the same things and see nearly the same
    offset. Drawing an independent sample per point would model receiver noise,
    not shadowing: it averages out over a grid and leaves mean coverage almost
    unchanged. Reported values are typically 5-50 m outdoors; 25 m is a
    reasonable urban-rubble default.
    """

    enabled: bool = True
    sigma_db: float = 2.0
    correlation_distance_m: float = 25.0


class ShadowingField:
    """A spatially correlated, zero-mean log-normal shadowing map in dB.

    Synthesized by spectral filtering: white noise is shaped by the square
    root of the power spectrum of an exponential autocorrelation function,
    rho(d) = exp(-d / correlation_distance), which is the Gudmundson model
    commonly used for shadowing maps. Sampling between lattice points is
    bilinear, so the field is continuous and a drone crossing a cell boundary
    sees no step change in RSSI.

    The realization is normalized so the lattice has exactly `sigma_db`
    standard deviation. That makes the contract testable; it also means the
    field's variance is deterministic rather than chi-squared, which is what
    a simulator wants. Bilinear interpolation between lattice points is a
    weighted average of correlated samples, so interpolated values have
    slightly less spread than the lattice - a few percent at the default
    resolution of correlation_distance / 4.

    The field is generated once over `bounds` and reused. Points outside
    `bounds` are clamped to the edge rather than extrapolated, so a drone that
    leaves the modelled area keeps a plausible value instead of raising.
    """

    #: Lattice spacing as a fraction of the correlation distance.
    RESOLUTION_FRACTION = 0.25

    def __init__(self,
                 sigma_db: float,
                 correlation_distance_m: float,
                 bounds: Tuple[float, float, float, float],
                 resolution_m: Optional[float] = None,
                 seed: Optional[int] = None):
        if sigma_db < 0.0:
            raise ValueError(f'sigma_db must be >= 0, got {sigma_db}')
        if correlation_distance_m <= 0.0:
            raise ValueError('correlation_distance_m must be > 0, got '
                             f'{correlation_distance_m}')

        x_min, y_min, x_max, y_max = bounds
        if x_max <= x_min or y_max <= y_min:
            raise ValueError(f'bounds must be (x_min, y_min, x_max, y_max) with '
                             f'x_max > x_min and y_max > y_min, got {bounds}')

        self.sigma_db = float(sigma_db)
        self.correlation_distance_m = float(correlation_distance_m)
        self.bounds = (float(x_min), float(y_min), float(x_max), float(y_max))

        if resolution_m is None:
            resolution_m = correlation_distance_m * self.RESOLUTION_FRACTION
        self.resolution_m = float(max(1e-3, resolution_m))

        # At least 4 cells per axis, so the FFT has something to work with.
        self._nx = max(4, int(math.ceil((x_max - x_min) / self.resolution_m)) + 1)
        self._ny = max(4, int(math.ceil((y_max - y_min) / self.resolution_m)) + 1)

        self._rng = np.random.default_rng(seed)
        self._field = np.zeros((self._ny, self._nx))
        self.regenerate()

    @property
    def shape(self) -> Tuple[int, int]:
        """Lattice shape (ny, nx)."""
        return (self._ny, self._nx)

    def regenerate(self, seed: Optional[int] = None) -> None:
        """Draw a fresh realization. Call this between episodes."""
        if seed is not None:
            self._rng = np.random.default_rng(seed)

        if self.sigma_db == 0.0:
            self._field = np.zeros((self._ny, self._nx))
            return

        ny, nx, h = self._ny, self._nx, self.resolution_m

        # Lag magnitudes on a torus: the FFT treats the lattice as periodic,
        # so lag nx-1 is really lag 1 in the other direction.
        ix = np.minimum(np.arange(nx), nx - np.arange(nx)) * h
        iy = np.minimum(np.arange(ny), ny - np.arange(ny)) * h
        lag = np.hypot(ix[None, :], iy[:, None])

        acf = np.exp(-lag / self.correlation_distance_m)
        psd = np.fft.fft2(acf).real
        # The discretized exponential ACF is only approximately
        # positive-definite; clip the small negative eigenvalues it produces.
        np.clip(psd, 0.0, None, out=psd)

        white = self._rng.normal(size=(ny, nx))
        field = np.fft.ifft2(np.fft.fft2(white) * np.sqrt(psd)).real

        field -= field.mean()
        std = field.std()
        if std > 0.0:
            field *= self.sigma_db / std
        self._field = field

    def sample(self, x, y):
        """Shadowing in dB at (x, y). Accepts scalars or arrays."""
        x_arr = np.asarray(x, dtype=float)
        y_arr = np.asarray(y, dtype=float)
        x_min, y_min, _, _ = self.bounds

        gx = np.clip((x_arr - x_min) / self.resolution_m, 0.0, self._nx - 1.0)
        gy = np.clip((y_arr - y_min) / self.resolution_m, 0.0, self._ny - 1.0)

        x0 = np.floor(gx).astype(int)
        y0 = np.floor(gy).astype(int)
        x1 = np.minimum(x0 + 1, self._nx - 1)
        y1 = np.minimum(y0 + 1, self._ny - 1)
        fx = gx - x0
        fy = gy - y0

        f = self._field
        top = f[y0, x0] * (1.0 - fx) + f[y0, x1] * fx
        bottom = f[y1, x0] * (1.0 - fx) + f[y1, x1] * fx
        out = top * (1.0 - fy) + bottom * fy

        if np.ndim(x) == 0 and np.ndim(y) == 0:
            return float(out)
        return out


class CorrelatedShadowing:
    """Per-transmitter shadowing maps that share a common component.

        shadow_i(p) = sqrt(rho) * C(p) + sqrt(1 - rho) * I_i(p)

    `C` is one field every transmitter sees; `I_i` is private to transmitter
    `i`. Both have standard deviation `sigma_db`, so the sum does too, and
    `rho` is exactly the correlation between two transmitters' shadowing to
    the same ground point.

    `rho` is the parameter that decides which way shadowing moves reported
    coverage, so it is worth stating explicitly rather than defaulting to
    independence:

    - rho = 1: shadowing belongs to the ground point. Every drone is
      obstructed identically, there is no diversity to gain, and coverage
      falls, because thresholding a zero-mean perturbation near saturation
      loses more cells than it wins.
    - rho = 0: every path is independent. Coverage takes the *best* server,
      and the maximum of N zero-mean draws has positive mean (about 1.16
      sigma for N = 5), so mean coverage *rises*. Modelling shadowing this
      way makes the system look better than the deterministic channel did,
      which is the opposite of why shadowing is worth adding.
    - rho = 0.5: the 3GPP inter-site shadowing correlation, and the default
      here. Air-to-ground shadowing is partly common (the obstruction near
      the ground terminal blocks everyone) and partly per-path (different
      elevation angles clear different rooftops).
    """

    #: 3GPP inter-site shadow fading correlation.
    DEFAULT_INTER_LINK_CORRELATION = 0.5

    def __init__(self,
                 sigma_db: float,
                 correlation_distance_m: float,
                 bounds: Tuple[float, float, float, float],
                 inter_link_correlation: float = DEFAULT_INTER_LINK_CORRELATION,
                 resolution_m: Optional[float] = None,
                 seed: Optional[int] = None):
        if not 0.0 <= inter_link_correlation <= 1.0:
            raise ValueError('inter_link_correlation must be in [0, 1], got '
                             f'{inter_link_correlation}')

        self.sigma_db = float(sigma_db)
        self.correlation_distance_m = float(correlation_distance_m)
        self.bounds = bounds
        self.inter_link_correlation = float(inter_link_correlation)
        self.resolution_m = resolution_m

        self._w_common = math.sqrt(self.inter_link_correlation)
        self._w_private = math.sqrt(1.0 - self.inter_link_correlation)

        self._seed = seed
        self._common = self._make_field(self._child_seed('common'))
        self._private: Dict[int, ShadowingField] = {}

    #: spawn_key reserved for the common field. A fixed constant, not
    #: hash('common'): string hashing is salted per process, so that would
    #: give a different field on every run.
    _COMMON_KEY = 2 ** 31 - 1

    def _child_seed(self, key):
        """Deterministic sub-seed, independent of the order fields are built."""
        if self._seed is None:
            return None
        spawn = self._COMMON_KEY if key == 'common' else int(key)
        return np.random.SeedSequence(entropy=self._seed, spawn_key=(spawn,))

    def _make_field(self, seed) -> ShadowingField:
        return ShadowingField(
            sigma_db=self.sigma_db,
            correlation_distance_m=self.correlation_distance_m,
            bounds=self.bounds,
            resolution_m=self.resolution_m,
            seed=seed,
        )

    def _private_for(self, tx_id: int) -> ShadowingField:
        existing = self._private.get(tx_id)
        if existing is None:
            existing = self._make_field(self._child_seed(tx_id))
            self._private[tx_id] = existing
        return existing

    def sample(self, tx_id: int, x, y):
        """Shadowing in dB for transmitter `tx_id` at (x, y). Vectorized."""
        if self.sigma_db <= 0.0:
            return 0.0 if np.ndim(x) == 0 and np.ndim(y) == 0 else np.zeros_like(
                np.asarray(x, dtype=float))

        common = self._common.sample(x, y)
        if self._w_private == 0.0:
            return self._w_common * common
        private = self._private_for(tx_id).sample(x, y)
        return self._w_common * common + self._w_private * private

    def regenerate(self, seed: Optional[int] = None) -> None:
        """Draw a fresh realization of every field. Call between episodes."""
        if seed is not None:
            self._seed = seed
        self._common.regenerate(self._child_seed('common'))
        for tx_id, field in self._private.items():
            field.regenerate(self._child_seed(tx_id))


class PropagationModel:
    """
    Log-distance propagation model with log-normal shadow fading.

    Path Loss: PL(d) = PL0 + 10 * n * log10(d) + X_sigma

    Where:
    - PL0 = reference loss at 1 meter
    - n = path loss exponent
    - X_sigma = shadow fading (log-normal, zero-mean Gaussian in dB)

    X_sigma comes from a spatially correlated `ShadowingField` when
    `shadow_bounds` is given, with one independent realization per
    transmitter. That is the model worth reporting: shadowing varies smoothly
    across the area, so where the swarm flies changes what it covers.

    Without `shadow_bounds` the older per-link cached draw is used instead:
    one value per `link_id`, fixed for the lifetime of the model. For
    drone-to-drone links that is a defensible approximation. For a coverage
    grid it is not - every cell shares one `link_id` per drone, so the
    "shadowing" degenerates into a constant per-drone RSSI offset that
    shifts a whole footprint up or down and never makes one patch of ground
    harder to serve than another. Pass `shadow_bounds` for grid work.
    """

    def __init__(self, config: RadioConfig, seed: Optional[int] = None,
                 shadow_bounds: Optional[Tuple[float, float, float, float]] = None):
        self.config = config
        self.rng = np.random.default_rng(seed)
        self.shadow_bounds = shadow_bounds

        self._seed = seed
        # Shadowing maps, built lazily so a model constructed without bounds
        # costs nothing. Transmitters share a common component and keep a
        # private one; see CorrelatedShadowing.
        self._shadowing: Optional[CorrelatedShadowing] = None

        # Legacy per-link cache, used when no bounds were supplied.
        self._shadow_cache: Dict[Tuple[int, int], float] = {}

    # ── Shadowing ───────────────────────────────────────────────

    def _shadowing_maps(self) -> CorrelatedShadowing:
        """The shadowing maps for this model, built on first use."""
        if self._shadowing is None:
            self._shadowing = CorrelatedShadowing(
                sigma_db=self.config.shadow_fading_std,
                correlation_distance_m=self.config.shadow_correlation_distance_m,
                bounds=self.shadow_bounds,
                inter_link_correlation=self.config.shadow_inter_link_correlation,
                seed=self._seed,
            )
        return self._shadowing

    def shadow_db(self, tx_id: Optional[int] = None,
                  rx_xy: Optional[Tuple[float, float]] = None,
                  link_id: Optional[Tuple[int, int]] = None) -> float:
        """Shadow fading in dB for one path.

        Uses the spatially correlated field when bounds and a receiver
        position are available, the cached per-link draw when only a
        `link_id` is, and an independent draw otherwise.
        """
        if not self.config.shadowing_enabled or self.config.shadow_fading_std <= 0.0:
            return 0.0

        if self.shadow_bounds is not None and rx_xy is not None and tx_id is not None:
            return self._shadowing_maps().sample(tx_id, rx_xy[0], rx_xy[1])

        if link_id is not None:
            if link_id not in self._shadow_cache:
                self._shadow_cache[link_id] = self.rng.normal(
                    0, self.config.shadow_fading_std
                )
            return self._shadow_cache[link_id]

        return float(self.rng.normal(0, self.config.shadow_fading_std))

    def regenerate_shadowing(self, seed: Optional[int] = None) -> None:
        """Draw fresh shadowing for every transmitter. Call between episodes."""
        if seed is not None:
            self._seed = seed
        self._shadow_cache.clear()
        if self._shadowing is not None:
            self._shadowing.regenerate(self._seed)

    
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
                          include_shadow: bool = True,
                          tx_id: Optional[int] = None,
                          rx_xy: Optional[Tuple[float, float]] = None) -> float:
        """
        Compute path loss using log-distance model.

        Args:
            distance_m: Distance between transmitter and receiver
            link_id: Optional tuple (tx_id, rx_id) for consistent shadowing
            include_shadow: Whether to include shadow fading
            tx_id: Transmitter id, selecting its shadowing realization
            rx_xy: Receiver ground position, for spatially correlated shadowing

        Returns:
            Path loss in dB
        """
        if distance_m < 1.0:
            distance_m = 1.0

        # Log-distance path loss
        pl = (self.config.reference_loss_db +
              10 * self.config.path_loss_exponent * np.log10(distance_m))

        if include_shadow:
            pl += self.shadow_db(tx_id=tx_id, rx_xy=rx_xy, link_id=link_id)

        return pl
    
    def compute_rssi(self, distance_m: float,
                     link_id: Optional[Tuple[int, int]] = None,
                     tx_power_dbm: Optional[float] = None,
                     tx_id: Optional[int] = None,
                     rx_xy: Optional[Tuple[float, float]] = None) -> float:
        """
        Compute received signal strength indicator (RSSI).

        RSSI = Tx_power + Antenna_gain - Path_loss

        Pass `tx_id` and `rx_xy` to get spatially correlated shadowing; see
        the class docstring for why `link_id` alone is not enough on a grid.
        """
        if tx_power_dbm is None:
            tx_power_dbm = self.config.tx_power_dbm

        path_loss = self.compute_path_loss(distance_m, link_id,
                                           tx_id=tx_id, rx_xy=rx_xy)
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
                             link_id: Optional[Tuple[int, int]] = None,
                             tx_id: Optional[int] = None,
                             rx_xy: Optional[Tuple[float, float]] = None
                             ) -> Dict[str, float]:
        """
        Compute all link metrics at once.

        Returns dict with: rssi_dbm, snr_db, rate_mbps, connected
        """
        rssi = self.compute_rssi(distance_m, link_id, tx_id=tx_id, rx_xy=rx_xy)
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
    
    def compute_max_range(self, outage_probability: Optional[float] = None
                          ) -> float:
        """
        Compute maximum communication range (where RSSI = sensitivity).

        With no argument this is the *median* range: shadowing is zero-mean,
        so half the locations at this distance are above sensitivity and half
        below. Quoting it as "the range" overstates reliable coverage.

        Pass `outage_probability` for the distance at which that fraction of
        locations falls below sensitivity. The shadowing margin is
        sigma * Phi^-1(1 - p), so a 10% outage target at sigma = 6 dB costs
        about 7.7 dB of link budget. With shadowing disabled the margin is
        zero and every outage target gives the median range.
        """
        # At max range: tx_power + antenna_gain - path_loss = rx_sensitivity
        # path_loss = tx_power + antenna_gain - rx_sensitivity
        max_path_loss = (self.config.tx_power_dbm +
                         2 * self.config.antenna_gain_dbi -
                         self.config.rx_sensitivity_dbm)

        if outage_probability is not None:
            if not 0.0 < outage_probability < 1.0:
                raise ValueError('outage_probability must be in (0, 1), got '
                                 f'{outage_probability}')
            if (self.config.shadowing_enabled
                    and self.config.shadow_fading_std > 0.0):
                margin = (self.config.shadow_fading_std
                          * NormalDist().inv_cdf(1.0 - outage_probability))
                max_path_loss -= margin

        # Solve: path_loss = PL0 + 10*n*log10(d)
        # d = 10^((path_loss - PL0) / (10*n))
        exponent = (max_path_loss - self.config.reference_loss_db) / (
            10 * self.config.path_loss_exponent
        )
        max_range = 10 ** exponent

        return max_range

    def clear_shadow_cache(self):
        """Forget all shadow fading - the cached per-link draws and the fields."""
        self._shadow_cache.clear()
        self._shadowing = None
