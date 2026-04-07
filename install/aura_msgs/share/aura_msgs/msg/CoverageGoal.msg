# CoverageGoal.msg
# Goal position from Strategic RL to MINCO trajectory planner

builtin_interfaces/Time timestamp
uint8 drone_id

# Target position (ENU frame)
geometry_msgs/Point position

# Optional: desired arrival time (0 = ASAP)
float64 desired_arrival_time

# Formation info
uint8 FORMATION_SPREAD = 0       # Maximize coverage area
uint8 FORMATION_CLUSTER = 1      # Cluster for high-density area
uint8 FORMATION_LINE = 2         # Line formation for corridor
uint8 FORMATION_ADAPTIVE = 3     # Let RL decide
uint8 formation_type

# Priority (higher = more important to reach)
float32 priority                 # 0-1

# Constraints
float32 min_altitude             # meters
float32 max_altitude             # meters
float32 max_velocity             # m/s, 0 = use default

# Network requirements at this position
float32 required_throughput_mbps # Minimum throughput needed
float32 required_coverage_radius # meters
