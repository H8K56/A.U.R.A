"""
Unit tests for the MissionStateMachine.

These run without ROS — the state machine is pure Python.

Usage:
    python3 -m pytest test/test_state_machine.py -v
    # or
    python3 test/test_state_machine.py
"""

import sys
import time


def test_initial_state():
    """State machine starts in IDLE"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase
    sm = MissionStateMachine()
    assert sm.phase == MissionPhase.IDLE
    assert not sm.is_rl_active


def test_start_transitions_to_preflight():
    """start() moves IDLE -> PREFLIGHT"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase
    sm = MissionStateMachine()
    sm.start()
    assert sm.phase == MissionPhase.PREFLIGHT


def test_full_happy_path():
    """Walk through complete mission lifecycle"""
    from aura_mission_control.state_machine import (
        MissionStateMachine, MissionPhase, MissionConfig
    )

    config = MissionConfig(
        preflight_timeout_sec=999,
        takeoff_timeout_sec=999,
        transit_timeout_sec=999,
        formation_timeout_sec=999,
        operations_duration_sec=0,  # unlimited
    )
    sm = MissionStateMachine(config)
    r = sm.readiness

    # IDLE -> PREFLIGHT
    sm.start()
    assert sm.phase == MissionPhase.PREFLIGHT

    # Satisfy preflight conditions
    r.num_drones_expected = 3
    r.num_drones_reporting = 3
    r.all_armed = True
    r.all_gps_fix = True
    r.min_battery_percent = 90.0
    sm.update()
    assert sm.phase == MissionPhase.TAKEOFF

    # Satisfy takeoff conditions
    r.all_at_takeoff_altitude = True
    sm.update()
    assert sm.phase == MissionPhase.TRANSIT

    # Satisfy transit conditions
    r.all_at_deploy_zone = True
    sm.update()
    assert sm.phase == MissionPhase.FORMATION

    # Satisfy formation conditions
    r.formation_converged = True
    r.mesh_connected = True
    sm.update()
    assert sm.phase == MissionPhase.OPERATIONS
    assert sm.is_rl_active  # <-- RL should be active now


def test_rl_only_active_in_operations():
    """RL policies must only activate during OPERATIONS phase"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase
    sm = MissionStateMachine()

    for phase in MissionPhase:
        sm.phase = phase
        if phase == MissionPhase.OPERATIONS:
            assert sm.is_rl_active, f"RL should be active in {phase.name}"
        else:
            assert not sm.is_rl_active, f"RL should NOT be active in {phase.name}"


def test_critical_battery_triggers_rtl():
    """Critical battery should trigger RTL from any active phase"""
    from aura_mission_control.state_machine import (
        MissionStateMachine, MissionPhase, MissionConfig
    )

    config = MissionConfig(critical_battery_percent=20.0)
    sm = MissionStateMachine(config)
    r = sm.readiness

    # Put into OPERATIONS
    sm.phase = MissionPhase.OPERATIONS
    sm.phase_start_time = time.monotonic()

    r.any_critical_battery = True
    r.min_battery_percent = 15.0
    sm.update()
    assert sm.phase == MissionPhase.RTL


def test_abort_from_any_state():
    """abort() should work from any active state"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase

    for phase in [MissionPhase.PREFLIGHT, MissionPhase.TAKEOFF,
                  MissionPhase.TRANSIT, MissionPhase.FORMATION,
                  MissionPhase.OPERATIONS, MissionPhase.RTL]:
        sm = MissionStateMachine()
        sm.phase = phase
        sm.phase_start_time = time.monotonic()
        sm.abort("test abort")
        assert sm.phase == MissionPhase.ABORT, \
            f"Abort from {phase.name} should work"


def test_lost_drones_trigger_abort():
    """Losing too many drones should abort"""
    from aura_mission_control.state_machine import (
        MissionStateMachine, MissionPhase, MissionConfig
    )

    config = MissionConfig(max_drones_lost_before_abort=2)
    sm = MissionStateMachine(config)
    r = sm.readiness

    sm.phase = MissionPhase.OPERATIONS
    sm.phase_start_time = time.monotonic()

    r.any_drone_lost = True
    r.num_drones_expected = 5
    r.num_drones_reporting = 3  # 2 lost
    sm.update()
    assert sm.phase == MissionPhase.ABORT


def test_preflight_timeout():
    """Preflight should abort on timeout"""
    from aura_mission_control.state_machine import (
        MissionStateMachine, MissionPhase, MissionConfig
    )

    config = MissionConfig(preflight_timeout_sec=0.01)
    sm = MissionStateMachine(config)
    sm.start()

    time.sleep(0.02)  # exceed timeout
    sm.update()
    assert sm.phase == MissionPhase.ABORT


def test_transition_log():
    """Transitions should be logged"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase

    sm = MissionStateMachine()
    sm.start()
    assert len(sm.transition_log) == 1
    assert sm.transition_log[0][1] == 'IDLE'
    assert sm.transition_log[0][2] == 'PREFLIGHT'


def test_invalid_transition_rejected():
    """Cannot skip phases (e.g. IDLE -> OPERATIONS)"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase

    sm = MissionStateMachine()
    # Try to jump directly to OPERATIONS (should be rejected)
    result = sm._transition(MissionPhase.OPERATIONS, "illegal jump")
    assert sm.phase == MissionPhase.IDLE  # should not have changed


def test_progress_percent():
    """Progress should increase through phases"""
    from aura_mission_control.state_machine import MissionStateMachine, MissionPhase

    sm = MissionStateMachine()
    prev_progress = -1.0

    for phase in [MissionPhase.IDLE, MissionPhase.PREFLIGHT,
                  MissionPhase.TAKEOFF, MissionPhase.TRANSIT,
                  MissionPhase.FORMATION, MissionPhase.OPERATIONS]:
        sm.phase = phase
        progress = sm.get_progress_percent()
        assert progress >= prev_progress, \
            f"Progress should increase: {phase.name} = {progress}"
        prev_progress = progress


def run_all():
    """Run all tests manually (without pytest)"""
    tests = [
        test_initial_state,
        test_start_transitions_to_preflight,
        test_full_happy_path,
        test_rl_only_active_in_operations,
        test_critical_battery_triggers_rtl,
        test_abort_from_any_state,
        test_lost_drones_trigger_abort,
        test_preflight_timeout,
        test_transition_log,
        test_invalid_transition_rejected,
        test_progress_percent,
    ]

    passed = 0
    failed = 0

    for test in tests:
        try:
            test()
            print(f"  PASS: {test.__name__}")
            passed += 1
        except Exception as e:
            print(f"  FAIL: {test.__name__}: {e}")
            failed += 1

    print(f"\n  {passed} passed, {failed} failed out of {len(tests)}")
    return failed == 0


if __name__ == '__main__':
    print("=" * 60)
    print("  A.U.R.A. Mission State Machine Tests")
    print("=" * 60)
    success = run_all()
    sys.exit(0 if success else 1)
