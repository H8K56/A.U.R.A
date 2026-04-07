// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:srv/EmergencyStop.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/srv/detail/emergency_stop__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/srv/detail/emergency_stop__functions.h"
#include "aura_msgs/srv/detail/emergency_stop__struct.h"


// Include directives for member types
// Member `reason`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__EmergencyStop_Request__init(message_memory);
}

void aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_fini_function(void * message_memory)
{
  aura_msgs__srv__EmergencyStop_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_member_array[3] = {
  {
    "drone_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__EmergencyStop_Request, drone_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stop_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__EmergencyStop_Request, stop_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "reason",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__EmergencyStop_Request, reason),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_members = {
  "aura_msgs__srv",  // message namespace
  "EmergencyStop_Request",  // message name
  3,  // number of fields
  sizeof(aura_msgs__srv__EmergencyStop_Request),
  aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_member_array,  // message members
  aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_type_support_handle = {
  0,
  &aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Request)() {
  if (!aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__EmergencyStop_Request__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aura_msgs/srv/detail/emergency_stop__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aura_msgs/srv/detail/emergency_stop__functions.h"
// already included above
// #include "aura_msgs/srv/detail/emergency_stop__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__srv__EmergencyStop_Response__init(message_memory);
}

void aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_fini_function(void * message_memory)
{
  aura_msgs__srv__EmergencyStop_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_member_array[3] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__EmergencyStop_Response, success),  // bytes offset in struct
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
    offsetof(aura_msgs__srv__EmergencyStop_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drones_affected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__srv__EmergencyStop_Response, drones_affected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_members = {
  "aura_msgs__srv",  // message namespace
  "EmergencyStop_Response",  // message name
  3,  // number of fields
  sizeof(aura_msgs__srv__EmergencyStop_Response),
  aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_member_array,  // message members
  aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_type_support_handle = {
  0,
  &aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Response)() {
  if (!aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__srv__EmergencyStop_Response__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aura_msgs/srv/detail/emergency_stop__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_members = {
  "aura_msgs__srv",  // service namespace
  "EmergencyStop",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_Request_message_type_support_handle,
  NULL  // response message
  // aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_Response_message_type_support_handle
};

static rosidl_service_type_support_t aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_type_support_handle = {
  0,
  &aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop)() {
  if (!aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_type_support_handle.typesupport_identifier) {
    aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, srv, EmergencyStop_Response)()->data;
  }

  return &aura_msgs__srv__detail__emergency_stop__rosidl_typesupport_introspection_c__EmergencyStop_service_type_support_handle;
}
