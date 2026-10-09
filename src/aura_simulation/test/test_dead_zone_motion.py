#!/usr/bin/env python3
"""Moving dead zones stay inside the disaster zone.

The bounce used to test `abs(center) > 180` — a box on the origin — and
respond by turning 90 degrees. Once zones moved to the disaster zone at
(120, -170), every zone was permanently outside that box, so the check fired
on every tick and the zone spun in place instead of roaming. A 90-degree turn
is not a reflection: it does not reliably point a zone back inside, and a zone
that starts outside can never return.

The fix clamps to the edge and mirrors the offending component, which is a
real reflection and cannot leave a zone stuck.

These tests drive the geometry directly rather than through rclpy, so they
need no ROS graph.
"""

import math

import pytest

from aura_simulation.dead_zone_publisher import (
    DISASTER_CENTER_X, DISASTER_CENTER_Y, PRESET_ZONES,
    ZONE_ROAM_X_MAX, ZONE_ROAM_X_MIN, ZONE_ROAM_Y_MAX, ZONE_ROAM_Y_MIN,
    ZONE_SPAWN_HALF_WIDTH_M, DeadZone,
)

X_MIN, X_MAX = ZONE_ROAM_X_MIN, ZONE_ROAM_X_MAX
Y_MIN, Y_MAX = ZONE_ROAM_Y_MIN, ZONE_ROAM_Y_MAX


def step(zone, dt=0.5):
    """One tick of the motion update, mirroring DeadZonePublisher.update()."""
    zone.center_x += zone.move_speed * math.cos(zone.move_angle) * dt
    zone.center_y += zone.move_speed * math.sin(zone.move_angle) * dt

    if not X_MIN <= zone.center_x <= X_MAX:
        zone.center_x = min(max(zone.center_x, X_MIN), X_MAX)
        zone.move_angle = math.pi - zone.move_angle
    if not Y_MIN <= zone.center_y <= Y_MAX:
        zone.center_y = min(max(zone.center_y, Y_MIN), Y_MAX)
        zone.move_angle = -zone.move_angle
    zone.move_angle %= 2 * math.pi
    return zone


def moving_zone(x, y, angle, speed=2.0):
    return DeadZone(zone_id=99, name='test', center_x=x, center_y=y,
                    radius_m=20.0, attenuation_db=10.0, is_moving=True,
                    move_speed=speed, move_angle=angle)


def inside(zone):
    return (X_MIN <= zone.center_x <= X_MAX
            and Y_MIN <= zone.center_y <= Y_MAX)


class TestZonesStayInBounds:

    @pytest.mark.parametrize("angle_deg", range(0, 360, 15))
    def test_a_zone_never_leaves_the_box(self, angle_deg):
        zone = moving_zone(DISASTER_CENTER_X, DISASTER_CENTER_Y,
                           math.radians(angle_deg), speed=5.0)
        for tick in range(4000):
            step(zone)
            assert inside(zone), f'escaped at tick {tick}: ' \
                                 f'({zone.center_x:.1f}, {zone.center_y:.1f})'

    def test_a_zone_spawned_outside_is_brought_back(self):
        """The state the old 90-degree turn could not recover from."""
        zone = moving_zone(X_MAX + 500.0, Y_MIN - 500.0, math.radians(45))
        step(zone)
        assert inside(zone)

    @pytest.mark.parametrize("start", [
        (X_MAX + 50.0, DISASTER_CENTER_Y),
        (X_MIN - 50.0, DISASTER_CENTER_Y),
        (DISASTER_CENTER_X, Y_MAX + 50.0),
        (DISASTER_CENTER_X, Y_MIN - 50.0),
    ])
    def test_recovery_from_each_edge(self, start):
        zone = moving_zone(start[0], start[1], math.radians(30))
        step(zone)
        assert inside(zone)

    def test_a_zone_outside_does_not_spin_in_place(self):
        """The old behaviour: turn 90 degrees every tick, never move back.
        After a few ticks the zone must have travelled somewhere real."""
        zone = moving_zone(X_MAX + 100.0, DISASTER_CENTER_Y, 0.0, speed=5.0)
        step(zone)
        start = (zone.center_x, zone.center_y)
        for _ in range(10):
            step(zone)
        moved = math.hypot(zone.center_x - start[0], zone.center_y - start[1])
        assert moved > 1.0, 'zone is stuck at the boundary'


class TestReflectionIsPhysical:

    def test_a_horizontal_bounce_reverses_only_x(self):
        zone = moving_zone(X_MAX - 0.1, DISASTER_CENTER_Y, 0.0, speed=5.0)
        step(zone)
        assert math.cos(zone.move_angle) < 0.0, 'x velocity did not reverse'
        assert abs(math.sin(zone.move_angle)) < 1e-9, 'y velocity changed'

    def test_a_vertical_bounce_reverses_only_y(self):
        zone = moving_zone(DISASTER_CENTER_X, Y_MAX - 0.1,
                           math.pi / 2, speed=5.0)
        step(zone)
        assert math.sin(zone.move_angle) < 0.0, 'y velocity did not reverse'
        assert abs(math.cos(zone.move_angle)) < 1e-9, 'x velocity changed'

    def test_a_corner_bounce_reverses_both(self):
        zone = moving_zone(X_MAX - 0.1, Y_MAX - 0.1,
                           math.radians(45), speed=5.0)
        step(zone)
        assert math.cos(zone.move_angle) < 0.0
        assert math.sin(zone.move_angle) < 0.0

    def test_angle_stays_in_a_single_turn(self):
        """It used to accumulate +pi/2 without wrapping, growing without
        bound for as long as the node ran."""
        zone = moving_zone(DISASTER_CENTER_X, DISASTER_CENTER_Y,
                           math.radians(37), speed=8.0)
        for _ in range(500):
            step(zone)
            assert 0.0 <= zone.move_angle < 2 * math.pi

    def test_a_zone_well_inside_is_untouched(self):
        zone = moving_zone(DISASTER_CENTER_X, DISASTER_CENTER_Y, 0.0, speed=2.0)
        angle_before = zone.move_angle
        step(zone)
        assert zone.move_angle == angle_before
        assert zone.center_x == pytest.approx(DISASTER_CENTER_X + 1.0)


class TestGeometryIsConsistent:

    def test_spawned_zones_start_inside_the_roam_box(self):
        half = ZONE_SPAWN_HALF_WIDTH_M
        assert DISASTER_CENTER_X - half >= X_MIN
        assert DISASTER_CENTER_X + half <= X_MAX
        assert DISASTER_CENTER_Y - half >= Y_MIN
        assert DISASTER_CENTER_Y + half <= Y_MAX

    def test_the_roam_box_is_derived_from_the_coverage_grid(self):
        """Not a hand-written box: a zone outside the grid attenuates ground
        nothing is scoring."""
        from aura_strategic_rl.disaster_scene import GRID_BOUNDS
        assert X_MIN >= GRID_BOUNDS[0]
        assert Y_MIN >= GRID_BOUNDS[1]
        assert X_MAX <= GRID_BOUNDS[2]
        assert Y_MAX <= GRID_BOUNDS[3]

    def test_the_roam_box_is_not_centred_on_the_origin(self):
        centre = ((X_MIN + X_MAX) / 2, (Y_MIN + Y_MAX) / 2)
        assert math.hypot(*centre) > 100.0

    def test_preset_zones_start_inside_the_roam_box(self):
        for key, zone in PRESET_ZONES.items():
            assert X_MIN <= zone.center_x <= X_MAX, key
            assert Y_MIN <= zone.center_y <= Y_MAX, key

    def test_preset_zones_are_near_the_disaster_zone(self):
        """They used to sit in a +/-80 m box on the origin, about 200 m away,
        attenuating ground the swarm never serves."""
        for key, zone in PRESET_ZONES.items():
            offset = math.hypot(zone.center_x - DISASTER_CENTER_X,
                                zone.center_y - DISASTER_CENTER_Y)
            assert offset < 250.0, f'{key} is {offset:.0f} m from the zone'
