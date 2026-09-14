#!/usr/bin/env python3
"""Observation/action space invariants for the strategic RL policy.

The 184-D observation and 15-D action shapes are a contract between
train_policy, the checkpoint and strategic_rl_node — a checkpoint trained
against one layout loads silently against another and produces garbage, so
the dimensions are pinned here.
"""

import numpy as np
import pytest

from aura_strategic_rl.spaces import (
    ActionConfig,
    ActionProcessor,
    ObservationConfig,
)


class TestObservationDimensions:

    def test_default_observation_is_184_dim(self):
        # 5 drones x 13 + 100 coverage cells + 4 network + 3 x 5 weather
        assert ObservationConfig().total_obs_dim == 184

    def test_per_drone_observation_is_13_dim(self):
        assert ObservationConfig().drone_obs_dim == 13

    @pytest.mark.parametrize("num_drones", [1, 3, 5, 8, 10])
    def test_dimension_scales_linearly_with_swarm_size(self, num_drones):
        cfg = ObservationConfig(num_drones=num_drones)
        fixed = 10 ** 2 + 4 + 3 * 5
        assert cfg.total_obs_dim == num_drones * 13 + fixed


class TestActionDimensions:

    def test_default_action_is_15_dim(self):
        assert ActionConfig().action_dim == 15

    @pytest.mark.parametrize("num_drones", [1, 3, 5, 8, 10])
    def test_three_dimensions_per_drone(self, num_drones):
        assert ActionConfig(num_drones=num_drones).action_dim == num_drones * 3


class TestActionClipping:
    """A policy emits tanh-squashed values in [-1, 1]; the processor must turn
    those into goals that always satisfy the altitude and area constraints."""

    def setup_method(self):
        self.cfg = ActionConfig()
        self.proc = ActionProcessor(self.cfg)
        self.center = np.array([self.cfg.world_center_x, self.cfg.world_center_y])

    def _start_positions(self, n=5, alt=40.0):
        return [np.array([self.cfg.world_center_x + 10.0 * i,
                          self.cfg.world_center_y,
                          alt]) for i in range(n)]

    def test_returns_one_goal_per_drone(self):
        goals = self.proc.process(np.zeros(15), self._start_positions())
        assert len(goals) == 5
        assert all(g.shape == (3,) for g in goals)

    def test_zero_action_holds_position(self):
        starts = self._start_positions()
        goals = self.proc.process(np.zeros(15), starts)
        for start, goal in zip(starts, goals):
            np.testing.assert_allclose(goal, start, atol=1e-9)

    def test_max_action_moves_exactly_the_step_limit(self):
        starts = self._start_positions()
        goals = self.proc.process(np.ones(15), starts)
        for start, goal in zip(starts, goals):
            assert goal[0] - start[0] == pytest.approx(self.cfg.max_delta_xy)
            assert goal[1] - start[1] == pytest.approx(self.cfg.max_delta_xy)
            assert goal[2] - start[2] == pytest.approx(self.cfg.max_delta_z)

    def test_per_step_displacement_is_bounded(self):
        """No single action may move a drone further than the configured limit."""
        rng = np.random.default_rng(0)
        starts = self._start_positions()
        for _ in range(200):
            raw = rng.uniform(-1.0, 1.0, 15)
            for start, goal in zip(starts, self.proc.process(raw, starts)):
                assert abs(goal[0] - start[0]) <= self.cfg.max_delta_xy + 1e-9
                assert abs(goal[1] - start[1]) <= self.cfg.max_delta_xy + 1e-9
                assert abs(goal[2] - start[2]) <= self.cfg.max_delta_z + 1e-9

    def test_altitude_clipped_to_bounds_from_below(self):
        starts = [np.array([self.cfg.world_center_x, self.cfg.world_center_y,
                            self.cfg.min_altitude])]
        cfg = ActionConfig(num_drones=1)
        goals = ActionProcessor(cfg).process(np.array([0.0, 0.0, -1.0]), starts)
        assert goals[0][2] == pytest.approx(cfg.min_altitude)

    def test_altitude_clipped_to_bounds_from_above(self):
        starts = [np.array([self.cfg.world_center_x, self.cfg.world_center_y,
                            self.cfg.max_altitude])]
        cfg = ActionConfig(num_drones=1)
        goals = ActionProcessor(cfg).process(np.array([0.0, 0.0, 1.0]), starts)
        assert goals[0][2] == pytest.approx(cfg.max_altitude)

    def test_goal_never_leaves_the_operating_disk(self):
        """Start outside the area bound and push further out: the circular clip
        must pull the goal back onto the boundary."""
        cfg = ActionConfig(num_drones=1)
        proc = ActionProcessor(cfg)
        far = np.array([cfg.world_center_x + cfg.area_bound + 500.0,
                        cfg.world_center_y, 40.0])
        goal = proc.process(np.array([1.0, 0.0, 0.0]), [far])[0]
        dist = np.linalg.norm(goal[:2] - self.center)
        assert dist <= cfg.area_bound + 1e-6

    def test_circular_clip_preserves_bearing(self):
        """Clipping must scale the radius, not square off the corner — a
        direction change would put the drone somewhere the policy never chose."""
        cfg = ActionConfig(num_drones=1)
        proc = ActionProcessor(cfg)
        offset = np.array([300.0, 400.0])  # 500 m out, 3-4-5 bearing
        far = np.array([cfg.world_center_x + offset[0],
                        cfg.world_center_y + offset[1], 40.0])
        goal = proc.process(np.zeros(3), [far])[0]
        clipped = goal[:2] - self.center
        assert np.linalg.norm(clipped) == pytest.approx(cfg.area_bound)
        # Same unit vector as the unclipped offset
        np.testing.assert_allclose(clipped / np.linalg.norm(clipped),
                                   offset / np.linalg.norm(offset), atol=1e-9)

    def test_clipped_goals_are_reachable_under_repeated_extreme_actions(self):
        """Drive the swarm with saturated actions for many steps and confirm
        constraints hold at every step, not just the first."""
        cfg = ActionConfig()
        proc = ActionProcessor(cfg)
        positions = self._start_positions()
        raw = np.tile([1.0, 1.0, 1.0], 5)
        for _ in range(500):
            positions = proc.process(raw, positions)
            for p in positions:
                assert cfg.min_altitude - 1e-6 <= p[2] <= cfg.max_altitude + 1e-6
                assert np.linalg.norm(p[:2] - self.center) <= cfg.area_bound + 1e-6

    def test_missing_current_positions_falls_back_to_delta(self):
        """process() tolerates fewer positions than drones; the goal is then the
        bare delta, which must still be clipped into the disk."""
        cfg = ActionConfig(num_drones=2)
        proc = ActionProcessor(cfg)
        goals = proc.process(np.ones(6), [])
        assert len(goals) == 2
        for g in goals:
            assert np.linalg.norm(g[:2] - self.center) <= cfg.area_bound + 1e-6
