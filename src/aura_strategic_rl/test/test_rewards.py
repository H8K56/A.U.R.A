#!/usr/bin/env python3
"""Reward-function invariants for the strategic RL policy.

These pin the *signs and orderings* the multi-objective reward relies on
rather than exact magnitudes, so retuning the weights does not break the
suite but inverting an incentive does.
"""

import numpy as np
import pytest

from aura_strategic_rl.rewards import RewardCalculator, RewardConfig


def nominal(**overrides):
    """A healthy swarm sitting on the disaster-zone centre."""
    cfg = RewardConfig()
    args = dict(
        coverage_percent=50.0,
        mesh_connected=True,
        avg_signal_dbm=-70.0,
        avg_throughput_mbps=50.0,
        avg_latency_ms=20.0,
        drone_positions=[
            (cfg.world_center_x + 30.0 * i, cfg.world_center_y, 40.0)
            for i in range(5)
        ],
    )
    args.update(overrides)
    return args


class TestRewardContract:

    def test_returns_total_and_components(self):
        total, comps = RewardCalculator().compute_reward(**nominal())
        assert isinstance(total, float)
        assert comps['total'] == pytest.approx(total)

    def test_components_sum_to_total(self):
        """The breakdown is what gets logged and plotted; if it stops adding up
        to the scalar the agent optimises, the logs are lying."""
        total, c = RewardCalculator().compute_reward(**nominal())
        summed = sum(v for k, v in c.items() if k != 'total')
        assert summed == pytest.approx(total, abs=1e-9)

    def test_reward_is_finite_for_extreme_inputs(self):
        calc = RewardCalculator()
        total, _ = calc.compute_reward(**nominal(
            coverage_percent=0.0,
            mesh_connected=False,
            avg_signal_dbm=-200.0,
            avg_throughput_mbps=0.0,
            avg_latency_ms=10_000.0,
            drone_positions=[(0.0, 0.0, 0.0)] * 5,
        ))
        assert np.isfinite(total)


class TestCoverageIncentive:

    def test_more_coverage_scores_higher(self):
        calc = RewardCalculator()
        scores = []
        for pct in (0.0, 25.0, 50.0, 75.0):
            calc.reset()
            total, _ = calc.compute_reward(**nominal(coverage_percent=pct))
            scores.append(total)
        assert scores == sorted(scores)

    def test_hitting_the_target_pays_a_bonus(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        below = calc._compute_coverage_reward(cfg.coverage_target - 0.1)
        at = calc._compute_coverage_reward(cfg.coverage_target)
        assert at - below > 0.2 * cfg.coverage_weight - 1e-6

    def test_improvement_bonus_only_pays_on_improvement(self):
        calc = RewardCalculator()
        calc.compute_reward(**nominal(coverage_percent=40.0))
        _, up = calc.compute_reward(**nominal(coverage_percent=60.0))
        assert up['improvement_bonus'] > 0.0
        _, down = calc.compute_reward(**nominal(coverage_percent=30.0))
        assert down['improvement_bonus'] == 0.0

    def test_improvement_bonus_needs_reset_between_episodes(self):
        """reset() must clear prev_coverage, or the first step of a new episode
        is scored against the last step of the previous one."""
        calc = RewardCalculator()
        calc.compute_reward(**nominal(coverage_percent=90.0))
        calc.reset()
        _, c = calc.compute_reward(**nominal(coverage_percent=10.0))
        assert c['improvement_bonus'] >= 0.0


class TestConnectivityIncentive:

    def test_disconnected_mesh_is_penalised_symmetrically(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_connectivity_reward(True) == cfg.connectivity_weight
        assert calc._compute_connectivity_reward(False) == -cfg.connectivity_weight

    def test_connectivity_dominates_marginal_coverage(self):
        """Keeping the mesh linked must outrank a small coverage gain, or the
        swarm learns to fragment itself chasing coverage."""
        calc = RewardCalculator()
        calc.reset()
        connected, _ = calc.compute_reward(**nominal(
            coverage_percent=50.0, mesh_connected=True))
        calc.reset()
        split, _ = calc.compute_reward(**nominal(
            coverage_percent=60.0, mesh_connected=False))
        assert connected > split


class TestNetworkQualityIncentives:

    def test_signal_reward_is_monotonic_and_bounded(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        vals = [calc._compute_signal_reward(d) for d in (-120, -90, -70, -50, -30)]
        assert vals == sorted(vals)
        assert vals[0] == pytest.approx(0.0)
        assert vals[-1] == pytest.approx(cfg.signal_weight)

    def test_throughput_reward_saturates_at_the_cap(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_throughput_reward(100.0) == pytest.approx(cfg.throughput_weight)
        assert calc._compute_throughput_reward(10_000.0) == pytest.approx(cfg.throughput_weight)
        assert calc._compute_throughput_reward(0.0) == pytest.approx(0.0)

    def test_lower_latency_scores_higher(self):
        calc = RewardCalculator()
        assert calc._compute_latency_reward(5.0) > calc._compute_latency_reward(80.0)
        assert calc._compute_latency_reward(500.0) == pytest.approx(0.0)


class TestSafetyPenalties:

    def test_collision_penalty_grows_as_drones_close_in(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        cx, cy = cfg.world_center_x, cfg.world_center_y

        def pen(sep):
            return calc._compute_safety_penalties(
                [(cx, cy, 40.0), (cx + sep, cy, 40.0)])

        safe = pen(cfg.min_separation_m * 2)
        near = pen(cfg.min_separation_m * 0.5)
        touching = pen(0.1)
        assert near > safe
        assert touching > near

    def test_no_collision_penalty_at_exactly_minimum_separation(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        cx, cy = cfg.world_center_x, cfg.world_center_y
        assert calc._compute_safety_penalties(
            [(cx, cy, 40.0), (cx + cfg.min_separation_m, cy, 40.0)]) == pytest.approx(0.0)

    def test_degraded_swarm_of_one_is_still_constrained(self):
        """Regression: an `n < 2` early return once skipped the per-drone
        altitude and boundary checks along with the pairwise collision loop, so
        a swarm degraded to a single survivor flew unconstrained — exactly the
        N-1 fault case the system is meant to handle."""
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_safety_penalties(
            [(cfg.world_center_x, cfg.world_center_y, 500.0)]) > 0.0
        assert calc._compute_safety_penalties(
            [(cfg.world_center_x + 10_000.0, cfg.world_center_y, 40.0)]) > 0.0

    def test_no_drones_yields_no_safety_penalty(self):
        assert RewardCalculator()._compute_safety_penalties([]) == 0.0

    def test_single_drone_has_no_collision_penalty(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_safety_penalties(
            [(cfg.world_center_x, cfg.world_center_y, 40.0)]) == 0.0

    @pytest.mark.parametrize("alt", [0.0, 5.0, 14.9])
    def test_flying_below_the_floor_is_penalised(self, alt):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_safety_penalties(
            [(cfg.world_center_x, cfg.world_center_y, alt)]) > 0.0

    @pytest.mark.parametrize("alt", [80.1, 120.0])
    def test_flying_above_the_ceiling_is_penalised(self, alt):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_safety_penalties(
            [(cfg.world_center_x, cfg.world_center_y, alt)]) > 0.0

    def test_boundary_penalty_is_clamped(self):
        """ROS inference can place a drone far outside the disk; the penalty
        must not blow up without bound and swamp every other term."""
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        far = calc._compute_safety_penalties(
            [(cfg.world_center_x + 10_000.0, cfg.world_center_y, 40.0)])
        edge = calc._compute_safety_penalties(
            [(cfg.world_center_x + cfg.area_bound, cfg.world_center_y, 40.0)])
        assert far == pytest.approx(edge)
        assert far <= cfg.boundary_penalty + 1e-9


class TestMovementPenalty:

    def test_large_movements_cost_more_than_small_ones(self):
        calc = RewardCalculator()
        assert calc._compute_movement_penalty([5.0] * 5) > calc._compute_movement_penalty([1.0] * 5)

    def test_penalty_is_never_negative(self):
        """The hover bonus is subtracted from the penalty; it must not turn the
        penalty into a reward for standing still."""
        calc = RewardCalculator()
        assert calc._compute_movement_penalty([0.0] * 5) >= 0.0

    def test_empty_movement_list_is_free(self):
        assert RewardCalculator()._compute_movement_penalty([]) == 0.0


class TestProximityShaping:

    def test_closer_to_the_disaster_zone_scores_higher(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        at_centre = calc._compute_proximity_reward(
            [(cfg.world_center_x, cfg.world_center_y, 40.0)])
        far = calc._compute_proximity_reward(
            [(cfg.world_center_x + 200.0, cfg.world_center_y, 40.0)])
        assert at_centre > far
        assert at_centre == pytest.approx(cfg.proximity_weight)

    def test_proximity_reward_floors_at_zero(self):
        cfg = RewardConfig()
        calc = RewardCalculator(cfg)
        assert calc._compute_proximity_reward(
            [(cfg.world_center_x + 10_000.0, cfg.world_center_y, 40.0)]) == 0.0

    def test_no_drones_yields_no_proximity_reward(self):
        assert RewardCalculator()._compute_proximity_reward([]) == 0.0


class TestConfigurability:

    def test_weights_are_honoured(self):
        """Retuning is done through RewardConfig; a weight that is ignored makes
        every sweep silently meaningless."""
        loud = RewardCalculator(RewardConfig(coverage_weight=10.0))
        quiet = RewardCalculator(RewardConfig(coverage_weight=1.0))
        assert loud._compute_coverage_reward(50.0) > quiet._compute_coverage_reward(50.0)

    def test_world_centre_is_shared_between_reward_terms(self):
        """rewards.py and spaces.py both hardcode the disaster centroid; if they
        drift apart the clip and the penalty disagree about where 'inside' is."""
        from aura_strategic_rl.spaces import ActionConfig
        r, a = RewardConfig(), ActionConfig()
        assert (r.world_center_x, r.world_center_y) == (a.world_center_x, a.world_center_y)
        assert r.area_bound == a.area_bound
        assert (r.min_altitude, r.max_altitude) == (a.min_altitude, a.max_altitude)
