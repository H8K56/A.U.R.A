#!/usr/bin/env python3
"""Mission decisions when network telemetry is missing.

NetworkMetrics is the only authoritative source for mesh state and coverage.
SwarmState carries the same field names, but every publisher sets them to a
hardcoded False/0.0 and nothing fills them in — so mission_control's old
fallback turned a dropped topic into "coverage 0%, mesh down". At formation
timeout that aborts the mission, which made a telemetry outage
indistinguishable from an actual mesh failure.

These tests pin the distinction: "mesh down" and "cannot tell" must lead to
different reported outcomes, and unknown must never be read as confirmed.

Runs without ROS — the state machine is pure Python.
"""

import time

import pytest

from aura_mission_control.state_machine import (
    MissionConfig, MissionPhase, MissionStateMachine,
)


def last_reason(sm) -> str:
    """Reason recorded for the most recent transition."""
    assert sm.transition_log, 'no transition was recorded'
    return sm.transition_log[-1][3]


def set_elapsed(sm, seconds: float) -> None:
    """phase_elapsed is derived from phase_start_time, so age the start."""
    sm.phase_start_time = time.monotonic() - seconds


def formation_ready(sm, *, mesh: bool, valid: bool, converged: bool = True):
    """Put the machine in FORMATION with a given network picture."""
    r = sm.readiness
    r.num_drones_expected = 5
    r.num_drones_reporting = 5
    r.formation_converged = converged
    r.mesh_connected = mesh
    r.network_data_valid = valid
    r.min_battery_percent = 80.0
    return r


def make_sm(**config_over):
    kwargs = dict(preflight_timeout_sec=999, takeoff_timeout_sec=999,
                  transit_timeout_sec=999, formation_timeout_sec=999,
                  operations_duration_sec=999)
    kwargs.update(config_over)
    config = MissionConfig(**kwargs)
    sm = MissionStateMachine(config=config)
    sm.phase = MissionPhase.FORMATION
    set_elapsed(sm, 0.0)
    return sm


class TestDefaultIsUnknown:

    def test_readiness_starts_with_invalid_network_data(self):
        """Nothing has arrived yet, so nothing is known."""
        sm = MissionStateMachine()
        assert sm.readiness.network_data_valid is False

    def test_unknown_is_not_treated_as_connected(self):
        sm = MissionStateMachine()
        assert sm.readiness.mesh_connected is False
        assert sm.readiness.network_data_valid is False


class TestFormationGate:

    def test_confirmed_mesh_enters_operations(self):
        sm = make_sm()
        formation_ready(sm, mesh=True, valid=True)
        assert sm._update_formation() == MissionPhase.OPERATIONS

    def test_unknown_mesh_holds_in_formation(self):
        """Unknown is not confirmed. Entering OPERATIONS unmonitored would
        start the relay mission with no way to see whether it is working."""
        sm = make_sm()
        formation_ready(sm, mesh=True, valid=False)
        assert sm._update_formation() == MissionPhase.FORMATION

    def test_confirmed_no_mesh_holds_in_formation(self):
        sm = make_sm()
        formation_ready(sm, mesh=False, valid=True)
        assert sm._update_formation() == MissionPhase.FORMATION

    def test_unconverged_formation_holds_even_with_mesh(self):
        sm = make_sm()
        formation_ready(sm, mesh=True, valid=True, converged=False)
        assert sm._update_formation() == MissionPhase.FORMATION


class TestFormationTimeout:
    """All three paths still abort or proceed as before — only the reported
    reason changes, and that is the whole point."""

    def test_timeout_with_confirmed_mesh_proceeds(self):
        sm = make_sm(formation_timeout_sec=10.0)
        formation_ready(sm, mesh=True, valid=True)
        set_elapsed(sm, 20.0)
        assert sm._update_formation() == MissionPhase.OPERATIONS

    def test_timeout_with_confirmed_no_mesh_aborts_for_no_mesh(self):
        sm = make_sm(formation_timeout_sec=10.0)
        formation_ready(sm, mesh=False, valid=True)
        set_elapsed(sm, 20.0)
        assert sm._update_formation() == MissionPhase.ABORT
        assert 'no mesh' in last_reason(sm).lower()
        assert 'telemetry' not in last_reason(sm).lower()

    def test_timeout_with_unknown_mesh_aborts_naming_telemetry(self):
        """Regression: this used to abort with "Formation timeout, no mesh",
        blaming the swarm for a dead topic."""
        sm = make_sm(formation_timeout_sec=10.0)
        formation_ready(sm, mesh=False, valid=False)
        set_elapsed(sm, 20.0)
        assert sm._update_formation() == MissionPhase.ABORT
        reason = last_reason(sm).lower()
        assert 'telemetry' in reason
        assert 'unknown' in reason

    def test_stale_telemetry_claiming_mesh_up_is_not_believed(self):
        """A stale message saying the mesh was fine must not let the timeout
        path proceed into OPERATIONS."""
        sm = make_sm(formation_timeout_sec=10.0)
        formation_ready(sm, mesh=True, valid=False)
        set_elapsed(sm, 20.0)
        assert sm._update_formation() == MissionPhase.ABORT
        assert 'telemetry' in last_reason(sm).lower()


class TestOperationsIsUnaffected:
    """Losing telemetry during OPERATIONS must not itself end the mission —
    the phase transitions there key off duration and battery only."""

    def test_unknown_network_does_not_leave_operations(self):
        config = MissionConfig(operations_duration_sec=999)
        sm = MissionStateMachine(config=config)
        sm.phase = MissionPhase.OPERATIONS
        set_elapsed(sm, 1.0)
        r = sm.readiness
        r.min_battery_percent = 80.0
        r.network_data_valid = False
        r.mesh_connected = False
        assert sm._update_operations() == MissionPhase.OPERATIONS

    def test_low_battery_still_triggers_rtl(self):
        config = MissionConfig(operations_duration_sec=999,
                               critical_battery_percent=15.0)
        sm = MissionStateMachine(config=config)
        sm.phase = MissionPhase.OPERATIONS
        set_elapsed(sm, 1.0)
        r = sm.readiness
        r.min_battery_percent = 20.0  # within critical + 10
        r.network_data_valid = True
        assert sm._update_operations() == MissionPhase.RTL


class TestRlSafetyBoundaryUnchanged:
    """The RL policy must still only be active in OPERATIONS — this change
    touches the gate into that phase, so the boundary is re-checked."""

    @pytest.mark.parametrize("phase", [
        MissionPhase.IDLE, MissionPhase.PREFLIGHT, MissionPhase.TAKEOFF,
        MissionPhase.TRANSIT, MissionPhase.FORMATION, MissionPhase.RTL,
        MissionPhase.COMPLETE, MissionPhase.ABORT,
    ])
    def test_rl_inactive_outside_operations(self, phase):
        sm = MissionStateMachine()
        sm.phase = phase
        assert sm.is_rl_active is False

    def test_rl_active_in_operations(self):
        sm = MissionStateMachine()
        sm.phase = MissionPhase.OPERATIONS
        assert sm.is_rl_active is True
