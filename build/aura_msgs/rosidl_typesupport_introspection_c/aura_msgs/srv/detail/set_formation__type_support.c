// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:srv/SetFormation.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/srv/detail/set_formation__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/srv/detail/set_formation__functions.h"
#include "aura_msgs/srv/detail/set_formation__struct.h"


// Include directives for member types
// Member `custom_positions`
// Member `center`
#include "geometry_msgs/msg/point.h"
// Member `custom_positions`
// Member `center`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__SetFormation_Request__init(message_memory);
}

void aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_fini_function(void * message_memory)
{
  aura_msgs__srv__SetFormation_Request__fini(message_memory);
}

size_t aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__size_function__SetFormation_Request__custom_positions(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_const_function__SetFormation_Request__custom_positions(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_function__SetFormation_Request__custom_positions(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__fetch_function__SetFormation_Request__custom_positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_const_function__SetFormation_Request__custom_positions(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__assign_function__SetFormation_Request__custom_positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_function__SetFormation_Request__custom_positions(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__resize_function__SetFormation_Request__custom_positions(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_member_array[6] = {
  {
    "formation_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, formation_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "custom_positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, custom_positions),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__size_function__SetFormation_Request__custom_positions,  // size() function pointer
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_const_function__SetFormation_Request__custom_positions,  // get_const(index) function pointer
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__get_function__SetFormation_Request__custom_positions,  // get(index) function pointer
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__fetch_function__SetFormation_Request__custom_positions,  // fetch(index, &value) function pointer
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__assign_function__SetFormation_Request__custom_positions,  // assign(index, value) function pointer
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__resize_function__SetFormation_Request__custom_positions  // resize(index) function pointer
  },
  {
    "spacing_meters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, spacing_meters),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "altitude_meters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, altitude_meters),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "center",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, center),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "heading_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Request, heading_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_members = {
  "aura_msgs__srv",  // message namespace
  "SetFormation_Request",  // message name
  6,  // number of fields
  sizeof(aura_msgs__srv__SetFormation_Request),
  aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_member_array,  // message members
  aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_type_support_handle = {
  0,
  &aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Request)() {
  aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__SetFormation_Request__rosidl_typesupport_introspection_c__SetFormation_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/srv/detail/set_formation__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/srv/detail/set_formation__functions.h"
// already included above
// #include "aura_msgs/srv/detail/set_formation__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__SetFormation_Response__init(message_memory);
}

void aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_fini_function(void * message_memory)
{
  aura_msgs__srv__SetFormation_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_member_array[3] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Response, success),  // bytes offset in struct
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
    offsetof(aura_msgs__srv__SetFormation_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "estimated_transition_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__SetFormation_Response, estimated_transition_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_members = {
  "aura_msgs__srv",  // message namespace
  "SetFormation_Response",  // message name
  3,  // number of fields
  sizeof(aura_msgs__srv__SetFormation_Response),
  aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_member_array,  // message members
  aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_type_support_handle = {
  0,
  &aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Response)() {
  if (!aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__SetFormation_Response__rosidl_typesupport_introspection_c__SetFormation_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aura_msgs/srv/detail/set_formation__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_members = {
  "aura_msgs__srv",  // service namespace
  "SetFormation",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_Request_message_type_support_handle,
  NULL  // response message
  // aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_Response_message_type_support_handle
};

static rosidl_service_type_support_t aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_type_support_handle = {
  0,
  &aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation)() {
  if (!aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, SetFormation_Response)()->data;
  }

  return &aura_msgs__srv__detail__set_formation__rosidl_typesupport_introspection_c__SetFormation_service_type_support_handle;
}
