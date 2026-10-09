#!/usr/bin/env python3
"""The vectorized coverage grid must equal the scalar one, cell for cell.

`compute_coverage` was three nested Python loops (cells x cells x drones). At
a 40x40 grid that cost ~194 ms per update against the node's configured 10 Hz
budget of 100 ms, so the coverage topic had been publishing at roughly half
its stated rate, and enlarging the grid to cover the whole disaster made it
worse.

Rewriting it as one numpy pass is only safe if the arithmetic is identical,
so this file keeps an independent scalar reference — written straight from the
formulas, not from the new code — and asserts the two agree exactly. The
reference is deliberately the slow, obvious implementation: that is what makes
it worth comparing against.

Runs without ROS.
"""

import math

import numpy as np
import pytest

from aura_network_sim.coverage_calculator import CoverageCalculator
from aura_network_sim.mesh_simulator import DroneNetworkState
from aura_network_sim.propagation import RadioConfig

BOUNDS = (-170.0, -350.0, 390.0, 20.0)


def radio(sigma=5.0, rho=0.5, enabled=True):
    return RadioConfig.from_ros_params(
        tx_power_dbm=20.0, noise_floor_dbm=-100.0, path_loss_exponent=3.0,
        reference_distance_m=1.0, max_mesh_distance_m=225.0, min_snr_db=10.0,
        signal_noise_std_db=sigma, frequency_ghz=2.4,
        rx_sensitivity_dbm=-80.0, shadow_correlation_distance_m=25.0,
        shadow_inter_link_correlation=rho, shadowing_enabled=enabled)


def swarm(n=5, radius=30.0, altitude=35.0, cx=120.0, cy=-170.0):
    drones = {}
    for i in range(n):
        angle = 2 * math.pi * i / n
        drones[i] = DroneNetworkState(
            drone_id=i,
            position=np.array([cx + radius * math.cos(angle),
                               cy + radius * math.sin(angle), altitude]))
        drones[i].tx_power_dbm = 20.0
    return drones


def scalar_reference(calc, drones, dead_zones=None):
    """The original formulation, cell by cell. Intentionally slow."""
    cfg = calc.config
    ny, nx = calc.grid_size_y, calc.grid_size_x
    signal = np.full((ny, nx), -200.0)
    throughput = np.zeros((ny, nx))
    serving = np.full((ny, nx), -1, dtype=int)

    for iy, y in enumerate(calc.grid_y):
        for ix, x in enumerate(calc.grid_x):
            ground = np.array([x, y, calc.ground_height])
            best_rssi, best_rate, best_id = -200.0, 0.0, -1

            for drone_id, drone in drones.items():
                distance = np.linalg.norm(ground - drone.position)
                rssi = calc.propagation.compute_rssi(
                    distance, tx_power_dbm=drone.tx_power_dbm,
                    tx_id=drone_id, rx_xy=(x, y))

                if dead_zones:
                    for zone in dead_zones:
                        dz_dx = x - zone['cx']
                        dz_dy = y - zone['cy']
                        if math.sqrt(dz_dx * dz_dx
                                     + dz_dy * dz_dy) < zone['radius']:
                            rssi -= zone['attenuation_db']

                if rssi > best_rssi:
                    best_rssi, best_id = rssi, drone_id
                    if rssi > cfg.rx_sensitivity_dbm:
                        best_rate = calc.propagation.get_data_rate(
                            calc.propagation.compute_snr(rssi))
                    else:
                        best_rate = 0.0

            signal[iy, ix] = best_rssi
            throughput[iy, ix] = best_rate
            serving[iy, ix] = best_id
    return signal, throughput, serving


def calculator(resolution=20.0, **kw):
    """Coarse by default — the scalar reference is the slow side of this."""
    return CoverageCalculator(config=radio(**kw), area_bounds=BOUNDS,
                              resolution_m=resolution, seed=0)


class TestEquivalence:

    @pytest.mark.parametrize("enabled,sigma", [
        (False, 0.0),   # deterministic channel
        (True, 2.0),
        (True, 5.0),
        (True, 10.0),
    ])
    def test_signal_map_matches_the_scalar_reference(self, enabled, sigma):
        calc = calculator(enabled=enabled, sigma=sigma)
        drones = swarm()
        got = calc.compute_coverage(drones)
        want_signal, _, _ = scalar_reference(calc, drones)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)

    def test_throughput_map_matches(self):
        calc = calculator()
        drones = swarm()
        got = calc.compute_coverage(drones)
        _, want_throughput, _ = scalar_reference(calc, drones)
        np.testing.assert_allclose(got.throughput, want_throughput, rtol=0,
                                   atol=1e-9)

    def test_serving_drone_map_matches(self):
        """Including the tie-breaking: the scalar version used a strict `>`,
        so the first drone in iteration order wins, which is what argmax does."""
        calc = calculator()
        drones = swarm()
        got = calc.compute_coverage(drones)
        _, _, want_serving = scalar_reference(calc, drones)
        np.testing.assert_array_equal(got.serving_drone, want_serving)

    def test_coverage_percent_matches(self):
        calc = calculator()
        drones = swarm()
        got = calc.compute_coverage(drones)
        want_signal, _, _ = scalar_reference(calc, drones)
        expected = 100.0 * np.mean(want_signal > calc.config.rx_sensitivity_dbm)
        assert got.coverage_percent == pytest.approx(expected)

    @pytest.mark.parametrize("resolution", [10.0, 20.0, 35.0])
    def test_equivalence_holds_at_several_resolutions(self, resolution):
        calc = calculator(resolution=resolution)
        drones = swarm()
        got = calc.compute_coverage(drones)
        want_signal, _, _ = scalar_reference(calc, drones)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)

    @pytest.mark.parametrize("n", [1, 2, 5, 8])
    def test_equivalence_for_different_swarm_sizes(self, n):
        calc = calculator()
        drones = swarm(n=n)
        got = calc.compute_coverage(drones)
        want_signal, _, want_serving = scalar_reference(calc, drones)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)
        np.testing.assert_array_equal(got.serving_drone, want_serving)

    def test_non_contiguous_drone_ids(self):
        """Ids index the shadowing fields, so a gap in them must not shift
        which field a drone gets, nor which id lands in serving_drone."""
        calc = calculator()
        drones = {k: v for k, v in zip([3, 7, 11], swarm(n=3).values())}
        for did, drone in drones.items():
            drone.drone_id = did
        got = calc.compute_coverage(drones)
        want_signal, _, want_serving = scalar_reference(calc, drones)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)
        np.testing.assert_array_equal(got.serving_drone, want_serving)
        assert set(np.unique(got.serving_drone)) <= {3, 7, 11, -1}


class TestDeadZonesStillApply:

    ZONES = [
        {'cx': 121.0, 'cy': -106.0, 'radius': 35.0, 'attenuation_db': 20.0},
        {'cx': 155.0, 'cy': -228.0, 'radius': 25.0, 'attenuation_db': 12.0},
    ]

    def test_dead_zone_attenuation_matches_the_reference(self):
        calc = calculator()
        drones = swarm()
        got = calc.compute_coverage(drones, dead_zones=self.ZONES)
        want_signal, _, _ = scalar_reference(calc, drones,
                                             dead_zones=self.ZONES)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)

    def test_overlapping_zones_accumulate(self):
        """Two zones covering one cell subtract both attenuations, as the
        scalar loop did by subtracting inside the per-zone loop."""
        overlapping = [
            {'cx': 120.0, 'cy': -170.0, 'radius': 60.0, 'attenuation_db': 10.0},
            {'cx': 130.0, 'cy': -170.0, 'radius': 60.0, 'attenuation_db': 15.0},
        ]
        calc = calculator()
        drones = swarm()
        got = calc.compute_coverage(drones, dead_zones=overlapping)
        want_signal, _, _ = scalar_reference(calc, drones,
                                             dead_zones=overlapping)
        np.testing.assert_allclose(got.signal_strength, want_signal, rtol=0,
                                   atol=1e-9)

    def test_a_dead_zone_lowers_coverage(self):
        calc = calculator()
        drones = swarm()
        clear = calc.compute_coverage(drones).coverage_percent
        blocked = calc.compute_coverage(
            drones, dead_zones=[{'cx': 120.0, 'cy': -170.0, 'radius': 150.0,
                                 'attenuation_db': 40.0}]).coverage_percent
        assert blocked < clear


class TestEdgeCases:

    def test_no_drones_leaves_the_grid_empty(self):
        calc = calculator()
        result = calc.compute_coverage({})
        assert result.coverage_percent == 0.0
        assert np.all(result.signal_strength == -200.0)
        assert np.all(result.serving_drone == -1)
        assert np.all(result.throughput == 0.0)

    def test_a_cell_directly_under_a_drone_does_not_blow_up(self):
        """The 1 m clamp: without it log10(0) appears for a drone at ground
        level over a cell centre."""
        calc = calculator()
        drones = swarm(n=1)
        cell_x, cell_y = calc.grid_x[3], calc.grid_y[4]
        drones[0].position = np.array([cell_x, cell_y, calc.ground_height])
        result = calc.compute_coverage(drones)
        assert np.all(np.isfinite(result.signal_strength))

    def test_a_distant_swarm_leaves_everything_uncovered(self):
        calc = calculator()
        result = calc.compute_coverage(swarm(cx=50_000.0, cy=50_000.0))
        assert result.coverage_percent == 0.0

    def test_throughput_is_zero_below_sensitivity(self):
        calc = calculator()
        result = calc.compute_coverage(swarm())
        uncovered = result.signal_strength <= calc.config.rx_sensitivity_dbm
        assert np.all(result.throughput[uncovered] == 0.0)

    def test_throughput_is_capped_by_the_mcs_table(self):
        calc = calculator()
        result = calc.compute_coverage(swarm())
        assert result.throughput.max() <= max(calc.config.mcs_thresholds.values())


class TestDataRateLookup:
    """The MCS scan became a binary search; the rungs must not shift."""

    @pytest.mark.parametrize("snr", [-50.0, 0.0, 3.9, 4.0, 6.9, 7.0, 15.0,
                                     30.9, 31.0, 100.0])
    def test_rate_map_matches_get_data_rate(self, snr):
        calc = calculator()
        signal = np.full((2, 2), snr + calc.config.noise_floor_dbm)
        got = calc._data_rate_map(signal)
        expected = calc.propagation.get_data_rate(snr)
        # _data_rate_map also zeroes anything below sensitivity.
        if signal[0, 0] <= calc.config.rx_sensitivity_dbm:
            expected = 0.0
        assert got[0, 0] == pytest.approx(expected)


class TestItIsActuallyFaster:

    def test_a_full_resolution_update_fits_the_10hz_budget(self):
        """Not a microbenchmark for its own sake: network_sim declares
        update_rate_hz 10.0, and the old implementation could not meet it."""
        import time
        calc = CoverageCalculator(config=radio(), area_bounds=BOUNDS,
                                  resolution_m=10.0, seed=0)
        drones = swarm()
        calc.compute_coverage(drones)  # warm up
        start = time.perf_counter()
        for _ in range(5):
            calc.compute_coverage(drones)
        elapsed_ms = (time.perf_counter() - start) / 5 * 1000
        assert elapsed_ms < 100.0, f'{elapsed_ms:.0f} ms per update'
