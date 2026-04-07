"""
Scenario Runner for A.U.R.A.

Automates test scenarios by:
  1. Starting the mission via service call
  2. Monitoring progress via /mission/status
  3. Logging key metrics at each phase transition
  4. Optionally injecting dead zones mid-mission to test adaptation
  5. Reporting final results

Usage:
    ros2 run aura_simulation scenario_runner
    ros2 run aura_simulation scenario_runner --ros-args -p inject_dead_zone:=true
"""

import time
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy

from std_srvs.srv import Trigger, SetBool
from aura_msgs.msg import MissionStatus, NetworkMetrics

PHASE_NAMES = {
    0: 'IDLE', 1: 'PREFLIGHT', 2: 'TAKEOFF', 3: 'TRANSIT',
    4: 'FORMATION', 5: 'OPERATIONS', 6: 'RTL',
    7: 'COMPLETE', 8: 'ABORT',
}


class ScenarioRunner(Node):
    """Automated scenario executor"""

    def __init__(self):
        super().__init__('scenario_runner')

        self.declare_parameter('auto_start_delay_sec', 5.0)
        self.declare_parameter('inject_dead_zone', False)
        self.declare_parameter('inject_at_ops_sec', 30.0)

        self.auto_start_delay = self.get_parameter('auto_start_delay_sec').value
        self.inject_dead_zone = self.get_parameter('inject_dead_zone').value
        self.inject_at_sec = self.get_parameter('inject_at_ops_sec').value

        # State
        self.current_phase = 0
        self.ops_start_time = None
        self.dead_zone_injected = False
        self.mission_started = False
        self.phase_log = []
        self.latest_coverage = 0.0
        self.latest_network = None

        # Subscribers
        reliable_qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE, depth=10)
        sensor_qos = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, depth=5)

        self.status_sub = self.create_subscription(
            MissionStatus, '/mission/status',
            self._status_callback, reliable_qos)

        self.network_sub = self.create_subscription(
            NetworkMetrics, '/network/metrics',
            self._network_callback, sensor_qos)

        # Service clients
        self.start_client = self.create_client(
            Trigger, '/mission_control/start_mission')
        self.add_zone_client = self.create_client(
            Trigger, '/dead_zone_publisher/add_random_zone')

        # Timer
        self.create_timer(1.0, self._tick)

        # Auto-start timer
        self.create_timer(self.auto_start_delay, self._auto_start)

        self.get_logger().info(
            f"Scenario runner initialized "
            f"(start delay: {self.auto_start_delay}s, "
            f"inject dead zone: {self.inject_dead_zone})"
        )

    def _auto_start(self):
        """Start mission after delay"""
        if self.mission_started:
            return

        if not self.start_client.service_is_ready():
            self.get_logger().warn("Waiting for mission_control start service...")
            return

        self.mission_started = True
        request = Trigger.Request()
        future = self.start_client.call_async(request)
        future.add_done_callback(self._start_result)

    def _start_result(self, future):
        result = future.result()
        if result.success:
            self.get_logger().info(f"Mission started: {result.message}")
        else:
            self.get_logger().error(f"Failed to start: {result.message}")

    def _status_callback(self, msg: MissionStatus):
        """Track mission progress"""
        old_phase = self.current_phase
        self.current_phase = msg.phase
        self.latest_coverage = msg.coverage_achieved

        if old_phase != msg.phase:
            phase_name = PHASE_NAMES.get(msg.phase, f'?{msg.phase}')
            self.phase_log.append({
                'time': msg.elapsed_time_sec,
                'phase': phase_name,
                'coverage': msg.coverage_achieved,
            })
            self.get_logger().info(
                f"[SCENARIO] Phase -> {phase_name} "
                f"(t={msg.elapsed_time_sec:.0f}s, "
                f"coverage={msg.coverage_achieved:.1f}%)"
            )

            if msg.phase == 5:  # OPERATIONS
                self.ops_start_time = time.monotonic()

            if msg.phase in (7, 8):  # COMPLETE or ABORT
                self._report_results(msg)

    def _network_callback(self, msg: NetworkMetrics):
        self.latest_network = msg

    def _tick(self):
        """Periodic check for dead zone injection"""
        if not self.inject_dead_zone or self.dead_zone_injected:
            return

        if self.ops_start_time is None:
            return

        elapsed_in_ops = time.monotonic() - self.ops_start_time
        if elapsed_in_ops >= self.inject_at_sec:
            self._inject_dead_zone()

    def _inject_dead_zone(self):
        """Inject a dead zone during operations to test RL adaptation"""
        if not self.add_zone_client.service_is_ready():
            self.get_logger().warn("Dead zone service not ready")
            return

        self.dead_zone_injected = True
        self.get_logger().info(
            f"[SCENARIO] Injecting dead zone at t={time.monotonic() - self.ops_start_time:.0f}s "
            f"into operations — testing RL adaptation"
        )

        request = Trigger.Request()
        future = self.add_zone_client.call_async(request)
        future.add_done_callback(lambda f: self.get_logger().info(
            f"[SCENARIO] Dead zone injected: {f.result().message}"
        ))

    def _report_results(self, final_status: MissionStatus):
        """Print final scenario report"""
        self.get_logger().info("\n" + "=" * 60)
        self.get_logger().info("  A.U.R.A. SCENARIO REPORT")
        self.get_logger().info("=" * 60)

        outcome = PHASE_NAMES.get(final_status.phase, 'UNKNOWN')
        self.get_logger().info(f"  Outcome:     {outcome}")
        self.get_logger().info(f"  Duration:    {final_status.elapsed_time_sec:.0f}s")
        self.get_logger().info(f"  Coverage:    {final_status.coverage_achieved:.1f}%")
        self.get_logger().info(f"  Drones OK:   {final_status.drones_operational}")
        self.get_logger().info(f"  Drones lost: {final_status.drones_failed}")

        self.get_logger().info("\n  Phase Timeline:")
        for entry in self.phase_log:
            self.get_logger().info(
                f"    t={entry['time']:>6.0f}s  {entry['phase']:<12} "
                f"coverage={entry['coverage']:.1f}%"
            )

        if self.dead_zone_injected:
            self.get_logger().info("\n  Dead zone was injected during operations")

        self.get_logger().info("=" * 60)


def main(args=None):
    rclpy.init(args=args)
    node = ScenarioRunner()
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
