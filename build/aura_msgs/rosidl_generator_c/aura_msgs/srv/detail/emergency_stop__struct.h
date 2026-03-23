// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:srv/EmergencyStop.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_H_
#define AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ALL_DRONES'.
enum
{
  aura_msgs__srv__EmergencyStop_Request__ALL_DRONES = 255
};

/// Constant 'STOP_HOVER'.
/**
  * Stop and hover in place
 */
enum
{
  aura_msgs__srv__EmergencyStop_Request__STOP_HOVER = 0
};

/// Constant 'STOP_LAND'.
/**
  * Land immediately
 */
enum
{
  aura_msgs__srv__EmergencyStop_Request__STOP_LAND = 1
};

/// Constant 'STOP_RTL'.
/**
  * Return to launch
 */
enum
{
  aura_msgs__srv__EmergencyStop_Request__STOP_RTL = 2
};

// Include directives for member types
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/EmergencyStop in the package aura_msgs.
typedef struct aura_msgs__srv__EmergencyStop_Request
{
  /// Request
  /// Target drone (255 = ALL)
  uint8_t drone_id;
  uint8_t stop_type;
  /// For logging
  rosidl_runtime_c__String reason;
} aura_msgs__srv__EmergencyStop_Request;

// Struct for a sequence of aura_msgs__srv__EmergencyStop_Request.
typedef struct aura_msgs__srv__EmergencyStop_Request__Sequence
{
  aura_msgs__srv__EmergencyStop_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__EmergencyStop_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/EmergencyStop in the package aura_msgs.
typedef struct aura_msgs__srv__EmergencyStop_Response
{
  bool success;
  rosidl_runtime_c__String message;
  uint8_t drones_affected;
} aura_msgs__srv__EmergencyStop_Response;

// Struct for a sequence of aura_msgs__srv__EmergencyStop_Response.
typedef struct aura_msgs__srv__EmergencyStop_Response__Sequence
{
  aura_msgs__srv__EmergencyStop_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__srv__EmergencyStop_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_H_
