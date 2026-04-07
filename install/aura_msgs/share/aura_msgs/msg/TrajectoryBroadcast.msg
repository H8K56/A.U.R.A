# TrajectoryBroadcast.msg
# MINCO trajectory broadcast for decentralized collision avoidance
# Other drones use this to predict where this drone will be

builtin_interfaces/Time timestamp
uint8 drone_id

# Trajectory start time (absolute)
builtin_interfaces/Time start_time

# MINCO parameters
# M-1 intermediate waypoints (q)
geometry_msgs/Point[] waypoints

# M piece durations in seconds (T)
float64[] time_allocation

# Total trajectory duration
float64 total_duration

# Trajectory metadata
uint8 num_pieces                 # M
bool is_valid                    # False if emergency stop active
float32 max_velocity             # m/s, for safety checking
float32 clearance                # meters, collision avoidance radius

# Goal information (for coordination)
geometry_msgs/Point goal_position
bool goal_reached
