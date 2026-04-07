// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'timestamp'
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'waypoints'
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'time_allocation'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/TrajectoryBroadcast in the package aura_msgs.
/**
  * TrajectoryBroadcast.msg
  * MINCO trajectory broadcast for decentralized collision avoidance
  * Other drones use this to predict where this drone will be
 */
typedef struct aura_msgs__msg__TrajectoryBroadcast
{
  builtin_interfaces__msg__Time timestamp;
  uint8_t drone_id;
  /// Trajectory start time (absolute)
  builtin_interfaces__msg__Time start_time;
  /// MINCO parameters
  /// M-1 intermediate waypoints (q)
  geometry_msgs__msg__Point__Sequence waypoints;
  /// M piece durations in seconds (T)
  rosidl_runtime_c__double__Sequence time_allocation;
  /// Total trajectory duration
  double total_duration;
  /// Trajectory metadata
  /// M
  uint8_t num_pieces;
  /// False if emergency stop active
  bool is_valid;
  /// m/s, for safety checking
  float max_velocity;
  /// meters, collision avoidance radius
  float clearance;
  /// Goal information (for coordination)
  geometry_msgs__msg__Point goal_position;
  bool goal_reached;
} aura_msgs__msg__TrajectoryBroadcast;

// Struct for a sequence of aura_msgs__msg__TrajectoryBroadcast.
typedef struct aura_msgs__msg__TrajectoryBroadcast__Sequence
{
  aura_msgs__msg__TrajectoryBroadcast * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__TrajectoryBroadcast__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_H_
