#!/usr/bin/env python3
"""RadioConfig construction from ROS parameters.

Receiver sensitivity decides which grid cells count as covered, so it sets
every coverage figure the system reports. It used to be derivable only from
noise_floor + min_snr, which meant `coverage_threshold_dbm` in the YAML
configs was silently ignored and the ROS pipeline reported ~100% coverage
against a -90 dBm threshold nobody had asked for.
"""

import math

import pytest

from aura_network_sim.propagation import RadioConfig


class TestDerivedSensitivity:
    """Default behaviour: sensitivity follows from the noise floor."""

    def test_sensitivity_is_noise_floor_plus_min_snr(self):
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=-100.0, min_snr_db=10.0)
        assert cfg.rx_sensitivity_dbm == pytest.approx(-90.0)

    @pytest.mark.parametrize("noise,snr,expected", [
        (-100.0, 10.0, -90.0),
        (-95.0, 15.0, -80.0),
        (-110.0, 6.0, -104.0),
    ])
    def test_derivation_tracks_both_inputs(self, noise, snr, expected):
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=noise, min_snr_db=snr)
        assert cfg.rx_sensitivity_dbm == pytest.approx(expected)

    def test_omitting_the_override_still_derives(self):
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=-100.0, min_snr_db=10.0,
                                          rx_sensitivity_dbm=None)
        assert cfg.rx_sensitivity_dbm == pytest.approx(-90.0)


class TestExplicitSensitivity:
    """An explicit threshold must win, so a deployment can report coverage
    against the number it actually cares about."""

    def test_override_replaces_the_derived_value(self):
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=-100.0, min_snr_db=10.0,
                                          rx_sensitivity_dbm=-80.0)
        assert cfg.rx_sensitivity_dbm == pytest.approx(-80.0)

    def test_override_is_not_mixed_with_the_noise_floor(self):
        """Regression guard: the override is the sensitivity, not an offset."""
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=-120.0, min_snr_db=3.0,
                                          rx_sensitivity_dbm=-75.0)
        assert cfg.rx_sensitivity_dbm == pytest.approx(-75.0)

    @pytest.mark.parametrize("value", [-110.0, -95.0, -80.0, -60.0])
    def test_any_plausible_threshold_is_honoured(self, value):
        cfg = RadioConfig.from_ros_params(rx_sensitivity_dbm=value)
        assert cfg.rx_sensitivity_dbm == pytest.approx(value)

    def test_noise_floor_is_still_recorded_when_overridden(self):
        """Throughput uses SNR against the noise floor, so overriding the
        coverage threshold must not disturb it."""
        cfg = RadioConfig.from_ros_params(noise_floor_dbm=-100.0, min_snr_db=10.0,
                                          rx_sensitivity_dbm=-80.0)
        assert cfg.noise_floor_dbm == pytest.approx(-100.0)
        assert cfg.min_snr_db == pytest.approx(10.0)


class TestCoverageRadiusImplication:
    """The threshold is only interesting through the range it implies, which is
    what made the original fault visible: a 400 m box and a 215 m radius."""

    @staticmethod
    def _range_m(cfg: RadioConfig) -> float:
        # signal = tx - (ref_loss + 10*n*log10(d)) = sensitivity
        budget = cfg.tx_power_dbm - cfg.rx_sensitivity_dbm - cfg.reference_loss_db
        return 10 ** (budget / (10 * cfg.path_loss_exponent))

    def test_a_stricter_threshold_shortens_the_range(self):
        loose = RadioConfig.from_ros_params(frequency_ghz=2.4,
                                            path_loss_exponent=3.0,
                                            rx_sensitivity_dbm=-90.0)
        strict = RadioConfig.from_ros_params(frequency_ghz=2.4,
                                             path_loss_exponent=3.0,
                                             rx_sensitivity_dbm=-80.0)
        assert self._range_m(strict) < self._range_m(loose)

    def test_the_configured_threshold_fits_inside_the_simulated_area(self):
        """sim_params.yaml configures -80 dBm over a 400 m box. If one drone's
        range covered the whole box, coverage would read ~100% regardless of
        where the swarm flew, which is exactly what the old derived -90 dBm
        did."""
        cfg = RadioConfig.from_ros_params(frequency_ghz=2.4,
                                          path_loss_exponent=2.7 + 0.3,
                                          rx_sensitivity_dbm=-80.0)
        half_diagonal = math.hypot(200.0, 200.0)
        assert self._range_m(cfg) < half_diagonal


class TestReferenceLoss:

    def test_reference_loss_grows_with_frequency(self):
        low = RadioConfig.from_ros_params(frequency_ghz=2.4)
        high = RadioConfig.from_ros_params(frequency_ghz=5.8)
        assert high.reference_loss_db > low.reference_loss_db

    def test_reference_loss_matches_free_space_at_one_metre(self):
        cfg = RadioConfig.from_ros_params(frequency_ghz=2.4,
                                          reference_distance_m=1.0)
        expected = 20 * math.log10(2.4) + 32.44
        assert cfg.reference_loss_db == pytest.approx(expected, abs=1e-6)
