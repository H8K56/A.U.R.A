#!/usr/bin/env python3
"""A.U.R.A. end-to-end integration smoke test — roadmap A.1.

The packages compile and their unit tests pass, but until now nothing checked
that they actually talk to each other. This brings up the full headless stack
(`sim_no_px4.launch.py` — no Gazebo, no PX4 SITL), watches the real topics, and
asserts the pipeline runs start to finish:

    sim_swarm_driver -> network_sim -> coverage_calculator
                     -> strategic_rl -> mission_control

It also checks the safety invariant CLAUDE.md calls out: the RL policy must
only command the swarm during the OPERATIONS phase, never during takeoff,
transit, formation, RTL or landing.

Usage
-----
    python3 scripts/integration_smoke_test.py
    python3 scripts/integration_smoke_test.py --timeout 240 --num-drones 3
    python3 scripts/integration_smoke_test.py --keep-going   # report all failures

Exits 0 if every check passes, 1 otherwise. Requires a sourced ROS 2 workspace.
"""

import argparse
import os
import signal
import subprocess
import sys
import time
from dataclasses import dataclass, field
from typing import Dict, List, Optional

try:
    import rclpy
    from rclpy.node import Node
    from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
    from aura_msgs.msg import SwarmState, NetworkMetrics, CoverageMap, CoverageGoal
    from aura_msgs.msg import MissionStatus
except ImportError as exc:  # pragma: no cover - environment problem, not logic
    print(f"FATAL: ROS 2 / aura_msgs not importable: {exc}\n"
          f"Source the workspace first:\n"
          f"  source /opt/ros/humble/setup.bash\n"
          f"  source /opt/px4_ros/install/setup.bash\n"
          f"  source install/setup.bash", file=sys.stderr)
    sys.exit(2)


# SwarmState.MISSION_* — mirrored here so a failure message can name the phase.
PHASE_NAMES = {
    0: 'IDLE', 1: 'PREFLIGHT', 2: 'TAKEOFF', 3: 'TRANSIT', 4: 'FORMATION',
    5: 'OPERATIONS', 6: 'RTL', 7: 'COMPLETE', 8: 'ABORT',
}
OPERATIONS = SwarmState.MISSION_OPERATIONS


@dataclass
class TopicRecord:
    count: int = 0
    first_seen: Optional[float] = None
    last_msg: object = None


@dataclass
class Observations:
    topics: Dict[str, TopicRecord] = field(default_factory=dict)
    phases_seen: List[int] = field(default_factory=list)
    # (mission_state at the time, goal drone_id) for every goal observed.
    goals_with_phase: List[tuple] = field(default_factory=list)
    swarm_drone_counts: List[int] = field(default_factory=list)
    # Authoritative coverage comes from /network/metrics. SwarmState carries a
    # coverage_percent field too, but sim_swarm_driver hardcodes it to 0.0
    # ("network_sim will compute this") and nothing ever writes it back, so it
    # is tracked separately rather than trusted.
    network_coverage_percents: List[float] = field(default_factory=list)
    swarm_coverage_percents: List[float] = field(default_factory=list)
    mesh_connected_samples: List[bool] = field(default_factory=list)

    def record(self, topic: str, msg) -> None:
        rec = self.topics.setdefault(topic, TopicRecord())
        rec.count += 1
        rec.last_msg = msg
        if rec.first_seen is None:
            rec.first_seen = time.monotonic()


class SmokeTestObserver(Node):
    """Passive observer — subscribes only, never commands the swarm."""

    def __init__(self, obs: Observations):
        super().__init__('integration_smoke_test')
        self.obs = obs
        self._mission_state: Optional[int] = None

        # The stack's publishers are best-effort/volatile in places; a
        # best-effort subscription matches anything.
        qos = QoSProfile(depth=20,
                         reliability=ReliabilityPolicy.BEST_EFFORT,
                         history=HistoryPolicy.KEEP_LAST)

        self.create_subscription(SwarmState, '/swarm/state', self._on_swarm, qos)
        self.create_subscription(NetworkMetrics, '/network/metrics',
                                 self._on_network, qos)
        self.create_subscription(CoverageMap, '/network/coverage_map',
                                 self._on_coverage, qos)
        self.create_subscription(CoverageGoal, '/coverage/goals',
                                 self._on_goal, qos)
        self.create_subscription(MissionStatus, '/mission/status',
                                 self._on_mission, qos)

    def _on_swarm(self, msg: SwarmState):
        self.obs.record('/swarm/state', msg)
        self._mission_state = msg.mission_state
        if msg.mission_state not in self.obs.phases_seen:
            self.obs.phases_seen.append(msg.mission_state)
        self.obs.swarm_drone_counts.append(len(msg.drones))
        self.obs.mesh_connected_samples.append(bool(msg.mesh_connected))
        self.obs.swarm_coverage_percents.append(float(msg.coverage_percent))

    def _on_network(self, msg: NetworkMetrics):
        self.obs.record('/network/metrics', msg)
        self.obs.network_coverage_percents.append(
            float(msg.total_coverage_percent))

    def _on_coverage(self, msg: CoverageMap):
        self.obs.record('/network/coverage_map', msg)

    def _on_goal(self, msg: CoverageGoal):
        self.obs.record('/coverage/goals', msg)
        # Correlate against the most recent phase: this is the safety boundary.
        self.obs.goals_with_phase.append((self._mission_state, msg.drone_id))

    def _on_mission(self, msg: MissionStatus):
        self.obs.record('/mission/status', msg)


# ── Checks ──────────────────────────────────────────────────────────────────

@dataclass
class CheckResult:
    name: str
    passed: bool
    detail: str
    # Advisory findings are reported but do not fail the run. Used for known,
    # documented gaps: gating on them would leave the test permanently red,
    # and a red test nobody can fix is a test nobody reads.
    advisory: bool = False


def build_checks(obs: Observations, args) -> List[CheckResult]:
    results: List[CheckResult] = []

    def check(name: str, passed: bool, detail: str = ''):
        results.append(CheckResult(name, passed, detail))

    # 1. Every stage of the pipeline produced output.
    required = ['/swarm/state', '/network/metrics', '/network/coverage_map',
                '/mission/status']
    for topic in required:
        rec = obs.topics.get(topic)
        check(f'publishes {topic}',
              rec is not None and rec.count > 0,
              f'{rec.count} messages' if rec else 'no messages received')

    # 2. The swarm driver reports the drone count it was asked for.
    counts = set(obs.swarm_drone_counts)
    check('swarm reports the configured drone count',
          counts == {args.num_drones},
          f'expected {args.num_drones}, saw {sorted(counts) or "nothing"}')

    # 3. The mission state machine actually advanced.
    advanced = [p for p in obs.phases_seen if p not in (0, 1)]
    check('mission advances past PREFLIGHT',
          bool(advanced),
          'phases: ' + (', '.join(PHASE_NAMES.get(p, str(p))
                                  for p in obs.phases_seen) or 'none'))

    # 4. It reached OPERATIONS — the phase the whole system exists to run.
    check('mission reaches OPERATIONS',
          OPERATIONS in obs.phases_seen,
          'phases: ' + (', '.join(PHASE_NAMES.get(p, str(p))
                                  for p in obs.phases_seen) or 'none'))

    # 5. Network metrics are populated, not just published empty.
    net = obs.topics.get('/network/metrics')
    if net and net.last_msg is not None:
        m = net.last_msg
        populated = (len(m.coverage_mask) > 0 and
                     m.grid_size_x > 0 and m.grid_size_y > 0)
        check('network metrics carry a populated grid', populated,
              f'grid {m.grid_size_x}x{m.grid_size_y}, '
              f'{len(m.coverage_mask)} cells, '
              f'mesh_connected={m.mesh_connected}')
    else:
        check('network metrics carry a populated grid', False, 'no message')

    # 6. CoverageMap.header is a message contract CLAUDE.md names explicitly.
    cov = obs.topics.get('/network/coverage_map')
    if cov and cov.last_msg is not None:
        stamp = cov.last_msg.header.stamp
        check('coverage map carries a populated header',
              (stamp.sec != 0 or stamp.nanosec != 0),
              f'stamp={stamp.sec}.{stamp.nanosec:09d}')
    else:
        check('coverage map carries a populated header', False, 'no message')

    # 7. The policy actually commanded the swarm.
    goals = obs.topics.get('/coverage/goals')
    check('policy publishes goals',
          goals is not None and goals.count > 0,
          f'{goals.count} goals' if goals else 'no goals — '
          'did the mission reach OPERATIONS?')

    # 8. SAFETY INVARIANT: goals only during OPERATIONS.
    out_of_phase = [(PHASE_NAMES.get(p, str(p)), d)
                    for p, d in obs.goals_with_phase if p != OPERATIONS]
    check('goals are only issued during OPERATIONS',
          not out_of_phase,
          'violations: ' + (', '.join(f'drone {d} in {p}'
                                      for p, d in out_of_phase[:5])
                            if out_of_phase else 'none'))

    # 9. Coverage is actually being computed, not stuck at zero.
    nonzero = [c for c in obs.network_coverage_percents if c > 0.0]
    check('network reports non-zero coverage',
          bool(nonzero),
          f'max {max(obs.network_coverage_percents):.1f}%'
          if obs.network_coverage_percents else 'no samples')

    # 10. SwarmState's network fields are still published as a hardcoded
    # 0.0/False by every publisher. That is now by design — they describe the
    # network, not the swarm, and NetworkMetrics is authoritative — so this is
    # tracked rather than enforced. It used to be load-bearing:
    # mission_control fell back to these values when /network/metrics was
    # missing, which turned a telemetry outage into "coverage 0%, mesh down"
    # and aborted the mission at formation timeout. That fallback is gone;
    # staleness is now carried explicitly by SwarmReadiness.network_data_valid.
    # The check stays so nobody reintroduces a dependency on these fields.
    swarm_cov_populated = any(c > 0.0 for c in obs.swarm_coverage_percents)
    results.append(CheckResult(
        'SwarmState.coverage_percent is populated',
        swarm_cov_populated,
        'always 0.0 — by design; read /network/metrics instead'
        if not swarm_cov_populated else 'populated',
        advisory=True,
    ))

    return results


# ── Runner ──────────────────────────────────────────────────────────────────

def run(args) -> int:
    launch_cmd = [
        'ros2', 'launch', 'aura_simulation', 'sim_no_px4.launch.py',
        f'num_drones:={args.num_drones}',
        'auto_start:=true',
        f'ops_duration:={args.ops_duration}',
        f'use_baseline:={"true" if args.use_baseline else "false"}',
    ]
    print('  launching:', ' '.join(launch_cmd))

    log_path = os.path.join(args.log_dir, 'launch.log') if args.log_dir else None
    log_file = open(log_path, 'w') if log_path else subprocess.DEVNULL

    # Own process group so the whole node tree can be signalled on teardown.
    proc = subprocess.Popen(
        launch_cmd,
        stdout=log_file if log_path else subprocess.DEVNULL,
        stderr=subprocess.STDOUT,
        start_new_session=True,
    )

    obs = Observations()
    rclpy.init(args=None)
    node = SmokeTestObserver(obs)

    deadline = time.monotonic() + args.timeout
    reached_operations = False
    try:
        while time.monotonic() < deadline:
            rclpy.spin_once(node, timeout_sec=0.2)

            if proc.poll() is not None:
                print(f'  launch exited early with code {proc.returncode}')
                break

            if OPERATIONS in obs.phases_seen:
                if not reached_operations:
                    reached_operations = True
                    # Keep observing a little longer so goals accumulate while
                    # the policy is actually allowed to act.
                    deadline = min(deadline,
                                   time.monotonic() + args.observe_operations)
                    print(f'  reached OPERATIONS — observing '
                          f'{args.observe_operations:.0f}s more')
    except KeyboardInterrupt:
        print('  interrupted')
    finally:
        node.destroy_node()
        rclpy.shutdown()
        _terminate(proc)
        if log_path:
            log_file.close()

    results = build_checks(obs, args)
    return _report(results, obs, log_path, args)


def _terminate(proc: subprocess.Popen) -> None:
    """SIGINT the whole launch tree, then escalate if it lingers."""
    if proc.poll() is not None:
        return
    try:
        os.killpg(os.getpgid(proc.pid), signal.SIGINT)
        proc.wait(timeout=15)
    except subprocess.TimeoutExpired:
        try:
            os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
            proc.wait(timeout=5)
        except Exception:
            pass
    except ProcessLookupError:
        pass


def _report(results: List[CheckResult], obs: Observations,
            log_path: Optional[str], args) -> int:
    print()
    print('=' * 70)
    print('  Integration smoke test')
    print('=' * 70)

    width = max(len(r.name) for r in results)
    for r in results:
        if r.passed:
            mark = 'PASS'
        elif r.advisory:
            mark = 'WARN'
        else:
            mark = 'FAIL'
        print(f'  [{mark}] {r.name.ljust(width)}  {r.detail}')

    print('-' * 70)
    print('  topic traffic:')
    for topic, rec in sorted(obs.topics.items()):
        print(f'    {topic.ljust(26)} {rec.count:5d} messages')

    failed = [r for r in results if not r.passed and not r.advisory]
    warned = [r for r in results if not r.passed and r.advisory]
    print('=' * 70)
    if failed:
        print(f'  FAILED — {len(failed)} of {len(results)} checks')
        if log_path:
            print(f'  launch output: {log_path}')
        return 1
    passed = len(results) - len(warned)
    msg = f'  PASSED — {passed} checks'
    if warned:
        msg += f', {len(warned)} advisory warning(s)'
    print(msg)
    return 0


def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        description='A.U.R.A. end-to-end integration smoke test (roadmap A.1)',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('--num-drones', type=int, default=5)
    parser.add_argument('--timeout', type=float, default=180.0,
                        help='Overall budget for reaching OPERATIONS')
    parser.add_argument('--observe-operations', type=float, default=20.0,
                        help='Seconds to keep watching after OPERATIONS begins')
    parser.add_argument('--ops-duration', type=float, default=60.0,
                        help='Mission OPERATIONS duration passed to the launch')
    parser.add_argument('--use-baseline', action='store_true', default=True,
                        help='Run the heuristic baseline rather than a checkpoint')
    parser.add_argument('--rl', dest='use_baseline', action='store_false',
                        help='Run the trained RL policy instead')
    parser.add_argument('--log-dir', type=str, default=None,
                        help='Directory to write launch output into')
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(argv)
    if args.log_dir:
        os.makedirs(args.log_dir, exist_ok=True)
    print('=' * 70)
    print('  A.U.R.A. integration smoke test')
    print(f'  drones={args.num_drones}  timeout={args.timeout:.0f}s  '
          f'policy={"baseline" if args.use_baseline else "rl"}')
    print('=' * 70)
    return run(args)


if __name__ == '__main__':
    sys.exit(main())
