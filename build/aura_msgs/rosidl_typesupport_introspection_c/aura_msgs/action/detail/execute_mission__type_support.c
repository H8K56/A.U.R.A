// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/action/detail/execute_mission__functions.h"
#include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `mission_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `coverage_area_vertices`
#include "geometry_msgs/msg/point.h"
// Member `coverage_area_vertices`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_Goal__init(message_memory);
}

void aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_Goal__fini(message_memory);
}

size_t aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__size_function__ExecuteMission_Goal__coverage_area_vertices(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_const_function__ExecuteMission_Goal__coverage_area_vertices(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_function__ExecuteMission_Goal__coverage_area_vertices(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__fetch_function__ExecuteMission_Goal__coverage_area_vertices(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_const_function__ExecuteMission_Goal__coverage_area_vertices(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__assign_function__ExecuteMission_Goal__coverage_area_vertices(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_function__ExecuteMission_Goal__coverage_area_vertices(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__resize_function__ExecuteMission_Goal__coverage_area_vertices(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_member_array[6] = {
  {
    "mission_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, mission_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mission_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, mission_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coverage_area_vertices",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, coverage_area_vertices),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__size_function__ExecuteMission_Goal__coverage_area_vertices,  // size() function pointer
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_const_function__ExecuteMission_Goal__coverage_area_vertices,  // get_const(index) function pointer
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__get_function__ExecuteMission_Goal__coverage_area_vertices,  // get(index) function pointer
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__fetch_function__ExecuteMission_Goal__coverage_area_vertices,  // fetch(index, &value) function pointer
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__assign_function__ExecuteMission_Goal__coverage_area_vertices,  // assign(index, value) function pointer
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__resize_function__ExecuteMission_Goal__coverage_area_vertices  // resize(index) function pointer
  },
  {
    "target_altitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, target_altitude),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_coverage_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, target_coverage_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_duration_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Goal, max_duration_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_Goal",  // message name
  6,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_Goal),
  aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Goal)() {
  aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_Goal__rosidl_typesupport_introspection_c__ExecuteMission_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_Result__init(message_memory);
}

void aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_member_array[6] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coverage_achieved",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, coverage_achieved),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "total_time_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, total_time_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "avg_network_quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, avg_network_quality),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "total_connections_served",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Result, total_connections_served),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_Result",  // message name
  6,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_Result),
  aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Result)() {
  if (!aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_Result__rosidl_typesupport_introspection_c__ExecuteMission_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `current_phase`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_Feedback__init(message_memory);
}

void aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_member_array[6] = {
  {
    "progress_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, progress_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_coverage_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, current_coverage_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_network_quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, current_network_quality),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drones_active",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, drones_active),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_phase",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, current_phase),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "elapsed_time_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_Feedback, elapsed_time_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_Feedback",  // message name
  6,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_Feedback),
  aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Feedback)() {
  if (!aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_Feedback__rosidl_typesupport_introspection_c__ExecuteMission_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "aura_msgs/action/execute_mission.h"
// Member `goal`
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_SendGoal_Request__init(message_memory);
}

void aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_SendGoal_Request),
  aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Request)() {
  aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Goal)();
  if (!aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_SendGoal_Response__init(message_memory);
}

void aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_SendGoal_Response),
  aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Response)() {
  aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_members = {
  "aura_msgs__action",  // service namespace
  "ExecuteMission_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_type_support_handle = {
  0,
  &aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal)() {
  if (!aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_type_support_handle.typesupport_identifier) {
    aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_SendGoal_Response)()->data;
  }

  return &aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_GetResult_Request__init(message_memory);
}

void aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_GetResult_Request),
  aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Request)() {
  aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "aura_msgs/action/execute_mission.h"
// Member `result`
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_GetResult_Response__init(message_memory);
}

void aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_GetResult_Response),
  aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Response)() {
  aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Result)();
  if (!aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_members = {
  "aura_msgs__action",  // service namespace
  "ExecuteMission_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_type_support_handle = {
  0,
  &aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult)() {
  if (!aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_type_support_handle.typesupport_identifier) {
    aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_GetResult_Response)()->data;
  }

  return &aura_msgs__action__detail__execute_mission__rosidl_typesupport_introspection_c__ExecuteMission_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__functions.h"
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "aura_msgs/action/execute_mission.h"
// Member `feedback`
// already included above
// #include "aura_msgs/action/detail/execute_mission__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__action__ExecuteMission_FeedbackMessage__init(message_memory);
}

void aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_fini_function(void * message_memory)
{
  aura_msgs__action__ExecuteMission_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__action__ExecuteMission_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_members = {
  "aura_msgs__action",  // message namespace
  "ExecuteMission_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(aura_msgs__action__ExecuteMission_FeedbackMessage),
  aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_member_array,  // message members
  aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_type_support_handle = {
  0,
  &aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_FeedbackMessage)() {
  aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, action, ExecuteMission_Feedback)();
  if (!aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__action__ExecuteMission_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteMission_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
