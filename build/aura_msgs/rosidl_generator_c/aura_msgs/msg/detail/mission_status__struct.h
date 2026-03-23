// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PHASE_INIT'.
/**
  * Mission phase
 */
enum
{
  aura_msgs__msg__MissionStatus__PHASE_INIT = 0
};

/// Constant 'PHASE_PREFLIGHT'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_PREFLIGHT = 1
};

/// Constant 'PHASE_LAUNCH'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_LAUNCH = 2
};

/// Constant 'PHASE_TRANSIT'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_TRANSIT = 3
};

/// Constant 'PHASE_DEPLOY'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_DEPLOY = 4
};

/// Constant 'PHASE_OPERATIONS'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_OPERATIONS = 5
};

/// Constant 'PHASE_RECOVERY'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_RECOVERY = 6
};

/// Constant 'PHASE_COMPLETE'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_COMPLETE = 7
};

/// Constant 'PHASE_ABORT'.
enum
{
  aura_msgs__msg__MissionStatus__PHASE_ABORT = 8
};

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'mission_id'
// Member 'active_alerts'
#include "rosidl_runtime_c/string.h"
// Member 'alert_severities'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/MissionStatus in the package aura_msgs.
/**
  * MissionStatus.msg
  * Mission progress and status
 */
typedef struct aura_msgs__msg__MissionStatus
{
  builtin_interfaces__msg__Time timestamp;
  rosidl_runtime_c__String mission_id;
  uint8_t phase;
  /// Progress
  /// 0-100
  float progress_percent;
  float elapsed_time_sec;
  float estimated_remaining_sec;
  /// Objectives status
  /// 0-100
  float coverage_achieved;
  /// 0-1
  float network_quality;
  /// Number of user connections
  uint32_t connections_established;
  uint32_t data_transferred_mb;
  /// Alerts
  rosidl_runtime_c__String__Sequence active_alerts;
  /// 0=info, 1=warning, 2=critical
  rosidl_runtime_c__uint8__Sequence alert_severities;
  /// Drone status summary
  uint8_t drones_operational;
  uint8_t drones_degraded;
  uint8_t drones_failed;
} aura_msgs__msg__MissionStatus;

// Struct for a sequence of aura_msgs__msg__MissionStatus.
typedef struct aura_msgs__msg__MissionStatus__Sequence
{
  aura_msgs__msg__MissionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__MissionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_H_
