#!/usr/bin/env python3
"""Training and deployment must agree on how an action is interpreted.

strategic_rl_node loads a checkpoint trained by train_policy. Anything the
two sides scale differently silently changes the policy's behaviour at
deploy time without any error — the failure mode these tests exist to
prevent.
"""

import numpy as np
import pytest

from aura_strategic_rl.spaces import ActionConfig, ActionProcessor


def _node_module():
    """strategic_rl_node needs rclpy and the generated aura_msgs."""
    pytest.importorskip("rclpy")
    return pytest.importorskip("aura_strategic_rl.strategic_rl_node")


class TestActionScaleContract:

    def test_vertical_and_horizontal_scales_genuinely_differ(self):
        """The reason a single 'max move distance' constant is unsafe: one
        number cannot express both limits."""
        cfg = ActionConfig()
        assert cfg.max_delta_z != cfg.max_delta_xy

    def test_node_does_not_redeclare_movement_limits(self):
        """Regression: RLConfig once carried its own max_move_distance (2.0)
        and applied it to all three axes, so a deployed policy stepped 2.5x
        further vertically than the 0.8 m it was trained on. The limits must
        live only in ActionConfig."""
        mod = _node_module()
        for attr in ('max_move_distance', 'min_altitude', 'max_altitude'):
            assert not hasattr(mod.RLConfig, attr), (
                f"RLConfig.{attr} duplicates ActionConfig — training and "
                f"deployment can drift apart again")

    def test_node_uses_the_shared_action_processor(self):
        mod = _node_module()
        import inspect
        src = inspect.getsource(mod)
        assert 'ActionProcessor' in src, (
            "strategic_rl_node must convert actions with the same "
            "ActionProcessor training used")


class TestDeployedGoalsObeyTrainingBounds:
    """Whatever the node produces must satisfy the constraints the reward
    function penalises, otherwise inference is pushed into states training
    always treated as unsafe."""

    def test_goals_stay_within_the_operating_disk_and_altitude_band(self):
        cfg = ActionConfig()
        proc = ActionProcessor(cfg)
        centre = np.array([cfg.world_center_x, cfg.world_center_y])
        rng = np.random.default_rng(5)

        positions = [
            np.array([cfg.world_center_x, cfg.world_center_y, 40.0])
            for _ in range(cfg.num_drones)
        ]
        for _ in range(300):
            positions = proc.process(rng.uniform(-1, 1, cfg.action_dim), positions)
            for p in positions:
                assert cfg.min_altitude - 1e-6 <= p[2] <= cfg.max_altitude + 1e-6
                assert np.linalg.norm(p[:2] - centre) <= cfg.area_bound + 1e-6

    def test_world_centre_is_configurable_for_retraining(self):
        """Retraining against a different disaster centroid must move the clip
        with it rather than falling back to the hardcoded default. (At
        inference the node deliberately keeps the trained centre and warns if
        rl_target disagrees, rather than re-centring under a live policy.)"""
        cfg = ActionConfig(num_drones=1, world_center_x=0.0, world_center_y=0.0)
        proc = ActionProcessor(cfg)
        far = np.array([cfg.area_bound + 1000.0, 0.0, 40.0])
        goal = proc.process(np.zeros(3), [far])[0]
        assert np.linalg.norm(goal[:2]) == pytest.approx(cfg.area_bound)
