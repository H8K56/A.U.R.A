"""
A.U.R.A. Mission Control

Mission state machine and swarm orchestration for the
Autonomous Urban Rescue Array disaster relief UAV swarm.

Manages mission lifecycle:
  IDLE -> PREFLIGHT -> TAKEOFF -> TRANSIT -> FORMATION -> OPERATIONS -> RTL -> COMPLETE

Key responsibilities:
  - Coordinate phase transitions based on swarm readiness
  - Gate RL activation (only during OPERATIONS)
  - Monitor safety conditions and trigger emergency procedures
  - Publish MissionStatus for all other nodes
"""

__version__ = '0.1.0'
