// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aura_msgs/msg/detail/network_metrics__struct.hpp"
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

void NetworkMetrics_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aura_msgs::msg::NetworkMetrics(_init);
}

void NetworkMetrics_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aura_msgs::msg::NetworkMetrics *>(message_memory);
  typed_message->~NetworkMetrics();
}

size_t size_function__NetworkMetrics__signal_strength_dbm(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__signal_strength_dbm(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__signal_strength_dbm(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__signal_strength_dbm(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__signal_strength_dbm(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__signal_strength_dbm(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__signal_strength_dbm(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__signal_strength_dbm(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__throughput_mbps(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__throughput_mbps(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__throughput_mbps(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__throughput_mbps(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__throughput_mbps(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__throughput_mbps(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__throughput_mbps(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__throughput_mbps(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__latency_ms(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__latency_ms(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__latency_ms(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__latency_ms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__latency_ms(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__latency_ms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__latency_ms(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__latency_ms(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__coverage_mask(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<bool> *>(untyped_member);
  return member->size();
}

void fetch_function__NetworkMetrics__coverage_mask(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & member = *reinterpret_cast<const std::vector<bool> *>(untyped_member);
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = member[index];
}

void assign_function__NetworkMetrics__coverage_mask(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & member = *reinterpret_cast<std::vector<bool> *>(untyped_member);
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  member[index] = value;
}

void resize_function__NetworkMetrics__coverage_mask(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<bool> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__link_from_drone(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__link_from_drone(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__link_from_drone(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__link_from_drone(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__NetworkMetrics__link_from_drone(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__link_from_drone(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__NetworkMetrics__link_from_drone(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__link_from_drone(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__link_to_drone(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__link_to_drone(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__link_to_drone(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__link_to_drone(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__NetworkMetrics__link_to_drone(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__link_to_drone(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__NetworkMetrics__link_to_drone(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__link_to_drone(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__link_throughput_mbps(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__link_throughput_mbps(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__link_throughput_mbps(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__link_throughput_mbps(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__link_throughput_mbps(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__link_throughput_mbps(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__link_throughput_mbps(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__link_throughput_mbps(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__link_latency_ms(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__link_latency_ms(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__link_latency_ms(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__link_latency_ms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__link_latency_ms(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__link_latency_ms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__link_latency_ms(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__link_latency_ms(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__NetworkMetrics__link_rssi_dbm(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__NetworkMetrics__link_rssi_dbm(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__NetworkMetrics__link_rssi_dbm(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__NetworkMetrics__link_rssi_dbm(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__NetworkMetrics__link_rssi_dbm(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__NetworkMetrics__link_rssi_dbm(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__NetworkMetrics__link_rssi_dbm(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__NetworkMetrics__link_rssi_dbm(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember NetworkMetrics_message_member_array[22] = {
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, timestamp),  // bytes offset in struct
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
    offsetof(aura_msgs::msg::NetworkMetrics, grid_size_x),  // bytes offset in struct
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
    offsetof(aura_msgs::msg::NetworkMetrics, grid_size_y),  // bytes offset in struct
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
    offsetof(aura_msgs::msg::NetworkMetrics, cell_size_meters),  // bytes offset in struct
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
    offsetof(aura_msgs::msg::NetworkMetrics, origin),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "signal_strength_dbm",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, signal_strength_dbm),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__signal_strength_dbm,  // size() function pointer
    get_const_function__NetworkMetrics__signal_strength_dbm,  // get_const(index) function pointer
    get_function__NetworkMetrics__signal_strength_dbm,  // get(index) function pointer
    fetch_function__NetworkMetrics__signal_strength_dbm,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__signal_strength_dbm,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__signal_strength_dbm  // resize(index) function pointer
  },
  {
    "throughput_mbps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, throughput_mbps),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__throughput_mbps,  // size() function pointer
    get_const_function__NetworkMetrics__throughput_mbps,  // get_const(index) function pointer
    get_function__NetworkMetrics__throughput_mbps,  // get(index) function pointer
    fetch_function__NetworkMetrics__throughput_mbps,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__throughput_mbps,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__throughput_mbps  // resize(index) function pointer
  },
  {
    "latency_ms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, latency_ms),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__latency_ms,  // size() function pointer
    get_const_function__NetworkMetrics__latency_ms,  // get_const(index) function pointer
    get_function__NetworkMetrics__latency_ms,  // get(index) function pointer
    fetch_function__NetworkMetrics__latency_ms,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__latency_ms,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__latency_ms  // resize(index) function pointer
  },
  {
    "coverage_mask",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, coverage_mask),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__coverage_mask,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    fetch_function__NetworkMetrics__coverage_mask,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__coverage_mask,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__coverage_mask  // resize(index) function pointer
  },
  {
    "total_coverage_percent",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, total_coverage_percent),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "avg_signal_strength_dbm",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, avg_signal_strength_dbm),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "avg_throughput_mbps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, avg_throughput_mbps),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "avg_latency_ms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, avg_latency_ms),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "packet_loss_percent",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, packet_loss_percent),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "link_from_drone",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, link_from_drone),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__link_from_drone,  // size() function pointer
    get_const_function__NetworkMetrics__link_from_drone,  // get_const(index) function pointer
    get_function__NetworkMetrics__link_from_drone,  // get(index) function pointer
    fetch_function__NetworkMetrics__link_from_drone,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__link_from_drone,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__link_from_drone  // resize(index) function pointer
  },
  {
    "link_to_drone",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, link_to_drone),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__link_to_drone,  // size() function pointer
    get_const_function__NetworkMetrics__link_to_drone,  // get_const(index) function pointer
    get_function__NetworkMetrics__link_to_drone,  // get(index) function pointer
    fetch_function__NetworkMetrics__link_to_drone,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__link_to_drone,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__link_to_drone  // resize(index) function pointer
  },
  {
    "link_throughput_mbps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, link_throughput_mbps),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__link_throughput_mbps,  // size() function pointer
    get_const_function__NetworkMetrics__link_throughput_mbps,  // get_const(index) function pointer
    get_function__NetworkMetrics__link_throughput_mbps,  // get(index) function pointer
    fetch_function__NetworkMetrics__link_throughput_mbps,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__link_throughput_mbps,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__link_throughput_mbps  // resize(index) function pointer
  },
  {
    "link_latency_ms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, link_latency_ms),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__link_latency_ms,  // size() function pointer
    get_const_function__NetworkMetrics__link_latency_ms,  // get_const(index) function pointer
    get_function__NetworkMetrics__link_latency_ms,  // get(index) function pointer
    fetch_function__NetworkMetrics__link_latency_ms,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__link_latency_ms,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__link_latency_ms  // resize(index) function pointer
  },
  {
    "link_rssi_dbm",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, link_rssi_dbm),  // bytes offset in struct
    nullptr,  // default value
    size_function__NetworkMetrics__link_rssi_dbm,  // size() function pointer
    get_const_function__NetworkMetrics__link_rssi_dbm,  // get_const(index) function pointer
    get_function__NetworkMetrics__link_rssi_dbm,  // get(index) function pointer
    fetch_function__NetworkMetrics__link_rssi_dbm,  // fetch(index, &value) function pointer
    assign_function__NetworkMetrics__link_rssi_dbm,  // assign(index, value) function pointer
    resize_function__NetworkMetrics__link_rssi_dbm  // resize(index) function pointer
  },
  {
    "backhaul_active",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, backhaul_active),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "backhaul_throughput_mbps",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, backhaul_throughput_mbps),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "backhaul_latency_ms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs::msg::NetworkMetrics, backhaul_latency_ms),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers NetworkMetrics_message_members = {
  "aura_msgs::msg",  // message namespace
  "NetworkMetrics",  // message name
  22,  // number of fields
  sizeof(aura_msgs::msg::NetworkMetrics),
  NetworkMetrics_message_member_array,  // message members
  NetworkMetrics_init_function,  // function to initialize message memory (memory has to be allocated)
  NetworkMetrics_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t NetworkMetrics_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &NetworkMetrics_message_members,
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
get_message_type_support_handle<aura_msgs::msg::NetworkMetrics>()
{
  return &::aura_msgs::msg::rosidl_typesupport_introspection_cpp::NetworkMetrics_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aura_msgs, msg, NetworkMetrics)() {
  return &::aura_msgs::msg::rosidl_typesupport_introspection_cpp::NetworkMetrics_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
