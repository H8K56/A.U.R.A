"""
Mission State Machine for A.U.R.A.

Pure Python state machine with no ROS dependencies.
This separation allows unit testing of transition logic without spinning up
a ROS graph — think of it like separating your game logic from the renderer.

State flow:

    IDLE ─► PREFLIGHT ─► TAKEOFF ─► TRANSIT ─► FORMATION ─► OPERATIONS ─► RTL ─► COMPLETE
      │         │            │          │           │             │          │
      └─────────┴────────────┴──────────┴───────────┴─────────────┘          │
                              (any state) ─► ABORT ◄────────────────────────┘

Design rationale:
  - Each state has ENTRY conditions (what must be true to enter)
  - Each state has EXIT conditions (what triggers transition to next)
  - ABORT is reachable from any state (safety-critical)
  - OPERATIONS is the only state where RL policies are active
"""

from enum import IntEnum
from dataclasses import dataclass, field
from typing import Optional, Callable, Dict, List
import time


class MissionPhase(IntEnum):
    """Mission phases — values match SwarmState.msg and MissionStatus.msg constants"""
    IDLE = 0
    PREFLIGHT = 1
    TAKEOFF = 2
    TRANSIT = 3
    FORMATION = 4
    OPERATIONS = 5
    RTL = 6
    COMPLETE = 7
    ABORT = 8


# Legal transitions (from -> list of valid destinations)
VALID_TRANSITIONS: Dict[MissionPhase, List[MissionPhase]] = {
    MissionPhase.IDLE:       [MissionPhase.PREFLIGHT, MissionPhase.ABORT],
    MissionPhase.PREFLIGHT:  [MissionPhase.TAKEOFF, MissionPhase.ABORT],
    MissionPhase.TAKEOFF:    [MissionPhase.TRANSIT, MissionPhase.ABORT],
    MissionPhase.TRANSIT:    [MissionPhase.FORMATION, MissionPhase.ABORT],
    MissionPhase.FORMATION:  [MissionPhase.OPERATIONS, MissionPhase.ABORT],
    MissionPhase.OPERATIONS: [MissionPhase.RTL, MissionPhase.ABORT],
    MissionPhase.RTL:        [MissionPhase.COMPLETE, MissionPhase.ABORT],
    MissionPhase.COMPLETE:   [MissionPhase.IDLE],
    MissionPhase.ABORT:      [MissionPhase.IDLE],
}


@dataclass
class SwarmReadiness:
    """Snapshot of swarm readiness — populated from ROS messages by the node"""
    num_drones_expected: int = 5
    num_drones_reporting: int = 0
    all_armed: bool = False
    all_gps_fix: bool = False
    min_battery_percent: float = 0.0
    all_at_takeoff_altitude: bool = False
    all_at_deploy_zone: bool = False
    formation_converged: bool = False
    mesh_connected: bool = False
    coverage_percent: float = 0.0
    coverage_target: float = 80.0
    backhaul_active: bool = False
    elapsed_time_sec: float = 0.0
    any_critical_battery: bool = False  # any drone < critical threshold
    any_drone_lost: bool = False        # heartbeat timeout


@dataclass
class MissionConfig:
    """Thresholds and timeouts for phase transitions"""
    # Preflight
    min_battery_for_launch: float = 50.0       # % minimum to start mission
    preflight_timeout_sec: float = 120.0       # abort if preflight takes too long

    # Takeoff
    takeoff_altitude_m: float = 15.0           # target takeoff altitude
    takeoff_altitude_tolerance_m: float = 2.0  # close enough to target
    takeoff_timeout_sec: float = 60.0

    # Transit
    deploy_zone_center: tuple = (0.0, 0.0)     # ENU coordinates
    deploy_zone_radius_m: float = 30.0         # within this = arrived
    transit_timeout_sec: float = 180.0

    # Formation
    formation_convergence_threshold: float = 5.0  # max inter-drone position error (m)
    formation_timeout_sec: float = 120.0
    min_mesh_connectivity: bool = True           # require mesh before OPERATIONS

    # Operations
    min_coverage_for_ops: float = 30.0           # minimum coverage % to stay in ops
    operations_duration_sec: float = 600.0       # mission duration (0 = unlimited)
    coverage_target: float = 80.0

    # Safety
    critical_battery_percent: float = 20.0       # trigger RTL
    lost_drone_timeout_sec: float = 10.0         # heartbeat timeout
    max_drones_lost_before_abort: int = 2        # abort if this many lost


class MissionStateMachine:
    """
    Pure state machine for A.U.R.A. mission lifecycle.

    Usage:
        sm = MissionStateMachine(config)
        sm.start()  # IDLE -> PREFLIGHT

        # Each tick, update readiness and call update():
        sm.readiness.num_drones_reporting = 5
        sm.readiness.all_armed = True
        ...
        new_phase = sm.update()
    """

    def __init__(self, config: MissionConfig = None):
        self.config = config or MissionConfig()
        self.phase = MissionPhase.IDLE
        self.readiness = SwarmReadiness()
        self.phase_start_time = time.monotonic()
        self.mission_start_time: Optional[float] = None
        self.transition_log: List[tuple] = []   # (timestamp, from, to, reason)
        self._on_transition: Optional[Callable] = None

    @property
    def phase_elapsed(self) -> float:
        """Seconds spent in current phase"""
        return time.monotonic() - self.phase_start_time

    @property
    def mission_elapsed(self) -> float:
        """Seconds since mission started (PREFLIGHT)"""
        if self.mission_start_time is None:
            return 0.0
        return time.monotonic() - self.mission_start_time

    @property
    def is_rl_active(self) -> bool:
        """RL policies should only run during OPERATIONS"""
        return self.phase == MissionPhase.OPERATIONS

    def set_transition_callback(self, callback: Callable):
        """Register callback(old_phase, new_phase, reason) for transitions"""
        self._on_transition = callback

    def start(self) -> MissionPhase:
        """Begin mission: IDLE -> PREFLIGHT"""
        return self._transition(MissionPhase.PREFLIGHT, "Mission start commanded")

    def abort(self, reason: str = "Manual abort") -> MissionPhase:
        """Abort from any state"""
        return self._transition(MissionPhase.ABORT, reason)

    def update(self) -> MissionPhase:
        """
        Evaluate current state and transition if conditions are met.
        Call this at the node's tick rate (e.g. 2-5 Hz).

        Returns the current (possibly new) phase.
        """
        r = self.readiness

        # ── Safety checks (any state) ───────────────────────────
        if self.phase not in (MissionPhase.IDLE, MissionPhase.COMPLETE, MissionPhase.ABORT):
            if r.any_critical_battery:
                return self._transition(MissionPhase.RTL,
                                        f"Critical battery ({r.min_battery_percent:.0f}%)")

            if r.any_drone_lost:
                lost_count = r.num_drones_expected - r.num_drones_reporting
                if lost_count >= self.config.max_drones_lost_before_abort:
                    return self._transition(MissionPhase.ABORT,
                                            f"{lost_count} drones lost — aborting")

        # ── Phase-specific logic ────────────────────────────────
        if self.phase == MissionPhase.PREFLIGHT:
            return self._update_preflight()
        elif self.phase == MissionPhase.TAKEOFF:
            return self._update_takeoff()
        elif self.phase == MissionPhase.TRANSIT:
            return self._update_transit()
        elif self.phase == MissionPhase.FORMATION:
            return self._update_formation()
        elif self.phase == MissionPhase.OPERATIONS:
            return self._update_operations()
        elif self.phase == MissionPhase.RTL:
            return self._update_rtl()

        return self.phase

    # ── Phase update methods ────────────────────────────────────

    def _update_preflight(self) -> MissionPhase:
        r = self.readiness

        # Timeout
        if self.phase_elapsed > self.config.preflight_timeout_sec:
            return self._transition(MissionPhase.ABORT, "Preflight timeout")

        # All drones reporting, armed, GPS, battery OK
        if (r.num_drones_reporting >= r.num_drones_expected
                and r.all_armed
                and r.all_gps_fix
                and r.min_battery_percent >= self.config.min_battery_for_launch):
            return self._transition(MissionPhase.TAKEOFF, "Preflight checks passed")

        return self.phase

    def _update_takeoff(self) -> MissionPhase:
        r = self.readiness

        if self.phase_elapsed > self.config.takeoff_timeout_sec:
            return self._transition(MissionPhase.ABORT, "Takeoff timeout")

        if r.all_at_takeoff_altitude:
            return self._transition(MissionPhase.TRANSIT, "All drones at altitude")

        return self.phase

    def _update_transit(self) -> MissionPhase:
        r = self.readiness

        if self.phase_elapsed > self.config.transit_timeout_sec:
            return self._transition(MissionPhase.ABORT, "Transit timeout")

        if r.all_at_deploy_zone:
            return self._transition(MissionPhase.FORMATION, "All drones in deploy zone")

        return self.phase

    def _update_formation(self) -> MissionPhase:
        r = self.readiness

        if self.phase_elapsed > self.config.formation_timeout_sec:
            # Formation timeout isn't necessarily fatal — fall through to ops
            # if mesh is connected, otherwise abort
            if r.mesh_connected:
                return self._transition(MissionPhase.OPERATIONS,
                                        "Formation timeout but mesh connected — proceeding")
            return self._transition(MissionPhase.ABORT, "Formation timeout, no mesh")

        # Need formation converged AND mesh connected
        if r.formation_converged and r.mesh_connected:
            return self._transition(MissionPhase.OPERATIONS,
                                    "Formation converged, mesh established")

        return self.phase

    def _update_operations(self) -> MissionPhase:
        r = self.readiness

        # Time-limited mission
        if (self.config.operations_duration_sec > 0
                and self.phase_elapsed > self.config.operations_duration_sec):
            return self._transition(MissionPhase.RTL, "Operations duration reached")

        # Battery-triggered RTL (non-critical, but getting low)
        if r.min_battery_percent < self.config.critical_battery_percent + 10:
            return self._transition(MissionPhase.RTL,
                                    f"Low battery ({r.min_battery_percent:.0f}%) — returning")

        return self.phase

    def _update_rtl(self) -> MissionPhase:
        r = self.readiness

        # All drones returned and landed (altitude near zero)
        if r.all_at_takeoff_altitude:
            # Reusing this flag to mean "all back at base altitude"
            # In practice you'd check a separate "all_landed" flag
            return self._transition(MissionPhase.COMPLETE, "All drones returned")

        return self.phase

    # ── Transition logic ────────────────────────────────────────

    def _transition(self, new_phase: MissionPhase, reason: str) -> MissionPhase:
        """Execute a state transition if it's valid"""
        if new_phase == self.phase:
            return self.phase

        if new_phase not in VALID_TRANSITIONS.get(self.phase, []):
            # Only exception: ABORT is reachable from anywhere
            if new_phase != MissionPhase.ABORT:
                return self.phase

        old_phase = self.phase
        self.phase = new_phase
        self.phase_start_time = time.monotonic()

        if new_phase == MissionPhase.PREFLIGHT:
            self.mission_start_time = time.monotonic()

        entry = (time.monotonic(), old_phase.name, new_phase.name, reason)
        self.transition_log.append(entry)

        if self._on_transition:
            self._on_transition(old_phase, new_phase, reason)

        return self.phase

    def get_progress_percent(self) -> float:
        """Rough overall mission progress estimate"""
        phase_weights = {
            MissionPhase.IDLE: 0.0,
            MissionPhase.PREFLIGHT: 5.0,
            MissionPhase.TAKEOFF: 15.0,
            MissionPhase.TRANSIT: 30.0,
            MissionPhase.FORMATION: 45.0,
            MissionPhase.OPERATIONS: 50.0,
            MissionPhase.RTL: 90.0,
            MissionPhase.COMPLETE: 100.0,
            MissionPhase.ABORT: 0.0,
        }
        base = phase_weights.get(self.phase, 0.0)

        # During OPERATIONS, progress based on elapsed time
        if self.phase == MissionPhase.OPERATIONS and self.config.operations_duration_sec > 0:
            ops_progress = min(1.0, self.phase_elapsed / self.config.operations_duration_sec)
            base += ops_progress * 40.0  # 50% to 90%

        return min(100.0, base)
