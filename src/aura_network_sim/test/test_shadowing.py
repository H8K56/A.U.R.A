#!/usr/bin/env python3
"""Log-normal shadowing: the field, its correlation, and what it does to coverage.

Roadmap §8. The propagation model always had a `shadow_fading_std` and always
added a Gaussian draw, so "add shadowing" looked done. It was not, and the way
it failed is the thing these tests pin:

`compute_rssi` cached one draw per `link_id`, and the coverage grid passed
`link_id=(drone_id, -1)` for *every cell*. So all ~1600 cells shared one value
per drone. That is not shadowing — it is a constant per-drone RSSI offset that
slides a whole footprint up or down together. It cannot make one street harder
to serve than the next, and because it is zero-mean it very nearly cancels out
of the reported coverage figure.

Real shadowing is spatially correlated: terrain and buildings obstruct nearby
points the same way. That correlation is what makes it matter, and
`ShadowingField` is what provides it.

Runs without ROS.
"""

import math
import os
import subprocess
import sys

import numpy as np
import pytest

from aura_network_sim.coverage_calculator import CoverageCalculator
from aura_network_sim.mesh_simulator import DroneNetworkState
from aura_network_sim.propagation import (
    CorrelatedShadowing, PropagationModel, RadioConfig, ShadowingField,
)

BOUNDS = (-200.0, -200.0, 200.0, 200.0)


def sample_points(n=20000, seed=0, margin=10.0):
    """Points well inside BOUNDS, so edge clamping does not skew statistics."""
    rng = np.random.default_rng(seed)
    x0, y0, x1, y1 = BOUNDS
    return (rng.uniform(x0 + margin, x1 - margin, n),
            rng.uniform(y0 + margin, y1 - margin, n))


def radio(sigma=5.0, rho=0.5, enabled=True, threshold=-80.0, corr=25.0):
    return RadioConfig.from_ros_params(
        tx_power_dbm=20.0, noise_floor_dbm=-100.0, path_loss_exponent=3.0,
        reference_distance_m=1.0, max_mesh_distance_m=225.0, min_snr_db=10.0,
        signal_noise_std_db=sigma, frequency_ghz=2.4,
        rx_sensitivity_dbm=threshold, shadow_correlation_distance_m=corr,
        shadow_inter_link_correlation=rho, shadowing_enabled=enabled)


def ring_of_drones(n=5, radius=30.0, altitude=30.0):
    """The tight cluster the RL policy actually holds during OPERATIONS."""
    drones = {}
    for i in range(n):
        angle = 2 * math.pi * i / n
        drones[i] = DroneNetworkState(
            drone_id=i,
            position=np.array([radius * math.cos(angle),
                               radius * math.sin(angle), altitude]))
        drones[i].tx_power_dbm = 20.0
    return drones


class TestFieldStatistics:

    def test_lattice_has_the_requested_standard_deviation(self):
        """Exact, not approximate: the realization is normalized, so the
        contract is testable and a simulator gets a deterministic variance
        instead of a chi-squared one."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        assert f._field.std() == pytest.approx(6.0, abs=1e-9)

    def test_field_is_zero_mean(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        assert f._field.mean() == pytest.approx(0.0, abs=1e-9)

    def test_zero_sigma_gives_no_shadowing(self):
        f = ShadowingField(0.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points(200)
        assert np.all(f.sample(xs, ys) == 0.0)

    def test_interpolated_spread_is_close_to_sigma(self):
        """Bilinear interpolation averages correlated lattice values, so
        between-lattice points have slightly less spread. A few percent is
        expected; much more would mean the lattice is too coarse."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        assert f.sample(xs, ys).std() == pytest.approx(6.0, rel=0.10)

    def test_interpolated_values_stay_zero_mean(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        assert f.sample(xs, ys).mean() == pytest.approx(0.0, abs=0.5)

    @pytest.mark.parametrize("sigma", [1.0, 4.0, 8.0, 12.0])
    def test_sigma_scales_the_field(self, sigma):
        f = ShadowingField(sigma, 25.0, BOUNDS, seed=3)
        assert f._field.std() == pytest.approx(sigma, abs=1e-9)


class TestSpatialCorrelation:
    """The whole point of the change. Without this, shadowing is just noise."""

    @staticmethod
    def _corr_at(field, separation, xs, ys):
        return float(np.corrcoef(field.sample(xs, ys),
                                 field.sample(xs + separation, ys))[0, 1])

    def test_correlation_decays_with_separation(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        corrs = [self._corr_at(f, d, xs, ys) for d in (0, 5, 15, 30, 60, 120)]
        assert corrs[0] == pytest.approx(1.0, abs=1e-9)
        for earlier, later in zip(corrs, corrs[1:]):
            assert later < earlier, f'correlation not decaying: {corrs}'

    def test_nearby_points_are_strongly_correlated(self):
        """A metre apart is the same building, so nearly the same shadowing."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        assert self._corr_at(f, 1.0, xs, ys) > 0.95

    def test_correlation_is_substantial_at_the_correlation_distance(self):
        """Nominally 1/e ~ 0.37. Bilinear smoothing widens it a little, so
        this asserts the band rather than the exact value."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        assert 0.25 < self._corr_at(f, 25.0, xs, ys) < 0.65

    def test_distant_points_are_essentially_uncorrelated(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        xs, ys = sample_points()
        assert abs(self._corr_at(f, 150.0, xs, ys)) < 0.2

    def test_a_longer_correlation_distance_correlates_further(self):
        xs, ys = sample_points()
        short = ShadowingField(6.0, 10.0, BOUNDS, seed=42)
        long = ShadowingField(6.0, 80.0, BOUNDS, seed=42)
        assert self._corr_at(long, 40.0, xs, ys) > self._corr_at(short, 40.0, xs, ys)

    def test_field_is_continuous(self):
        """A drone crossing a lattice boundary must not see an RSSI step."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=42)
        res = f.resolution_m
        edge = BOUNDS[0] + 10 * res  # exactly on a lattice line
        before = f.sample(edge - 1e-4, 0.0)
        after = f.sample(edge + 1e-4, 0.0)
        assert abs(after - before) < 1e-3


class TestFieldReproducibility:

    def test_same_seed_gives_the_same_field(self):
        a = ShadowingField(6.0, 25.0, BOUNDS, seed=7)
        b = ShadowingField(6.0, 25.0, BOUNDS, seed=7)
        assert np.array_equal(a._field, b._field)

    def test_different_seeds_give_different_fields(self):
        a = ShadowingField(6.0, 25.0, BOUNDS, seed=7)
        b = ShadowingField(6.0, 25.0, BOUNDS, seed=8)
        assert not np.array_equal(a._field, b._field)

    def test_regenerate_draws_a_new_realization(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=7)
        before = f._field.copy()
        f.regenerate(seed=8)
        assert not np.array_equal(before, f._field)
        assert f._field.std() == pytest.approx(6.0, abs=1e-9)

    def test_reproducible_in_a_separate_interpreter(self):
        """Guards against seeding anything off `hash()` of a string, which is
        salted per process: in-process equality would still pass while every
        new run produced a different channel."""
        code = (
            'from aura_network_sim.propagation import CorrelatedShadowing;'
            'print("%.12f" % CorrelatedShadowing('
            '6.0, 25.0, (-200.0, -200.0, 200.0, 200.0), 0.5, seed=99'
            ').sample(0, 10.0, 20.0))'
        )
        outputs = set()
        for hashseed in ('0', '1', '12345'):
            env = dict(os.environ, PYTHONHASHSEED=hashseed)
            proc = subprocess.run([sys.executable, '-c', code],
                                  capture_output=True, text=True, env=env)
            assert proc.returncode == 0, proc.stderr
            outputs.add(proc.stdout.strip())
        assert len(outputs) == 1, f'field depends on hash salt: {outputs}'


class TestFieldSampling:

    def test_scalar_in_scalar_out(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=1)
        assert isinstance(f.sample(0.0, 0.0), float)

    def test_array_shape_is_preserved(self):
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=1)
        grid_x, grid_y = np.meshgrid(np.linspace(-100, 100, 13),
                                     np.linspace(-100, 100, 17))
        assert f.sample(grid_x, grid_y).shape == (17, 13)

    def test_points_outside_bounds_clamp_instead_of_raising(self):
        """A drone that leaves the modelled area keeps a plausible value."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=1)
        inside = f.sample(-199.0, -199.0)
        far = f.sample(-10_000.0, -10_000.0)
        assert np.isfinite(far)
        assert far == pytest.approx(f.sample(-200.0, -200.0))
        assert np.isfinite(inside)

    def test_sampling_is_a_pure_read(self):
        """Sampling must not advance any RNG, or coverage would depend on how
        many cells happened to be evaluated first."""
        f = ShadowingField(6.0, 25.0, BOUNDS, seed=1)
        first = f.sample(12.0, 34.0)
        _ = f.sample(np.linspace(-150, 150, 500), np.zeros(500))
        assert f.sample(12.0, 34.0) == first


class TestFieldValidation:

    def test_negative_sigma_is_rejected(self):
        with pytest.raises(ValueError, match='sigma_db'):
            ShadowingField(-1.0, 25.0, BOUNDS)

    @pytest.mark.parametrize("corr", [0.0, -5.0])
    def test_non_positive_correlation_distance_is_rejected(self, corr):
        with pytest.raises(ValueError, match='correlation_distance_m'):
            ShadowingField(6.0, corr, BOUNDS)

    @pytest.mark.parametrize("bad", [
        (0.0, 0.0, 0.0, 10.0),      # zero width
        (0.0, 0.0, 10.0, 0.0),      # zero height
        (10.0, 0.0, -10.0, 10.0),   # inverted x
    ])
    def test_degenerate_bounds_are_rejected(self, bad):
        with pytest.raises(ValueError, match='bounds'):
            ShadowingField(6.0, 25.0, bad)


class TestInterLinkCorrelation:
    """rho decides the *sign* of shadowing's effect on coverage, so it gets
    its own tests rather than riding on a default."""

    @staticmethod
    def _measured_rho(rho, seeds=range(12)):
        xs, ys = sample_points(8000)
        vals = []
        for s in seeds:
            cs = CorrelatedShadowing(6.0, 25.0, BOUNDS, rho, seed=s)
            vals.append(np.corrcoef(cs.sample(0, xs, ys),
                                    cs.sample(1, xs, ys))[0, 1])
        return float(np.mean(vals))

    def test_full_correlation_makes_every_transmitter_identical(self):
        """rho=1: shadowing belongs to the ground point. No diversity to gain."""
        cs = CorrelatedShadowing(6.0, 25.0, BOUNDS, 1.0, seed=5)
        xs, ys = sample_points(500)
        assert np.allclose(cs.sample(0, xs, ys), cs.sample(3, xs, ys))

    def test_zero_correlation_makes_transmitters_independent(self):
        cs = CorrelatedShadowing(6.0, 25.0, BOUNDS, 0.0, seed=5)
        xs, ys = sample_points(500)
        assert not np.allclose(cs.sample(0, xs, ys), cs.sample(3, xs, ys))

    @pytest.mark.parametrize("rho", [0.0, 0.25, 0.5, 0.75, 1.0])
    def test_measured_correlation_matches_the_request(self, rho):
        """Averaged over realizations: a single 400 m field holds only ~250
        independent patches, so one draw scatters by about 0.1."""
        assert self._measured_rho(rho) == pytest.approx(rho, abs=0.08)

    @pytest.mark.parametrize("rho", [0.0, 0.5, 1.0])
    def test_marginal_spread_is_sigma_regardless_of_rho(self, rho):
        """sqrt(rho)*common + sqrt(1-rho)*private has variance sigma^2 for
        every rho — mixing the two must not change how deep the fades are."""
        cs = CorrelatedShadowing(6.0, 25.0, BOUNDS, rho, seed=5)
        xs, ys = sample_points()
        assert cs.sample(0, xs, ys).std() == pytest.approx(6.0, rel=0.12)

    @pytest.mark.parametrize("rho", [-0.01, 1.01, 2.0])
    def test_out_of_range_correlation_is_rejected(self, rho):
        with pytest.raises(ValueError, match='inter_link_correlation'):
            CorrelatedShadowing(6.0, 25.0, BOUNDS, rho)

    def test_default_is_the_3gpp_inter_site_value(self):
        cs = CorrelatedShadowing(6.0, 25.0, BOUNDS)
        assert cs.inter_link_correlation == pytest.approx(0.5)

    def test_transmitter_order_does_not_change_its_field(self):
        """Fields are built on demand. Seeding them from a shared stream would
        make a drone's channel depend on which drone was evaluated first."""
        first = CorrelatedShadowing(6.0, 25.0, BOUNDS, 0.5, seed=7)
        _ = first.sample(3, 0.0, 0.0)      # build tx 3 before tx 0
        value_after = first.sample(0, 10.0, 20.0)

        second = CorrelatedShadowing(6.0, 25.0, BOUNDS, 0.5, seed=7)
        value_first = second.sample(0, 10.0, 20.0)

        assert value_after == pytest.approx(value_first)

    def test_zero_sigma_is_zero_for_scalars_and_arrays(self):
        cs = CorrelatedShadowing(0.0, 25.0, BOUNDS, 0.5, seed=7)
        assert cs.sample(0, 1.0, 2.0) == 0.0
        xs, ys = sample_points(50)
        assert np.all(cs.sample(0, xs, ys) == 0.0)

    def test_regenerate_changes_every_transmitter(self):
        cs = CorrelatedShadowing(6.0, 25.0, BOUNDS, 0.5, seed=7)
        xs, ys = sample_points(300)
        before = [cs.sample(i, xs, ys).copy() for i in range(3)]
        cs.regenerate(seed=8)
        for i, old in enumerate(before):
            assert not np.allclose(old, cs.sample(i, xs, ys))


class TestPropagationModelIntegration:

    def test_disabled_shadowing_gives_exact_deterministic_path_loss(self):
        model = PropagationModel(radio(sigma=6.0, enabled=False), seed=1,
                                 shadow_bounds=BOUNDS)
        cfg = model.config
        expected = (cfg.reference_loss_db
                    + 10 * cfg.path_loss_exponent * math.log10(100.0))
        assert model.compute_path_loss(100.0, tx_id=0,
                                       rx_xy=(10.0, 20.0)) == pytest.approx(expected)

    def test_shadowing_varies_across_positions_when_bounds_are_given(self):
        model = PropagationModel(radio(sigma=6.0), seed=1, shadow_bounds=BOUNDS)
        values = [model.shadow_db(tx_id=0, rx_xy=(x, 0.0))
                  for x in np.linspace(-180, 180, 40)]
        assert np.std(values) > 1.0

    def test_without_bounds_one_link_id_is_a_single_frozen_offset(self):
        """The old behaviour, pinned deliberately. This is what the coverage
        grid was getting for every one of its cells."""
        model = PropagationModel(radio(sigma=6.0), seed=1)
        first = model.compute_path_loss(100.0, link_id=(0, -1))
        again = model.compute_path_loss(100.0, link_id=(0, -1))
        assert first == again

    def test_with_bounds_the_same_link_varies_by_position(self):
        """The regression test for the actual defect: distinct ground points
        must not share one cached draw."""
        model = PropagationModel(radio(sigma=6.0), seed=1, shadow_bounds=BOUNDS)
        near = model.shadow_db(tx_id=0, rx_xy=(-150.0, -150.0))
        far = model.shadow_db(tx_id=0, rx_xy=(150.0, 150.0))
        assert near != far

    def test_repeated_sampling_of_one_point_is_stable(self):
        """Shadowing is a map, not per-call noise: asking twice about the same
        place must give the same answer."""
        model = PropagationModel(radio(sigma=6.0), seed=1, shadow_bounds=BOUNDS)
        first = model.shadow_db(tx_id=2, rx_xy=(33.0, -44.0))
        assert model.shadow_db(tx_id=2, rx_xy=(33.0, -44.0)) == first

    def test_clear_shadow_cache_forgets_the_maps(self):
        model = PropagationModel(radio(sigma=6.0), seed=None,
                                 shadow_bounds=BOUNDS)
        before = model.shadow_db(tx_id=0, rx_xy=(0.0, 0.0))
        model.clear_shadow_cache()
        after = model.shadow_db(tx_id=0, rx_xy=(0.0, 0.0))
        assert before != after  # unseeded, so a new realization differs

    def test_rssi_includes_the_shadowing_term(self):
        model = PropagationModel(radio(sigma=6.0), seed=1, shadow_bounds=BOUNDS)
        shadow = model.shadow_db(tx_id=0, rx_xy=(50.0, 50.0))
        rssi = model.compute_rssi(100.0, tx_id=0, rx_xy=(50.0, 50.0))
        cfg = model.config
        median = (cfg.tx_power_dbm + 2 * cfg.antenna_gain_dbi
                  - cfg.reference_loss_db
                  - 10 * cfg.path_loss_exponent * math.log10(100.0))
        assert rssi == pytest.approx(median - shadow)


class TestRangeUnderShadowing:
    """`compute_max_range()` is the *median* range. Quoting it as "the range"
    claims coverage at a distance where half the locations are already out."""

    def test_an_outage_target_shortens_the_range(self):
        model = PropagationModel(radio(sigma=6.0))
        assert model.compute_max_range(0.1) < model.compute_max_range()

    def test_a_stricter_outage_target_shortens_it_further(self):
        model = PropagationModel(radio(sigma=6.0))
        assert model.compute_max_range(0.01) < model.compute_max_range(0.1)

    def test_a_larger_sigma_costs_more_range(self):
        quiet = PropagationModel(radio(sigma=2.0))
        noisy = PropagationModel(radio(sigma=8.0))
        assert noisy.compute_max_range(0.1) < quiet.compute_max_range(0.1)
        # The median is unaffected: shadowing is zero-mean.
        assert noisy.compute_max_range() == pytest.approx(quiet.compute_max_range())

    def test_fifty_percent_outage_is_the_median_range(self):
        model = PropagationModel(radio(sigma=6.0))
        assert model.compute_max_range(0.5) == pytest.approx(
            model.compute_max_range())

    def test_disabled_shadowing_has_no_outage_margin(self):
        model = PropagationModel(radio(sigma=6.0, enabled=False))
        assert model.compute_max_range(0.01) == pytest.approx(
            model.compute_max_range())

    @pytest.mark.parametrize("bad", [0.0, 1.0, -0.1, 1.5])
    def test_invalid_outage_probability_is_rejected(self, bad):
        model = PropagationModel(radio(sigma=6.0))
        with pytest.raises(ValueError, match='outage_probability'):
            model.compute_max_range(bad)


class TestCoverageReliability:
    """Mean coverage and reliable coverage move in opposite directions, and
    reporting only the first is how a disaster relay looks better than it is."""

    #: Coarser than production (10 m): these assertions are about the
    #: distribution across realizations, not resolution, and the coverage
    #: loop is pure Python — 10 m would put this file at 85 s in CI.
    RESOLUTION_M = 20.0
    REALIZATIONS = 40

    @classmethod
    def _calc(cls, sigma, rho=0.5, enabled=True):
        return CoverageCalculator(config=radio(sigma=sigma, rho=rho,
                                               enabled=enabled),
                                  area_bounds=BOUNDS,
                                  resolution_m=cls.RESOLUTION_M, seed=0)

    def test_without_shadowing_every_realization_is_identical(self):
        calc = self._calc(0.0, enabled=False)
        deterministic = calc.compute_coverage(ring_of_drones()).coverage_percent
        rel = calc.compute_coverage_reliability(ring_of_drones(),
                                                realizations=5)
        assert rel.mean_coverage_percent == pytest.approx(deterministic)
        assert rel.reliable_coverage_percent == pytest.approx(deterministic)
        assert rel.marginal_percent == pytest.approx(0.0)
        assert rel.spread_percent == pytest.approx(0.0)

    def test_reliable_coverage_is_below_mean_coverage(self):
        """The headline result of §8."""
        rel = self._calc(5.0).compute_coverage_reliability(
            ring_of_drones(), realizations=self.REALIZATIONS, reliability=0.9)
        assert rel.reliable_coverage_percent < rel.mean_coverage_percent

    def test_shadowing_creates_a_large_marginal_area(self):
        """The deterministic model draws a crisp coverage boundary. This is
        how much of the map that boundary was hiding."""
        rel = self._calc(5.0).compute_coverage_reliability(
            ring_of_drones(), realizations=self.REALIZATIONS)
        assert rel.marginal_percent > 25.0

    def test_a_larger_sigma_lowers_reliable_coverage(self):
        quiet = self._calc(2.0).compute_coverage_reliability(
            ring_of_drones(), realizations=self.REALIZATIONS, reliability=0.9)
        noisy = self._calc(8.0).compute_coverage_reliability(
            ring_of_drones(), realizations=self.REALIZATIONS, reliability=0.9)
        assert noisy.reliable_coverage_percent < quiet.reliable_coverage_percent

    def test_a_stricter_reliability_target_covers_less_area(self):
        calc = self._calc(5.0)
        drones = ring_of_drones()
        loose = calc.compute_coverage_reliability(drones, realizations=self.REALIZATIONS,
                                                  reliability=0.5)
        strict = calc.compute_coverage_reliability(drones, realizations=self.REALIZATIONS,
                                                   reliability=0.99)
        assert strict.reliable_coverage_percent < loose.reliable_coverage_percent

    def test_results_are_reproducible_from_the_seed(self):
        a = self._calc(5.0).compute_coverage_reliability(
            ring_of_drones(), realizations=20, seed=7)
        b = self._calc(5.0).compute_coverage_reliability(
            ring_of_drones(), realizations=20, seed=7)
        assert np.array_equal(a.coverage_probability, b.coverage_probability)

    def test_probabilities_are_well_formed(self):
        calc = self._calc(5.0)
        rel = calc.compute_coverage_reliability(ring_of_drones(),
                                                realizations=20)
        assert rel.coverage_probability.shape == (calc.grid_size_y,
                                                  calc.grid_size_x)
        assert np.all(rel.coverage_probability >= 0.0)
        assert np.all(rel.coverage_probability <= 1.0)
        assert len(rel.per_realization_percent) == 20

    @pytest.mark.parametrize("bad", [0, -1])
    def test_realization_count_must_be_positive(self, bad):
        with pytest.raises(ValueError, match='realizations'):
            self._calc(5.0).compute_coverage_reliability(ring_of_drones(),
                                                         realizations=bad)

    @pytest.mark.parametrize("bad", [0.0, -0.5, 1.5])
    def test_reliability_must_be_a_probability(self, bad):
        with pytest.raises(ValueError, match='reliability'):
            self._calc(5.0).compute_coverage_reliability(ring_of_drones(),
                                                         reliability=bad)


class TestCoverageIsSpatiallyStructured:
    """What the degenerate per-link cache could never produce."""

    def test_shadowing_differs_from_cell_to_cell(self):
        calc = CoverageCalculator(config=radio(sigma=6.0), area_bounds=BOUNDS,
                                  resolution_m=10.0, seed=3)
        drones = ring_of_drones()
        with_shadow = calc.compute_coverage(drones).signal_strength

        flat = CoverageCalculator(config=radio(sigma=6.0, enabled=False),
                                  area_bounds=BOUNDS, resolution_m=10.0, seed=3)
        without = flat.compute_coverage(drones).signal_strength

        delta = with_shadow - without
        # A constant per-drone offset would make this near-zero everywhere
        # except at serving-drone boundaries.
        assert np.std(delta) > 1.0

    def test_identical_distances_can_have_different_signals(self):
        """Two cells the same distance from the swarm are no longer
        interchangeable — which is what makes where the swarm flies matter."""
        calc = CoverageCalculator(config=radio(sigma=8.0), area_bounds=BOUNDS,
                                  resolution_m=10.0, seed=11)
        result = calc.compute_coverage(ring_of_drones())
        ys, xs = np.meshgrid(calc.grid_y, calc.grid_x, indexing='ij')
        radius = np.hypot(xs, ys)
        ring = (radius > 95.0) & (radius < 105.0)
        assert np.count_nonzero(ring) > 10
        assert np.std(result.signal_strength[ring]) > 1.0
