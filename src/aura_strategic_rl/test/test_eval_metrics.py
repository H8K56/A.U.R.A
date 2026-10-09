#!/usr/bin/env python3
"""Metric logic in scripts/evaluate.py (roadmap §12).

The eval script is how every later change gets measured against the frozen
baseline, so its arithmetic needs to be as trustworthy as the thing it is
measuring. These tests pin the fault analysis in particular, because the
obvious implementation reports "recovered in 0.0 s" for a fault that did
nothing at all.
"""

import importlib.util
import os

import numpy as np
import pytest


def _load_evaluate_module():
    """Load scripts/evaluate.py by path — it is a script, not an installed
    module, and it must stay runnable straight from a checkout."""
    here = os.path.dirname(os.path.abspath(__file__))
    repo_root = os.path.abspath(os.path.join(here, '..', '..', '..'))
    path = os.path.join(repo_root, 'scripts', 'evaluate.py')
    if not os.path.exists(path):
        pytest.skip(f'evaluate.py not found at {path}')
    spec = importlib.util.spec_from_file_location('aura_evaluate', path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


ev = _load_evaluate_module()


def steady(value, n):
    return [float(value)] * n


class TestNoFaultInjected:

    def test_nothing_reported_without_a_fault(self):
        r = ev.fault_metrics(steady(20.0, 50), [True] * 50, fault_index=None)
        assert r['fault_injected'] is False
        assert r['fault_degraded'] is False
        assert r['fault_recovery_steps'] is None

    def test_fault_index_past_the_end_is_ignored(self):
        r = ev.fault_metrics(steady(20.0, 10), [True] * 10, fault_index=99)
        assert r['fault_injected'] is False


class TestFaultWithNoEffect:
    """The case that caught a real bug: the drone is gone but nothing changed."""

    def test_unchanged_coverage_is_not_degradation(self):
        cov = steady(20.0, 60)
        r = ev.fault_metrics(cov, [True] * 60, fault_index=30)
        assert r['fault_injected'] is True
        assert r['fault_degraded'] is False

    def test_recovery_is_undefined_not_zero(self):
        """"Recovered in 0.0 s" would be a lie here — there was nothing to
        recover from."""
        r = ev.fault_metrics(steady(20.0, 60), [True] * 60, fault_index=30)
        assert r['fault_recovered'] is False
        assert r['fault_recovery_steps'] is None

    def test_a_dip_inside_tolerance_is_not_degradation(self):
        cov = steady(20.0, 30) + steady(19.0, 30)  # -5%, inside the 10% band
        r = ev.fault_metrics(cov, [True] * 60, fault_index=30)
        assert r['fault_degraded'] is False
        assert r['coverage_drop_pct'] == pytest.approx(5.0)


class TestCoverageDegradation:

    def test_a_real_drop_is_degradation(self):
        cov = steady(20.0, 30) + steady(10.0, 30)  # -50%
        r = ev.fault_metrics(cov, [True] * 60, fault_index=30)
        assert r['fault_degraded'] is True
        assert r['coverage_drop_pct'] == pytest.approx(50.0)

    def test_recovery_time_is_measured_from_the_fault(self):
        # Drops at 30, back above 18.0 from index 40 onward.
        cov = steady(20.0, 30) + steady(10.0, 10) + steady(20.0, 30)
        r = ev.fault_metrics(cov, [True] * 70, fault_index=30)
        assert r['fault_degraded'] is True
        assert r['fault_recovered'] is True
        assert r['fault_recovery_steps'] == 10

    def test_unrecovered_fault_reports_no_recovery(self):
        cov = steady(20.0, 30) + steady(5.0, 30)
        r = ev.fault_metrics(cov, [True] * 60, fault_index=30)
        assert r['fault_degraded'] is True
        assert r['fault_recovered'] is False
        assert r['fault_recovery_steps'] is None

    def test_a_single_good_step_does_not_count_as_recovery(self):
        """Coverage fluctuates while drones reposition; recovery must hold."""
        cov = (steady(20.0, 30) + steady(10.0, 5) + [20.0]
               + steady(10.0, 20))
        r = ev.fault_metrics(cov, [True] * len(cov), fault_index=30)
        assert r['fault_recovered'] is False

    def test_a_sustained_run_does_count(self):
        cov = steady(20.0, 30) + steady(10.0, 5) + steady(20.0, 10)
        r = ev.fault_metrics(cov, [True] * len(cov), fault_index=30)
        assert r['fault_recovered'] is True
        assert r['fault_recovery_steps'] == 5


class TestConnectivityDegradation:

    def test_losing_the_mesh_is_degradation_even_at_full_coverage(self):
        """A partitioned mesh is a failure regardless of how much ground the
        fragments still cover — relaying is the point of the system."""
        connected = [True] * 30 + [False] * 10 + [True] * 20
        r = ev.fault_metrics(steady(20.0, 60), connected, fault_index=30)
        assert r['fault_degraded'] is True
        assert r['connectivity_lost'] is True

    def test_recovery_requires_the_mesh_back(self):
        connected = [True] * 30 + [False] * 10 + [True] * 20
        r = ev.fault_metrics(steady(20.0, 60), connected, fault_index=30)
        assert r['fault_recovered'] is True
        assert r['fault_recovery_steps'] == 10

    def test_coverage_alone_cannot_mask_a_partition(self):
        connected = [True] * 30 + [False] * 30
        r = ev.fault_metrics(steady(20.0, 60), connected, fault_index=30)
        assert r['fault_recovered'] is False


class TestEpisodeSummary:

    def _episode(self, coverage, connected, fault_index=None, batteries=None):
        n = len(coverage)
        return {
            'seed': 1,
            'steps': n,
            'fault_index': fault_index,
            'series': {
                'coverage_percent': coverage,
                'snr_db': steady(30.0, n),
                'throughput_mbps': steady(50.0, n),
                'latency_ms': steady(10.0, n),
                'mesh_connected': connected,
                'battery_mean': batteries or list(np.linspace(100.0, 90.0, n)),
                'num_active_drones': [5] * n,
                'reward': steady(1.0, n),
            },
        }

    def test_energy_is_battery_actually_consumed(self):
        ep = self._episode(steady(20.0, 10), [True] * 10)
        s = ev.summarise_episode(ep, dt=0.5)
        assert s['energy_used_pct'] == pytest.approx(10.0)

    def test_coverage_per_energy_divides_by_consumption(self):
        ep = self._episode(steady(20.0, 10), [True] * 10)
        s = ev.summarise_episode(ep, dt=0.5)
        assert s['coverage_per_energy'] == pytest.approx(2.0)

    def test_zero_energy_does_not_divide_by_zero(self):
        ep = self._episode(steady(20.0, 10), [True] * 10,
                           batteries=steady(100.0, 10))
        s = ev.summarise_episode(ep, dt=0.5)
        assert np.isnan(s['coverage_per_energy'])

    def test_connectivity_fraction_is_time_connected(self):
        ep = self._episode(steady(20.0, 10), [True] * 7 + [False] * 3)
        s = ev.summarise_episode(ep, dt=0.5)
        assert s['connectivity_fraction'] == pytest.approx(0.7)

    def test_recovery_seconds_use_the_env_timestep(self):
        cov = steady(20.0, 30) + steady(10.0, 10) + steady(20.0, 30)
        ep = self._episode(cov, [True] * 70, fault_index=30)
        s = ev.summarise_episode(ep, dt=0.5)
        assert s['fault_recovery_s'] == pytest.approx(10 * 0.5)

    def test_final_and_mean_coverage_are_both_reported(self):
        """Training logs final-step coverage; reporting only the mean would
        make the two incomparable."""
        ep = self._episode(list(np.linspace(0.0, 40.0, 11)), [True] * 11)
        s = ev.summarise_episode(ep, dt=0.5)
        assert s['coverage_final_pct'] == pytest.approx(40.0)
        assert s['coverage_mean_pct'] == pytest.approx(20.0)


class TestAggregation:

    def _row(self, **over):
        row = {
            'seed': 0, 'steps': 10, 'coverage_mean_pct': 20.0,
            'coverage_final_pct': 25.0, 'snr_mean_db': 30.0,
            'throughput_mean_mbps': 50.0, 'latency_mean_ms': 10.0,
            'connectivity_fraction': 1.0, 'energy_used_pct': 5.0,
            'coverage_per_energy': 4.0, 'reward_total': 100.0,
            'coverage_drop_pct': float('nan'), 'fault_recovery_s': float('nan'),
            'fault_injected': False, 'fault_degraded': False,
            'fault_recovered': False, 'connectivity_lost': False,
        }
        row.update(over)
        return row

    def test_rates_are_not_applicable_without_faults(self):
        agg = ev.aggregate([self._row(), self._row()])
        assert agg['fault_injected_episodes'] == 0
        assert np.isnan(agg['fault_degradation_rate'])
        assert np.isnan(agg['fault_recovery_rate'])

    def test_degradation_rate_is_over_injected_episodes(self):
        rows = [self._row(fault_injected=True, fault_degraded=True),
                self._row(fault_injected=True, fault_degraded=False)]
        agg = ev.aggregate(rows)
        assert agg['fault_degradation_rate'] == pytest.approx(0.5)

    def test_recovery_rate_is_conditional_on_degrading(self):
        """An episode that never degraded must not count as a failure to
        recover — that would understate resilience."""
        rows = [
            self._row(fault_injected=True, fault_degraded=True,
                      fault_recovered=True),
            self._row(fault_injected=True, fault_degraded=False),
        ]
        agg = ev.aggregate(rows)
        assert agg['fault_recovery_rate'] == pytest.approx(1.0)
        assert agg['fault_degraded_episodes'] == 1

    def test_nan_values_are_excluded_from_means(self):
        rows = [self._row(fault_recovery_s=2.0, fault_injected=True,
                          fault_degraded=True, fault_recovered=True),
                self._row(fault_injected=True, fault_degraded=True)]
        agg = ev.aggregate(rows)
        assert agg['fault_recovery_s_mean'] == pytest.approx(2.0)

    def test_all_nan_field_yields_nan_not_a_crash(self):
        agg = ev.aggregate([self._row(), self._row()])
        assert np.isnan(agg['fault_recovery_s_mean'])
