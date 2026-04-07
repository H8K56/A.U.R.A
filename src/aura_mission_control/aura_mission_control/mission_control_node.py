"""
Mission Control Node for A.U.R.A.

ROS 2 node that wraps the MissionStateMachine. Responsibilities:
  - Subscribe to SwarmState, NetworkMetrics for readiness assessment
  - Publish MissionStatus at regular intervals
  - Send phase-appropriate commands to PX4 interface and trajectory planner
  - Handle operator commands (start, abort) via services
  - Log all state transitions

Think of this as the "glue" between the pure state machine logic
and the ROS 2 communication layer.
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy
import numpy as np
from typing import Optional

from std_msgs.msg import String, Header
from std_srvs.srv import Trigger, SetBool
from geometry_msgs.msg import Point

from aura_msgs.msg import (
    SwarmState,
    DroneState,
    NetworkMetrics,
    MissionStatus,
    CoverageGoal,
)
from aura_msgs.srv import EmergencyStop

from .state_machine import (
    MissionStateMachine,
    MissionPhase,
    MissionConfig,
    SwarmReadiness,
)


class MissionControlNode(Node):
    """
    Central mission orchestrator for A.U.R.A. swarm.

    Subscribes:
        /swarm/state          (SwarmState)     — aggregated drone states
        /network/metrics      (NetworkMetrics) — network performance

    Publishes:
        /mission/status       (MissionStatus)  — mission progress for all nodes
        /mission/phase        (String)         — simple phase name for logging/UI

    Services:
        ~/start_mission       (Trigger)        — command mission start
        ~/abort_mission       (Trigger)        — command mission abort
        ~/emergency_stop      (Trigger)        — immediate all-stop
    """

    def __init__(self):
        super().__init__('mission_control')

        # ── Declare parameters ──────────────────────────────────
        self._declare_params()
        config = self._build_config()

        # ── State machine ───────────────────────────────────────
        self.state_machine = MissionStateMachine(config)
        self.state_machine.set_transition_callback(self._on_phase_transition)

        # ── Latest messages ─────────────────────────────────────
        self.latest_swarm: Optional[SwarmState] = None
        self.latest_network: Optional[NetworkMetrics] = None
        self.drone_last_seen: dict = {}  # drone_id -> timestamp

        # ── QoS ─────────────────────────────────────────────────
        reliable_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            depth=10,
        )
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            depth=5,
        )

        # ── Subscribers ─────────────────────────────────────────
        self.swarm_sub = self.create_subscription(
            SwarmState, '/swarm/state',
            self._swarm_callback, sensor_qos)

        self.network_sub = self.create_subscription(
            NetworkMetrics, '/network/metrics',
            self._network_callback, sensor_qos)

        # ── Publishers ──────────────────────────────────────────
        self.status_pub = self.create_publisher(
            MissionStatus, '/mission/status', reliable_qos)

        self.phase_pub = self.create_publisher(
            String, '/mission/phase', reliable_qos)

        # ── Services ────────────────────────────────────────────
        self.start_srv = self.create_service(
            Trigger, '~/start_mission', self._start_mission_cb)

        self.abort_srv = self.create_service(
            Trigger, '~/abort_mission', self._abort_mission_cb)

        self.estop_srv = self.create_service(
            Trigger, '~/emergency_stop', self._emergency_stop_cb)

        # ── Timers ──────────────────────────────────────────────
        tick_rate = self.get_parameter('tick_rate_hz').value
        self.tick_timer = self.create_timer(1.0 / tick_rate, self._tick)

        status_rate = self.get_parameter('status_publish_rate_hz').value
        self.status_timer = self.create_timer(1.0 / status_rate, self._publish_status)

        # ── Auto-start ──────────────────────────────────────────
        if self.get_parameter('auto_start').value:
            # Delay auto-start to let other nodes initialize
            self.create_timer(3.0, self._auto_start, callback_group=None)

        self.get_logger().info(
            f"Mission control started "
            f"(tick: {tick_rate} Hz, "
            f"drones: {config.num_drones_expected if hasattr(config, 'num_drones_expected') else 'auto'}, "
            f"ops duration: {config.operations_duration_sec}s)"
        )

    # ── Parameter declaration ───────────────────────────────────

    def _declare_params(self):
        """Declare all ROS parameters with defaults"""
        self.declare_parameter('tick_rate_hz', 2.0)
        self.declare_parameter('status_publish_rate_hz', 1.0)
        self.declare_parameter('auto_start', False)
        self.declare_parameter('num_drones', 5)

        # Preflight
        self.declare_parameter('min_battery_for_launch', 50.0)
        self.declare_parameter('preflight_timeout_sec', 120.0)

        # Takeoff
        self.declare_parameter('takeoff_altitude_m', 15.0)
        self.declare_parameter('takeoff_altitude_tolerance_m', 2.0)
        self.declare_parameter('takeoff_timeout_sec', 60.0)

        # Transit
        self.declare_parameter('deploy_zone_x', 0.0)
        self.declare_parameter('deploy_zone_y', 0.0)
        self.declare_parameter('deploy_zone_radius_m', 30.0)
        self.declare_parameter('transit_timeout_sec', 180.0)

        # Formation
        self.declare_parameter('formation_convergence_threshold', 5.0)
        self.declare_parameter('formation_timeout_sec', 120.0)
        self.declare_parameter('require_mesh_for_ops', True)

        # Operations
        self.declare_parameter('operations_duration_sec', 600.0)
        self.declare_parameter('coverage_target', 80.0)

        # Safety
        self.declare_parameter('critical_battery_percent', 20.0)
        self.declare_parameter('lost_drone_timeout_sec', 10.0)
        self.declare_parameter('max_drones_lost_before_abort', 2)

    def _build_config(self) -> MissionConfig:
        """Build MissionConfig from ROS parameters"""
        config = MissionConfig()
        config.min_battery_for_launch = self.get_parameter('min_battery_for_launch').value
        config.preflight_timeout_sec = self.get_parameter('preflight_timeout_sec').value
        config.takeoff_altitude_m = self.get_parameter('takeoff_altitude_m').value
        config.takeoff_altitude_tolerance_m = self.get_parameter('takeoff_altitude_tolerance_m').value
        config.takeoff_timeout_sec = self.get_parameter('takeoff_timeout_sec').value
        config.deploy_zone_center = (
            self.get_parameter('deploy_zone_x').value,
            self.get_parameter('deploy_zone_y').value,
        )
        config.deploy_zone_radius_m = self.get_parameter('deploy_zone_radius_m').value
        config.transit_timeout_sec = self.get_parameter('transit_timeout_sec').value
        config.formation_convergence_threshold = self.get_parameter('formation_convergence_threshold').value
        config.formation_timeout_sec = self.get_parameter('formation_timeout_sec').value
        config.min_mesh_connectivity = self.get_parameter('require_mesh_for_ops').value
        config.operations_duration_sec = self.get_parameter('operations_duration_sec').value
        config.coverage_target = self.get_parameter('coverage_target').value
        config.critical_battery_percent = self.get_parameter('critical_battery_percent').value
        config.lost_drone_timeout_sec = self.get_parameter('lost_drone_timeout_sec').value
        config.max_drones_lost_before_abort = self.get_parameter('max_drones_lost_before_abort').value
        return config

    # ── Callbacks ───────────────────────────────────────────────

    def _swarm_callback(self, msg: SwarmState):
        """Process incoming swarm state"""
        self.latest_swarm = msg

        now = self.get_clock().now().nanoseconds / 1e9

        # Track per-drone heartbeats
        for drone in msg.drones:
            self.drone_last_seen[drone.drone_id] = now

    def _network_callback(self, msg: NetworkMetrics):
        """Process incoming network metrics"""
        self.latest_network = msg

    # ── Main tick ───────────────────────────────────────────────

    def _tick(self):
        """
        Main control loop — runs at tick_rate_hz.
        Updates readiness snapshot, then lets the state machine decide.
        """
        self._update_readiness()
        self.state_machine.update()

    def _update_readiness(self):
        """
        Populate the SwarmReadiness struct from latest ROS messages.
        This is where sensor data meets decision logic.
        """
        r = self.state_machine.readiness
        r.num_drones_expected = self.get_parameter('num_drones').value

        now = self.get_clock().now().nanoseconds / 1e9
        config = self.state_machine.config

        if self.latest_swarm is None:
            r.num_drones_reporting = 0
            return

        swarm = self.latest_swarm
        drones = swarm.drones
        n = len(drones)
        r.num_drones_reporting = n

        if n == 0:
            return

        # ── Battery ─────────────────────────────────────────────
        batteries = [d.battery_percent for d in drones]
        r.min_battery_percent = min(batteries)
        r.any_critical_battery = r.min_battery_percent < config.critical_battery_percent

        # ── Armed & GPS ─────────────────────────────────────────
        # In simulation, we may not have explicit arm status — infer from flight mode
        r.all_armed = all(
            d.flight_mode != DroneState.FLIGHT_MODE_IDLE for d in drones
        )
        r.all_gps_fix = all(d.gps_fix for d in drones)

        # ── Altitude check (takeoff complete) ───────────────────
        target_alt = config.takeoff_altitude_m
        tol = config.takeoff_altitude_tolerance_m
        r.all_at_takeoff_altitude = all(
            abs(d.position.z - target_alt) < tol for d in drones
        )

        # ── Deploy zone check (transit complete) ────────────────
        cx, cy = config.deploy_zone_center
        radius = config.deploy_zone_radius_m
        r.all_at_deploy_zone = all(
            np.sqrt((d.position.x - cx) ** 2 + (d.position.y - cy) ** 2) < radius
            for d in drones
        )

        # ── Formation convergence ───────────────────────────────
        if n >= 2:
            positions = np.array([[d.position.x, d.position.y, d.position.z]
                                  for d in drones])
            centroid = positions.mean(axis=0)
            deviations = np.linalg.norm(positions - centroid, axis=1)
            spread_std = np.std(deviations)
            # Formation is "converged" when drones are spread out but stable
            # (low std in their distances from centroid)
            r.formation_converged = spread_std < config.formation_convergence_threshold
        else:
            r.formation_converged = True

        # ── Network ─────────────────────────────────────────────
        if self.latest_network is not None:
            net = self.latest_network
            r.mesh_connected = net.mesh_connected
            r.coverage_percent = net.total_coverage_percent
            r.backhaul_active = net.backhaul_active
        else:
            r.mesh_connected = swarm.mesh_connected
            r.coverage_percent = swarm.coverage_percent
            r.backhaul_active = swarm.backhaul_connected

        r.coverage_target = config.coverage_target

        # ── Lost drone detection ────────────────────────────────
        timeout = config.lost_drone_timeout_sec
        lost_count = 0
        for drone_id in range(r.num_drones_expected):
            last_seen = self.drone_last_seen.get(drone_id, 0.0)
            if now - last_seen > timeout and self.state_machine.phase != MissionPhase.IDLE:
                lost_count += 1

        r.any_drone_lost = lost_count > 0
        r.elapsed_time_sec = self.state_machine.mission_elapsed

    # ── Phase transition handler ────────────────────────────────

    def _on_phase_transition(self, old_phase: MissionPhase,
                             new_phase: MissionPhase, reason: str):
        """Called by state machine on every transition"""
        self.get_logger().info(
            f"Phase transition: {old_phase.name} -> {new_phase.name} ({reason})"
        )

        # Publish phase name for simple subscribers
        phase_msg = String()
        phase_msg.data = new_phase.name
        self.phase_pub.publish(phase_msg)

        # Immediate status publish on transition
        self._publish_status()

    # ── Status publishing ───────────────────────────────────────

    def _publish_status(self):
        """Publish MissionStatus message"""
        sm = self.state_machine
        r = sm.readiness

        msg = MissionStatus()
        msg.timestamp = self.get_clock().now().to_msg()
        msg.mission_id = 'aura_mission_001'

        msg.phase = sm.phase.value
        msg.progress_percent = sm.get_progress_percent()
        msg.elapsed_time_sec = sm.mission_elapsed
        msg.estimated_remaining_sec = self._estimate_remaining()

        msg.coverage_achieved = r.coverage_percent
        msg.network_quality = 1.0 if r.mesh_connected else 0.0

        # Drone status summary
        if self.latest_swarm is not None:
            drones = self.latest_swarm.drones
            operational = sum(1 for d in drones
                              if d.battery_percent > self.state_machine.config.critical_battery_percent)
            degraded = sum(1 for d in drones
                           if 0 < d.battery_percent <= self.state_machine.config.critical_battery_percent)
            failed = r.num_drones_expected - r.num_drones_reporting
            msg.drones_operational = operational
            msg.drones_degraded = degraded
            msg.drones_failed = failed

        # Active alerts
        alerts, severities = self._collect_alerts()
        msg.active_alerts = alerts
        msg.alert_severities = severities

        self.status_pub.publish(msg)

    def _estimate_remaining(self) -> float:
        """Rough estimate of time remaining"""
        sm = self.state_machine
        if sm.phase == MissionPhase.OPERATIONS:
            if sm.config.operations_duration_sec > 0:
                return max(0.0, sm.config.operations_duration_sec - sm.phase_elapsed)
        elif sm.phase in (MissionPhase.COMPLETE, MissionPhase.ABORT):
            return 0.0
        return -1.0  # unknown

    def _collect_alerts(self):
        """Generate active alerts and severities"""
        alerts = []
        severities = []
        r = self.state_machine.readiness

        if r.any_critical_battery:
            alerts.append(f"Critical battery: {r.min_battery_percent:.0f}%")
            severities.append(2)  # critical

        if r.any_drone_lost:
            lost = r.num_drones_expected - r.num_drones_reporting
            alerts.append(f"{lost} drone(s) not reporting")
            severities.append(2)

        if not r.mesh_connected and self.state_machine.phase == MissionPhase.OPERATIONS:
            alerts.append("Mesh network disconnected")
            severities.append(1)  # warning

        if (r.coverage_percent < r.coverage_target
                and self.state_machine.phase == MissionPhase.OPERATIONS):
            alerts.append(f"Coverage {r.coverage_percent:.0f}% below target {r.coverage_target:.0f}%")
            severities.append(0)  # info

        return alerts, severities

    # ── Service handlers ────────────────────────────────────────

    def _start_mission_cb(self, request, response):
        """Handle start mission service call"""
        if self.state_machine.phase != MissionPhase.IDLE:
            response.success = False
            response.message = f"Cannot start: currently in {self.state_machine.phase.name}"
        else:
            self.state_machine.start()
            response.success = True
            response.message = "Mission started — entering PREFLIGHT"
        return response

    def _abort_mission_cb(self, request, response):
        """Handle abort mission service call"""
        self.state_machine.abort("Operator abort command")
        response.success = True
        response.message = "Mission aborted"
        return response

    def _emergency_stop_cb(self, request, response):
        """Handle emergency stop — immediate halt"""
        self.state_machine.abort("EMERGENCY STOP")
        response.success = True
        response.message = "Emergency stop executed"
        self.get_logger().fatal("EMERGENCY STOP ACTIVATED")
        return response

    def _auto_start(self):
        """Auto-start mission after delay (if configured)"""
        if self.state_machine.phase == MissionPhase.IDLE:
            self.get_logger().info("Auto-starting mission...")
            self.state_machine.start()
        # Cancel this timer (one-shot)
        # ROS 2 Humble doesn't have cancel() on timer easily,
        # so we just no-op on subsequent calls
        pass


def main(args=None):
    rclpy.init(args=args)
    node = MissionControlNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info("Mission control shutting down")
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()
