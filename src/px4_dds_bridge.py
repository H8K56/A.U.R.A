"""
PX4 microDDS Bridge for A.U.R.A.

Replaces the MAVROS bridge. Communicates directly with PX4 via
MicroXRCE-DDS agent using px4_msgs. No MAVROS dependency.

Topic mapping (per drone, N = PX4 instance number):
    IN:  /px4_N/fmu/out/vehicle_local_position_v1  →  position
         /px4_N/fmu/out/vehicle_status_v1           →  armed, mode
         /px4_N/fmu/out/vehicle_attitude             →  orientation
         /px4_N/fmu/out/battery_status_v1            →  battery
         /px4_N/fmu/out/vehicle_global_position      →  GPS
    OUT: /px4_N/fmu/in/vehicle_command               →  arm, mode
         /px4_N/fmu/in/offboard_control_mode         →  offboard enable
         /px4_N/fmu/in/trajectory_setpoint           →  position goals

Architecture:
    PX4 → MicroXRCEAgent → px4_dds_bridge → /swarm/state
                                           → /drone_{id}/state
                                           ← /coverage/goals
                                           ← /mission/phase
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import (
    QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy,
)
import numpy as np
import math
from typing import Dict, Optional
from dataclasses import dataclass, field

from geometry_msgs.msg import Point, Vector3, Quaternion
from std_msgs.msg import String

from px4_msgs.msg import (
    VehicleLocalPosition,
    VehicleStatus,
    VehicleAttitude,
    BatteryStatus,
    VehicleGlobalPosition,
    VehicleCommand,
    OffboardControlMode,
    TrajectorySetpoint,
)

from aura_msgs.msg import (
    DroneState,
    SwarmState,
    CoverageGoal,
)


# PX4 arming states
ARMING_STATE_DISARMED = 1
ARMING_STATE_ARMED = 2

# PX4 nav states (from VehicleStatus)
NAV_STATE_MANUAL = 0
NAV_STATE_ALTCTL = 1
NAV_STATE_POSCTL = 2
NAV_STATE_AUTO_MISSION = 3
NAV_STATE_AUTO_LOITER = 4
NAV_STATE_AUTO_RTL = 5
NAV_STATE_AUTO_TAKEOFF = 17
NAV_STATE_AUTO_LAND = 18
NAV_STATE_OFFBOARD = 14
NAV_STATE_STAB = 15

# VehicleCommand constants
VEHICLE_CMD_COMPONENT_ARM_DISARM = 400
VEHICLE_CMD_DO_SET_MODE = 176

# Mission phase mapping
PHASE_TO_MISSION_STATE = {
    'IDLE': 0, 'PREFLIGHT': 1, 'TAKEOFF': 2, 'TRANSIT': 3,
    'FORMATION': 4, 'OPERATIONS': 5, 'RTL': 6,
    'COMPLETE': 7, 'ABORT': 8,
}

# PX4 nav_state → A.U.R.A. flight mode
NAV_STATE_TO_FLIGHT_MODE = {
    NAV_STATE_MANUAL: DroneState.FLIGHT_MODE_IDLE,
    NAV_STATE_ALTCTL: DroneState.FLIGHT_MODE_IDLE,
    NAV_STATE_POSCTL: DroneState.FLIGHT_MODE_IDLE,
    NAV_STATE_STAB: DroneState.FLIGHT_MODE_IDLE,
    NAV_STATE_AUTO_TAKEOFF: DroneState.FLIGHT_MODE_TAKEOFF,
    NAV_STATE_AUTO_MISSION: DroneState.FLIGHT_MODE_TRANSIT,
    NAV_STATE_AUTO_LOITER: DroneState.FLIGHT_MODE_FORMATION,
    NAV_STATE_OFFBOARD: DroneState.FLIGHT_MODE_OPERATIONS,
    NAV_STATE_AUTO_RTL: DroneState.FLIGHT_MODE_RTL,
    NAV_STATE_AUTO_LAND: DroneState.FLIGHT_MODE_RTL,
}


@dataclass
class PX4Drone:
    drone_id: int
    px4_instance: int  # 1-based PX4 instance number
    role: int = 0
    position: np.ndarray = field(default_factory=lambda: np.zeros(3))
    velocity: np.ndarray = field(default_factory=lambda: np.zeros(3))
    orientation: tuple = (0.0, 0.0, 0.0, 1.0)
    armed: bool = False
    connected: bool = False
    nav_state: int = 0
    arming_state: int = 1
    battery_percent: float = 100.0
    battery_voltage: float = 16.8
    gps_fix: bool = False
    num_satellites: int = 0
    lat: float = 0.0
    lon: float = 0.0
    alt: float = 0.0
    goal_position: Optional[np.ndarray] = None
    sending_setpoints: bool = False
    last_status_time: float = 0.0


class PX4DDSBridge(Node):

    def __init__(self):
        super().__init__('px4_dds_bridge')

        # Parameters
        self.declare_parameter('num_drones', 5)
        self.declare_parameter('publish_rate_hz', 10.0)
        self.declare_parameter('hub_drone_id', 0)
        self.declare_parameter('setpoint_rate_hz', 20.0)
        self.declare_parameter('takeoff_altitude_m', 15.0)
        self.declare_parameter('auto_arm', True)

        self.num_drones = self.get_parameter('num_drones').value
        rate = self.get_parameter('publish_rate_hz').value
        hub_id = self.get_parameter('hub_drone_id').value
        self.setpoint_rate = self.get_parameter('setpoint_rate_hz').value
        self.takeoff_alt = self.get_parameter('takeoff_altitude_m').value
        self.auto_arm = self.get_parameter('auto_arm').value

        self.current_phase = 'IDLE'
        self.offboard_counter = {}  # per-drone counter for offboard pre-arm

        # PX4 QoS — must match PX4's DDS publisher QoS
        px4_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=5,
        )

        # A.U.R.A. QoS
        reliable_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE, depth=10)

        # ── Drone state tracking ──────────────────────────
        self.drones: Dict[int, PX4Drone] = {}
        for i in range(self.num_drones):
            px4_inst = i + 1  # PX4 instances are 1-based
            self.drones[i] = PX4Drone(
                drone_id=i,
                px4_instance=px4_inst,
                role=1 if i == hub_id else 0,
            )
            self.offboard_counter[i] = 0

        # ── A.U.R.A. publishers ───────────────────────────
        self.swarm_pub = self.create_publisher(
            SwarmState, '/swarm/state', reliable_qos)
        self.drone_pubs = {}
        for i in range(self.num_drones):
            self.drone_pubs[i] = self.create_publisher(
                DroneState, f'/drone_{i}/state', reliable_qos)

        # ── A.U.R.A. subscribers ──────────────────────────
        self.create_subscription(
            CoverageGoal, '/coverage/goals',
            self._coverage_goal_cb, reliable_qos)
        self.create_subscription(
            String, '/mission/phase',
            self._phase_cb, reliable_qos)

        # ── Per-drone PX4 subscribers & publishers ────────
        self.cmd_pubs = {}
        self.offboard_mode_pubs = {}
        self.setpoint_pubs = {}

        for i in range(self.num_drones):
            ns = f'/px4_{self.drones[i].px4_instance}'

            # Subscribe to PX4 output topics
            # Note: some topics use _v1 suffix in newer PX4
            self.create_subscription(
                VehicleLocalPosition,
                f'{ns}/fmu/out/vehicle_local_position_v1',
                lambda msg, idx=i: self._local_pos_cb(msg, idx),
                px4_qos)

            self.create_subscription(
                VehicleStatus,
                f'{ns}/fmu/out/vehicle_status_v1',
                lambda msg, idx=i: self._status_cb(msg, idx),
                px4_qos)

            self.create_subscription(
                VehicleAttitude,
                f'{ns}/fmu/out/vehicle_attitude',
                lambda msg, idx=i: self._attitude_cb(msg, idx),
                px4_qos)

            self.create_subscription(
                BatteryStatus,
                f'{ns}/fmu/out/battery_status_v1',
                lambda msg, idx=i: self._battery_cb(msg, idx),
                px4_qos)

            self.create_subscription(
                VehicleGlobalPosition,
                f'{ns}/fmu/out/vehicle_global_position',
                lambda msg, idx=i: self._global_pos_cb(msg, idx),
                px4_qos)

            # Publishers for PX4 commands
            self.cmd_pubs[i] = self.create_publisher(
                VehicleCommand,
                f'{ns}/fmu/in/vehicle_command',
                reliable_qos)

            self.offboard_mode_pubs[i] = self.create_publisher(
                OffboardControlMode,
                f'{ns}/fmu/in/offboard_control_mode',
                reliable_qos)

            self.setpoint_pubs[i] = self.create_publisher(
                TrajectorySetpoint,
                f'{ns}/fmu/in/trajectory_setpoint',
                reliable_qos)

        # ── Timers ────────────────────────────────────────
        self.create_timer(1.0 / rate, self._publish_swarm_state)
        self.create_timer(1.0 / self.setpoint_rate, self._send_setpoints)

        self.get_logger().info(
            f'PX4 DDS Bridge started: {self.num_drones} drones, '
            f'namespace=/px4_N, rate={rate} Hz')

    # ── PX4 callbacks ────────────────────────────────────

    def _local_pos_cb(self, msg: VehicleLocalPosition, idx: int):
        d = self.drones[idx]
        # PX4 uses NED, A.U.R.A. uses ENU
        d.position = np.array([msg.x, -msg.y, -msg.z])
        d.velocity = np.array([msg.vx, -msg.vy, -msg.vz])
        d.connected = True  # If we get data, PX4 is alive

    def _status_cb(self, msg: VehicleStatus, idx: int):
        d = self.drones[idx]
        d.arming_state = msg.arming_state
        d.armed = (msg.arming_state == ARMING_STATE_ARMED)
        d.nav_state = msg.nav_state
        d.connected = True
        d.last_status_time = self.get_clock().now().nanoseconds / 1e9

    def _attitude_cb(self, msg: VehicleAttitude, idx: int):
        d = self.drones[idx]
        q = msg.q  # [w, x, y, z] in PX4
        # PX4 quaternion is [w, x, y, z], ROS is [x, y, z, w]
        # Also NED→ENU rotation
        d.orientation = (float(q[1]), float(-q[2]), float(-q[3]), float(q[0]))

    def _battery_cb(self, msg: BatteryStatus, idx: int):
        d = self.drones[idx]
        if msg.remaining >= 0:
            d.battery_percent = float(msg.remaining) * 100.0
        d.battery_voltage = float(msg.voltage_v) if msg.voltage_v > 0 else 16.8

    def _global_pos_cb(self, msg: VehicleGlobalPosition, idx: int):
        d = self.drones[idx]
        d.lat = msg.lat
        d.lon = msg.lon
        d.alt = msg.alt
        d.gps_fix = True

    # ── A.U.R.A. callbacks ───────────────────────────────

    def _coverage_goal_cb(self, msg: CoverageGoal):
        did = msg.drone_id
        if did in self.drones:
            # A.U.R.A. uses ENU, PX4 uses NED — convert when sending
            self.drones[did].goal_position = np.array([
                msg.position.x, msg.position.y, msg.position.z])
            self.drones[did].sending_setpoints = True

    def _phase_cb(self, msg: String):
        new_phase = msg.data
        if new_phase != self.current_phase:
            self.get_logger().info(
                f'Phase: {self.current_phase} -> {new_phase}')
            self.current_phase = new_phase

            if new_phase == 'PREFLIGHT' and self.auto_arm:
                self._start_offboard_sequence()
            elif new_phase == 'TAKEOFF':
                self._takeoff_all()
            elif new_phase == 'RTL':
                self._rtl_all()

    # ── Drone commands ───────────────────────────────────

    def _publish_vehicle_command(self, drone_idx: int,
                                  command: int,
                                  param1: float = 0.0,
                                  param2: float = 0.0):
        """Send a VehicleCommand to a specific PX4 instance."""
        d = self.drones[drone_idx]
        msg = VehicleCommand()
        msg.param1 = param1
        msg.param2 = param2
        msg.command = command
        msg.target_system = d.px4_instance
        msg.target_component = 1
        msg.source_system = 1
        msg.source_component = 1
        msg.from_external = True
        msg.timestamp = int(self.get_clock().now().nanoseconds / 1000)
        self.cmd_pubs[drone_idx].publish(msg)

    def _start_offboard_sequence(self):
        """
        PX4 offboard mode requires:
        1. Stream OffboardControlMode + TrajectorySetpoint for ~1s
        2. Then switch to OFFBOARD mode
        3. Then arm

        We start streaming immediately; the setpoint timer handles
        the continuous stream. After 20 cycles (~1s at 20Hz), we
        send the mode + arm commands.
        """
        for i in range(self.num_drones):
            d = self.drones[i]
            # Set initial hover position (current + small altitude)
            d.goal_position = np.array([
                d.position[0], d.position[1], max(d.position[2], 0.5)])
            d.sending_setpoints = True
            self.offboard_counter[i] = 0

        self.get_logger().info('Starting offboard sequence for all drones')

    def _takeoff_all(self):
        for i in range(self.num_drones):
            d = self.drones[i]
            d.goal_position = np.array([
                d.position[0], d.position[1], self.takeoff_alt])
            d.sending_setpoints = True

    def _rtl_all(self):
        for i in range(self.num_drones):
            self._publish_vehicle_command(
                i, VEHICLE_CMD_DO_SET_MODE, 1.0, 5.0)  # AUTO.RTL
            self.drones[i].sending_setpoints = False

    # ── Setpoint streaming ───────────────────────────────

    def _send_setpoints(self):
        for i in range(self.num_drones):
            d = self.drones[i]
            if not d.sending_setpoints or d.goal_position is None:
                continue

            # Always publish OffboardControlMode (required by PX4)
            ocm = OffboardControlMode()
            ocm.position = True
            ocm.velocity = False
            ocm.acceleration = False
            ocm.attitude = False
            ocm.body_rate = False
            ocm.timestamp = int(self.get_clock().now().nanoseconds / 1000)
            self.offboard_mode_pubs[i].publish(ocm)

            # Publish TrajectorySetpoint (ENU → NED conversion)
            sp = TrajectorySetpoint()
            sp.position[0] = float(d.goal_position[0])   # x (ENU) → x (NED)
            sp.position[1] = float(-d.goal_position[1])   # y (ENU) → -y (NED)
            sp.position[2] = float(-d.goal_position[2])   # z (ENU) → -z (NED)
            sp.yaw = float('nan')  # Let PX4 handle yaw
            sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)
            self.setpoint_pubs[i].publish(sp)

            # After streaming for ~1s, switch to OFFBOARD and arm
            self.offboard_counter[i] += 1
            if self.offboard_counter[i] == 20:  # ~1s at 20Hz
                # Switch to OFFBOARD mode: param1=1 (custom), param2=6 (OFFBOARD)
                self._publish_vehicle_command(
                    i, VEHICLE_CMD_DO_SET_MODE, 1.0, 6.0)
                self.get_logger().info(
                    f'Drone {i}: OFFBOARD mode requested')

            if self.offboard_counter[i] == 25:  # ~0.25s after mode switch
                # Arm
                self._publish_vehicle_command(
                    i, VEHICLE_CMD_COMPONENT_ARM_DISARM, 1.0)
                self.get_logger().info(f'Drone {i}: Arm requested')

    # ── SwarmState publishing ────────────────────────────

    def _publish_swarm_state(self):
        now = self.get_clock().now().nanoseconds / 1e9

        msg = SwarmState()
        msg.timestamp = self.get_clock().now().to_msg()
        msg.num_drones_total = self.num_drones
        msg.num_drones_active = sum(
            1 for d in self.drones.values()
            if d.connected and (now - d.last_status_time) < 5.0)
        msg.num_hubs = sum(
            1 for d in self.drones.values() if d.role == 1)
        msg.num_leaves = sum(
            1 for d in self.drones.values() if d.role == 0)
        msg.mission_state = PHASE_TO_MISSION_STATE.get(
            self.current_phase, 0)

        for i in range(self.num_drones):
            ds = self._make_drone_state(self.drones[i])
            msg.drones.append(ds)
            self.drone_pubs[i].publish(ds)

        # Network metrics (filled by network_sim, defaults here)
        msg.coverage_percent = 0.0
        msg.coverage_quality = 0.0
        msg.avg_throughput_mbps = 0.0
        msg.avg_latency_ms = 0.0
        msg.packet_loss_percent = 0.0
        msg.mesh_connected = False
        msg.backhaul_connected = False

        self.swarm_pub.publish(msg)

    def _make_drone_state(self, d: PX4Drone) -> DroneState:
        ds = DroneState()
        ds.timestamp = self.get_clock().now().to_msg()
        ds.drone_id = d.drone_id
        ds.role = d.role
        ds.position = Point(
            x=float(d.position[0]), y=float(d.position[1]),
            z=float(d.position[2]))
        ds.velocity = Vector3(
            x=float(d.velocity[0]), y=float(d.velocity[1]),
            z=float(d.velocity[2]))
        ds.orientation = Quaternion(
            x=float(d.orientation[0]), y=float(d.orientation[1]),
            z=float(d.orientation[2]), w=float(d.orientation[3]))

        ds.flight_mode = NAV_STATE_TO_FLIGHT_MODE.get(
            d.nav_state, DroneState.FLIGHT_MODE_IDLE)
        ds.armed = d.armed
        ds.battery_percent = float(d.battery_percent)
        ds.battery_voltage = float(d.battery_voltage)
        ds.signal_strength_dbm = -65.0  # Placeholder
        ds.gps_fix = d.gps_fix
        ds.num_satellites = 12  # Placeholder for SITL
        ds.throughput_mbps = 0.0
        ds.latency_ms = 0.0
        ds.connected_neighbors = 0
        return ds


def main(args=None):
    rclpy.init(args=args)
    node = PX4DDSBridge()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info('PX4 DDS Bridge shutting down')
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()
