#!/usr/bin/env python3
"""Drone-failure behaviour in SwarmGymEnv.

The N-1 fault-tolerance claim and the eval script's fault-recovery metric both
depend on a drone being able to drop out mid-episode. These tests pin what that
does — and, just as importantly, that an episode with no failures behaves
exactly as it did before the mechanism existed.
"""

import numpy as np
import pytest

from aura_strategic_rl.swarm_gym_env import EnvConfig, SwarmGymEnv


def make_env(seed=7, weather=False):
    return SwarmGymEnv(
        config=EnvConfig(num_drones=5, max_steps=200,
                        randomize_initial_positions=True,
                        randomize_weather=weather,
                        weather_probability=0.0 if not weather else 0.5),
        seed=seed,
    )


class TestNoFailuresChangesNothing:
    """The mechanism must be inert until someone injects a fault."""

    def test_all_drones_active_after_reset(self):
        env = make_env()
        _, info = env.reset()
        assert info['num_active_drones'] == 5
        assert info['failed_drone_ids'] == []
        assert all(not d.is_failed for d in env.drones)

    def test_reset_clears_previous_failures(self):
        env = make_env()
        env.reset()
        env.fail_drone(2)
        assert env.drones[2].is_failed
        _, info = env.reset()
        assert info['failed_drone_ids'] == []
        assert all(not d.is_failed for d in env.drones)

    def test_connectivity_still_requires_every_drone_when_none_failed(self):
        """Original semantics: with no failures, one stranded drone means the
        mesh is not connected."""
        env = make_env()
        env.reset()
        env.drones[4].position = np.array([10_000.0, 10_000.0, 40.0])
        env._update_network()
        assert env._check_mesh_connected() is False

    def test_active_set_is_every_drone_when_none_failed(self):
        env = make_env()
        env.reset()
        assert len(env._active_drones()) == len(env.drones)

    def test_rollout_is_unchanged_and_deterministic(self):
        """Two identical seeds with no faults must produce identical
        trajectories — the fault plumbing must not perturb the RNG or the
        physics."""
        rng = np.random.default_rng(0)
        actions = [rng.uniform(-1, 1, 15) for _ in range(30)]

        def rollout():
            env = make_env(seed=11)
            env.reset()
            out = []
            for a in actions:
                obs, reward, _, _, info = env.step(a)
                out.append((obs.copy(), reward, info['coverage_percent']))
            return out

        for (o1, r1, c1), (o2, r2, c2) in zip(rollout(), rollout()):
            np.testing.assert_array_equal(o1, o2)
            assert r1 == r2 and c1 == c2


class TestFailingADrone:

    def test_failed_drone_is_reported(self):
        env = make_env()
        env.reset()
        env.fail_drone(3)
        info = env._get_info()
        assert info['failed_drone_ids'] == [3]
        assert info['num_active_drones'] == 4

    def test_failed_drone_stops_moving(self):
        env = make_env()
        env.reset()
        env.fail_drone(1)
        before = env.drones[1].position.copy()
        for _ in range(10):
            env.step(np.ones(15))  # saturated: a live drone would travel
        np.testing.assert_array_equal(env.drones[1].position, before)
        np.testing.assert_array_equal(env.drones[1].velocity, np.zeros(3))

    def test_failed_drone_stops_relaying(self):
        env = make_env()
        env.reset()
        env.fail_drone(2)
        assert env.drones[2].neighbors == []
        for d in env.drones:
            assert 2 not in d.neighbors

    def test_failed_drone_reports_no_link(self):
        env = make_env()
        env.reset()
        env.fail_drone(0)
        d = env.drones[0]
        assert d.throughput_mbps == 0.0
        assert d.signal_strength_dbm == -100.0
        assert d.latency_ms == 999.0

    def test_failed_drone_stops_providing_coverage(self):
        """Park the swarm tightly on the disaster centre, then remove one: the
        covered area must shrink."""
        env = make_env()
        env.reset()
        cx, cy = env.config.world_center_x, env.config.world_center_y
        for i, d in enumerate(env.drones):
            d.position = np.array([cx + 40.0 * i, cy, 40.0])
        env._update_network()
        before = env._compute_coverage_percent()

        env.fail_drone(4)
        after = env._compute_coverage_percent()
        assert after < before

    def test_failed_drone_does_not_drain_battery(self):
        env = make_env()
        env.reset()
        env.fail_drone(1)
        battery = env.drones[1].battery
        for _ in range(20):
            env.step(np.ones(15))
        assert env.drones[1].battery == battery

    def test_surviving_swarm_can_still_be_connected(self):
        """A drone failing must not by itself mark the mesh partitioned — that
        is the whole N-1 claim."""
        env = make_env()
        env.reset()
        cx, cy = env.config.world_center_x, env.config.world_center_y
        for i, d in enumerate(env.drones):
            d.position = np.array([cx + 20.0 * i, cy, 40.0])
        env._update_network()
        assert env._check_mesh_connected() is True

        env.fail_drone(4)  # outermost drone
        assert env._check_mesh_connected() is True

    def test_losing_a_relay_can_partition_the_survivors(self):
        """Strung out in a line, removing the middle hop must be detected as a
        partition — otherwise the metric would never report a real failure."""
        cfg = EnvConfig(num_drones=5, randomize_initial_positions=False,
                        randomize_weather=False)
        env = SwarmGymEnv(config=cfg, seed=3)
        env.reset()
        cx, cy = cfg.world_center_x, cfg.world_center_y
        spacing = cfg.max_mesh_distance * 0.9  # neighbours only
        for i, d in enumerate(env.drones):
            d.position = np.array([cx + spacing * i, cy, 40.0])
        env._update_network()
        assert env._check_mesh_connected() is True

        env.fail_drone(2)  # middle of the chain
        assert env._check_mesh_connected() is False

    def test_averages_ignore_the_failed_drone(self):
        """A dead drone reporting -100 dBm and 999 ms must not be averaged into
        the surviving swarm's reported quality."""
        env = make_env()
        env.reset()
        cx, cy = env.config.world_center_x, env.config.world_center_y
        for i, d in enumerate(env.drones):
            d.position = np.array([cx + 20.0 * i, cy, 40.0])
        env._update_network()

        env.fail_drone(4)
        assert env._compute_avg_latency() < 999.0
        assert env._compute_avg_throughput() > 0.0
        assert all(d.drone_id != 4 for d in env._active_drones())

    def test_all_drones_failed_falls_back_rather_than_dividing_by_zero(self):
        env = make_env()
        env.reset()
        for i in range(5):
            env.fail_drone(i)
        assert np.isfinite(env._compute_avg_signal())
        assert np.isfinite(env._compute_avg_throughput())
        assert env._check_mesh_connected() is True  # nothing left to partition

    @pytest.mark.parametrize("bad_id", [-1, 5, 99])
    def test_out_of_range_drone_id_raises(self, bad_id):
        env = make_env()
        env.reset()
        with pytest.raises(IndexError):
            env.fail_drone(bad_id)


class TestRecovery:

    def test_recovered_drone_relays_again(self):
        env = make_env()
        env.reset()
        cx, cy = env.config.world_center_x, env.config.world_center_y
        for i, d in enumerate(env.drones):
            d.position = np.array([cx + 20.0 * i, cy, 40.0])
        env._update_network()

        env.fail_drone(3)
        assert env.drones[3].neighbors == []

        env.recover_drone(3)
        assert env.drones[3].neighbors != []
        assert env._get_info()['failed_drone_ids'] == []
        assert env._get_info()['num_active_drones'] == 5

    def test_recovered_drone_moves_again(self):
        env = make_env()
        env.reset()
        env.fail_drone(1)
        env.recover_drone(1)
        before = env.drones[1].position.copy()
        for _ in range(5):
            env.step(np.ones(15))
        assert not np.array_equal(env.drones[1].position, before)


class TestSnrMetric:

    def test_snr_is_signal_above_the_noise_floor(self):
        env = make_env()
        env.reset()
        expected = np.mean([
            d.signal_strength_dbm - env.config.noise_floor_dbm
            for d in env.drones
        ])
        assert env._compute_avg_snr_db() == pytest.approx(expected)

    def test_snr_is_exposed_in_info(self):
        env = make_env()
        _, info = env.reset()
        assert 'avg_snr_db' in info
        assert np.isfinite(info['avg_snr_db'])
