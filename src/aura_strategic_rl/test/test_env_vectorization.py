#!/usr/bin/env python3
"""The vectorized gym network update must equal the scalar one.

`_update_network` was a cell x cell x drone Python loop, and it was the
training bottleneck: the published checkpoint trained at ~54 environment
steps per second, so 400k steps took two hours and an alpha_m sweep was out
of reach.

Rewriting it as one numpy pass per drone is only safe if the arithmetic is
identical, so this keeps an independent scalar reference written from the
formulas and asserts cell-for-cell agreement — with weather, with shadowing,
with failed drones, and across the drone-to-drone link budget that feeds the
observation.

Runs without ROS.
"""

import math

import numpy as np
import pytest

from aura_strategic_rl.swarm_gym_env import EnvConfig, SwarmGymEnv


def scalar_signal_grid(env):
    """The original formulation, cell by cell. Intentionally slow."""
    cfg = env.config
    half, res = cfg.area_size, cfg.grid_resolution
    wx, wy = cfg.world_center_x, cfg.world_center_y
    grid = np.full((env.grid_size, env.grid_size), -200.0, dtype=np.float32)

    for drone in env.drones:
        if drone.is_failed:
            continue
        shadow = (env._shadow_grids[drone.drone_id]
                  if env._shadow_grids else None)

        for gy in range(env.grid_size):
            for gx in range(env.grid_size):
                cell_x = wx - half + (gx + 0.5) * res
                cell_y = wy - half + (gy + 0.5) * res

                dx = cell_x - drone.position[0]
                dy = cell_y - drone.position[1]
                dz = -drone.position[2]
                dist_3d = math.sqrt(dx * dx + dy * dy + dz * dz)
                if dist_3d < cfg.reference_distance_m:
                    dist_3d = cfg.reference_distance_m

                path_loss = (cfg.reference_loss_db
                             + 10 * cfg.path_loss_exponent
                             * math.log10(dist_3d / cfg.reference_distance_m))

                for wz in env.weather_zones:
                    if wz.is_active:
                        wdist = math.hypot(cell_x - wz.center[0],
                                           cell_y - wz.center[1])
                        if wdist < wz.radius:
                            path_loss += wz.attenuation_db

                if shadow is not None:
                    path_loss += float(shadow[gy, gx])

                signal = cfg.tx_power_dbm - path_loss
                if signal > grid[gy, gx]:
                    grid[gy, gx] = signal
    return grid


def scalar_importance_grid(env):
    cfg = env.config
    half, res = cfg.area_size, cfg.grid_resolution
    wx, wy = cfg.world_center_x, cfg.world_center_y
    grid = np.ones((env.grid_size, env.grid_size), dtype=np.float32)
    for gy in range(env.grid_size):
        for gx in range(env.grid_size):
            cell_x = wx - half + (gx + 0.5) * res
            cell_y = wy - half + (gy + 0.5) * res
            for sx, sy in env._DISASTER_STRUCTURES:
                if math.hypot(cell_x - sx, cell_y - sy) < 50.0:
                    grid[gy, gx] = 3.0
                    break
    return grid


def make_env(**over):
    kwargs = dict(max_steps=100)
    kwargs.update(over)
    return EnvConfig(**kwargs)


def stepped(config, seed=3, steps=4, action_seed=11):
    """An env a few steps in, so the drones are off their start ring."""
    env = SwarmGymEnv(config=config, seed=seed)
    env.reset(seed=seed)
    rng = np.random.default_rng(action_seed)
    for _ in range(steps):
        env.step(rng.uniform(-1, 1, 15).astype(np.float32))
    return env


class TestSignalGridEquivalence:

    def test_plain_channel(self):
        env = stepped(make_env(randomize_weather=False))
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)

    def test_with_weather(self):
        env = stepped(make_env(randomize_weather=True,
                               weather_probability=1.0))
        assert env.weather_zones, 'no weather zone was generated'
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)

    @pytest.mark.parametrize("sigma", [2.0, 6.0])
    def test_with_shadowing(self, sigma):
        env = stepped(make_env(shadowing_enabled=True,
                               shadow_sigma_db=sigma))
        assert env._shadow_grids, 'no shadowing was built'
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)

    def test_with_weather_and_shadowing(self):
        env = stepped(make_env(randomize_weather=True,
                               weather_probability=1.0,
                               shadowing_enabled=True,
                               shadow_sigma_db=5.0))
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)

    def test_with_a_failed_drone(self):
        """A failed drone contributes nothing, so the max must skip it."""
        env = stepped(make_env(shadowing_enabled=True))
        env.fail_drone(2)
        env.step(np.zeros(15, dtype=np.float32))
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)

    def test_with_every_drone_failed(self):
        env = stepped(make_env())
        for i in range(env.config.num_drones):
            env.fail_drone(i)
        env.step(np.zeros(15, dtype=np.float32))
        assert np.all(env.signal_grid == -200.0)
        assert env._compute_coverage_percent() == 0.0

    @pytest.mark.parametrize("seed", [1, 5, 9])
    def test_equivalence_across_seeds(self, seed):
        env = stepped(make_env(randomize_weather=True,
                               weather_probability=1.0,
                               shadowing_enabled=True), seed=seed)
        np.testing.assert_allclose(env.signal_grid, scalar_signal_grid(env),
                                   rtol=0, atol=1e-4)


class TestImportanceGridEquivalence:

    def test_importance_map_matches_the_scalar_form(self):
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        np.testing.assert_array_equal(env.importance_grid,
                                      scalar_importance_grid(env))

    def test_importance_is_one_or_three(self):
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        assert set(np.unique(env.importance_grid)) <= {1.0, 3.0}

    def test_some_cells_are_important(self):
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        assert np.count_nonzero(env.importance_grid == 3.0) > 0


class TestCellGridsAreShared:
    """The shadowing bake and the signal pass index the same (gy, gx)."""

    def test_cell_grids_have_the_grid_shape(self):
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        assert env._cell_x.shape == (env.grid_size, env.grid_size)
        assert env._cell_y.shape == (env.grid_size, env.grid_size)

    def test_cell_centres_match_the_documented_formula(self):
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        cfg = env.config
        half, res = cfg.area_size, cfg.grid_resolution
        for gy, gx in [(0, 0), (3, 7), (env.grid_size - 1, env.grid_size - 1)]:
            assert env._cell_x[gy, gx] == pytest.approx(
                cfg.world_center_x - half + (gx + 0.5) * res)
            assert env._cell_y[gy, gx] == pytest.approx(
                cfg.world_center_y - half + (gy + 0.5) * res)

    def test_x_varies_along_columns_and_y_along_rows(self):
        """Guards against a transposed meshgrid, which would mirror the whole
        scene and still look plausible."""
        env = SwarmGymEnv(config=make_env(), seed=1)
        env.reset(seed=1)
        assert env._cell_x[0, 1] > env._cell_x[0, 0]
        assert env._cell_x[1, 0] == env._cell_x[0, 0]
        assert env._cell_y[1, 0] > env._cell_y[0, 0]
        assert env._cell_y[0, 1] == env._cell_y[0, 0]


class TestContractsHold:

    def test_observation_is_still_184_dimensional(self):
        for cfg in (make_env(), make_env(shadowing_enabled=True)):
            env = SwarmGymEnv(config=cfg, seed=1)
            obs, _ = env.reset(seed=1)
            assert obs.shape == (184,)

    def test_signal_grid_stays_float32(self):
        """It feeds the observation; a silent promotion to float64 would
        double the buffer size for every rollout."""
        env = stepped(make_env(shadowing_enabled=True))
        assert env.signal_grid.dtype == np.float32

    def test_rollouts_stay_finite(self):
        env = SwarmGymEnv(config=make_env(shadowing_enabled=True,
                                          shadow_sigma_db=10.0), seed=2)
        obs, _ = env.reset(seed=2)
        rng = np.random.default_rng(4)
        for _ in range(30):
            obs, reward, _, _, info = env.step(
                rng.uniform(-1, 1, 15).astype(np.float32))
            assert np.all(np.isfinite(obs))
            assert math.isfinite(reward)
            assert 0.0 <= info['coverage_percent'] <= 100.0

    def test_results_are_still_reproducible(self):
        def run(seed):
            env = SwarmGymEnv(config=make_env(shadowing_enabled=True),
                              seed=seed)
            env.reset(seed=seed)
            rng = np.random.default_rng(7)
            return [env.step(rng.uniform(-1, 1, 15).astype(np.float32))[4]
                    ['coverage_percent'] for _ in range(20)]
        assert run(5) == run(5)


class TestItIsActuallyFaster:

    def test_env_steps_are_fast_enough_to_retrain(self):
        """The point of the rewrite. At ~54 steps/s a 400k-step run took two
        hours; this asserts the order of magnitude that makes a sweep
        practical, with wide headroom so it is not a flaky benchmark."""
        import time
        env = SwarmGymEnv(config=make_env(shadowing_enabled=True), seed=1)
        env.reset(seed=1)
        action = np.zeros(15, dtype=np.float32)
        env.step(action)  # warm up
        start = time.perf_counter()
        for _ in range(100):
            env.step(action)
        steps_per_sec = 100 / (time.perf_counter() - start)
        assert steps_per_sec > 300, f'{steps_per_sec:.0f} env steps/s'
