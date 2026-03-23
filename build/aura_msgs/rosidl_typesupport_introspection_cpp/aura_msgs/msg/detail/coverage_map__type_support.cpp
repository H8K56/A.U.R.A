// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aura_msgs/msg/detail/coverage_map__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace aura_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void CoverageMap_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aura_msgs::msg::CoverageMap(_init);
}

void CoverageMap_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aura_msgs::msg::CoverageMap *>(message_memory);
  typed_message->~CoverageMap();
}

size_t size_function__CoverageMap__is_covered(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<bool> *>(untyped_member);
  return member->size();
}

void fetch_function__CoverageMap__is_covered(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & member = *reinterpret_cast<const std::vector<bool> *>(untyped_member);
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = member[index];
}

void assign_function__CoverageMap__is_covered(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & member = *reinterpret_cast<std::vector<bool> *>(untyped_member);
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  member[index] = value;
}

void resize_function__CoverageMap__is_covered(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<bool> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__is_target(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<bool> *>(untyped_member);
  return member->size();
}

void fetch_function__CoverageMap__is_target(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & member = *reinterpret_cast<const std::vector<bool> *>(untyped_member);
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = member[index];
}

void assign_function__CoverageMap__is_target(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & member = *reinterpret_cast<std::vector<bool> *>(untyped_member);
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  member[index] = value;
}

void resize_function__CoverageMap__is_target(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<bool> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__demand_level(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CoverageMap__demand_level(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CoverageMap__demand_level(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CoverageMap__demand_level(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CoverageMap__demand_level(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CoverageMap__demand_level(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CoverageMap__demand_level(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CoverageMap__demand_level(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__coverage_quality(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CoverageMap__coverage_quality(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CoverageMap__coverage_quality(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CoverageMap__coverage_quality(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CoverageMap__coverage_quality(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CoverageMap__coverage_quality(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CoverageMap__coverage_quality(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CoverageMap__coverage_quality(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__priority_zone_centers(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CoverageMap__priority_zone_centers(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void * get_function__CoverageMap__priority_zone_centers(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void fetch_function__CoverageMap__priority_zone_centers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Point *>(
    get_const_function__CoverageMap__priority_zone_centers(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Point *>(untyped_value);
  value = item;
}

void assign_function__CoverageMap__priority_zone_centers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Point *>(
    get_function__CoverageMap__priority_zone_centers(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Point *>(untyped_value);
  item = value;
}

void resize_function__CoverageMap__priority_zone_centers(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__priority_zone_radii(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CoverageMap__priority_zone_radii(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CoverageMap__priority_zone_radii(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CoverageMap__priority_zone_radii(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CoverageMap__priority_zone_radii(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CoverageMap__priority_zone_radii(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CoverageMap__priority_zone_radii(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CoverageMap__priority_zone_radii(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__CoverageMap__priority_zone_weights(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__CoverageMap__priority_zone_weights(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__CoverageMap__priority_zone_weights(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__CoverageMap__priority_zone_weights(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__CoverageMap__priority_zone_weights(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__CoverageMap__priority_zone_weights(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__CoverageMap__priority_zone_weights(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__CoverageMap__priority_zone_weights(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember CoverageMap_message_member_array[12] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "grid_size_x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, grid_size_x),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "grid_size_y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, grid_size_y),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "cell_size_meters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, cell_size_meters),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "origin",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Point>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, origin),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "is_covered",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, is_covered),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__is_covered,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    fetch_function__CoverageMap__is_covered,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__is_covered,  // assign(index, value) function pointer
    resize_function__CoverageMap__is_covered  // resize(index) function pointer
  },
  {
    "is_target",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, is_target),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__is_target,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    fetch_function__CoverageMap__is_target,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__is_target,  // assign(index, value) function pointer
    resize_function__CoverageMap__is_target  // resize(index) function pointer
  },
  {
    "demand_level",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, demand_level),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__demand_level,  // size() function pointer
    get_const_function__CoverageMap__demand_level,  // get_const(index) function pointer
    get_function__CoverageMap__demand_level,  // get(index) function pointer
    fetch_function__CoverageMap__demand_level,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__demand_level,  // assign(index, value) function pointer
    resize_function__CoverageMap__demand_level  // resize(index) function pointer
  },
  {
    "coverage_quality",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, coverage_quality),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__coverage_quality,  // size() function pointer
    get_const_function__CoverageMap__coverage_quality,  // get_const(index) function pointer
    get_function__CoverageMap__coverage_quality,  // get(index) function pointer
    fetch_function__CoverageMap__coverage_quality,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__coverage_quality,  // assign(index, value) function pointer
    resize_function__CoverageMap__coverage_quality  // resize(index) function pointer
  },
  {
    "priority_zone_centers",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Point>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, priority_zone_centers),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__priority_zone_centers,  // size() function pointer
    get_const_function__CoverageMap__priority_zone_centers,  // get_const(index) function pointer
    get_function__CoverageMap__priority_zone_centers,  // get(index) function pointer
    fetch_function__CoverageMap__priority_zone_centers,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__priority_zone_centers,  // assign(index, value) function pointer
    resize_function__CoverageMap__priority_zone_centers  // resize(index) function pointer
  },
  {
    "priority_zone_radii",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, priority_zone_radii),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__priority_zone_radii,  // size() function pointer
    get_const_function__CoverageMap__priority_zone_radii,  // get_const(index) function pointer
    get_function__CoverageMap__priority_zone_radii,  // get(index) function pointer
    fetch_function__CoverageMap__priority_zone_radii,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__priority_zone_radii,  // assign(index, value) function pointer
    resize_function__CoverageMap__priority_zone_radii  // resize(index) function pointer
  },
  {
    "priority_zone_weights",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::CoverageMap, priority_zone_weights),  // bytes offset in struct
    nullptr,  // default value
    size_function__CoverageMap__priority_zone_weights,  // size() function pointer
    get_const_function__CoverageMap__priority_zone_weights,  // get_const(index) function pointer
    get_function__CoverageMap__priority_zone_weights,  // get(index) function pointer
    fetch_function__CoverageMap__priority_zone_weights,  // fetch(index, &value) function pointer
    assign_function__CoverageMap__priority_zone_weights,  // assign(index, value) function pointer
    resize_function__CoverageMap__priority_zone_weights  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers CoverageMap_message_members = {
  "aura_msgs::msg",  // message namespace
  "CoverageMap",  // message name
  12,  // number of fields
  sizeof(aura_msgs::msg::CoverageMap),
  CoverageMap_message_member_array,  // message members
  CoverageMap_init_function,  // function to initialize message memory (memory has to be allocated)
  CoverageMap_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t CoverageMap_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &CoverageMap_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace aura_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aura_msgs::msg::CoverageMap>()
{
  return &::aura_msgs::msg::rosidl_typesupport_introspection_cpp::CoverageMap_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aura_msgs, msg, CoverageMap)() {
  return &::aura_msgs::msg::rosidl_typesupport_introspection_cpp::CoverageMap_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
