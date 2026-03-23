// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_
#define AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MISSION_COVERAGE'.
/**
  * Standard coverage mission
 */
enum
{
  aura_msgs__action__ExecuteMission_Goal__MISSION_COVERAGE = 0
};

/// Constant 'MISSION_SEARCH'.
/**
  * Search pattern
 */
enum
{
  aura_msgs__action__ExecuteMission_Goal__MISSION_SEARCH = 1
};

/// Constant 'MISSION_RELAY'.
/**
  * Point-to-point relay
 */
enum
{
  aura_msgs__action__ExecuteMission_Goal__MISSION_RELAY = 2
};

// Include directives for member types
// Member 'mission_id'
#include "rosidl_runtime_c/string.h"
// Member 'coverage_area_vertices'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_Goal
{
  /// Goal
  rosidl_runtime_c__String mission_id;
  uint8_t mission_type;
  /// Polygon defining area
  geometry_msgs__msg__Point__Sequence coverage_area_vertices;
  float target_altitude;
  /// Stop when achieved
  float target_coverage_percent;
  /// 0 = no limit
  float max_duration_sec;
} aura_msgs__action__ExecuteMission_Goal;

// Struct for a sequence of aura_msgs__action__ExecuteMission_Goal.
typedef struct aura_msgs__action__ExecuteMission_Goal__Sequence
{
  aura_msgs__action__ExecuteMission_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_Result
{
  bool success;
  rosidl_runtime_c__String message;
  float coverage_achieved;
  float total_time_sec;
  float avg_network_quality;
  uint32_t total_connections_served;
} aura_msgs__action__ExecuteMission_Result;

// Struct for a sequence of aura_msgs__action__ExecuteMission_Result.
typedef struct aura_msgs__action__ExecuteMission_Result__Sequence
{
  aura_msgs__action__ExecuteMission_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'current_phase'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_Feedback
{
  float progress_percent;
  float current_coverage_percent;
  float current_network_quality;
  uint8_t drones_active;
  rosidl_runtime_c__String current_phase;
  float elapsed_time_sec;
} aura_msgs__action__ExecuteMission_Feedback;

// Struct for a sequence of aura_msgs__action__ExecuteMission_Feedback.
typedef struct aura_msgs__action__ExecuteMission_Feedback__Sequence
{
  aura_msgs__action__ExecuteMission_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "aura_msgs/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  aura_msgs__action__ExecuteMission_Goal goal;
} aura_msgs__action__ExecuteMission_SendGoal_Request;

// Struct for a sequence of aura_msgs__action__ExecuteMission_SendGoal_Request.
typedef struct aura_msgs__action__ExecuteMission_SendGoal_Request__Sequence
{
  aura_msgs__action__ExecuteMission_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} aura_msgs__action__ExecuteMission_SendGoal_Response;

// Struct for a sequence of aura_msgs__action__ExecuteMission_SendGoal_Response.
typedef struct aura_msgs__action__ExecuteMission_SendGoal_Response__Sequence
{
  aura_msgs__action__ExecuteMission_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} aura_msgs__action__ExecuteMission_GetResult_Request;

// Struct for a sequence of aura_msgs__action__ExecuteMission_GetResult_Request.
typedef struct aura_msgs__action__ExecuteMission_GetResult_Request__Sequence
{
  aura_msgs__action__ExecuteMission_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_GetResult_Response
{
  int8_t status;
  aura_msgs__action__ExecuteMission_Result result;
} aura_msgs__action__ExecuteMission_GetResult_Response;

// Struct for a sequence of aura_msgs__action__ExecuteMission_GetResult_Response.
typedef struct aura_msgs__action__ExecuteMission_GetResult_Response__Sequence
{
  aura_msgs__action__ExecuteMission_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package aura_msgs.
typedef struct aura_msgs__action__ExecuteMission_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  aura_msgs__action__ExecuteMission_Feedback feedback;
} aura_msgs__action__ExecuteMission_FeedbackMessage;

// Struct for a sequence of aura_msgs__action__ExecuteMission_FeedbackMessage.
typedef struct aura_msgs__action__ExecuteMission_FeedbackMessage__Sequence
{
  aura_msgs__action__ExecuteMission_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__action__ExecuteMission_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_
