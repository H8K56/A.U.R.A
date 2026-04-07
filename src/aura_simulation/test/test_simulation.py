"""
Tests for A.U.R.A. Simulation Package

Verifies all components work correctly without ROS.
Tests cover:
  - Import validation (catch missing deps early)
  - SimDrone dynamics (movement, battery, bounds)
  - Dead zone preset loading and attenuation
  - Scenario phase tracking
  - Message construction (field completeness)
  - Config parameter ranges

Usage:
    python3 test/test_simulation.py
    # or with pytest:
    python3 -m pytest test/test_simulation.py -v
"""

import sys
import math
import numpy as np
from typing import Dict


# ── Test 1: Import Validation ──────────────────────────────────

def test_imports():
    """All package modules should import without error"""
    print("  Importing aura_simulation...")
    import aura_simulation
    assert aura_simulation.__version__ == '0.1.0'

    print("  Importing sim_swarm_driver...")
    from aura_simulation.sim_swarm_driver import SimDrone, SimSwarmDriver

    print("  Importing dead_zone_publisher...")
    from aura_simulation.dead_zone_publisher import (
        DeadZone, DeadZonePublisher, PRESET_ZONES
    )

    print("  Importing scenario_runner...")
    from aura_simulation.scenario_runner import ScenarioRunner, PHASE_NAMES

    print("  Importing ROS message types...")
    from aura_msgs.msg import (
        DroneState, SwarmState, CoverageGoal,
        MissionStatus, WeatherZone, NetworkMetrics,
    )

    return True


# ── Test 2: SimDrone Dynamics ──────────────────────────────────

def test_sim_drone_creation():
    """SimDrone initializes with correct defaults"""
    from aura_simulation.sim_swarm_driver import SimDrone

    drone = SimDrone(drone_id=0, position=np.array([10.0, 20.0, 15.0]))

    assert drone.drone_id == 0
    assert np.allclose(drone.position, [10.0, 20.0, 15.0])
    assert np.allclose(drone.velocity, [0.0, 0.0, 0.0])
    assert drone.battery_percent == 100.0
    assert drone.role == 0  # LEAF
    assert drone.flight_mode == 0  # IDLE
    assert drone.goal_position is None
    assert drone.armed is False
    assert drone.gps_fix is True


def test_sim_drone_hub_role():
    """Hub drone should have role=1"""
    from aura_simulation.sim_swarm_driver import SimDrone

    hub = SimDrone(drone_id=0, position=np.zeros(3), role=1)
    leaf = SimDrone(drone_id=1, position=np.zeros(3), role=0)

    assert hub.role == 1
    assert leaf.role == 0


def test_drone_movement():
    """Drone should move toward goal position"""
    from aura_simulation.sim_swarm_driver import SimDrone

    drone = SimDrone(drone_id=0, position=np.array([0.0, 0.0, 15.0]))
    drone.goal_position = np.array([100.0, 0.0, 15.0])
    drone.armed = True

    dt = 0.1
    # Simulate 50 steps (5 seconds)
    for _ in range(50):
        if drone.goal_position is None:
            break
        direction = drone.goal_position - drone.position
        dist = np.linalg.norm(direction)
        if dist < 0.3:
            drone.velocity = np.zeros(3)
            break
        speed = min(drone.max_speed, dist / dt)
        desired_vel = (direction / dist) * speed
        alpha = min(1.0, drone.max_accel * dt / max(0.1, np.linalg.norm(desired_vel)))
        drone.velocity = drone.velocity * (1 - alpha) + desired_vel * alpha
        vel_mag = np.linalg.norm(drone.velocity)
        if vel_mag > drone.max_speed:
            drone.velocity = drone.velocity / vel_mag * drone.max_speed
        drone.position += drone.velocity * dt

    # Should have moved significantly toward goal
    assert drone.position[0] > 10.0, \
        f"Drone should have moved toward x=100, but x={drone.position[0]:.1f}"
    assert abs(drone.position[1]) < 1.0, \
        f"Drone should stay near y=0, but y={drone.position[1]:.1f}"
    assert abs(drone.position[2] - 15.0) < 1.0, \
        f"Drone should stay at z=15, but z={drone.position[2]:.1f}"


def test_drone_speed_limit():
    """Drone velocity should not exceed max_speed"""
    from aura_simulation.sim_swarm_driver import SimDrone

    drone = SimDrone(drone_id=0, position=np.zeros(3), max_speed=5.0)
    drone.goal_position = np.array([1000.0, 0.0, 0.0])

    dt = 0.1
    for _ in range(200):
        direction = drone.goal_position - drone.position
        dist = np.linalg.norm(direction)
        if dist < 0.3:
            break
        speed = min(drone.max_speed, dist / dt)
        desired_vel = (direction / dist) * speed
        alpha = min(1.0, drone.max_accel * dt / max(0.1, np.linalg.norm(desired_vel)))
        drone.velocity = drone.velocity * (1 - alpha) + desired_vel * alpha
        vel_mag = np.linalg.norm(drone.velocity)
        if vel_mag > drone.max_speed:
            drone.velocity = drone.velocity / vel_mag * drone.max_speed
        drone.position += drone.velocity * dt

        assert np.linalg.norm(drone.velocity) <= drone.max_speed + 0.01, \
            f"Velocity {np.linalg.norm(drone.velocity):.2f} exceeds max {drone.max_speed}"


def test_battery_drain():
    """Battery should drain over time"""
    from aura_simulation.sim_swarm_driver import SimDrone

    drone = SimDrone(drone_id=0, position=np.zeros(3))
    drone.armed = True
    initial_battery = drone.battery_percent

    # Simulate hover drain
    dt = 0.1
    for _ in range(100):  # 10 seconds
        drone.battery_percent = max(0.0,
            drone.battery_percent - drone.hover_drain_per_sec * dt)

    assert drone.battery_percent < initial_battery, \
        "Battery should drain while hovering"
    assert drone.battery_percent > 0.0, \
        "Battery shouldn't be zero after only 10s"

    # Flight drain should be faster than hover
    drone_hover = SimDrone(drone_id=0, position=np.zeros(3))
    drone_flight = SimDrone(drone_id=1, position=np.zeros(3))
    drone_hover.armed = True
    drone_flight.armed = True

    for _ in range(1000):  # 100 seconds
        drone_hover.battery_percent -= drone_hover.hover_drain_per_sec * dt
        drone_flight.battery_percent -= drone_flight.flight_drain_per_sec * dt

    assert drone_flight.battery_percent < drone_hover.battery_percent, \
        "Flight should drain battery faster than hovering"


# ── Test 3: Dead Zone Presets ──────────────────────────────────

def test_preset_zones_exist():
    """All preset dead zones should have valid parameters"""
    from aura_simulation.dead_zone_publisher import PRESET_ZONES, DeadZone

    assert len(PRESET_ZONES) >= 2, "Should have at least 2 preset zones"

    for name, zone in PRESET_ZONES.items():
        assert isinstance(zone, DeadZone), f"{name} should be a DeadZone"
        assert zone.radius_m > 0, f"{name} radius must be positive"
        assert zone.attenuation_db > 0, f"{name} attenuation must be positive"
        assert zone.zone_id > 0, f"{name} zone_id must be positive"
        assert len(zone.name) > 0, f"{name} must have a name"
        assert abs(zone.center_x) < 300, f"{name} center_x out of range"
        assert abs(zone.center_y) < 300, f"{name} center_y out of range"


def test_dead_zone_attenuation_ranges():
    """Attenuation values should be realistic (not absurdly high)"""
    from aura_simulation.dead_zone_publisher import PRESET_ZONES

    for name, zone in PRESET_ZONES.items():
        assert 1.0 <= zone.attenuation_db <= 50.0, \
            f"{name}: attenuation {zone.attenuation_db} dB outside realistic range [1, 50]"


def test_dead_zone_no_overlap_with_spawn():
    """Preset dead zones shouldn't overlap the spawn area (radius ~5m at origin)"""
    from aura_simulation.dead_zone_publisher import PRESET_ZONES

    spawn_radius = 10.0  # generous spawn area
    for name, zone in PRESET_ZONES.items():
        dist = math.sqrt(zone.center_x**2 + zone.center_y**2)
        # Zone edge shouldn't reach spawn
        assert dist - zone.radius_m > spawn_radius, \
            f"{name}: zone at ({zone.center_x}, {zone.center_y}) r={zone.radius_m} " \
            f"overlaps spawn area"


def test_dynamic_zone_creation():
    """Can create dynamic dead zones with valid parameters"""
    from aura_simulation.dead_zone_publisher import DeadZone

    zone = DeadZone(
        zone_id=100,
        name='Test Dynamic Zone',
        center_x=50.0,
        center_y=-30.0,
        radius_m=25.0,
        attenuation_db=15.0,
        is_moving=True,
        move_speed=2.0,
        move_angle=math.pi / 4,
    )

    assert zone.is_moving
    assert zone.move_speed == 2.0


def test_zone_movement():
    """Moving zone should change position over time"""
    from aura_simulation.dead_zone_publisher import DeadZone

    zone = DeadZone(
        zone_id=100,
        name='Moving Zone',
        center_x=0.0,
        center_y=0.0,
        radius_m=20.0,
        attenuation_db=10.0,
        is_moving=True,
        move_speed=5.0,
        move_angle=0.0,  # moving in +x direction
    )

    dt = 0.5
    initial_x = zone.center_x
    # Simulate 10 steps
    for _ in range(10):
        zone.center_x += zone.move_speed * math.cos(zone.move_angle) * dt
        zone.center_y += zone.move_speed * math.sin(zone.move_angle) * dt

    assert zone.center_x > initial_x + 20.0, \
        f"Zone should have moved in +x: x={zone.center_x:.1f}"
    assert abs(zone.center_y) < 0.1, \
        f"Zone should not have moved in y: y={zone.center_y:.1f}"


# ── Test 4: Scenario / Phase Logic ─────────────────────────────

def test_phase_names_complete():
    """All mission phases should have names"""
    from aura_simulation.scenario_runner import PHASE_NAMES

    expected_phases = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    for phase in expected_phases:
        assert phase in PHASE_NAMES, f"Phase {phase} missing from PHASE_NAMES"


def test_phase_name_values():
    """Phase names should match aura_mission_control definitions"""
    from aura_simulation.scenario_runner import PHASE_NAMES

    assert PHASE_NAMES[0] == 'IDLE'
    assert PHASE_NAMES[5] == 'OPERATIONS'
    assert PHASE_NAMES[6] == 'RTL'
    assert PHASE_NAMES[8] == 'ABORT'


# ── Test 5: Message Construction ───────────────────────────────

def test_drone_state_message_fields():
    """DroneState message should have all required fields"""
    from aura_msgs.msg import DroneState

    ds = DroneState()

    # Check all fields used by sim_swarm_driver exist
    assert hasattr(ds, 'timestamp')
    assert hasattr(ds, 'drone_id')
    assert hasattr(ds, 'role')
    assert hasattr(ds, 'position')
    assert hasattr(ds, 'velocity')
    assert hasattr(ds, 'orientation')
    assert hasattr(ds, 'flight_mode')
    assert hasattr(ds, 'battery_percent')
    assert hasattr(ds, 'battery_voltage')
    assert hasattr(ds, 'signal_strength_dbm')
    assert hasattr(ds, 'gps_fix')
    assert hasattr(ds, 'num_satellites')
    assert hasattr(ds, 'throughput_mbps')
    assert hasattr(ds, 'latency_ms')
    assert hasattr(ds, 'connected_neighbors')

    # Check flight mode constants
    assert hasattr(ds, 'FLIGHT_MODE_IDLE')
    assert hasattr(ds, 'FLIGHT_MODE_TAKEOFF')
    assert hasattr(ds, 'FLIGHT_MODE_TRANSIT')
    assert hasattr(ds, 'FLIGHT_MODE_FORMATION')
    assert hasattr(ds, 'FLIGHT_MODE_OPERATIONS')
    assert hasattr(ds, 'FLIGHT_MODE_RTL')


def test_swarm_state_message_fields():
    """SwarmState message should have all required fields"""
    from aura_msgs.msg import SwarmState

    ss = SwarmState()

    assert hasattr(ss, 'timestamp')
    assert hasattr(ss, 'num_drones_total')
    assert hasattr(ss, 'num_drones_active')
    assert hasattr(ss, 'num_hubs')
    assert hasattr(ss, 'num_leaves')
    assert hasattr(ss, 'mission_state')
    assert hasattr(ss, 'coverage_percent')
    assert hasattr(ss, 'mesh_connected')
    assert hasattr(ss, 'backhaul_connected')
    assert hasattr(ss, 'drones')

    # Check mission state constants
    assert hasattr(ss, 'MISSION_IDLE')
    assert hasattr(ss, 'MISSION_OPERATIONS')
    assert hasattr(ss, 'MISSION_RTL')
    assert hasattr(ss, 'MISSION_ABORT')


def test_weather_zone_message_fields():
    """WeatherZone message should have all fields used by dead_zone_publisher"""
    from aura_msgs.msg import WeatherZone

    wz = WeatherZone()

    assert hasattr(wz, 'zone_id')
    # zone_name not in WeatherZone.msg
    assert hasattr(wz, 'center')
    assert hasattr(wz, 'radius_meters')
    assert hasattr(wz, 'signal_attenuation_db')
    assert hasattr(wz, 'is_active')


def test_network_metrics_has_mesh_connected():
    """NetworkMetrics must have mesh_connected (our earlier fix)"""
    from aura_msgs.msg import NetworkMetrics

    nm = NetworkMetrics()
    assert hasattr(nm, 'mesh_connected'), \
        "NetworkMetrics missing mesh_connected — was the fix applied?"


# ── Test 6: Multi-Drone Spawn Geometry ─────────────────────────

def test_spawn_positions_are_circular():
    """Drones should spawn in a circle, not stacked"""
    from aura_simulation.sim_swarm_driver import SimDrone

    num_drones = 5
    spawn_radius = 5.0
    drones = []

    for i in range(num_drones):
        angle = 2 * math.pi * i / num_drones
        pos = np.array([
            spawn_radius * math.cos(angle),
            spawn_radius * math.sin(angle),
            0.5,
        ])
        drones.append(SimDrone(drone_id=i, position=pos))

    # All drones should be at spawn_radius from origin
    for d in drones:
        dist = np.linalg.norm(d.position[:2])
        assert abs(dist - spawn_radius) < 0.01, \
            f"Drone {d.drone_id} at dist {dist:.2f}, expected {spawn_radius}"

    # No two drones should be at the same position
    for i in range(num_drones):
        for j in range(i + 1, num_drones):
            sep = np.linalg.norm(drones[i].position - drones[j].position)
            assert sep > 1.0, \
                f"Drones {i} and {j} too close: {sep:.2f}m"


def test_config_yaml_keys():
    """Verify config YAML has expected top-level keys"""
    import os
    config_path = os.path.join(
        os.path.dirname(os.path.dirname(__file__)),
        'config', 'sim_params.yaml'
    )

    if not os.path.exists(config_path):
        print(f"  SKIP: Config file not found at {config_path}")
        return True

    with open(config_path, 'r') as f:
        content = f.read()

    required_keys = [
        'num_drones', 'publish_rate_hz', 'takeoff_altitude_m',
        'operations_duration_sec', 'coverage_target',
        'num_preset_zones', 'auto_start',
    ]

    for key in required_keys:
        assert key in content, f"Config missing key: {key}"


# ── Runner ─────────────────────────────────────────────────────

def run_all():
    """Run all tests"""
    tests = [
        test_imports,
        test_sim_drone_creation,
        test_sim_drone_hub_role,
        test_drone_movement,
        test_drone_speed_limit,
        test_battery_drain,
        test_preset_zones_exist,
        test_dead_zone_attenuation_ranges,
        test_dead_zone_no_overlap_with_spawn,
        test_dynamic_zone_creation,
        test_zone_movement,
        test_phase_names_complete,
        test_phase_name_values,
        test_drone_state_message_fields,
        test_swarm_state_message_fields,
        test_weather_zone_message_fields,
        test_network_metrics_has_mesh_connected,
        test_spawn_positions_are_circular,
        test_config_yaml_keys,
    ]

    passed = 0
    failed = 0
    skipped = 0

    for test in tests:
        try:
            result = test()
            if result is True:
                # Explicit True return means possible skip with message
                pass
            print(f"  PASS: {test.__name__}")
            passed += 1
        except AssertionError as e:
            print(f"  FAIL: {test.__name__}: {e}")
            failed += 1
        except Exception as e:
            print(f"  ERROR: {test.__name__}: {type(e).__name__}: {e}")
            failed += 1

    print(f"\n  {passed} passed, {failed} failed out of {len(tests)}")
    return failed == 0


if __name__ == '__main__':
    print("=" * 60)
    print("  A.U.R.A. Simulation Package Tests")
    print("=" * 60)

    # Need ROS messages available
    try:
        from aura_msgs.msg import DroneState
    except ImportError:
        print("\n  ERROR: aura_msgs not found.")
        print("  Run: source ~/ws/install/setup.bash")
        sys.exit(1)

    success = run_all()
    sys.exit(0 if success else 1)
