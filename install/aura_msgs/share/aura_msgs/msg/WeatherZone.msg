# WeatherZone.msg
# Weather zone that affects flight and network

builtin_interfaces/Time timestamp
uint32 zone_id

# Zone geometry (cylinder)
geometry_msgs/Point center
float32 radius_meters
float32 min_altitude
float32 max_altitude

# Weather type
uint8 WEATHER_CLEAR = 0
uint8 WEATHER_RAIN = 1
uint8 WEATHER_HEAVY_RAIN = 2
uint8 WEATHER_WIND = 3
uint8 WEATHER_SEVERE_WIND = 4
uint8 WEATHER_DUST = 5
uint8 weather_type

# Severity (0-1, affects penalties)
float32 severity

# Effects
float32 wind_speed_ms            # m/s
float32 wind_direction_rad       # radians from north
float32 signal_attenuation_db    # Additional signal loss
bool no_fly                      # Complete flight restriction

# Timing
builtin_interfaces/Time start_time
builtin_interfaces/Time end_time
bool is_active
