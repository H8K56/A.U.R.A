// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "aura_msgs/msg/detail/swarm_state__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace aura_msgs
{

namespace msg
{

namespace rosidl_typesupport_cpp
{

typedef struct _SwarmState_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SwarmState_type_support_ids_t;

static const _SwarmState_type_support_ids_t _SwarmState_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SwarmState_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SwarmState_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SwarmState_type_support_symbol_names_t _SwarmState_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, aura_msgs, msg, SwarmState)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aura_msgs, msg, SwarmState)),
  }
};

typedef struct _SwarmState_type_support_data_t
{
  void * data[2];
} _SwarmState_type_support_data_t;

static _SwarmState_type_support_data_t _SwarmState_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SwarmState_message_typesupport_map = {
  2,
  "aura_msgs",
  &_SwarmState_message_typesupport_ids.typesupport_identifier[0],
  &_SwarmState_message_typesupport_symbol_names.symbol_name[0],
  &_SwarmState_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SwarmState_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SwarmState_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace msg

}  // namespace aura_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aura_msgs::msg::SwarmState>()
{
  return &::aura_msgs::msg::rosidl_typesupport_cpp::SwarmState_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, aura_msgs, msg, SwarmState)() {
  return get_message_type_support_handle<aura_msgs::msg::SwarmState>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp
