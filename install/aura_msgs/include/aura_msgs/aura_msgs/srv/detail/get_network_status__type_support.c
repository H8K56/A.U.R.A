// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/srv/detail/get_network_status__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/srv/detail/get_network_status__functions.h"
#include "aura_msgs/srv/detail/get_network_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__GetNetworkStatus_Request__init(message_memory);
}

void aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_fini_function(void * message_memory)
{
  aura_msgs__srv__GetNetworkStatus_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_member_array[2] = {
  {
    "include_coverage_map",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Request, include_coverage_map),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "include_link_details",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Request, include_link_details),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_members = {
  "aura_msgs__srv",  // message namespace
  "GetNetworkStatus_Request",  // message name
  2,  // number of fields
  sizeof(aura_msgs__srv__GetNetworkStatus_Request),
  aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_member_array,  // message members
  aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_type_support_handle = {
  0,
  &aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Request)() {
  if (!aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__GetNetworkStatus_Request__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/srv/detail/get_network_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/srv/detail/get_network_status__functions.h"
// already included above
// #include "aura_msgs/srv/detail/get_network_status__struct.h"


// Include directives for member types
// Member `metrics`
#include "aura_msgs/msg/network_metrics.h"
// Member `metrics`
#include "aura_msgs/msg/detail/network_metrics__rosidl_typesupport_introspection_c.h"
// Member `issues`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__GetNetworkStatus_Response__init(message_memory);
}

void aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_fini_function(void * message_memory)
{
  aura_msgs__srv__GetNetworkStatus_Response__fini(message_memory);
}

size_t aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__size_function__GetNetworkStatus_Response__issues(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetNetworkStatus_Response__issues(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_function__GetNetworkStatus_Response__issues(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__fetch_function__GetNetworkStatus_Response__issues(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetNetworkStatus_Response__issues(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__assign_function__GetNetworkStatus_Response__issues(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_function__GetNetworkStatus_Response__issues(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__resize_function__GetNetworkStatus_Response__issues(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_member_array[4] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "metrics",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Response, metrics),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "overall_health",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Response, overall_health),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "issues",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__GetNetworkStatus_Response, issues),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__size_function__GetNetworkStatus_Response__issues,  // size() function pointer
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_const_function__GetNetworkStatus_Response__issues,  // get_const(index) function pointer
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__get_function__GetNetworkStatus_Response__issues,  // get(index) function pointer
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__fetch_function__GetNetworkStatus_Response__issues,  // fetch(index, &value) function pointer
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__assign_function__GetNetworkStatus_Response__issues,  // assign(index, value) function pointer
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__resize_function__GetNetworkStatus_Response__issues  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_members = {
  "aura_msgs__srv",  // message namespace
  "GetNetworkStatus_Response",  // message name
  4,  // number of fields
  sizeof(aura_msgs__srv__GetNetworkStatus_Response),
  aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_member_array,  // message members
  aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_type_support_handle = {
  0,
  &aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Response)() {
  aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, NetworkMetrics)();
  if (!aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__GetNetworkStatus_Response__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aura_msgs/srv/detail/get_network_status__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_members = {
  "aura_msgs__srv",  // service namespace
  "GetNetworkStatus",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_Request_message_type_support_handle,
  NULL  // response message
  // aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_Response_message_type_support_handle
};

static rosidl_service_type_support_t aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_type_support_handle = {
  0,
  &aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus)() {
  if (!aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, GetNetworkStatus_Response)()->data;
  }

  return &aura_msgs__srv__detail__get_network_status__rosidl_typesupport_introspection_c__GetNetworkStatus_service_type_support_handle;
}
