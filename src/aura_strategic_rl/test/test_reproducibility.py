#!/usr/bin/env python3
"""Determinism guarantees for RL training runs (roadmap A.4).

A result that cannot be regenerated cannot be defended, so the seeding path
is tested directly rather than by re-running training.
"""

import numpy as np
import pytest

from aura_strategic_rl.swarm_gym_env import EnvConfig, SwarmGymEnv


def make_env(seed=None):
    return SwarmGymEnv(
        config=EnvConfig(num_drones=5, max_steps=50,
                        randomize_initial_positions=True,
                        randomize_weather=True, weather_probability=0.5),
        seed=seed,
    )


class TestEnvSeeding:

    def test_same_seed_gives_identical_reset(self):
        a, _ = make_env(7).reset()
        b, _ = make_env(7).reset()
        np.testing.assert_array_equal(a, b)

    def test_different_seeds_give_different_resets(self):
        a, _ = make_env(7).reset()
        b, _ = make_env(8).reset()
        assert not np.array_equal(a, b)

    def test_reset_seed_argument_overrides_constructor_seed(self):
        env = make_env(1)
        a, _ = env.reset(seed=99)
        b, _ = make_env(99).reset()
        np.testing.assert_array_equal(a, b)

    def test_parallel_envs_do_not_share_a_stream(self):
        """train_policy runs several envs at once. If they drew from the global
        numpy stream, seeding one would reseed them all and rollouts would stop
        being reproducible."""
        envs = [make_env(100 + i) for i in range(4)]
        first = [e.reset()[0] for e in envs]

        # Reseeding one env must not disturb the others' streams.
        envs[0].reset(seed=12345)
        again = [e.reset()[0] for e in envs[1:]]

        fresh = [make_env(100 + i) for i in range(1, 4)]
        for e in fresh:
            e.reset()
        expected = [e.reset()[0] for e in fresh]
        for got, want in zip(again, expected):
            np.testing.assert_array_equal(got, want)

    def test_global_numpy_stream_is_untouched(self):
        """Seeding an env must not hijack np.random for the rest of the process
        — PPO's minibatch shuffle draws from it."""
        np.random.seed(0)
        before = np.random.random(5)

        np.random.seed(0)
        make_env(42).reset()
        after = np.random.random(5)

        np.testing.assert_array_equal(before, after)

    def test_unseeded_envs_still_work(self):
        obs, _ = make_env(None).reset()
        assert np.all(np.isfinite(obs))


class TestEpisodeDeterminism:

    def test_identical_action_sequences_give_identical_trajectories(self):
        rng = np.random.default_rng(3)
        actions = [rng.uniform(-1, 1, 15) for _ in range(20)]

        def rollout(seed):
            env = make_env(seed)
            env.reset()
            out = []
            for a in actions:
                obs, reward, term, trunc, _ = env.step(a)
                out.append((obs.copy(), reward))
                if term or trunc:
                    break
            return out

        for (o1, r1), (o2, r2) in zip(rollout(21), rollout(21)):
            np.testing.assert_array_equal(o1, o2)
            assert r1 == r2


class TestTrainingSeedHelper:

    def test_set_global_seeds_makes_torch_and_numpy_repeat(self):
        torch = pytest.importorskip("torch")
        from aura_strategic_rl.train_policy import set_global_seeds

        set_global_seeds(5)
        t1, n1 = torch.randn(4), np.random.random(4)
        set_global_seeds(5)
        t2, n2 = torch.randn(4), np.random.random(4)

        assert torch.equal(t1, t2)
        np.testing.assert_array_equal(n1, n2)

    def test_run_config_captures_what_is_needed_to_repeat_a_run(self):
        """training_log.json holds metrics only; run_config.json is what makes
        a run reproducible, so its key fields are pinned."""
        pytest.importorskip("torch")
        import argparse
        import json
        import tempfile

        from aura_strategic_rl.train_policy import PPOTrainer, save_run_config

        args = argparse.Namespace(
            timesteps=1024, num_drones=5, num_envs=1, n_steps=64,
            batch_size=16, n_epochs=1, gamma=0.99, lr=3e-4, ent_coef=0.01,
            weather=False, seed=42, deterministic=False, device='cpu',
            save_path='',
        )
        trainer = PPOTrainer(num_drones=5, num_envs=1, n_steps=64,
                             batch_size=16, n_epochs=1, device='cpu', seed=42)

        with tempfile.TemporaryDirectory() as d:
            with open(save_run_config(args, trainer, d)) as f:
                cfg = json.load(f)

        for key in ('seed', 'git_revision', 'torch_version', 'numpy_version',
                    'device', 'args', 'obs_dim', 'action_dim',
                    'env_config', 'reward_config'):
            assert key in cfg, f"run_config.json is missing {key}"
        assert cfg['seed'] == 42
        assert cfg['obs_dim'] == 184
        assert cfg['action_dim'] == 15


class TestBaselineSeeding:

    def test_hho_baseline_is_reproducible(self):
        """The Hungarian/HHO baselines are what PPO is measured against; an
        unseeded baseline makes the comparison unrepeatable."""
        from aura_strategic_rl.baseline_hho import HHOConfig, HarrisHawksOptimizer

        cfg = HHOConfig()
        a = HarrisHawksOptimizer(cfg, num_drones=5, seed=11)
        b = HarrisHawksOptimizer(cfg, num_drones=5, seed=11)
        a.initialize_population()
        b.initialize_population()
        np.testing.assert_array_equal(a.population, b.population)

    def test_hho_different_seeds_differ(self):
        from aura_strategic_rl.baseline_hho import HHOConfig, HarrisHawksOptimizer

        cfg = HHOConfig()
        a = HarrisHawksOptimizer(cfg, num_drones=5, seed=11)
        b = HarrisHawksOptimizer(cfg, num_drones=5, seed=12)
        a.initialize_population()
        b.initialize_population()
        assert not np.array_equal(a.population, b.population)
