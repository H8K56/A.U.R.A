// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/msg/detail/trajectory_broadcast__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/msg/detail/trajectory_broadcast__functions.h"
#include "aura_msgs/msg/detail/trajectory_broadcast__struct.h"


// Include directives for member types
// Member `timestamp`
// Member `start_time`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
// Member `start_time`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `waypoints`
// Member `goal_position`
#include "geometry_msgs/msg/point.h"
// Member `waypoints`
// Member `goal_position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `time_allocation`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__msg__TrajectoryBroadcast__init(message_memory);
}

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_fini_function(void * message_memory)
{
  aura_msgs__msg__TrajectoryBroadcast__fini(message_memory);
}

size_t aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__size_function__TrajectoryBroadcast__waypoints(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__waypoints(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__waypoints(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__fetch_function__TrajectoryBroadcast__waypoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__waypoints(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__assign_function__TrajectoryBroadcast__waypoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__waypoints(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__resize_function__TrajectoryBroadcast__waypoints(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

size_t aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__size_function__TrajectoryBroadcast__time_allocation(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__time_allocation(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__time_allocation(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__fetch_function__TrajectoryBroadcast__time_allocation(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__time_allocation(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__assign_function__TrajectoryBroadcast__time_allocation(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__time_allocation(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__resize_function__TrajectoryBroadcast__time_allocation(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array[12] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drone_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, drone_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "start_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, start_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waypoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, waypoints),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__size_function__TrajectoryBroadcast__waypoints,  // size() function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__waypoints,  // get_const(index) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__waypoints,  // get(index) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__fetch_function__TrajectoryBroadcast__waypoints,  // fetch(index, &value) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__assign_function__TrajectoryBroadcast__waypoints,  // assign(index, value) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__resize_function__TrajectoryBroadcast__waypoints  // resize(index) function pointer
  },
  {
    "time_allocation",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, time_allocation),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__size_function__TrajectoryBroadcast__time_allocation,  // size() function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_const_function__TrajectoryBroadcast__time_allocation,  // get_const(index) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__get_function__TrajectoryBroadcast__time_allocation,  // get(index) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__fetch_function__TrajectoryBroadcast__time_allocation,  // fetch(index, &value) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__assign_function__TrajectoryBroadcast__time_allocation,  // assign(index, value) function pointer
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__resize_function__TrajectoryBroadcast__time_allocation  // resize(index) function pointer
  },
  {
    "total_duration",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, total_duration),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_pieces",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, num_pieces),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_valid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, is_valid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, max_velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "clearance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, clearance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, goal_position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal_reached",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__TrajectoryBroadcast, goal_reached),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_members = {
  "aura_msgs__msg",  // message namespace
  "TrajectoryBroadcast",  // message name
  12,  // number of fields
  sizeof(aura_msgs__msg__TrajectoryBroadcast),
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array,  // message members
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_type_support_handle = {
  0,
  &aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, TrajectoryBroadcast)() {
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_member_array[10].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_type_support_handle.typesupport_identifier) {
    aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__msg__TrajectoryBroadcast__rosidl_typesupport_introspection_c__TrajectoryBroadcast_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
