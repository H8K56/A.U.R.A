"""
Mission Monitor for A.U.R.A.

Simple CLI dashboard that subscribes to /mission/status and
displays real-time mission progress. Useful for debugging
and demonstration.

Usage:
    ros2 run aura_mission_control mission_monitor
"""

import os
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy

from aura_msgs.msg import MissionStatus, SwarmState, NetworkMetrics


# Phase names for display
PHASE_NAMES = {
    0: 'IDLE',
    1: 'PREFLIGHT',
    2: 'TAKEOFF',
    3: 'TRANSIT',
    4: 'FORMATION',
    5: 'OPERATIONS',
    6: 'RTL',
    7: 'COMPLETE',
    8: 'ABORT',
}

PHASE_ICONS = {
    0: '⏸ ',
    1: '🔍',
    2: '🛫',
    3: '✈ ',
    4: '📐',
    5: '🤖',
    6: '🔙',
    7: '✅',
    8: '🚨',
}


class MissionMonitor(Node):
    """Real-time CLI dashboard for A.U.R.A. mission"""

    def __init__(self):
        super().__init__('mission_monitor')

        reliable_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE, depth=10)
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT, depth=5)

        self.status_sub = self.create_subscription(
            MissionStatus, '/mission/status',
            self._status_callback, reliable_qos)

        self.swarm_sub = self.create_subscription(
            SwarmState, '/swarm/state',
            self._swarm_callback, sensor_qos)

        self.network_sub = self.create_subscription(
            NetworkMetrics, '/network/metrics',
            self._network_callback, sensor_qos)

        self.latest_status = None
        self.latest_swarm = None
        self.latest_network = None

        # Refresh display at 2 Hz
        self.create_timer(0.5, self._display)

        self.get_logger().info("Mission monitor started — waiting for data...")

    def _status_callback(self, msg):
        self.latest_status = msg

    def _swarm_callback(self, msg):
        self.latest_swarm = msg

    def _network_callback(self, msg):
        self.latest_network = msg

    def _display(self):
        """Render the dashboard"""
        os.system('clear')
        w = 72

        print('=' * w)
        print(' A.U.R.A. MISSION MONITOR '.center(w))
        print('=' * w)

        if self.latest_status is None:
            print('\n  Waiting for mission status...'.center(w))
            print('  (Is mission_control_node running?)'.center(w))
            return

        s = self.latest_status
        phase_name = PHASE_NAMES.get(s.phase, 'UNKNOWN')
        phase_icon = PHASE_ICONS.get(s.phase, '? ')

        # Phase banner
        print(f'\n  {phase_icon}  Phase: {phase_name}'.ljust(w))
        print(f'  Mission ID: {s.mission_id}'.ljust(w))

        # Progress bar
        pct = s.progress_percent
        bar_width = 40
        filled = int(bar_width * pct / 100)
        bar = '█' * filled + '░' * (bar_width - filled)
        print(f'\n  Progress: [{bar}] {pct:.1f}%')

        # Timing
        elapsed = s.elapsed_time_sec
        remaining = s.estimated_remaining_sec
        elapsed_str = f'{int(elapsed // 60)}m {int(elapsed % 60)}s'
        if remaining > 0:
            remain_str = f'{int(remaining // 60)}m {int(remaining % 60)}s'
        elif remaining == 0:
            remain_str = 'Done'
        else:
            remain_str = '--'
        print(f'  Elapsed: {elapsed_str}  |  Remaining: {remain_str}')

        # Coverage & Network
        print(f'\n  {"─" * (w - 4)}')
        print(f'  Coverage:  {s.coverage_achieved:.1f}%')
        print(f'  Network:   {"Connected" if s.network_quality > 0.5 else "Disconnected"}')

        # Drone summary
        print(f'\n  Drones:    '
              f'{s.drones_operational} operational  |  '
              f'{s.drones_degraded} degraded  |  '
              f'{s.drones_failed} failed')

        # Network details (if available)
        if self.latest_network is not None:
            net = self.latest_network
            print(f'\n  {"─" * (w - 4)}')
            print(f'  Signal:     {net.avg_signal_strength_dbm:.1f} dBm')
            print(f'  Throughput: {net.avg_throughput_mbps:.1f} Mbps')
            print(f'  Latency:    {net.avg_latency_ms:.1f} ms')
            print(f'  Links:      {len(net.link_from_drone)}')

        # Per-drone info (if available)
        if self.latest_swarm is not None and self.latest_swarm.drones:
            print(f'\n  {"─" * (w - 4)}')
            print(f'  {"ID":<4} {"Role":<6} {"Position":<24} {"Bat":<7} {"Mode":<12}')
            for d in self.latest_swarm.drones:
                role = 'HUB' if d.role == 1 else 'LEAF'
                pos = f'({d.position.x:.1f}, {d.position.y:.1f}, {d.position.z:.1f})'
                bat = f'{d.battery_percent:.0f}%'
                modes = {0: 'IDLE', 1: 'TAKEOFF', 2: 'TRANSIT',
                         3: 'FORMATION', 4: 'OPS', 5: 'RTL', 6: 'EMERGENCY'}
                mode = modes.get(d.flight_mode, f'?{d.flight_mode}')
                print(f'  {d.drone_id:<4} {role:<6} {pos:<24} {bat:<7} {mode:<12}')

        # Alerts
        if s.active_alerts:
            print(f'\n  {"─" * (w - 4)}')
            severity_labels = {0: 'INFO', 1: 'WARN', 2: 'CRIT'}
            for alert, sev in zip(s.active_alerts, s.alert_severities):
                label = severity_labels.get(sev, '?')
                print(f'  [{label}] {alert}')

        # RL status
        rl_active = s.phase == 5  # OPERATIONS
        rl_str = 'ACTIVE — optimizing positions' if rl_active else 'INACTIVE'
        print(f'\n  RL Policy: {rl_str}')

        print(f'\n{"=" * w}')
        print('  Ctrl+C to exit'.center(w))


def main(args=None):
    rclpy.init(args=args)
    node = MissionMonitor()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()
