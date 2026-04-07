# CoverageMap.msg
# Coverage map for RL observation space

std_msgs/Header header
builtin_interfaces/Time timestamp

# Grid parameters
uint32 grid_size_x
uint32 grid_size_y
float32 cell_size_meters
geometry_msgs/Point origin

# Coverage status (flattened arrays)
bool[] is_covered                # Cell has coverage
bool[] is_target                 # Cell is in target coverage area
float32[] demand_level           # 0-1, how much demand at this cell
float32[] coverage_quality       # 0-1, quality of coverage

# Priority zones (e.g., hospitals, rescue staging)
geometry_msgs/Point[] priority_zone_centers
float32[] priority_zone_radii
float32[] priority_zone_weights  # Importance multiplier
