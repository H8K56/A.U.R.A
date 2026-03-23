# DroneState.msg
# Individual drone state for swarm coordination

# Header
builtin_interfaces/Time timestamp
uint8 drone_id

# Role in swarm
uint8 ROLE_LEAF = 0
uint8 ROLE_HUB = 1
uint8 role

# Position and velocity (ENU frame)
geometry_msgs/Point position
geometry_msgs/Vector3 velocity
geometry_msgs/Quaternion orientation

# Flight status
uint8 FLIGHT_MODE_IDLE = 0
uint8 FLIGHT_MODE_TAKEOFF = 1
uint8 FLIGHT_MODE_TRANSIT = 2
uint8 FLIGHT_MODE_FORMATION = 3
uint8 FLIGHT_MODE_OPERATIONS = 4
uint8 FLIGHT_MODE_RTL = 5
uint8 FLIGHT_MODE_EMERGENCY = 6
uint8 flight_mode

# Health metrics
float32 battery_percent          # 0-100
float32 battery_voltage          # Volts
float32 signal_strength_dbm      # dBm to nearest neighbor
bool gps_fix
uint8 num_satellites

# Network metrics for this drone
float32 throughput_mbps
float32 latency_ms
uint8 connected_neighbors        # Number of mesh connections
