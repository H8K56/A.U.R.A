// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_H_
#define AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetNetworkStatus in the package aura_msgs.
typedef struct aura_msgs__srv__GetNetworkStatus_Request
{
  /// Request
  /// Include full grid data
  bool include_coverage_map;
  /// Include per-link metrics
  bool include_link_details;
} aura_msgs__srv__GetNetworkStatus_Request;

// Struct for a sequence of aura_msgs__srv__GetNetworkStatus_Request.
typedef struct aura_msgs__srv__GetNetworkStatus_Request__Sequence
{
  aura_msgs__srv__GetNetworkStatus_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__GetNetworkStatus_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'metrics'
#include "aura_msgs/msg/detail/network_metrics__struct.h"
// Member 'issues'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetNetworkStatus in the package aura_msgs.
typedef struct aura_msgs__srv__GetNetworkStatus_Response
{
  bool success;
  aura_msgs__msg__NetworkMetrics metrics;
  /// 0-1, aggregate network health
  float overall_health;
  /// List of current issues
  rosidl_runtime_c__String__Sequence issues;
} aura_msgs__srv__GetNetworkStatus_Response;

// Struct for a sequence of aura_msgs__srv__GetNetworkStatus_Response.
typedef struct aura_msgs__srv__GetNetworkStatus_Response__Sequence
{
  aura_msgs__srv__GetNetworkStatus_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__GetNetworkStatus_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_H_
