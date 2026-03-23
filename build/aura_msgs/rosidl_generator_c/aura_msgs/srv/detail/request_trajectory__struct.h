// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:srv/RequestTrajectory.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_H_
#define AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in srv/RequestTrajectory in the package aura_msgs.
typedef struct aura_msgs__srv__RequestTrajectory_Request
{
  /// Request
  uint8_t drone_id;
  geometry_msgs__msg__Point goal_position;
  /// 0 = use default
  double max_velocity;
  /// 0 = no time constraint
  double max_time;
  bool avoid_weather_zones;
} aura_msgs__srv__RequestTrajectory_Request;

// Struct for a sequence of aura_msgs__srv__RequestTrajectory_Request.
typedef struct aura_msgs__srv__RequestTrajectory_Request__Sequence
{
  aura_msgs__srv__RequestTrajectory_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__RequestTrajectory_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'trajectory'
#include "aura_msgs/msg/detail/trajectory_broadcast__struct.h"

/// Struct defined in srv/RequestTrajectory in the package aura_msgs.
typedef struct aura_msgs__srv__RequestTrajectory_Response
{
  bool success;
  rosidl_runtime_c__String message;
  /// The planned trajectory
  aura_msgs__msg__TrajectoryBroadcast trajectory;
  /// Seconds to reach goal
  double estimated_time;
  /// Joules
  double estimated_energy;
} aura_msgs__srv__RequestTrajectory_Response;

// Struct for a sequence of aura_msgs__srv__RequestTrajectory_Response.
typedef struct aura_msgs__srv__RequestTrajectory_Response__Sequence
{
  aura_msgs__srv__RequestTrajectory_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__RequestTrajectory_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_H_
