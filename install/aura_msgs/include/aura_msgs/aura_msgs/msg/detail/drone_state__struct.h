// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ROLE_LEAF'.
/**
  * Role in swarm
 */
enum
{
  aura_msgs__msg__DroneState__ROLE_LEAF = 0
};

/// Constant 'ROLE_HUB'.
enum
{
  aura_msgs__msg__DroneState__ROLE_HUB = 1
};

/// Constant 'FLIGHT_MODE_IDLE'.
/**
  * Flight status
 */
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_IDLE = 0
};

/// Constant 'FLIGHT_MODE_TAKEOFF'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_TAKEOFF = 1
};

/// Constant 'FLIGHT_MODE_TRANSIT'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_TRANSIT = 2
};

/// Constant 'FLIGHT_MODE_FORMATION'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_FORMATION = 3
};

/// Constant 'FLIGHT_MODE_OPERATIONS'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_OPERATIONS = 4
};

/// Constant 'FLIGHT_MODE_RTL'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_RTL = 5
};

/// Constant 'FLIGHT_MODE_EMERGENCY'.
enum
{
  aura_msgs__msg__DroneState__FLIGHT_MODE_EMERGENCY = 6
};

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__struct.h"

/// Struct defined in msg/DroneState in the package aura_msgs.
/**
  * DroneState.msg
  * Individual drone state for swarm coordination
 */
typedef struct aura_msgs__msg__DroneState
{
  /// Header
  builtin_interfaces__msg__Time timestamp;
  uint8_t drone_id;
  uint8_t role;
  /// Position and velocity (ENU frame)
  geometry_msgs__msg__Point position;
  geometry_msgs__msg__Vector3 velocity;
  geometry_msgs__msg__Quaternion orientation;
  uint8_t flight_mode;
  /// Health metrics
  /// 0-100
  float battery_percent;
  /// Volts
  float battery_voltage;
  /// dBm to nearest neighbor
  float signal_strength_dbm;
  bool gps_fix;
  uint8_t num_satellites;
  /// Network metrics for this drone
  float throughput_mbps;
  float latency_ms;
  /// Number of mesh connections
  uint8_t connected_neighbors;
} aura_msgs__msg__DroneState;

// Struct for a sequence of aura_msgs__msg__DroneState.
typedef struct aura_msgs__msg__DroneState__Sequence
{
  aura_msgs__msg__DroneState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__DroneState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_H_
