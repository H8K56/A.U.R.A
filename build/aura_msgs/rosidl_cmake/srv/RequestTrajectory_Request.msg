# RequestTrajectory.srv
# Request MINCO to plan trajectory to goal

# Request
uint8 drone_id
geometry_msgs/Point goal_position
float64 max_velocity             # 0 = use default
float64 max_time                 # 0 = no time constraint
bool avoid_weather_zones
