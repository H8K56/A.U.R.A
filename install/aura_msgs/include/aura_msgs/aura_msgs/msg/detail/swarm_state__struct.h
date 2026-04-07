// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MISSION_IDLE'.
/**
  * Mission state
 */
enum
{
  aura_msgs__msg__SwarmState__MISSION_IDLE = 0
};

/// Constant 'MISSION_PREFLIGHT'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_PREFLIGHT = 1
};

/// Constant 'MISSION_TAKEOFF'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_TAKEOFF = 2
};

/// Constant 'MISSION_TRANSIT'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_TRANSIT = 3
};

/// Constant 'MISSION_FORMATION'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_FORMATION = 4
};

/// Constant 'MISSION_OPERATIONS'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_OPERATIONS = 5
};

/// Constant 'MISSION_RTL'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_RTL = 6
};

/// Constant 'MISSION_COMPLETE'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_COMPLETE = 7
};

/// Constant 'MISSION_ABORT'.
enum
{
  aura_msgs__msg__SwarmState__MISSION_ABORT = 8
};

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'drones'
#include "aura_msgs/msg/detail/drone_state__struct.h"

/// Struct defined in msg/SwarmState in the package aura_msgs.
/**
  * SwarmState.msg
  * Aggregated swarm state for mission control
 */
typedef struct aura_msgs__msg__SwarmState
{
  builtin_interfaces__msg__Time timestamp;
  /// Swarm composition
  uint8_t num_drones_total;
  uint8_t num_drones_active;
  uint8_t num_hubs;
  uint8_t num_leaves;
  uint8_t mission_state;
  /// Coverage metrics
  /// 0-100, area covered
  float coverage_percent;
  /// 0-1, signal quality in covered area
  float coverage_quality;
  /// Network health
  float avg_throughput_mbps;
  float avg_latency_ms;
  float packet_loss_percent;
  /// Is the mesh fully connected?
  bool mesh_connected;
  /// Is hub connected to command post?
  bool backhaul_connected;
  /// All drone states
  aura_msgs__msg__DroneState__Sequence drones;
} aura_msgs__msg__SwarmState;

// Struct for a sequence of aura_msgs__msg__SwarmState.
typedef struct aura_msgs__msg__SwarmState__Sequence
{
  aura_msgs__msg__SwarmState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__SwarmState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_H_
