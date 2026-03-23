// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/msg/detail/mission_status__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/msg/detail/mission_status__functions.h"
#include "aura_msgs/msg/detail/mission_status__struct.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `mission_id`
// Member `active_alerts`
#include "rosidl_runtime_c/string_functions.h"
// Member `alert_severities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__msg__MissionStatus__init(message_memory);
}

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_fini_function(void * message_memory)
{
  aura_msgs__msg__MissionStatus__fini(message_memory);
}

size_t aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__size_function__MissionStatus__active_alerts(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__active_alerts(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__active_alerts(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__fetch_function__MissionStatus__active_alerts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__active_alerts(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__assign_function__MissionStatus__active_alerts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__active_alerts(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__resize_function__MissionStatus__active_alerts(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__size_function__MissionStatus__alert_severities(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__alert_severities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__alert_severities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__fetch_function__MissionStatus__alert_severities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__alert_severities(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__assign_function__MissionStatus__alert_severities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__alert_severities(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__resize_function__MissionStatus__alert_severities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_member_array[15] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mission_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, mission_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "phase",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, phase),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "progress_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, progress_percent),  // bytes offset in struct
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
    offsetof(aura_msgs__msg__MissionStatus, elapsed_time_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "estimated_remaining_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, estimated_remaining_sec),  // bytes offset in struct
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
    offsetof(aura_msgs__msg__MissionStatus, coverage_achieved),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "network_quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, network_quality),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "connections_established",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, connections_established),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data_transferred_mb",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, data_transferred_mb),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "active_alerts",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, active_alerts),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__size_function__MissionStatus__active_alerts,  // size() function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__active_alerts,  // get_const(index) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__active_alerts,  // get(index) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__fetch_function__MissionStatus__active_alerts,  // fetch(index, &value) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__assign_function__MissionStatus__active_alerts,  // assign(index, value) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__resize_function__MissionStatus__active_alerts  // resize(index) function pointer
  },
  {
    "alert_severities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, alert_severities),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__size_function__MissionStatus__alert_severities,  // size() function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_const_function__MissionStatus__alert_severities,  // get_const(index) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__get_function__MissionStatus__alert_severities,  // get(index) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__fetch_function__MissionStatus__alert_severities,  // fetch(index, &value) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__assign_function__MissionStatus__alert_severities,  // assign(index, value) function pointer
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__resize_function__MissionStatus__alert_severities  // resize(index) function pointer
  },
  {
    "drones_operational",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, drones_operational),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drones_degraded",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, drones_degraded),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drones_failed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__MissionStatus, drones_failed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_members = {
  "aura_msgs__msg",  // message namespace
  "MissionStatus",  // message name
  15,  // number of fields
  sizeof(aura_msgs__msg__MissionStatus),
  aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_member_array,  // message members
  aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_type_support_handle = {
  0,
  &aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, MissionStatus)() {
  aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_type_support_handle.typesupport_identifier) {
    aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__msg__MissionStatus__rosidl_typesupport_introspection_c__MissionStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
