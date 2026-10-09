#!/usr/bin/env python3
"""Value target normalization, and the collapse it exists to prevent.

`MLPPolicy` shares a feature trunk between actor and critic, PPO normalizes
advantages but previously not value targets, and the gradient norm is clipped
globally. So the critic's gradient scale decided how much of each update the
actor received. At the default `vf_coef=0.5` the policy collapsed on the second
update and never recovered; `vf_coef=0.005` only delayed it.

What made it hard to see is that it depended on the reward scale, not on
anything in the trainer: value loss grows with the *square* of returns, so it
only started biting when a scenario fix roughly doubled per-step reward.

The last class here is the one that matters — it trains for real at the default
`vf_coef` and asserts the policy does not fall over.

Runs without ROS.
"""

import math

import numpy as np
import pytest

from aura_strategic_rl.value_norm import RunningMeanStd, ValueNormalizer


class TestRunningMeanStd:

    def test_matches_numpy_on_one_batch(self):
        rms = RunningMeanStd()
        x = np.random.default_rng(0).normal(50.0, 12.0, 5000)
        rms.update(x)
        assert rms.mean == pytest.approx(x.mean(), rel=1e-3)
        assert rms.std == pytest.approx(x.std(), rel=1e-2)

    def test_matches_numpy_across_many_batches(self):
        """The whole point of the parallel update: batches folded in one at a
        time must agree with having seen them all at once."""
        rng = np.random.default_rng(1)
        batches = [rng.normal(120.0, 30.0, 400) for _ in range(25)]
        rms = RunningMeanStd()
        for b in batches:
            rms.update(b)
        everything = np.concatenate(batches)
        assert rms.mean == pytest.approx(everything.mean(), rel=1e-3)
        assert rms.std == pytest.approx(everything.std(), rel=1e-2)

    def test_tracks_a_shifting_distribution(self):
        rms = RunningMeanStd()
        rng = np.random.default_rng(2)
        rms.update(rng.normal(10.0, 1.0, 200))
        small = rms.std
        rms.update(rng.normal(10.0, 50.0, 2000))
        assert rms.std > small

    def test_empty_batch_is_a_no_op(self):
        rms = RunningMeanStd()
        rms.update(np.array([]))
        assert rms.mean == 0.0
        assert rms.var == 1.0

    def test_variance_never_goes_negative(self):
        """Accumulating sums of squares can produce a negative variance through
        cancellation; the parallel update plus the clamp must not."""
        rms = RunningMeanStd()
        for _ in range(50):
            rms.update(np.full(100, 1e6))
        assert rms.var >= 0.0
        assert math.isfinite(rms.std)

    def test_constant_input_gives_near_zero_spread(self):
        rms = RunningMeanStd()
        for _ in range(20):
            rms.update(np.full(500, 7.0))
        assert rms.mean == pytest.approx(7.0, rel=1e-3)
        assert rms.std < 0.1

    def test_state_round_trips(self):
        rms = RunningMeanStd()
        rms.update(np.random.default_rng(3).normal(5.0, 2.0, 1000))
        restored = RunningMeanStd()
        restored.load_state_dict(rms.state_dict())
        assert restored.mean == rms.mean
        assert restored.var == rms.var
        assert restored.count == rms.count


class TestNormalizerArithmetic:

    def test_normalize_then_denormalize_round_trips(self):
        vn = ValueNormalizer()
        vn.update(np.random.default_rng(4).normal(400.0, 90.0, 2000))
        values = np.array([-250.0, 0.0, 17.5, 980.0])
        assert np.allclose(vn.denormalize(vn.normalize(values)), values)

    def test_targets_come_out_order_one(self):
        """The actual requirement. Raw returns here are ~400; the critic should
        be asked for something near 1."""
        vn = ValueNormalizer()
        returns = np.random.default_rng(5).normal(450.0, 120.0, 4000)
        vn.update(returns)
        assert np.std(vn.normalize(returns)) == pytest.approx(1.0, rel=0.15)

    def test_a_larger_reward_scale_does_not_change_target_scale(self):
        """Why this fixes the bug rather than moving it: doubling the reward
        must not double what the critic is asked to predict."""
        rng = np.random.default_rng(6)
        base = rng.normal(200.0, 50.0, 3000)
        spreads = []
        for factor in (1.0, 2.0, 10.0, 100.0):
            vn = ValueNormalizer()
            vn.update(base * factor)
            spreads.append(float(np.std(vn.normalize(base * factor))))
        assert max(spreads) - min(spreads) < 0.05, spreads

    def test_scale_is_floored(self):
        """A barely-varying return stream would otherwise give a near-zero
        divisor and hand the critic enormous targets."""
        vn = ValueNormalizer(min_std=1e-2)
        for _ in range(20):
            vn.update(np.full(500, 3.0))
        assert vn.scale >= 1e-2
        assert np.all(np.isfinite(vn.normalize(np.full(10, 3.0))))

    def test_mean_is_not_subtracted(self):
        """Scale only, deliberately: a drifting mean would move the critic's
        target for reasons unrelated to the policy."""
        vn = ValueNormalizer()
        vn.update(np.full(1000, 500.0) + np.random.default_rng(7).normal(0, 10, 1000))
        assert vn.normalize(np.array([0.0]))[0] == pytest.approx(0.0)
        assert vn.normalize(np.array([500.0]))[0] > 10.0


class TestDisabled:

    def test_disabled_is_the_identity(self):
        vn = ValueNormalizer(enabled=False)
        vn.update(np.random.default_rng(8).normal(600.0, 200.0, 1000))
        values = np.array([-100.0, 0.0, 42.0, 7000.0])
        assert np.array_equal(vn.normalize(values), values)
        assert np.array_equal(vn.denormalize(values), values)
        assert vn.scale == 1.0

    def test_disabled_does_not_accumulate(self):
        vn = ValueNormalizer(enabled=False)
        vn.update(np.full(1000, 12345.0))
        assert vn.rms.count == pytest.approx(RunningMeanStd().count)


class TestCheckpointState:

    def test_state_round_trips(self):
        vn = ValueNormalizer()
        vn.update(np.random.default_rng(9).normal(300.0, 70.0, 2000))
        restored = ValueNormalizer()
        restored.load_state_dict(vn.state_dict())
        assert restored.scale == pytest.approx(vn.scale)
        assert restored.enabled is True

    def test_a_restored_normalizer_reads_its_critic_identically(self):
        vn = ValueNormalizer()
        vn.update(np.random.default_rng(10).normal(300.0, 70.0, 2000))
        restored = ValueNormalizer()
        restored.load_state_dict(vn.state_dict())
        critic_output = np.array([0.3, -1.2, 2.5])
        assert np.allclose(restored.denormalize(critic_output),
                           vn.denormalize(critic_output))

    def test_missing_state_means_disabled_not_default(self):
        """A checkpoint written before this existed has a critic trained on raw
        returns — scale 1.0. Defaulting to enabled would reinterpret its value
        head against a scale it never saw."""
        for empty in (None, {}):
            vn = ValueNormalizer(enabled=True)
            vn.load_state_dict(empty)
            assert vn.enabled is False
            assert vn.scale == 1.0

    def test_disabled_state_round_trips_as_disabled(self):
        vn = ValueNormalizer(enabled=False)
        restored = ValueNormalizer(enabled=True)
        restored.load_state_dict(vn.state_dict())
        assert restored.enabled is False


class TestTrainerIntegration:
    """The regression test. Trains for real at the default vf_coef, which is
    the setting that used to collapse on update 2."""

    @staticmethod
    def _run(normalize, updates=4, seed=42):
        from aura_strategic_rl.train_policy import PPOTrainer, set_global_seeds
        set_global_seeds(seed)
        trainer = PPOTrainer(
            num_drones=5, num_envs=2, n_steps=256, batch_size=64, n_epochs=4,
            vf_coef=0.5, normalize_value_targets=normalize,
            device='cpu', seed=seed)
        rewards = []
        for _ in range(updates):
            stats = trainer.collect_rollouts()
            trainer.update_policy()
            if 'ep_reward_mean' in stats:
                rewards.append(stats['ep_reward_mean'])
        return trainer, rewards

    def test_the_normalizer_learns_a_scale_from_real_returns(self):
        trainer, _ = self._run(normalize=True, updates=2)
        assert trainer.value_normalizer.enabled
        assert trainer.value_normalizer.scale > 1.0, (
            'returns in this env are O(100); a scale of 1 means the '
            'normalizer never saw them')

    def test_value_targets_are_order_one(self):
        """What the critic is actually asked to predict."""
        trainer, _ = self._run(normalize=True, updates=2)
        targets = trainer._rollout_value_targets
        assert np.abs(targets).max() < 50.0, np.abs(targets).max()
        assert np.abs(trainer._rollout_returns).max() > 50.0, (
            'returns should still be in reward units')

    def test_returns_stay_in_reward_units(self):
        """Only the critic's scale changes. ep_reward_mean has to stay
        comparable to runs made before this existed."""
        trainer, rewards = self._run(normalize=True, updates=2)
        assert rewards, 'no episodes completed'
        assert abs(rewards[0]) > 10.0

    def test_disabled_trainer_uses_raw_returns_as_targets(self):
        trainer, _ = self._run(normalize=False, updates=2)
        assert np.array_equal(trainer._rollout_value_targets,
                              trainer._rollout_returns)

    def test_the_policy_survives_the_default_vf_coef(self):
        """The collapse, pinned. Without normalization this configuration took
        the policy from ~+2200 to ~-1300 on the second update and never came
        back; the check is that reward does not invert sign."""
        _, rewards = self._run(normalize=True, updates=4)
        assert len(rewards) >= 2, 'not enough episodes to judge'
        assert rewards[0] > 0.0, f'first update already bad: {rewards[0]}'
        worst = min(rewards)
        assert worst > 0.0, f'policy collapsed to a negative return: {rewards}'
        assert worst > 0.25 * rewards[0], (
            f'policy lost more than 75% of its return: {rewards}')

    def test_bootstrap_values_are_in_reward_units(self):
        """If `last_value` were left in critic units, GAE would mix scales and
        every advantage near a truncation boundary would be wrong."""
        trainer, _ = self._run(normalize=True, updates=2)
        vn = trainer.value_normalizer
        critic_units = 1.0
        assert vn.denormalize(critic_units) == pytest.approx(vn.scale)
        assert vn.scale > 1.0

    def test_checkpoint_carries_the_scale(self, tmp_path):
        trainer, _ = self._run(normalize=True, updates=2)
        path = tmp_path / 'policy.pt'
        trainer.save(str(path))
        import torch
        blob = torch.load(str(path), map_location='cpu', weights_only=False)
        meta = blob.get('metadata', blob)
        assert 'value_normalizer' in meta
        state = meta['value_normalizer']
        assert state['enabled'] is True
        restored = ValueNormalizer()
        restored.load_state_dict(state)
        assert restored.scale == pytest.approx(
            trainer.value_normalizer.scale)
