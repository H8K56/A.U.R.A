#!/usr/bin/env python3
"""A.U.R.A. standardized evaluation — roadmap §12.

Runs seeded episodes in SwarmGymEnv and reports the metrics the paper and the
roadmap care about, so any change to the stack can be measured against the
frozen baseline rather than eyeballed:

    coverage · SNR · throughput · connectivity · energy · fault recovery

Every run writes run_config.json (seed, git revision, library versions, full
env/reward config) next to its results, for the same reason train_policy does:
a number you cannot regenerate is not a result.

Usage
-----
    # Compare the trained policy against the heuristic baseline
    python3 scripts/evaluate.py --policies rl,baseline --episodes 20

    # Measure fault recovery: kill drone 2 at step 100
    python3 scripts/evaluate.py --policies rl --fault-step 100 --fault-drone 2

    # Quick smoke run (used by CI)
    python3 scripts/evaluate.py --policies static --episodes 2 --max-steps 40 \
        --no-plots

A note on SINR: the roadmap asks for SINR, but the propagation model has no
interference term (roadmap §8), so what is reported here is SNR. Calling it
SINR would overstate what the model computes. When §8 lands, add the
interference term and rename the metric then.
"""

import argparse
import csv
import json
import os
import subprocess
import sys
from dataclasses import asdict
from datetime import datetime, timezone
from typing import Callable, Dict, List, Optional

import numpy as np

# Keep the ROS-independent path importable when run straight from the repo.
_REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for _pkg in ('aura_strategic_rl',):
    _candidate = os.path.join(_REPO_ROOT, 'src', _pkg)
    if _candidate not in sys.path:
        sys.path.insert(0, _candidate)

from aura_strategic_rl.swarm_gym_env import EnvConfig, SwarmGymEnv  # noqa: E402


# ── Policies ────────────────────────────────────────────────────────────────

class Policy:
    """Minimal adapter so every policy is driven the same way."""

    name = 'policy'

    def reset(self) -> None:
        pass

    def act(self, obs: np.ndarray, env: SwarmGymEnv) -> np.ndarray:
        raise NotImplementedError


class StaticPolicy(Policy):
    """Hold station. The control case — any policy worth training should beat
    it, and if it does not that is the finding."""

    name = 'static'

    def __init__(self, action_dim: int):
        self.action_dim = action_dim

    def act(self, obs, env):
        return np.zeros(self.action_dim)


class RandomPolicy(Policy):
    """Uniform random actions — the noise floor for every metric."""

    name = 'random'

    def __init__(self, action_dim: int, seed: int):
        self.action_dim = action_dim
        self.rng = np.random.default_rng(seed)

    def act(self, obs, env):
        return self.rng.uniform(-1.0, 1.0, self.action_dim)


class HeuristicPolicy(Policy):
    """The non-learned spread heuristic `strategic_rl_node` falls back to when
    `use_baseline` is set, so this is what the RL policy is replacing."""

    name = 'baseline'

    def __init__(self, num_drones: int, action_dim: int):
        from aura_strategic_rl.policy import BaselinePolicy
        self._impl = BaselinePolicy(num_drones=num_drones, action_dim=action_dim)

    def reset(self):
        self._impl.step_count = 0

    def act(self, obs, env):
        action, _, _ = self._impl.get_action(obs, deterministic=True)
        return np.asarray(action, dtype=np.float64)


class TrainedPolicy(Policy):
    """A PPO checkpoint, driven deterministically (mean action, no sampling)."""

    name = 'rl'

    def __init__(self, path: str, device: str = 'cpu'):
        import torch
        from aura_strategic_rl.policy import PolicyCheckpoint

        self._torch = torch
        self.policy, self.metadata = PolicyCheckpoint.load(path, device=device)
        self.policy.eval()
        self.device = device
        self.path = path

    def act(self, obs, env):
        torch = self._torch
        with torch.no_grad():
            obs_t = torch.FloatTensor(obs).unsqueeze(0).to(self.device)
            action, _, _ = self.policy.get_action(obs_t, deterministic=True)
        return action.squeeze(0).cpu().numpy()


DEFAULT_POLICY_PATHS = {
    5: 'models/rl_5drones_newworld/best_policy.pt',
    4: 'models/rl_4drones_newworld_v2/best_policy.pt',
    3: 'models/rl_3drones/best_policy.pt',
}


def build_policy(name: str, args, env: SwarmGymEnv, seed: int) -> Policy:
    action_dim = env.action_config.action_dim
    if name == 'static':
        return StaticPolicy(action_dim)
    if name == 'random':
        return RandomPolicy(action_dim, seed)
    if name == 'baseline':
        return HeuristicPolicy(args.num_drones, action_dim)
    if name == 'rl':
        path = args.policy_path or os.path.join(
            _REPO_ROOT, DEFAULT_POLICY_PATHS.get(args.num_drones, ''))
        if not path or not os.path.exists(path):
            raise FileNotFoundError(
                f"No policy checkpoint for {args.num_drones} drones at {path!r}. "
                f"Pass --policy-path explicitly.")
        policy = TrainedPolicy(path, device=args.device)
        expected = env.obs_config.total_obs_dim
        got = policy.metadata.get('obs_dim')
        if got is not None and got != expected:
            raise ValueError(
                f"Checkpoint {path} expects obs_dim {got}, but this "
                f"configuration builds {expected}. Evaluating it would compare "
                f"a policy against observations it never saw.")
        return policy
    raise ValueError(f"Unknown policy {name!r}")


# ── Episode rollout ─────────────────────────────────────────────────────────

def run_episode(env: SwarmGymEnv, policy: Policy, seed: int,
                max_steps: int,
                fault_step: Optional[int] = None,
                fault_drone: int = 0) -> Dict:
    """One seeded episode, returning per-step series plus the fault timing."""
    policy.reset()
    obs, info = env.reset(seed=seed)

    series = {
        'coverage_percent': [],
        'snr_db': [],
        'throughput_mbps': [],
        'latency_ms': [],
        'mesh_connected': [],
        'battery_mean': [],
        'num_active_drones': [],
        'reward': [],
    }

    def record(inf: Dict, reward: float) -> None:
        series['coverage_percent'].append(float(inf['coverage_percent']))
        series['snr_db'].append(float(inf['avg_snr_db']))
        series['throughput_mbps'].append(float(inf['avg_throughput_mbps']))
        series['latency_ms'].append(float(inf['avg_latency_ms']))
        series['mesh_connected'].append(bool(inf['mesh_connected']))
        series['battery_mean'].append(float(np.mean(inf['batteries'])))
        series['num_active_drones'].append(int(inf['num_active_drones']))
        series['reward'].append(float(reward))

    record(info, 0.0)
    fault_applied_at = None

    for step in range(1, max_steps + 1):
        if fault_step is not None and step == fault_step:
            env.fail_drone(fault_drone)
            fault_applied_at = len(series['coverage_percent'])

        action = policy.act(obs, env)
        obs, reward, terminated, truncated, info = env.step(action)
        record(info, reward)

        if terminated or truncated:
            break

    return {
        'seed': seed,
        'series': series,
        'fault_index': fault_applied_at,
        'steps': len(series['coverage_percent']),
    }


# ── Metrics ─────────────────────────────────────────────────────────────────

def fault_metrics(coverage: List[float], connected: List[bool],
                  fault_index: Optional[int],
                  pre_window: int = 10,
                  recovery_fraction: float = 0.9,
                  hold: int = 5) -> Dict:
    """Characterise what losing a drone actually did, and how long it lasted.

    Degradation first, recovery second — and the distinction matters. A naive
    implementation reports "recovered in 0.0 s" when the swarm never degraded
    at all, which reads like fast recovery but means the fault had no
    measurable effect. Those are completely different findings, so they are
    reported as different fields.

    Degraded means the mesh partitioned, or coverage fell below
    `recovery_fraction` of its pre-fault level, at any point after the fault.
    Recovered means connected and back above that level for `hold` consecutive
    steps — the hold filters out a single lucky step while drones reposition.
    """
    blank = {
        'fault_injected': False, 'fault_degraded': False,
        'fault_recovered': False, 'fault_recovery_steps': None,
        'coverage_drop_pct': float('nan'),
        'connectivity_lost': False,
    }
    if fault_index is None or fault_index >= len(coverage):
        return blank

    start = max(0, fault_index - pre_window)
    pre_fault = coverage[start:fault_index]
    if not pre_fault:
        return blank
    baseline = float(np.mean(pre_fault))
    target = baseline * recovery_fraction

    after_cov = coverage[fault_index:]
    after_con = connected[fault_index:]

    worst = min(after_cov) if after_cov else baseline
    drop_pct = (baseline - worst) / baseline * 100.0 if baseline > 1e-9 else 0.0
    connectivity_lost = not all(after_con)
    degraded = connectivity_lost or worst < target

    result = dict(blank)
    result.update({
        'fault_injected': True,
        'fault_degraded': bool(degraded),
        'coverage_drop_pct': float(drop_pct),
        'connectivity_lost': bool(connectivity_lost),
    })

    if not degraded:
        # Nothing to recover from; recovery time is undefined, not zero.
        return result

    run = 0
    for i in range(fault_index, len(coverage)):
        if connected[i] and coverage[i] >= target:
            run += 1
            if run >= hold:
                result['fault_recovered'] = True
                # Recovery began `hold - 1` steps before this one.
                result['fault_recovery_steps'] = (i - hold + 1) - fault_index
                return result
        else:
            run = 0
    return result


def summarise_episode(ep: Dict, dt: float) -> Dict:
    s = ep['series']
    battery = s['battery_mean']
    energy_used = battery[0] - battery[-1] if battery else 0.0
    coverage_mean = float(np.mean(s['coverage_percent']))

    fault = fault_metrics(
        s['coverage_percent'], s['mesh_connected'], ep['fault_index'])
    recovery = fault['fault_recovery_steps']

    return {
        'seed': ep['seed'],
        'steps': ep['steps'],
        'coverage_mean_pct': coverage_mean,
        'coverage_final_pct': float(s['coverage_percent'][-1]),
        'snr_mean_db': float(np.mean(s['snr_db'])),
        'throughput_mean_mbps': float(np.mean(s['throughput_mbps'])),
        'latency_mean_ms': float(np.mean(s['latency_ms'])),
        'connectivity_fraction': float(np.mean(s['mesh_connected'])),
        'energy_used_pct': float(energy_used),
        # Coverage per unit of battery spent — the "coverage per joule" proxy
        # roadmap §14 asks for, in the units this battery model actually has.
        'coverage_per_energy': (coverage_mean / energy_used
                                if energy_used > 1e-9 else float('nan')),
        'reward_total': float(np.sum(s['reward'])),
        'fault_recovery_s': (recovery * dt if recovery is not None else float('nan')),
        'coverage_drop_pct': fault['coverage_drop_pct'],
        'fault_injected': fault['fault_injected'],
        'fault_degraded': fault['fault_degraded'],
        'fault_recovered': fault['fault_recovered'],
        'connectivity_lost': fault['connectivity_lost'],
    }


AGGREGATE_FIELDS = [
    'coverage_mean_pct', 'coverage_final_pct', 'snr_mean_db',
    'throughput_mean_mbps', 'latency_mean_ms', 'connectivity_fraction',
    'energy_used_pct', 'coverage_per_energy', 'reward_total',
    'coverage_drop_pct', 'fault_recovery_s',
]


def aggregate(per_episode: List[Dict]) -> Dict:
    out = {'episodes': len(per_episode)}
    for field in AGGREGATE_FIELDS:
        values = np.array([e[field] for e in per_episode], dtype=float)
        finite = values[np.isfinite(values)]
        out[f'{field}_mean'] = float(np.mean(finite)) if finite.size else float('nan')
        out[f'{field}_std'] = float(np.std(finite)) if finite.size else float('nan')
    # Rates are conditional, and the conditions matter. Degradation rate is
    # over episodes where a fault was injected; recovery rate is over episodes
    # that actually degraded — recovering from nothing is not a result.
    injected = [e for e in per_episode if e['fault_injected']]
    degraded = [e for e in injected if e['fault_degraded']]
    out['fault_injected_episodes'] = len(injected)
    out['fault_degraded_episodes'] = len(degraded)
    out['fault_degradation_rate'] = (len(degraded) / len(injected)
                                     if injected else float('nan'))
    out['fault_recovery_rate'] = (
        float(np.mean([e['fault_recovered'] for e in degraded]))
        if degraded else float('nan'))
    out['connectivity_lost_rate'] = (
        float(np.mean([e['connectivity_lost'] for e in injected]))
        if injected else float('nan'))
    return out


# ── Reporting ───────────────────────────────────────────────────────────────

def git_revision() -> str:
    try:
        return subprocess.check_output(
            ['git', 'rev-parse', '--short', 'HEAD'],
            cwd=_REPO_ROOT, stderr=subprocess.DEVNULL).decode().strip()
    except (subprocess.CalledProcessError, OSError):
        return 'unknown'


def write_run_config(args, env: SwarmGymEnv, out_dir: str) -> str:
    cfg = {
        'timestamp_utc': datetime.now(timezone.utc).isoformat(),
        'git_revision': git_revision(),
        'python': sys.version.split()[0],
        'numpy_version': np.__version__,
        'args': vars(args),
        'env_config': asdict(env.config),
        'reward_config': asdict(env.reward_config),
        'obs_dim': env.obs_config.total_obs_dim,
        'action_dim': env.action_config.action_dim,
        'metric_notes': {
            'snr_db': 'SNR, not SINR: the propagation model has no '
                      'interference term (roadmap §8).',
            'energy_used_pct': 'Mean battery percentage consumed over the '
                               'episode; the battery model is optimistic '
                               '(roadmap §9).',
            'fault_recovery_s': 'Seconds from fault injection until the mesh '
                                'is connected and coverage is back to 90% of '
                                'its pre-fault level for 5 consecutive steps. '
                                'NaN means it never recovered.',
        },
    }
    try:
        import torch
        cfg['torch_version'] = torch.__version__
    except ImportError:
        cfg['torch_version'] = None

    path = os.path.join(out_dir, 'run_config.json')
    with open(path, 'w') as f:
        json.dump(cfg, f, indent=2, default=str)
    return path


def write_summary_csv(summaries: Dict[str, Dict], out_dir: str) -> str:
    path = os.path.join(out_dir, 'summary.csv')
    fields = ['policy', 'episodes'] + [
        f'{m}_{s}' for m in AGGREGATE_FIELDS for s in ('mean', 'std')
    ] + ['fault_injected_episodes', 'fault_degraded_episodes',
         'fault_degradation_rate', 'fault_recovery_rate',
         'connectivity_lost_rate']
    with open(path, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fields)
        writer.writeheader()
        for policy, agg in summaries.items():
            writer.writerow({'policy': policy, **{k: v for k, v in agg.items()
                                                  if k in fields}})
    return path


def print_table(summaries: Dict[str, Dict]) -> None:
    rows = [
        ('Coverage % (mean)', 'coverage_mean_pct_mean', 'coverage_mean_pct_std', '{:.1f}'),
        ('Coverage % (final)', 'coverage_final_pct_mean', 'coverage_final_pct_std', '{:.1f}'),
        ('SNR dB', 'snr_mean_db_mean', 'snr_mean_db_std', '{:.1f}'),
        ('Throughput Mbps', 'throughput_mean_mbps_mean', 'throughput_mean_mbps_std', '{:.1f}'),
        ('Connectivity', 'connectivity_fraction_mean', 'connectivity_fraction_std', '{:.3f}'),
        ('Energy used %', 'energy_used_pct_mean', 'energy_used_pct_std', '{:.2f}'),
        ('Coverage/energy', 'coverage_per_energy_mean', 'coverage_per_energy_std', '{:.1f}'),
        ('Coverage drop %', 'coverage_drop_pct_mean', 'coverage_drop_pct_std', '{:.1f}'),
        ('Fault recovery s', 'fault_recovery_s_mean', 'fault_recovery_s_std', '{:.1f}'),
    ]
    policies = list(summaries)
    width = max(18, max((len(p) for p in policies), default=0) + 2)

    print()
    print('  ' + 'Metric'.ljust(20) + ''.join(p.ljust(width) for p in policies))
    print('  ' + '-' * (20 + width * len(policies)))
    for label, mean_key, std_key, fmt in rows:
        cells = []
        for p in policies:
            mean, std = summaries[p].get(mean_key), summaries[p].get(std_key)
            if mean is None or not np.isfinite(mean):
                cells.append('—'.ljust(width))
            else:
                cells.append((fmt.format(mean) + ' ± ' + fmt.format(std)).ljust(width))
        print('  ' + label.ljust(20) + ''.join(cells))

    # Fault outcomes need words, not just numbers: "0.0 s recovery" and "never
    # degraded" are different findings that a mean cannot distinguish.
    if any(summaries[p].get('fault_injected_episodes') for p in policies):
        print()
        print('  ' + 'Fault outcome'.ljust(20)
              + ''.join(p.ljust(width) for p in policies))
        print('  ' + '-' * (20 + width * len(policies)))
        for label, key in (('degraded', 'fault_degradation_rate'),
                           ('recovered | degraded', 'fault_recovery_rate'),
                           ('lost connectivity', 'connectivity_lost_rate')):
            cells = []
            for p in policies:
                val = summaries[p].get(key)
                if val is None or not np.isfinite(val):
                    cells.append('n/a'.ljust(width))
                else:
                    cells.append(f'{val * 100:.0f}%'.ljust(width))
            print('  ' + label.ljust(20) + ''.join(cells))
        for p in policies:
            if summaries[p].get('fault_degraded_episodes') == 0 and \
                    summaries[p].get('fault_injected_episodes'):
                print(f'  note: {p} never degraded — the fault had no '
                      f'measurable effect, so recovery time is undefined.')
    print()


# ── Plots ───────────────────────────────────────────────────────────────────

def _band(ax, episodes, key, label):
    """Mean across episodes with a ±1σ band, truncated to the shortest run."""
    length = min(len(e['series'][key]) for e in episodes)
    data = np.array([e['series'][key][:length] for e in episodes], dtype=float)
    mean, std = data.mean(axis=0), data.std(axis=0)
    x = np.arange(length)
    line, = ax.plot(x, mean, label=label, linewidth=1.8)
    ax.fill_between(x, mean - std, mean + std, alpha=0.15, color=line.get_color())
    return line


def make_plots(results: Dict[str, List[Dict]], summaries: Dict[str, Dict],
               out_dir: str, dt: float) -> List[str]:
    import matplotlib
    matplotlib.use('Agg')  # headless: this runs in CI and over ssh
    import matplotlib.pyplot as plt

    written = []

    def save(fig, name):
        path = os.path.join(out_dir, name)
        fig.tight_layout()
        fig.savefig(path, dpi=130)
        plt.close(fig)
        written.append(path)

    # 1. Coverage over time
    fig, ax = plt.subplots(figsize=(8, 4.5))
    for policy, eps in results.items():
        _band(ax, eps, 'coverage_percent', policy)
    ax.set_xlabel('step')
    ax.set_ylabel('coverage (%)')
    ax.set_title('Coverage over time (mean ±1σ)')
    ax.legend()
    ax.grid(alpha=0.3)
    save(fig, 'coverage.png')

    # 2. Connectivity over time
    fig, ax = plt.subplots(figsize=(8, 4.5))
    for policy, eps in results.items():
        length = min(len(e['series']['mesh_connected']) for e in eps)
        data = np.array([e['series']['mesh_connected'][:length] for e in eps],
                        dtype=float)
        ax.plot(np.arange(length), data.mean(axis=0), label=policy, linewidth=1.8)
    ax.set_xlabel('step')
    ax.set_ylabel('fraction of episodes with mesh connected')
    ax.set_ylim(-0.05, 1.05)
    ax.set_title('Mesh connectivity over time')
    ax.legend()
    ax.grid(alpha=0.3)
    save(fig, 'connectivity.png')

    # 3. Network quality
    fig, axes = plt.subplots(1, 2, figsize=(11, 4.2))
    for policy, eps in results.items():
        _band(axes[0], eps, 'snr_db', policy)
        _band(axes[1], eps, 'throughput_mbps', policy)
    axes[0].set_xlabel('step')
    axes[0].set_ylabel('SNR (dB)')
    axes[0].set_title('SNR — no interference term modelled')
    axes[1].set_xlabel('step')
    axes[1].set_ylabel('throughput (Mbps)')
    axes[1].set_title('Mean throughput')
    for ax in axes:
        ax.legend()
        ax.grid(alpha=0.3)
    save(fig, 'network_quality.png')

    # 4. Energy
    fig, axes = plt.subplots(1, 2, figsize=(11, 4.2))
    for policy, eps in results.items():
        _band(axes[0], eps, 'battery_mean', policy)
    axes[0].set_xlabel('step')
    axes[0].set_ylabel('mean battery (%)')
    axes[0].set_title('Battery drain — model is optimistic (roadmap §9)')
    axes[0].legend()
    axes[0].grid(alpha=0.3)

    policies = list(summaries)
    values = [summaries[p]['coverage_per_energy_mean'] for p in policies]
    errors = [summaries[p]['coverage_per_energy_std'] for p in policies]
    axes[1].bar(policies, values, yerr=errors, capsize=4, alpha=0.85)
    axes[1].set_ylabel('coverage % per battery %')
    axes[1].set_title('Coverage per unit energy')
    axes[1].grid(alpha=0.3, axis='y')
    save(fig, 'energy.png')

    # 5. Fault recovery — only when a fault was actually injected
    faulted = {p: eps for p, eps in results.items()
               if any(e['fault_index'] is not None for e in eps)}
    if faulted:
        fig, ax = plt.subplots(figsize=(8, 4.5))
        for policy, eps in faulted.items():
            line = _band(ax, eps, 'coverage_percent', policy)
            idx = next(e['fault_index'] for e in eps
                       if e['fault_index'] is not None)
            ax.axvline(idx, color=line.get_color(), linestyle='--', alpha=0.7)
            mean_recovery = summaries[policy]['fault_recovery_s_mean']
            if np.isfinite(mean_recovery):
                ax.axvline(idx + mean_recovery / dt, color=line.get_color(),
                           linestyle=':', alpha=0.7)
        ax.set_xlabel('step')
        ax.set_ylabel('coverage (%)')
        ax.set_title('Fault recovery — dashed: drone lost, dotted: recovered')
        ax.legend()
        ax.grid(alpha=0.3)
        save(fig, 'fault_recovery.png')

    # 6. Summary comparison
    metrics = [
        ('coverage_mean_pct', 'Coverage %'),
        ('connectivity_fraction', 'Connectivity'),
        ('throughput_mean_mbps', 'Throughput Mbps'),
        ('snr_mean_db', 'SNR dB'),
    ]
    fig, axes = plt.subplots(1, len(metrics), figsize=(4 * len(metrics), 4))
    for ax, (key, label) in zip(np.atleast_1d(axes), metrics):
        vals = [summaries[p][f'{key}_mean'] for p in policies]
        errs = [summaries[p][f'{key}_std'] for p in policies]
        ax.bar(policies, vals, yerr=errs, capsize=4, alpha=0.85)
        ax.set_title(label)
        ax.grid(alpha=0.3, axis='y')
        ax.tick_params(axis='x', rotation=20)
    save(fig, 'summary.png')

    return written


# ── Main ────────────────────────────────────────────────────────────────────

def evaluate(args) -> Dict:
    from aura_strategic_rl.train_policy import set_global_seeds
    set_global_seeds(args.seed)

    env_config = EnvConfig(
        num_drones=args.num_drones,
        max_steps=args.max_steps,
        randomize_initial_positions=True,
        randomize_weather=args.weather,
        weather_probability=0.5 if args.weather else 0.0,
    )

    os.makedirs(args.output_dir, exist_ok=True)

    results: Dict[str, List[Dict]] = {}
    summaries: Dict[str, Dict] = {}
    per_episode_tables: Dict[str, List[Dict]] = {}

    for policy_name in args.policies:
        env = SwarmGymEnv(config=env_config, seed=args.seed)
        policy = build_policy(policy_name, args, env, args.seed)

        episodes, rows = [], []
        for i in range(args.episodes):
            # Distinct but reproducible seed per episode, shared across
            # policies so they face identical scenarios.
            ep = run_episode(
                env, policy, seed=args.seed + i, max_steps=args.max_steps,
                fault_step=args.fault_step, fault_drone=args.fault_drone)
            episodes.append(ep)
            rows.append(summarise_episode(ep, env_config.dt))
            print(f"  {policy_name}: episode {i + 1}/{args.episodes} "
                  f"coverage={rows[-1]['coverage_mean_pct']:.1f}% "
                  f"connectivity={rows[-1]['connectivity_fraction']:.2f}")

        results[policy_name] = episodes
        per_episode_tables[policy_name] = rows
        summaries[policy_name] = aggregate(rows)

    cfg_path = write_run_config(args, SwarmGymEnv(config=env_config),
                                args.output_dir)
    csv_path = write_summary_csv(summaries, args.output_dir)

    raw_path = os.path.join(args.output_dir, 'results.json')
    with open(raw_path, 'w') as f:
        json.dump({
            'summaries': summaries,
            'per_episode': per_episode_tables,
            'series': {p: [e['series'] for e in eps]
                       for p, eps in results.items()},
        }, f, indent=2, default=str)

    plots = []
    if not args.no_plots:
        try:
            plots = make_plots(results, summaries, args.output_dir,
                               env_config.dt)
        except ImportError as exc:
            print(f"  [plots] skipped — matplotlib unavailable ({exc})")

    print_table(summaries)
    print(f"  run config : {cfg_path}")
    print(f"  summary    : {csv_path}")
    print(f"  raw results: {raw_path}")
    for p in plots:
        print(f"  plot       : {p}")

    return summaries


def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        description='A.U.R.A. standardized evaluation (roadmap §12)',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('--policies', type=str, default='rl,baseline',
                        help='Comma-separated: rl, baseline, static, random')
    parser.add_argument('--episodes', type=int, default=10)
    parser.add_argument('--seed', type=int, default=42)
    parser.add_argument('--num-drones', type=int, default=5)
    parser.add_argument('--max-steps', type=int, default=300)
    parser.add_argument('--weather', action='store_true',
                        help='Enable weather randomization')
    parser.add_argument('--policy-path', type=str, default=None,
                        help='Checkpoint for --policies rl (default: by drone count)')
    parser.add_argument('--device', type=str, default='cpu',
                        choices=['cpu', 'cuda'])
    parser.add_argument('--fault-step', type=int, default=None,
                        help='Fail a drone at this step to measure recovery')
    parser.add_argument('--fault-drone', type=int, default=2)
    parser.add_argument('--output-dir', type=str, default=None)
    parser.add_argument('--no-plots', action='store_true')

    args = parser.parse_args(argv)
    args.policies = [p.strip() for p in args.policies.split(',') if p.strip()]
    if args.output_dir is None:
        stamp = datetime.now().strftime('%Y%m%d-%H%M%S')
        args.output_dir = os.path.join(_REPO_ROOT, 'results', f'eval-{stamp}')
    return args


def main(argv=None) -> int:
    args = parse_args(argv)
    print('=' * 64)
    print('A.U.R.A. evaluation')
    print('=' * 64)
    print(f'  policies : {", ".join(args.policies)}')
    print(f'  episodes : {args.episodes}   steps: {args.max_steps}   '
          f'seed: {args.seed}')
    if args.fault_step is not None:
        print(f'  fault    : drone {args.fault_drone} at step {args.fault_step}')
    print(f'  output   : {args.output_dir}')
    print('=' * 64)
    evaluate(args)
    return 0


if __name__ == '__main__':
    sys.exit(main())
