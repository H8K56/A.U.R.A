# MissionStatus.msg
# Mission progress and status

builtin_interfaces/Time timestamp
string mission_id

# Mission phase
uint8 PHASE_INIT = 0
uint8 PHASE_PREFLIGHT = 1
uint8 PHASE_LAUNCH = 2
uint8 PHASE_TRANSIT = 3
uint8 PHASE_DEPLOY = 4
uint8 PHASE_OPERATIONS = 5
uint8 PHASE_RECOVERY = 6
uint8 PHASE_COMPLETE = 7
uint8 PHASE_ABORT = 8
uint8 phase

# Progress
float32 progress_percent         # 0-100
float32 elapsed_time_sec
float32 estimated_remaining_sec

# Objectives status
float32 coverage_achieved        # 0-100
float32 network_quality          # 0-1
uint32 connections_established   # Number of user connections
uint32 data_transferred_mb

# Alerts
string[] active_alerts
uint8[] alert_severities         # 0=info, 1=warning, 2=critical

# Drone status summary
uint8 drones_operational
uint8 drones_degraded
uint8 drones_failed
