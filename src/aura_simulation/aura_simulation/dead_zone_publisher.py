"""
Network Dead Zone Publisher for A.U.R.A.

Publishes WeatherZone messages representing areas of signal degradation.
Dead zones can be:
  - Pre-configured via YAML (e.g. collapsed building blocking signal)
  - Added/removed at runtime via service calls (for live demos)
  - Moved dynamically to test RL adaptation

The network_sim_node uses these to attenuate signal in affected areas,
causing coverage holes that the RL policy should compensate for.

Usage:
    ros2 run aura_simulation dead_zone_publisher
    ros2 run aura_simulation dead_zone_publisher --ros-args -p num_preset_zones:=2

    # Add a zone at runtime:
    ros2 service call /dead_zones/add aura_msgs/srv/SetFormation \
        "{formation_type: 0}"  # (simplified — see service handler)
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
import numpy as np
import math
from typing import List, Dict
from dataclasses import dataclass, field

from std_srvs.srv import Trigger, SetBool
from geometry_msgs.msg import Point

from aura_msgs.msg import WeatherZone


@dataclass
class DeadZone:
    """Internal representation of a network dead zone"""
    zone_id: int
    name: str
    center_x: float              # ENU meters
    center_y: float
    radius_m: float
    attenuation_db: float        # signal loss in dB (higher = worse)
    is_active: bool = True
    is_moving: bool = False      # for dynamic zones
    move_speed: float = 0.0      # m/s
    move_angle: float = 0.0      # radians, direction of movement


# ── Preset disaster scenarios ───────────────────────────────────

PRESET_ZONES = {
    'collapsed_building': DeadZone(
        zone_id=1,
        name='Collapsed Building',
        center_x=60.0, center_y=40.0,
        radius_m=35.0,
        attenuation_db=20.0,
    ),
    'rubble_field': DeadZone(
        zone_id=2,
        name='Rubble Field',
        center_x=-50.0, center_y=70.0,
        radius_m=25.0,
        attenuation_db=12.0,
    ),
    'underground_parking': DeadZone(
        zone_id=3,
        name='Underground Parking (deep shadow)',
        center_x=30.0, center_y=-60.0,
        radius_m=20.0,
        attenuation_db=30.0,
    ),
    'metal_debris': DeadZone(
        zone_id=4,
        name='Metal Debris Scatter',
        center_x=-80.0, center_y=-30.0,
        radius_m=40.0,
        attenuation_db=8.0,
    ),
}


class DeadZonePublisher(Node):
    """
    Publishes network dead zones as WeatherZone messages.

    Publishes:
        /network/dead_zones    (WeatherZone)  — one message per zone per tick

    Services:
        ~/toggle_zone          (SetBool)      — enable/disable all zones
        ~/add_random_zone      (Trigger)      — add a random new zone
        ~/clear_zones          (Trigger)      — remove all dynamic zones
        ~/toggle_moving        (SetBool)      — enable/disable zone movement
    """

    def __init__(self):
        super().__init__('dead_zone_publisher')

        # ── Parameters ──────────────────────────────────────────
        self.declare_parameter('publish_rate_hz', 2.0)
        self.declare_parameter('num_preset_zones', 2)
        self.declare_parameter('enable_moving_zones', False)
        self.declare_parameter('zone_move_speed', 2.0)

        num_presets = self.get_parameter('num_preset_zones').value
        self.zones_moving = self.get_parameter('enable_moving_zones').value
        self.move_speed = self.get_parameter('zone_move_speed').value

        # ── Load preset zones ───────────────────────────────────
        self.zones: List[DeadZone] = []
        preset_names = list(PRESET_ZONES.keys())
        for i in range(min(num_presets, len(preset_names))):
            zone = PRESET_ZONES[preset_names[i]]
            self.zones.append(zone)
            self.get_logger().info(
                f"Loaded dead zone: '{zone.name}' at "
                f"({zone.center_x:.0f}, {zone.center_y:.0f}) "
                f"r={zone.radius_m:.0f}m atten={zone.attenuation_db:.0f}dB"
            )

        self.next_zone_id = 100  # IDs for dynamically added zones
        self.all_enabled = True

        # ── Publisher ───────────────────────────────────────────
        qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE, depth=10)
        self.zone_pub = self.create_publisher(
            WeatherZone, '/network/dead_zones', qos)

        # ── Services ────────────────────────────────────────────
        self.create_service(
            SetBool, '~/toggle_zone', self._toggle_zone_cb)
        self.create_service(
            Trigger, '~/add_random_zone', self._add_random_zone_cb)
        self.create_service(
            Trigger, '~/clear_zones', self._clear_dynamic_cb)
        self.create_service(
            SetBool, '~/toggle_moving', self._toggle_moving_cb)

        # ── Timer ───────────────────────────────────────────────
        rate = self.get_parameter('publish_rate_hz').value
        self.dt = 1.0 / rate
        self.create_timer(self.dt, self._update)

        self.get_logger().info(
            f"Dead zone publisher started: {len(self.zones)} zones, "
            f"rate={rate} Hz, moving={self.zones_moving}"
        )

    # ── Main loop ───────────────────────────────────────────────

    def _update(self):
        """Update zone positions and publish"""
        if not self.all_enabled:
            return

        for zone in self.zones:
            if not zone.is_active:
                continue

            # Move zone if enabled
            if self.zones_moving and zone.is_moving:
                zone.center_x += zone.move_speed * math.cos(zone.move_angle) * self.dt
                zone.center_y += zone.move_speed * math.sin(zone.move_angle) * self.dt

                # Bounce off boundaries
                bound = 180.0
                if abs(zone.center_x) > bound or abs(zone.center_y) > bound:
                    zone.move_angle += math.pi * 0.5  # turn 90 degrees

            # Publish
            msg = WeatherZone()
            msg.zone_id = zone.zone_id
            # zone_name not in WeatherZone.msg
            msg.center = Point(x=zone.center_x, y=zone.center_y, z=0.0)
            msg.radius_meters = zone.radius_m
            msg.signal_attenuation_db = zone.attenuation_db
            msg.wind_speed_ms = 0.0
            msg.is_active = zone.is_active

            self.zone_pub.publish(msg)

    # ── Service handlers ────────────────────────────────────────

    def _toggle_zone_cb(self, request, response):
        """Enable/disable all zones"""
        self.all_enabled = request.data
        state = "enabled" if self.all_enabled else "disabled"
        response.success = True
        response.message = f"All dead zones {state}"
        self.get_logger().info(response.message)
        return response

    def _add_random_zone_cb(self, request, response):
        """Add a random dead zone"""
        zone = DeadZone(
            zone_id=self.next_zone_id,
            name=f'Dynamic Zone {self.next_zone_id}',
            center_x=np.random.uniform(-120, 120),
            center_y=np.random.uniform(-120, 120),
            radius_m=np.random.uniform(15, 45),
            attenuation_db=np.random.uniform(8, 25),
            is_moving=self.zones_moving,
            move_speed=self.move_speed,
            move_angle=np.random.uniform(0, 2 * math.pi),
        )
        self.zones.append(zone)
        self.next_zone_id += 1

        response.success = True
        response.message = (
            f"Added '{zone.name}' at ({zone.center_x:.0f}, {zone.center_y:.0f}) "
            f"r={zone.radius_m:.0f}m atten={zone.attenuation_db:.0f}dB"
        )
        self.get_logger().info(response.message)
        return response

    def _clear_dynamic_cb(self, request, response):
        """Remove all dynamically added zones (keep presets)"""
        before = len(self.zones)
        self.zones = [z for z in self.zones if z.zone_id < 100]
        removed = before - len(self.zones)
        response.success = True
        response.message = f"Removed {removed} dynamic zones"
        self.get_logger().info(response.message)
        return response

    def _toggle_moving_cb(self, request, response):
        """Enable/disable zone movement"""
        self.zones_moving = request.data
        for zone in self.zones:
            if zone.zone_id >= 100:  # only dynamic zones move
                zone.is_moving = request.data
        state = "enabled" if self.zones_moving else "disabled"
        response.success = True
        response.message = f"Zone movement {state}"
        self.get_logger().info(response.message)
        return response


def main(args=None):
    rclpy.init(args=args)
    node = DeadZonePublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.get_logger().info("Dead zone publisher shutting down")
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()
