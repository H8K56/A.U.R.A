# SwarmState.msg
# Aggregated swarm state for mission control

builtin_interfaces/Time timestamp

# Swarm composition
uint8 num_drones_total
uint8 num_drones_active
uint8 num_hubs
uint8 num_leaves

# Mission state
uint8 MISSION_IDLE = 0
uint8 MISSION_PREFLIGHT = 1
uint8 MISSION_TAKEOFF = 2
uint8 MISSION_TRANSIT = 3
uint8 MISSION_FORMATION = 4
uint8 MISSION_OPERATIONS = 5
uint8 MISSION_RTL = 6
uint8 MISSION_COMPLETE = 7
uint8 MISSION_ABORT = 8
uint8 mission_state

# Coverage metrics
float32 coverage_percent         # 0-100, area covered
float32 coverage_quality         # 0-1, signal quality in covered area

# Network health
float32 avg_throughput_mbps
float32 avg_latency_ms
float32 packet_loss_percent
bool mesh_connected              # Is the mesh fully connected?
bool backhaul_connected          # Is hub connected to command post?

# All drone states
DroneState[] drones
