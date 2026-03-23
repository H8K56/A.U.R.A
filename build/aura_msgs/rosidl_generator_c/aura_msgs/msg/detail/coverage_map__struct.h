// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_H_

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
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'origin'
// Member 'priority_zone_centers'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'is_covered'
// Member 'is_target'
// Member 'demand_level'
// Member 'coverage_quality'
// Member 'priority_zone_radii'
// Member 'priority_zone_weights'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/CoverageMap in the package aura_msgs.
/**
  * CoverageMap.msg
  * Coverage map for RL observation space
 */
typedef struct aura_msgs__msg__CoverageMap
{
  builtin_interfaces__msg__Time timestamp;
  /// Grid parameters
  uint32_t grid_size_x;
  uint32_t grid_size_y;
  float cell_size_meters;
  geometry_msgs__msg__Point origin;
  /// Coverage status (flattened arrays)
  /// Cell has coverage
  rosidl_runtime_c__boolean__Sequence is_covered;
  /// Cell is in target coverage area
  rosidl_runtime_c__boolean__Sequence is_target;
  /// 0-1, how much demand at this cell
  rosidl_runtime_c__float__Sequence demand_level;
  /// 0-1, quality of coverage
  rosidl_runtime_c__float__Sequence coverage_quality;
  /// Priority zones (e.g., hospitals, rescue staging)
  geometry_msgs__msg__Point__Sequence priority_zone_centers;
  rosidl_runtime_c__float__Sequence priority_zone_radii;
  /// Importance multiplier
  rosidl_runtime_c__float__Sequence priority_zone_weights;
} aura_msgs__msg__CoverageMap;

// Struct for a sequence of aura_msgs__msg__CoverageMap.
typedef struct aura_msgs__msg__CoverageMap__Sequence
{
  aura_msgs__msg__CoverageMap * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__CoverageMap__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_H_
