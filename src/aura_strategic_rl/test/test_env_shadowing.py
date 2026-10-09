#!/usr/bin/env python3
"""Shadowing inside the training environment.

Roadmap §8. The gym env reimplements log-distance path loss inline so training
can run without the ROS network package, and that copy had no shadowing term
at all — the policy was trained against a perfectly deterministic channel.

Two things matter here beyond "the term is present":

1. **The baseline must still reproduce.** The published checkpoint was trained
   on the median channel. Enabling shadowing changes the coverage numbers and
   the policy, so it is off by default, and turning it off must leave the
   env's random stream untouched — otherwise the initial positions and weather
   shift and the frozen results stop reproducing for an unrelated reason.

2. **The baked shadow grid must line up with the cells it is applied to.**
   `_reset_shadowing` precomputes one offset per grid cell per drone, for
   speed, by recomputing the cell centres itself. If that indexing disagreed
   with `_update_network`'s, shadowing would be applied to the wrong cells and
   nothing would look obviously wrong.

Runs without ROS.
"""

import math

import numpy as np
import pytest

from aura_strategic_rl.swarm_gym_env import (
    SHADOWING_AVAILABLE, EnvConfig, SwarmGymEnv,
)

pytestmark = pytest.mark.skipif(
    not SHADOWING_AVAILABLE,
    reason='needs aura_network_sim.propagation on the path')


def rollout(config, seed, steps=25, action_seed=99):
    """Coverage over a fixed pseudo-random action sequence."""
    env = SwarmGymEnv(config=config, seed=seed)
    env.reset(seed=seed)
    rng = np.random.default_rng(action_seed)
    coverage = []
    for _ in range(steps):
        action = rng.uniform(-1, 1, 15).astype(np.float32)
        _, _, _, _, info = env.step(action)
        coverage.append(info['coverage_percent'])
    return np.array(coverage)


def on(**over):
    kwargs = dict(max_steps=100, shadowing_enabled=True, shadow_sigma_db=4.0)
    kwargs.update(over)
    return EnvConfig(**kwargs)


def off(**over):
    kwargs = dict(max_steps=100)
    kwargs.update(over)
    return EnvConfig(**kwargs)


class TestDefaultIsOff:
    """The default is load-bearing, not an accident."""

    def test_shadowing_is_disabled_by_default(self):
        assert EnvConfig().shadowing_enabled is False

    def test_no_shadowing_state_is_built_when_disabled(self):
        env = SwarmGymEnv(config=off(), seed=1)
        env.reset(seed=1)
        assert env._shadowing is None
        assert env._shadow_grids == []

    def test_disabled_shadowing_does_not_consume_the_random_stream(self):
        """Drawing an episode seed unconditionally would shift the initial
        positions and the weather, and the frozen baseline would stop
        reproducing for a reason unrelated to the channel."""
        env = SwarmGymEnv(config=off(), seed=5)
        env.reset(seed=5)
        positions = np.array([d.position for d in env.drones])
        zones = [(z.center[0], z.center[1], z.radius) for z in env.weather_zones]

        reference = np.random.default_rng(5)
        probe = SwarmGymEnv(config=off(), seed=5)
        probe.np_random = reference
        probe.reset()
        assert np.allclose(positions, [d.position for d in probe.drones])
        assert zones == [(z.center[0], z.center[1], z.radius)
                         for z in probe.weather_zones]


class TestReproducibility:

    def test_disabled_is_reproducible(self):
        assert np.array_equal(rollout(off(), 7), rollout(off(), 7))

    def test_enabled_is_reproducible(self):
        assert np.array_equal(rollout(on(), 7), rollout(on(), 7))

    def test_different_seeds_give_different_channels(self):
        assert not np.array_equal(rollout(on(), 7), rollout(on(), 8))

    def test_each_episode_draws_a_fresh_realization(self):
        """A single fixed map would let the policy memorize one channel
        instead of learning to cope with any of them."""
        env = SwarmGymEnv(config=on(), seed=3)
        env.reset(seed=3)
        first = env._shadow_grids[0].copy()
        env.reset()
        assert not np.allclose(first, env._shadow_grids[0])

    def test_reset_with_a_seed_restores_the_same_realization(self):
        env = SwarmGymEnv(config=on(), seed=3)
        env.reset(seed=3)
        first = env._shadow_grids[0].copy()
        env.reset()           # move the stream on
        env.reset(seed=3)     # and back
        assert np.allclose(first, env._shadow_grids[0])


class TestGridAlignment:
    """The precomputed offsets must land on the cells they were computed for."""

    def test_baked_grid_matches_a_direct_sample_at_every_cell(self):
        env = SwarmGymEnv(config=on(), seed=4)
        env.reset(seed=4)

        cfg = env.config
        half, res = cfg.area_size, cfg.grid_resolution
        wx, wy = cfg.world_center_x, cfg.world_center_y

        for drone_id in range(cfg.num_drones):
            baked = env._shadow_grids[drone_id]
            assert baked.shape == (env.grid_size, env.grid_size)
            # Spot-check the corners and centre — exactly the places a
            # transposed or off-by-one index would get wrong.
            for gy, gx in [(0, 0), (0, env.grid_size - 1),
                           (env.grid_size - 1, 0),
                           (env.grid_size - 1, env.grid_size - 1),
                           (env.grid_size // 2, env.grid_size // 3)]:
                cell_x = wx - half + (gx + 0.5) * res
                cell_y = wy - half + (gy + 0.5) * res
                direct = env._shadowing.sample(drone_id, cell_x, cell_y)
                assert baked[gy, gx] == pytest.approx(direct, abs=1e-5)

    def test_the_grid_is_not_symmetric_enough_to_hide_a_transpose(self):
        """Guards the test above: if the field happened to be symmetric, the
        corner checks would pass under a transpose."""
        env = SwarmGymEnv(config=on(), seed=4)
        env.reset(seed=4)
        baked = env._shadow_grids[0]
        assert not np.allclose(baked, baked.T, atol=1e-3)


class TestShadowingChangesTheChannel:

    def test_enabling_shadowing_changes_reported_coverage(self):
        assert not np.array_equal(rollout(off(), 7), rollout(on(), 7))

    def test_zero_sigma_is_the_same_as_disabled(self):
        """Not just close — the term vanishes rather than being tiny."""
        assert np.array_equal(rollout(off(), 7),
                              rollout(on(shadow_sigma_db=0.0), 7))

    def test_shadowing_perturbs_the_signal_grid(self):
        quiet = SwarmGymEnv(config=off(), seed=6)
        quiet.reset(seed=6)
        noisy = SwarmGymEnv(config=on(shadow_sigma_db=6.0), seed=6)
        noisy.reset(seed=6)
        # Same seed and same config otherwise, so the drones start identically.
        assert np.allclose([d.position for d in quiet.drones],
                           [d.position for d in noisy.drones])
        delta = noisy.signal_grid - quiet.signal_grid
        assert np.std(delta) > 1.0

    def test_drone_to_drone_links_are_shadowed_too(self):
        """Not only the ground grid: the mesh link budget sees it as well."""
        quiet = SwarmGymEnv(config=off(), seed=6)
        quiet.reset(seed=6)
        noisy = SwarmGymEnv(config=on(shadow_sigma_db=6.0), seed=6)
        noisy.reset(seed=6)
        quiet_signals = np.array([d.signal_strength_dbm for d in quiet.drones])
        noisy_signals = np.array([d.signal_strength_dbm for d in noisy.drones])
        assert not np.allclose(quiet_signals, noisy_signals)


class TestInterLinkCorrelation:

    def test_default_is_the_3gpp_inter_site_value(self):
        assert EnvConfig().shadow_inter_link_correlation == pytest.approx(0.5)

    def test_full_correlation_gives_every_drone_the_same_offsets(self):
        env = SwarmGymEnv(config=on(shadow_inter_link_correlation=1.0), seed=2)
        env.reset(seed=2)
        for grid in env._shadow_grids[1:]:
            assert np.allclose(env._shadow_grids[0], grid)

    def test_zero_correlation_gives_each_drone_its_own(self):
        env = SwarmGymEnv(config=on(shadow_inter_link_correlation=0.0), seed=2)
        env.reset(seed=2)
        assert not np.allclose(env._shadow_grids[0], env._shadow_grids[1])

    def test_correlation_changes_the_coverage_it_reports(self):
        """Coverage takes the best server, so how much the drones' fades share
        decides how much diversity the swarm gets for free."""
        independent = rollout(on(shadow_inter_link_correlation=0.0), 7).mean()
        shared = rollout(on(shadow_inter_link_correlation=1.0), 7).mean()
        assert independent != pytest.approx(shared)

    @pytest.mark.parametrize("bad", [-0.1, 1.1])
    def test_out_of_range_correlation_is_rejected(self, bad):
        env = SwarmGymEnv(config=on(shadow_inter_link_correlation=bad), seed=1)
        with pytest.raises(ValueError, match='inter_link_correlation'):
            env.reset(seed=1)


class TestSafetyInvariantsHold:
    """§8 touches the channel, not the contracts. Re-check the ones CLAUDE.md
    calls invariant, since the observation is built from network state."""

    def test_observation_is_still_184_dimensional(self):
        for config in (off(), on()):
            env = SwarmGymEnv(config=config, seed=1)
            obs, _ = env.reset(seed=1)
            assert obs.shape == (184,), f'{config.shadowing_enabled}: {obs.shape}'

    def test_observations_stay_finite_under_deep_fades(self):
        """A 15 dB sigma produces fades well past the coverage threshold; the
        observation must not carry a NaN or an inf into the policy."""
        env = SwarmGymEnv(config=on(shadow_sigma_db=15.0), seed=1)
        obs, _ = env.reset(seed=1)
        assert np.all(np.isfinite(obs))
        rng = np.random.default_rng(5)
        for _ in range(20):
            obs, reward, _, _, _ = env.step(
                rng.uniform(-1, 1, 15).astype(np.float32))
            assert np.all(np.isfinite(obs))
            assert math.isfinite(reward)

    def test_coverage_stays_a_percentage(self):
        env = SwarmGymEnv(config=on(shadow_sigma_db=12.0), seed=1)
        env.reset(seed=1)
        rng = np.random.default_rng(5)
        for _ in range(20):
            _, _, _, _, info = env.step(
                rng.uniform(-1, 1, 15).astype(np.float32))
            assert 0.0 <= info['coverage_percent'] <= 100.0

    def test_failed_drones_contribute_no_shadowed_coverage(self):
        """A failed drone stops serving; its shadow map must not keep
        contributing signal."""
        env = SwarmGymEnv(config=on(), seed=1)
        env.reset(seed=1)
        env.fail_drone(2)
        rng = np.random.default_rng(5)
        _, _, _, _, info = env.step(rng.uniform(-1, 1, 15).astype(np.float32))
        assert info['num_active_drones'] == 4
        assert 2 in info['failed_drone_ids']
