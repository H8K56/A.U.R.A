"""
Simulated Swarm Driver for A.U.R.A.

Software-in-the-loop replacement for PX4 SITL + Gazebo.
Simulates N drones with simplified dynamics that:
  - Start at configurable spawn positions
  - Respond to CoverageGoal messages by flying toward goal positions
  - Publish SwarmState at configurable rate
  - Support mission phase transitions (idle -> takeoff -> transit -> etc.)
  - Model battery drain

This lets you test the full A.U.R.A. software stack (mission control,
network sim, RL policy) without the overhead of a physics simulator.

Think of it as a "mock PX4" — same interface, simplified physics.
"""

import math
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
import numpy as np
from typing import List, Dict, Optional
from dataclasses import dataclass, field

from std_msgs.msg import String
from geometry_msgs.msg import Point, Vector3, Quaternion

from aura_msgs.msg import (
    DroneState,
    SwarmState,
    CoverageGoal,
    MissionStatus,
)


@dataclass
class SimDrone:
    """Internal state of a simulated drone"""
    drone_id: int
    position: np.ndarray          # [x, y, z] ENU meters
    velocity: np.ndarray = field(default_factory=lambda: np.zeros(3))
    battery_percent: float = 100.0
    role: int = 0                 # 0=LEAF, 1=HUB
    flight_mode: int = 0          # matches DroneState constants
    goal_position: Optional[np.ndarray] = None
    armed: bool = False
    gps_fix: bool = True
    num_satellites: int = 12

    # Dynamics
    max_speed: float = 5.0        # m/s
    max_accel: float = 2.0        # m/s^2

    # Battery model
    hover_drain_per_sec: float = 0.015    # %/s while hovering (~11 min flight)
    flight_drain_per_sec: float = 0.025   # %/s while moving


class SimSwarmDriver(Node):
    """
    Simulated swarm driver node.

    Subscribes:
        /coverage/goals       (CoverageGoal)   — position commands from RL/baseline
        /mission/phase        (String)         — mission phase for mode switching

    Publishes:
        /swarm/state          (SwarmState)     — aggregated drone states
        /drone/{id}/state     (DroneState)     — per-drone state
    """

    def __init__(self):
        super().__init__('sim_swarm_driver')

        # ── Parameters ──────────────────────────────────────────
        self.declare_parameter('num_drones', 5)
        self.declare_parameter('publish_rate_hz', 10.0)
        self.declare_parameter('spawn_radius_m', 5.0)
        self.declare_parameter('spawn_altitude_m', 0.5)
        self.declare_parameter('deploy_zone_x', 0.0)
        self.declare_parameter('deploy_zone_y', 0.0)
        self.declare_parameter('takeoff_altitude_m', 15.0)
        self.declare_parameter('max_speed_m_s', 5.0)
        self.declare_parameter('hub_drone_id', 0)

        num_drones = self.get_parameter('num_drones').value
        spawn_radius = self.get_parameter('spawn_radius_m').value
        spawn_alt = self.get_parameter('spawn_altitude_m').value
        self.deploy_x = self.get_parameter('deploy_zone_x').value
        self.deploy_y = self.get_parameter('deploy_zone_y').value
        self.takeoff_alt = self.get_parameter('takeoff_altitude_m').value
        max_speed = self.get_parameter('max_speed_m_s').value
        hub_id = self.get_parameter('hub_drone_id').value

        # ── Initialize drones ───────────────────────────────────
        self.drones: List[SimDrone] = []
        for i in range(num_drones):
            angle = 2 * math.pi * i / num_drones
            pos = np.array([
                spawn_radius * math.cos(angle),
                spawn_radius * math.sin(angle),
                spawn_alt,
            ])
            drone = SimDrone(
                drone_id=i,
                position=pos,
                role=1 if i == hub_id else 0,
                max_speed=max_speed,
            )
            self.drones.append(drone)

        self.current_phase = 'IDLE'
        self.dt = 1.0 / self.get_parameter('publish_rate_hz').value

        # ── QoS ─────────────────────────────────────────────────
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT, depth=5)
        reliable_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE, depth=10)

        # ── Subscribers ─────────────────────────────────────────
        self.goal_sub = self.create_subscription(
            CoverageGoal, '/coverage/goals',
            self._goal_callback, reliable_qos)

        self.phase_sub = self.create_subscription(
            String, '/mission/phase',
            self._phase_callback, reliable_qos)

        # ── Publishers ──────────────────────────────────────────
        # QoS fix: SwarmState must be RELIABLE to match subscribers
        self.swarm_pub = self.create_publisher(
            SwarmState, '/swarm/state', reliable_qos)

        self.drone_pubs: Dict[int, object] = {}
        for drone in self.drones:
            pub = self.create_publisher(
                DroneState, f'/drone_{drone.drone_id}/state', sensor_qos)
            self.drone_pubs[drone.drone_id] = pub

        # ── Main loop ───────────────────────────────────────────
        rate = self.get_parameter('publish_rate_hz').value
        self.update_timer = self.create_timer(1.0 / rate, self._update)

        self.get_logger().info(
            f"Sim swarm driver started: {num_drones} drones, "
            f"rate={rate} Hz, hub=drone_{hub_id}"
        )

    # ── Callbacks ───────────────────────────────────────────────

    def _goal_callback(self, msg: CoverageGoal):
        """Receive position command for a drone"""
        drone_id = msg.drone_id
        if 0 <= drone_id < len(self.drones):
            self.drones[drone_id].goal_position = np.array([
                msg.position.x, msg.position.y, msg.position.z
            ])

    def _phase_callback(self, msg: String):
        """Track current mission phase"""
        old_phase = self.current_phase
        self.current_phase = msg.data

        if old_phase != self.current_phase:
            self.get_logger().info(f"Phase change: {old_phase} -> {self.current_phase}")
            self._handle_phase_change()

    def _handle_phase_change(self):
        """Set drone behavior based on mission phase"""
        phase = self.current_phase

        if phase == 'PREFLIGHT':
            for d in self.drones:
                d.armed = True
                d.flight_mode = DroneState.FLIGHT_MODE_TAKEOFF

        elif phase == 'TAKEOFF':
            for d in self.drones:
                d.flight_mode = DroneState.FLIGHT_MODE_TAKEOFF
                d.goal_position = np.array([
                    d.position[0], d.position[1], self.takeoff_alt
                ])

        elif phase == 'TRANSIT':
            # Fly to deploy zone in a spread formation
            n = len(self.drones)
            for i, d in enumerate(self.drones):
                d.flight_mode = DroneState.FLIGHT_MODE_TRANSIT
                angle = 2 * math.pi * i / n
                spread = 40.0  # meters apart at deploy zone
                d.goal_position = np.array([
                    self.deploy_x + spread * math.cos(angle),
                    self.deploy_y + spread * math.sin(angle),
                    self.takeoff_alt + (10.0 if d.role == 1 else 0.0),
                ])

        elif phase == 'FORMATION':
            for d in self.drones:
                d.flight_mode = DroneState.FLIGHT_MODE_FORMATION
            # Goals will come from the strategic RL / baseline controller

        elif phase == 'OPERATIONS':
            for d in self.drones:
                d.flight_mode = DroneState.FLIGHT_MODE_OPERATIONS
            # RL takes over goal setting

        elif phase == 'RTL':
            for d in self.drones:
                d.flight_mode = DroneState.FLIGHT_MODE_RTL
                d.goal_position = np.array([
                    0.0, 0.0, self.takeoff_alt
                ])

        elif phase in ('COMPLETE', 'ABORT'):
            for d in self.drones:
                d.flight_mode = DroneState.FLIGHT_MODE_TAKEOFF
                d.goal_position = np.array([
                    d.position[0], d.position[1], 0.5
                ])

    # ── Main update loop ────────────────────────────────────────

    def _update(self):
        """Physics step + publish"""
        for drone in self.drones:
            self._step_drone(drone)

        self._publish_swarm_state()

        for drone in self.drones:
            self._publish_drone_state(drone)

    def _step_drone(self, drone: SimDrone):
        """Simplified drone dynamics — move toward goal"""
        if drone.goal_position is None:
            drone.velocity = np.zeros(3)
            self._drain_battery(drone, moving=False)
            return

        direction = drone.goal_position - drone.position
        dist = np.linalg.norm(direction)

        if dist < 0.3:
            # Close enough — hold position
            drone.velocity = np.zeros(3)
            self._drain_battery(drone, moving=False)
            return

        # Compute desired velocity
        speed = min(drone.max_speed, dist / self.dt)

        # Smooth acceleration (simple exponential approach)
        desired_vel = (direction / dist) * speed
        alpha = min(1.0, drone.max_accel * self.dt / max(0.1, np.linalg.norm(desired_vel)))
        drone.velocity = drone.velocity * (1 - alpha) + desired_vel * alpha

        # Clamp speed
        vel_mag = np.linalg.norm(drone.velocity)
        if vel_mag > drone.max_speed:
            drone.velocity = drone.velocity / vel_mag * drone.max_speed

        # Update position
        drone.position += drone.velocity * self.dt

        # Battery drain
        self._drain_battery(drone, moving=True)

    def _drain_battery(self, drone: SimDrone, moving: bool):
        """Simple battery drain model"""
        if not drone.armed:
            return

        rate = drone.flight_drain_per_sec if moving else drone.hover_drain_per_sec
        drone.battery_percent = max(0.0, drone.battery_percent - rate * self.dt)

    # ── Publishing ──────────────────────────────────────────────

    def _publish_swarm_state(self):
        """Publish aggregated SwarmState"""
        msg = SwarmState()
        msg.timestamp = self.get_clock().now().to_msg()

        msg.num_drones_total = len(self.drones)
        msg.num_drones_active = sum(1 for d in self.drones if d.armed)
        msg.num_hubs = sum(1 for d in self.drones if d.role == 1)
        msg.num_leaves = sum(1 for d in self.drones if d.role == 0)

        # Mission state from phase
        phase_map = {
            'IDLE': SwarmState.MISSION_IDLE,
            'PREFLIGHT': SwarmState.MISSION_PREFLIGHT,
            'TAKEOFF': SwarmState.MISSION_TAKEOFF,
            'TRANSIT': SwarmState.MISSION_TRANSIT,
            'FORMATION': SwarmState.MISSION_FORMATION,
            'OPERATIONS': SwarmState.MISSION_OPERATIONS,
            'RTL': SwarmState.MISSION_RTL,
            'COMPLETE': SwarmState.MISSION_COMPLETE,
            'ABORT': SwarmState.MISSION_ABORT,
        }
        msg.mission_state = phase_map.get(self.current_phase, SwarmState.MISSION_IDLE)

        # Aggregate metrics
        batteries = [d.battery_percent for d in self.drones]
        msg.coverage_percent = 0.0  # network_sim will compute this
        msg.coverage_quality = 0.0
        msg.avg_throughput_mbps = 0.0
        msg.avg_latency_ms = 0.0
        msg.packet_loss_percent = 0.0
        msg.mesh_connected = False   # network_sim will compute this
        msg.backhaul_connected = False

        # Drone states
        for drone in self.drones:
            ds = self._make_drone_state(drone)
            msg.drones.append(ds)

        self.swarm_pub.publish(msg)

    def _publish_drone_state(self, drone: SimDrone):
        """Publish individual DroneState"""
        ds = self._make_drone_state(drone)
        self.drone_pubs[drone.drone_id].publish(ds)

    def _make_drone_state(self, drone: SimDrone) -> DroneState:
        """Build DroneState message from SimDrone"""
        ds = DroneState()
        ds.timestamp = self.get_clock().now().to_msg()
        ds.drone_id = drone.drone_id
        ds.role = drone.role

        ds.position = Point(
            x=float(drone.position[0]),
            y=float(drone.position[1]),
            z=float(drone.position[2]),
        )
        ds.velocity = Vector3(
            x=float(drone.velocity[0]),
            y=float(drone.velocity[1]),
            z=float(drone.velocity[2]),
        )
        ds.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)

        ds.flight_mode = drone.flight_mode
        ds.battery_percent = float(drone.battery_percent)
        ds.battery_voltage = 14.8 * (drone.battery_percent / 100.0)
        ds.signal_strength_dbm = -65.0  # placeholder, network_sim overrides
        ds.gps_fix = drone.gps_fix
        ds.num_satellites = drone.num_satellites

        ds.throughput_mbps = 0.0
        ds.latency_ms = 0.0
        ds.connected_neighbors = 0

        return ds


def main(args=None):
    rclpy.init(args=args)
    node = SimSwarmDriver()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info("Sim swarm driver shutting down")
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()
