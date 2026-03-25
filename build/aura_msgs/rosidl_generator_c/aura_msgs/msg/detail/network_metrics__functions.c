// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/network_metrics__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `origin`
#include "geometry_msgs/msg/detail/point__functions.h"
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

bool
aura_msgs__msg__NetworkMetrics__init(aura_msgs__msg__NetworkMetrics * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // grid_size_x
  // grid_size_y
  // cell_size_meters
  // origin
  if (!geometry_msgs__msg__Point__init(&msg->origin)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // signal_strength_dbm
  if (!rosidl_runtime_c__float__Sequence__init(&msg->signal_strength_dbm, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__init(&msg->throughput_mbps, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // latency_ms
  if (!rosidl_runtime_c__float__Sequence__init(&msg->latency_ms, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // coverage_mask
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->coverage_mask, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // total_coverage_percent
  // avg_signal_strength_dbm
  // avg_throughput_mbps
  // avg_latency_ms
  // packet_loss_percent
  // link_from_drone
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->link_from_drone, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // link_to_drone
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->link_to_drone, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // link_throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__init(&msg->link_throughput_mbps, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // link_latency_ms
  if (!rosidl_runtime_c__float__Sequence__init(&msg->link_latency_ms, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // link_rssi_dbm
  if (!rosidl_runtime_c__float__Sequence__init(&msg->link_rssi_dbm, 0)) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
    return false;
  }
  // backhaul_active
  // backhaul_throughput_mbps
  // backhaul_latency_ms
  return true;
}

void
aura_msgs__msg__NetworkMetrics__fini(aura_msgs__msg__NetworkMetrics * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // grid_size_x
  // grid_size_y
  // cell_size_meters
  // origin
  geometry_msgs__msg__Point__fini(&msg->origin);
  // signal_strength_dbm
  rosidl_runtime_c__float__Sequence__fini(&msg->signal_strength_dbm);
  // throughput_mbps
  rosidl_runtime_c__float__Sequence__fini(&msg->throughput_mbps);
  // latency_ms
  rosidl_runtime_c__float__Sequence__fini(&msg->latency_ms);
  // coverage_mask
  rosidl_runtime_c__boolean__Sequence__fini(&msg->coverage_mask);
  // total_coverage_percent
  // avg_signal_strength_dbm
  // avg_throughput_mbps
  // avg_latency_ms
  // packet_loss_percent
  // link_from_drone
  rosidl_runtime_c__uint8__Sequence__fini(&msg->link_from_drone);
  // link_to_drone
  rosidl_runtime_c__uint8__Sequence__fini(&msg->link_to_drone);
  // link_throughput_mbps
  rosidl_runtime_c__float__Sequence__fini(&msg->link_throughput_mbps);
  // link_latency_ms
  rosidl_runtime_c__float__Sequence__fini(&msg->link_latency_ms);
  // link_rssi_dbm
  rosidl_runtime_c__float__Sequence__fini(&msg->link_rssi_dbm);
  // backhaul_active
  // backhaul_throughput_mbps
  // backhaul_latency_ms
}

bool
aura_msgs__msg__NetworkMetrics__are_equal(const aura_msgs__msg__NetworkMetrics * lhs, const aura_msgs__msg__NetworkMetrics * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->timestamp), &(rhs->timestamp)))
  {
    return false;
  }
  // grid_size_x
  if (lhs->grid_size_x != rhs->grid_size_x) {
    return false;
  }
  // grid_size_y
  if (lhs->grid_size_y != rhs->grid_size_y) {
    return false;
  }
  // cell_size_meters
  if (lhs->cell_size_meters != rhs->cell_size_meters) {
    return false;
  }
  // origin
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->origin), &(rhs->origin)))
  {
    return false;
  }
  // signal_strength_dbm
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->signal_strength_dbm), &(rhs->signal_strength_dbm)))
  {
    return false;
  }
  // throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->throughput_mbps), &(rhs->throughput_mbps)))
  {
    return false;
  }
  // latency_ms
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->latency_ms), &(rhs->latency_ms)))
  {
    return false;
  }
  // coverage_mask
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->coverage_mask), &(rhs->coverage_mask)))
  {
    return false;
  }
  // total_coverage_percent
  if (lhs->total_coverage_percent != rhs->total_coverage_percent) {
    return false;
  }
  // avg_signal_strength_dbm
  if (lhs->avg_signal_strength_dbm != rhs->avg_signal_strength_dbm) {
    return false;
  }
  // avg_throughput_mbps
  if (lhs->avg_throughput_mbps != rhs->avg_throughput_mbps) {
    return false;
  }
  // avg_latency_ms
  if (lhs->avg_latency_ms != rhs->avg_latency_ms) {
    return false;
  }
  // packet_loss_percent
  if (lhs->packet_loss_percent != rhs->packet_loss_percent) {
    return false;
  }
  // link_from_drone
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->link_from_drone), &(rhs->link_from_drone)))
  {
    return false;
  }
  // link_to_drone
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->link_to_drone), &(rhs->link_to_drone)))
  {
    return false;
  }
  // link_throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->link_throughput_mbps), &(rhs->link_throughput_mbps)))
  {
    return false;
  }
  // link_latency_ms
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->link_latency_ms), &(rhs->link_latency_ms)))
  {
    return false;
  }
  // link_rssi_dbm
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->link_rssi_dbm), &(rhs->link_rssi_dbm)))
  {
    return false;
  }
  // backhaul_active
  if (lhs->backhaul_active != rhs->backhaul_active) {
    return false;
  }
  // backhaul_throughput_mbps
  if (lhs->backhaul_throughput_mbps != rhs->backhaul_throughput_mbps) {
    return false;
  }
  // backhaul_latency_ms
  if (lhs->backhaul_latency_ms != rhs->backhaul_latency_ms) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__NetworkMetrics__copy(
  const aura_msgs__msg__NetworkMetrics * input,
  aura_msgs__msg__NetworkMetrics * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->timestamp), &(output->timestamp)))
  {
    return false;
  }
  // grid_size_x
  output->grid_size_x = input->grid_size_x;
  // grid_size_y
  output->grid_size_y = input->grid_size_y;
  // cell_size_meters
  output->cell_size_meters = input->cell_size_meters;
  // origin
  if (!geometry_msgs__msg__Point__copy(
      &(input->origin), &(output->origin)))
  {
    return false;
  }
  // signal_strength_dbm
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->signal_strength_dbm), &(output->signal_strength_dbm)))
  {
    return false;
  }
  // throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->throughput_mbps), &(output->throughput_mbps)))
  {
    return false;
  }
  // latency_ms
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->latency_ms), &(output->latency_ms)))
  {
    return false;
  }
  // coverage_mask
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->coverage_mask), &(output->coverage_mask)))
  {
    return false;
  }
  // total_coverage_percent
  output->total_coverage_percent = input->total_coverage_percent;
  // avg_signal_strength_dbm
  output->avg_signal_strength_dbm = input->avg_signal_strength_dbm;
  // avg_throughput_mbps
  output->avg_throughput_mbps = input->avg_throughput_mbps;
  // avg_latency_ms
  output->avg_latency_ms = input->avg_latency_ms;
  // packet_loss_percent
  output->packet_loss_percent = input->packet_loss_percent;
  // link_from_drone
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->link_from_drone), &(output->link_from_drone)))
  {
    return false;
  }
  // link_to_drone
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->link_to_drone), &(output->link_to_drone)))
  {
    return false;
  }
  // link_throughput_mbps
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->link_throughput_mbps), &(output->link_throughput_mbps)))
  {
    return false;
  }
  // link_latency_ms
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->link_latency_ms), &(output->link_latency_ms)))
  {
    return false;
  }
  // link_rssi_dbm
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->link_rssi_dbm), &(output->link_rssi_dbm)))
  {
    return false;
  }
  // backhaul_active
  output->backhaul_active = input->backhaul_active;
  // backhaul_throughput_mbps
  output->backhaul_throughput_mbps = input->backhaul_throughput_mbps;
  // backhaul_latency_ms
  output->backhaul_latency_ms = input->backhaul_latency_ms;
  return true;
}

aura_msgs__msg__NetworkMetrics *
aura_msgs__msg__NetworkMetrics__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__NetworkMetrics * msg = (aura_msgs__msg__NetworkMetrics *)allocator.allocate(sizeof(aura_msgs__msg__NetworkMetrics), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__NetworkMetrics));
  bool success = aura_msgs__msg__NetworkMetrics__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__NetworkMetrics__destroy(aura_msgs__msg__NetworkMetrics * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__NetworkMetrics__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__NetworkMetrics__Sequence__init(aura_msgs__msg__NetworkMetrics__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__NetworkMetrics * data = NULL;

  if (size) {
    data = (aura_msgs__msg__NetworkMetrics *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__NetworkMetrics), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__NetworkMetrics__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__NetworkMetrics__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
aura_msgs__msg__NetworkMetrics__Sequence__fini(aura_msgs__msg__NetworkMetrics__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      aura_msgs__msg__NetworkMetrics__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

aura_msgs__msg__NetworkMetrics__Sequence *
aura_msgs__msg__NetworkMetrics__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__NetworkMetrics__Sequence * array = (aura_msgs__msg__NetworkMetrics__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__NetworkMetrics__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__NetworkMetrics__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__NetworkMetrics__Sequence__destroy(aura_msgs__msg__NetworkMetrics__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__NetworkMetrics__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__NetworkMetrics__Sequence__are_equal(const aura_msgs__msg__NetworkMetrics__Sequence * lhs, const aura_msgs__msg__NetworkMetrics__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__NetworkMetrics__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__NetworkMetrics__Sequence__copy(
  const aura_msgs__msg__NetworkMetrics__Sequence * input,
  aura_msgs__msg__NetworkMetrics__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__NetworkMetrics);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__NetworkMetrics * data =
      (aura_msgs__msg__NetworkMetrics *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__NetworkMetrics__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__NetworkMetrics__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__NetworkMetrics__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
