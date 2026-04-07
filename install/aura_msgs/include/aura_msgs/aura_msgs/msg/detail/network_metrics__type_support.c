// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/msg/detail/network_metrics__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/msg/detail/network_metrics__functions.h"
#include "aura_msgs/msg/detail/network_metrics__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `origin`
#include "geometry_msgs/msg/point.h"
// Member `origin`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `signal_strength_dbm`
// Member `throughput_mbps`
// Member `latency_ms`
// Member `coverage_mask`
// Member `link_from_drone`
// Member `link_to_drone`
// Member `link_throughput_mbps`
// Member `link_latency_ms`
// Member `link_rssi_dbm`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__msg__NetworkMetrics__init(message_memory);
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_fini_function(void * message_memory)
{
  aura_msgs__msg__NetworkMetrics__fini(message_memory);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__signal_strength_dbm(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__signal_strength_dbm(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__signal_strength_dbm(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__signal_strength_dbm(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__signal_strength_dbm(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__signal_strength_dbm(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__signal_strength_dbm(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__signal_strength_dbm(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__throughput_mbps(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__throughput_mbps(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__throughput_mbps(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__throughput_mbps(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__throughput_mbps(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__throughput_mbps(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__throughput_mbps(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__throughput_mbps(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__latency_ms(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__latency_ms(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__latency_ms(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__latency_ms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__latency_ms(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__latency_ms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__latency_ms(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__latency_ms(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__coverage_mask(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__coverage_mask(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__coverage_mask(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__coverage_mask(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__coverage_mask(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__coverage_mask(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__coverage_mask(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__coverage_mask(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_from_drone(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_from_drone(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_from_drone(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_from_drone(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_from_drone(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_from_drone(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_from_drone(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_from_drone(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_to_drone(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_to_drone(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_to_drone(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_to_drone(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_to_drone(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_to_drone(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_to_drone(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_to_drone(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_throughput_mbps(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_throughput_mbps(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_throughput_mbps(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_throughput_mbps(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_throughput_mbps(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_throughput_mbps(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_throughput_mbps(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_throughput_mbps(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_latency_ms(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_latency_ms(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_latency_ms(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_latency_ms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_latency_ms(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_latency_ms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_latency_ms(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_latency_ms(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_rssi_dbm(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_rssi_dbm(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_rssi_dbm(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_rssi_dbm(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_rssi_dbm(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_rssi_dbm(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_rssi_dbm(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_rssi_dbm(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_member_array[24] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grid_size_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, grid_size_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grid_size_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, grid_size_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_size_meters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, cell_size_meters),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "origin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, origin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "signal_strength_dbm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, signal_strength_dbm),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__signal_strength_dbm,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__signal_strength_dbm,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__signal_strength_dbm,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__signal_strength_dbm,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__signal_strength_dbm,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__signal_strength_dbm  // resize(index) function pointer
  },
  {
    "throughput_mbps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, throughput_mbps),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__throughput_mbps,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__throughput_mbps,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__throughput_mbps,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__throughput_mbps,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__throughput_mbps,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__throughput_mbps  // resize(index) function pointer
  },
  {
    "latency_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, latency_ms),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__latency_ms,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__latency_ms,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__latency_ms,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__latency_ms,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__latency_ms,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__latency_ms  // resize(index) function pointer
  },
  {
    "coverage_mask",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, coverage_mask),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__coverage_mask,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__coverage_mask,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__coverage_mask,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__coverage_mask,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__coverage_mask,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__coverage_mask  // resize(index) function pointer
  },
  {
    "total_coverage_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, total_coverage_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "avg_signal_strength_dbm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, avg_signal_strength_dbm),  // bytes offset in struct
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
    offsetof(aura_msgs__msg__NetworkMetrics, avg_throughput_mbps),  // bytes offset in struct
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
    offsetof(aura_msgs__msg__NetworkMetrics, avg_latency_ms),  // bytes offset in struct
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
    offsetof(aura_msgs__msg__NetworkMetrics, packet_loss_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "link_from_drone",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, link_from_drone),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_from_drone,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_from_drone,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_from_drone,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_from_drone,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_from_drone,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_from_drone  // resize(index) function pointer
  },
  {
    "link_to_drone",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, link_to_drone),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_to_drone,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_to_drone,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_to_drone,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_to_drone,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_to_drone,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_to_drone  // resize(index) function pointer
  },
  {
    "link_throughput_mbps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, link_throughput_mbps),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_throughput_mbps,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_throughput_mbps,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_throughput_mbps,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_throughput_mbps,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_throughput_mbps,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_throughput_mbps  // resize(index) function pointer
  },
  {
    "link_latency_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, link_latency_ms),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_latency_ms,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_latency_ms,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_latency_ms,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_latency_ms,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_latency_ms,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_latency_ms  // resize(index) function pointer
  },
  {
    "link_rssi_dbm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, link_rssi_dbm),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__size_function__NetworkMetrics__link_rssi_dbm,  // size() function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_const_function__NetworkMetrics__link_rssi_dbm,  // get_const(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__get_function__NetworkMetrics__link_rssi_dbm,  // get(index) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__fetch_function__NetworkMetrics__link_rssi_dbm,  // fetch(index, &value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__assign_function__NetworkMetrics__link_rssi_dbm,  // assign(index, value) function pointer
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__resize_function__NetworkMetrics__link_rssi_dbm  // resize(index) function pointer
  },
  {
    "mesh_connected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, mesh_connected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "backhaul_active",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, backhaul_active),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "backhaul_throughput_mbps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, backhaul_throughput_mbps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "backhaul_latency_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__NetworkMetrics, backhaul_latency_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_members = {
  "aura_msgs__msg",  // message namespace
  "NetworkMetrics",  // message name
  24,  // number of fields
  sizeof(aura_msgs__msg__NetworkMetrics),
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_member_array,  // message members
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_type_support_handle = {
  0,
  &aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, NetworkMetrics)() {
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_type_support_handle.typesupport_identifier) {
    aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__msg__NetworkMetrics__rosidl_typesupport_introspection_c__NetworkMetrics_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
