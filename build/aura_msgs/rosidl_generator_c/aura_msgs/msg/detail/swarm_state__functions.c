// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/swarm_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `drones`
#include "aura_msgs/msg/detail/drone_state__functions.h"

bool
aura_msgs__msg__SwarmState__init(aura_msgs__msg__SwarmState * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__SwarmState__fini(msg);
    return false;
  }
  // num_drones_total
  // num_drones_active
  // num_hubs
  // num_leaves
  // mission_state
  // coverage_percent
  // coverage_quality
  // avg_throughput_mbps
  // avg_latency_ms
  // packet_loss_percent
  // mesh_connected
  // backhaul_connected
  // drones
  if (!aura_msgs__msg__DroneState__Sequence__init(&msg->drones, 0)) {
    aura_msgs__msg__SwarmState__fini(msg);
    return false;
  }
  return true;
}

void
aura_msgs__msg__SwarmState__fini(aura_msgs__msg__SwarmState * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // num_drones_total
  // num_drones_active
  // num_hubs
  // num_leaves
  // mission_state
  // coverage_percent
  // coverage_quality
  // avg_throughput_mbps
  // avg_latency_ms
  // packet_loss_percent
  // mesh_connected
  // backhaul_connected
  // drones
  aura_msgs__msg__DroneState__Sequence__fini(&msg->drones);
}

bool
aura_msgs__msg__SwarmState__are_equal(const aura_msgs__msg__SwarmState * lhs, const aura_msgs__msg__SwarmState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->timestamp), &(rhs->timestamp)))
  {
    return false;
  }
  // num_drones_total
  if (lhs->num_drones_total != rhs->num_drones_total) {
    return false;
  }
  // num_drones_active
  if (lhs->num_drones_active != rhs->num_drones_active) {
    return false;
  }
  // num_hubs
  if (lhs->num_hubs != rhs->num_hubs) {
    return false;
  }
  // num_leaves
  if (lhs->num_leaves != rhs->num_leaves) {
    return false;
  }
  // mission_state
  if (lhs->mission_state != rhs->mission_state) {
    return false;
  }
  // coverage_percent
  if (lhs->coverage_percent != rhs->coverage_percent) {
    return false;
  }
  // coverage_quality
  if (lhs->coverage_quality != rhs->coverage_quality) {
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
  // mesh_connected
  if (lhs->mesh_connected != rhs->mesh_connected) {
    return false;
  }
  // backhaul_connected
  if (lhs->backhaul_connected != rhs->backhaul_connected) {
    return false;
  }
  // drones
  if (!aura_msgs__msg__DroneState__Sequence__are_equal(
      &(lhs->drones), &(rhs->drones)))
  {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__SwarmState__copy(
  const aura_msgs__msg__SwarmState * input,
  aura_msgs__msg__SwarmState * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->timestamp), &(output->timestamp)))
  {
    return false;
  }
  // num_drones_total
  output->num_drones_total = input->num_drones_total;
  // num_drones_active
  output->num_drones_active = input->num_drones_active;
  // num_hubs
  output->num_hubs = input->num_hubs;
  // num_leaves
  output->num_leaves = input->num_leaves;
  // mission_state
  output->mission_state = input->mission_state;
  // coverage_percent
  output->coverage_percent = input->coverage_percent;
  // coverage_quality
  output->coverage_quality = input->coverage_quality;
  // avg_throughput_mbps
  output->avg_throughput_mbps = input->avg_throughput_mbps;
  // avg_latency_ms
  output->avg_latency_ms = input->avg_latency_ms;
  // packet_loss_percent
  output->packet_loss_percent = input->packet_loss_percent;
  // mesh_connected
  output->mesh_connected = input->mesh_connected;
  // backhaul_connected
  output->backhaul_connected = input->backhaul_connected;
  // drones
  if (!aura_msgs__msg__DroneState__Sequence__copy(
      &(input->drones), &(output->drones)))
  {
    return false;
  }
  return true;
}

aura_msgs__msg__SwarmState *
aura_msgs__msg__SwarmState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__SwarmState * msg = (aura_msgs__msg__SwarmState *)allocator.allocate(sizeof(aura_msgs__msg__SwarmState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__SwarmState));
  bool success = aura_msgs__msg__SwarmState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__SwarmState__destroy(aura_msgs__msg__SwarmState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__SwarmState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__SwarmState__Sequence__init(aura_msgs__msg__SwarmState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__SwarmState * data = NULL;

  if (size) {
    data = (aura_msgs__msg__SwarmState *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__SwarmState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__SwarmState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__SwarmState__fini(&data[i - 1]);
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
aura_msgs__msg__SwarmState__Sequence__fini(aura_msgs__msg__SwarmState__Sequence * array)
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
      aura_msgs__msg__SwarmState__fini(&array->data[i]);
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

aura_msgs__msg__SwarmState__Sequence *
aura_msgs__msg__SwarmState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__SwarmState__Sequence * array = (aura_msgs__msg__SwarmState__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__SwarmState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__SwarmState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__SwarmState__Sequence__destroy(aura_msgs__msg__SwarmState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__SwarmState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__SwarmState__Sequence__are_equal(const aura_msgs__msg__SwarmState__Sequence * lhs, const aura_msgs__msg__SwarmState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__SwarmState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__SwarmState__Sequence__copy(
  const aura_msgs__msg__SwarmState__Sequence * input,
  aura_msgs__msg__SwarmState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__SwarmState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__SwarmState * data =
      (aura_msgs__msg__SwarmState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__SwarmState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__SwarmState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__SwarmState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
