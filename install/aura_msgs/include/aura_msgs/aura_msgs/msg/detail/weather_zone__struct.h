// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'WEATHER_CLEAR'.
/**
  * Weather type
 */
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_CLEAR = 0
};

/// Constant 'WEATHER_RAIN'.
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_RAIN = 1
};

/// Constant 'WEATHER_HEAVY_RAIN'.
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_HEAVY_RAIN = 2
};

/// Constant 'WEATHER_WIND'.
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_WIND = 3
};

/// Constant 'WEATHER_SEVERE_WIND'.
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_SEVERE_WIND = 4
};

/// Constant 'WEATHER_DUST'.
enum
{
  aura_msgs__msg__WeatherZone__WEATHER_DUST = 5
};

// Include directives for member types
// Member 'timestamp'
// Member 'start_time'
// Member 'end_time'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/WeatherZone in the package aura_msgs.
/**
  * WeatherZone.msg
  * Weather zone that affects flight and network
 */
typedef struct aura_msgs__msg__WeatherZone
{
  builtin_interfaces__msg__Time timestamp;
  uint32_t zone_id;
  /// Zone geometry (cylinder)
  geometry_msgs__msg__Point center;
  float radius_meters;
  float min_altitude;
  float max_altitude;
  uint8_t weather_type;
  /// Severity (0-1, affects penalties)
  float severity;
  /// Effects
  /// m/s
  float wind_speed_ms;
  /// radians from north
  float wind_direction_rad;
  /// Additional signal loss
  float signal_attenuation_db;
  /// Complete flight restriction
  bool no_fly;
  /// Timing
  builtin_interfaces__msg__Time start_time;
  builtin_interfaces__msg__Time end_time;
  bool is_active;
} aura_msgs__msg__WeatherZone;

// Struct for a sequence of aura_msgs__msg__WeatherZone.
typedef struct aura_msgs__msg__WeatherZone__Sequence
{
  aura_msgs__msg__WeatherZone * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__WeatherZone__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_H_
