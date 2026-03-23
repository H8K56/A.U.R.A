// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/CoverageGoal.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_H_

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
  * Formation info
  * Maximize coverage area
 */
enum
{
  aura_msgs__msg__CoverageGoal__FORMATION_SPREAD = 0
};

/// Constant 'FORMATION_CLUSTER'.
/**
  * Cluster for high-density area
 */
enum
{
  aura_msgs__msg__CoverageGoal__FORMATION_CLUSTER = 1
};

/// Constant 'FORMATION_LINE'.
/**
  * Line formation for corridor
 */
enum
{
  aura_msgs__msg__CoverageGoal__FORMATION_LINE = 2
};

/// Constant 'FORMATION_ADAPTIVE'.
/**
  * Let RL decide
 */
enum
{
  aura_msgs__msg__CoverageGoal__FORMATION_ADAPTIVE = 3
};

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/CoverageGoal in the package aura_msgs.
/**
  * CoverageGoal.msg
  * Goal position from Strategic RL to MINCO trajectory planner
 */
typedef struct aura_msgs__msg__CoverageGoal
{
  builtin_interfaces__msg__Time timestamp;
  uint8_t drone_id;
  /// Target position (ENU frame)
  geometry_msgs__msg__Point position;
  /// Optional: desired arrival time (0 = ASAP)
  double desired_arrival_time;
  uint8_t formation_type;
  /// Priority (higher = more important to reach)
  /// 0-1
  float priority;
  /// Constraints
  /// meters
  float min_altitude;
  /// meters
  float max_altitude;
  /// m/s, 0 = use default
  float max_velocity;
  /// Network requirements at this position
  /// Minimum throughput needed
  float required_throughput_mbps;
  /// meters
  float required_coverage_radius;
} aura_msgs__msg__CoverageGoal;

// Struct for a sequence of aura_msgs__msg__CoverageGoal.
typedef struct aura_msgs__msg__CoverageGoal__Sequence
{
  aura_msgs__msg__CoverageGoal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__CoverageGoal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_H_
