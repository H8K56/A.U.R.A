// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:srv/SetFormation.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_H_
#define AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'FORMATION_SPREAD'.
/**
  * Request
 */
enum
{
  aura_msgs__srv__SetFormation_Request__FORMATION_SPREAD = 0
};

/// Constant 'FORMATION_CLUSTER'.
enum
{
  aura_msgs__srv__SetFormation_Request__FORMATION_CLUSTER = 1
};

/// Constant 'FORMATION_LINE'.
enum
{
  aura_msgs__srv__SetFormation_Request__FORMATION_LINE = 2
};

/// Constant 'FORMATION_GRID'.
enum
{
  aura_msgs__srv__SetFormation_Request__FORMATION_GRID = 3
};

/// Constant 'FORMATION_CUSTOM'.
enum
{
  aura_msgs__srv__SetFormation_Request__FORMATION_CUSTOM = 4
};

// Include directives for member types
// Member 'custom_positions'
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in srv/SetFormation in the package aura_msgs.
typedef struct aura_msgs__srv__SetFormation_Request
{
  uint8_t formation_type;
  /// For custom formation: relative positions from hub
  geometry_msgs__msg__Point__Sequence custom_positions;
  /// Formation parameters
  /// Distance between drones
  float spacing_meters;
  /// Formation altitude
  float altitude_meters;
  /// Formation center point
  geometry_msgs__msg__Point center;
  /// Formation heading (for line/grid)
  float heading_rad;
} aura_msgs__srv__SetFormation_Request;

// Struct for a sequence of aura_msgs__srv__SetFormation_Request.
typedef struct aura_msgs__srv__SetFormation_Request__Sequence
{
  aura_msgs__srv__SetFormation_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__SetFormation_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetFormation in the package aura_msgs.
typedef struct aura_msgs__srv__SetFormation_Response
{
  bool success;
  rosidl_runtime_c__String message;
  float estimated_transition_time;
} aura_msgs__srv__SetFormation_Response;

// Struct for a sequence of aura_msgs__srv__SetFormation_Response.
typedef struct aura_msgs__srv__SetFormation_Response__Sequence
{
  aura_msgs__srv__SetFormation_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__SetFormation_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_H_
