// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/msg/detail/swarm_state__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/msg/detail/swarm_state__functions.h"
#include "aura_msgs/msg/detail/swarm_state__struct.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `drones`
#include "aura_msgs/msg/drone_state.h"
// Member `drones`
#include "aura_msgs/msg/detail/drone_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__msg__SwarmState__init(message_memory);
}

void aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_fini_function(void * message_memory)
{
  aura_msgs__msg__SwarmState__fini(message_memory);
}

size_t aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__size_function__SwarmState__drones(
  const void * untyped_member)
{
  const aura_msgs__msg__DroneState__Sequence * member =
    (const aura_msgs__msg__DroneState__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_const_function__SwarmState__drones(
  const void * untyped_member, size_t index)
{
  const aura_msgs__msg__DroneState__Sequence * member =
    (const aura_msgs__msg__DroneState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_function__SwarmState__drones(
  void * untyped_member, size_t index)
{
  aura_msgs__msg__DroneState__Sequence * member =
    (aura_msgs__msg__DroneState__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__fetch_function__SwarmState__drones(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aura_msgs__msg__DroneState * item =
    ((const aura_msgs__msg__DroneState *)
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_const_function__SwarmState__drones(untyped_member, index));
  aura_msgs__msg__DroneState * value =
    (aura_msgs__msg__DroneState *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__assign_function__SwarmState__drones(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aura_msgs__msg__DroneState * item =
    ((aura_msgs__msg__DroneState *)
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_function__SwarmState__drones(untyped_member, index));
  const aura_msgs__msg__DroneState * value =
    (const aura_msgs__msg__DroneState *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__resize_function__SwarmState__drones(
  void * untyped_member, size_t size)
{
  aura_msgs__msg__DroneState__Sequence * member =
    (aura_msgs__msg__DroneState__Sequence *)(untyped_member);
  aura_msgs__msg__DroneState__Sequence__fini(member);
  return aura_msgs__msg__DroneState__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_member_array[14] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_drones_total",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, num_drones_total),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_drones_active",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, num_drones_active),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_hubs",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, num_hubs),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_leaves",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, num_leaves),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mission_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, mission_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coverage_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, coverage_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coverage_quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, coverage_quality),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "avg_throughput_mbps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, avg_throughput_mbps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "avg_latency_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, avg_latency_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "packet_loss_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, packet_loss_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mesh_connected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, mesh_connected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "backhaul_connected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, backhaul_connected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drones",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__SwarmState, drones),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__size_function__SwarmState__drones,  // size() function pointer
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_const_function__SwarmState__drones,  // get_const(index) function pointer
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__get_function__SwarmState__drones,  // get(index) function pointer
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__fetch_function__SwarmState__drones,  // fetch(index, &value) function pointer
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__assign_function__SwarmState__drones,  // assign(index, value) function pointer
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__resize_function__SwarmState__drones  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_members = {
  "aura_msgs__msg",  // message namespace
  "SwarmState",  // message name
  14,  // number of fields
  sizeof(aura_msgs__msg__SwarmState),
  aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_member_array,  // message members
  aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_type_support_handle = {
  0,
  &aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, SwarmState)() {
  aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_member_array[13].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, DroneState)();
  if (!aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_type_support_handle.typesupport_identifier) {
    aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__msg__SwarmState__rosidl_typesupport_introspection_c__SwarmState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
