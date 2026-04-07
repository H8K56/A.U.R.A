// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/drone_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `orientation`
#include "geometry_msgs/msg/detail/quaternion__functions.h"

bool
aura_msgs__msg__DroneState__init(aura_msgs__msg__DroneState * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__DroneState__fini(msg);
    return false;
  }
  // drone_id
  // role
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    aura_msgs__msg__DroneState__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__init(&msg->velocity)) {
    aura_msgs__msg__DroneState__fini(msg);
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__init(&msg->orientation)) {
    aura_msgs__msg__DroneState__fini(msg);
    return false;
  }
  // flight_mode
  // battery_percent
  // battery_voltage
  // signal_strength_dbm
  // gps_fix
  // num_satellites
  // throughput_mbps
  // latency_ms
  // connected_neighbors
  return true;
}

void
aura_msgs__msg__DroneState__fini(aura_msgs__msg__DroneState * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // drone_id
  // role
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // velocity
  geometry_msgs__msg__Vector3__fini(&msg->velocity);
  // orientation
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
  // flight_mode
  // battery_percent
  // battery_voltage
  // signal_strength_dbm
  // gps_fix
  // num_satellites
  // throughput_mbps
  // latency_ms
  // connected_neighbors
}

bool
aura_msgs__msg__DroneState__are_equal(const aura_msgs__msg__DroneState * lhs, const aura_msgs__msg__DroneState * rhs)
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
  // drone_id
  if (lhs->drone_id != rhs->drone_id) {
    return false;
  }
  // role
  if (lhs->role != rhs->role) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__are_equal(
      &(lhs->orientation), &(rhs->orientation)))
  {
    return false;
  }
  // flight_mode
  if (lhs->flight_mode != rhs->flight_mode) {
    return false;
  }
  // battery_percent
  if (lhs->battery_percent != rhs->battery_percent) {
    return false;
  }
  // battery_voltage
  if (lhs->battery_voltage != rhs->battery_voltage) {
    return false;
  }
  // signal_strength_dbm
  if (lhs->signal_strength_dbm != rhs->signal_strength_dbm) {
    return false;
  }
  // gps_fix
  if (lhs->gps_fix != rhs->gps_fix) {
    return false;
  }
  // num_satellites
  if (lhs->num_satellites != rhs->num_satellites) {
    return false;
  }
  // throughput_mbps
  if (lhs->throughput_mbps != rhs->throughput_mbps) {
    return false;
  }
  // latency_ms
  if (lhs->latency_ms != rhs->latency_ms) {
    return false;
  }
  // connected_neighbors
  if (lhs->connected_neighbors != rhs->connected_neighbors) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__DroneState__copy(
  const aura_msgs__msg__DroneState * input,
  aura_msgs__msg__DroneState * output)
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
  // drone_id
  output->drone_id = input->drone_id;
  // role
  output->role = input->role;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // orientation
  if (!geometry_msgs__msg__Quaternion__copy(
      &(input->orientation), &(output->orientation)))
  {
    return false;
  }
  // flight_mode
  output->flight_mode = input->flight_mode;
  // battery_percent
  output->battery_percent = input->battery_percent;
  // battery_voltage
  output->battery_voltage = input->battery_voltage;
  // signal_strength_dbm
  output->signal_strength_dbm = input->signal_strength_dbm;
  // gps_fix
  output->gps_fix = input->gps_fix;
  // num_satellites
  output->num_satellites = input->num_satellites;
  // throughput_mbps
  output->throughput_mbps = input->throughput_mbps;
  // latency_ms
  output->latency_ms = input->latency_ms;
  // connected_neighbors
  output->connected_neighbors = input->connected_neighbors;
  return true;
}

aura_msgs__msg__DroneState *
aura_msgs__msg__DroneState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__DroneState * msg = (aura_msgs__msg__DroneState *)allocator.allocate(sizeof(aura_msgs__msg__DroneState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__DroneState));
  bool success = aura_msgs__msg__DroneState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__DroneState__destroy(aura_msgs__msg__DroneState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__DroneState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__DroneState__Sequence__init(aura_msgs__msg__DroneState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__DroneState * data = NULL;

  if (size) {
    data = (aura_msgs__msg__DroneState *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__DroneState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__DroneState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__DroneState__fini(&data[i - 1]);
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
aura_msgs__msg__DroneState__Sequence__fini(aura_msgs__msg__DroneState__Sequence * array)
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
      aura_msgs__msg__DroneState__fini(&array->data[i]);
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

aura_msgs__msg__DroneState__Sequence *
aura_msgs__msg__DroneState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__DroneState__Sequence * array = (aura_msgs__msg__DroneState__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__DroneState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__DroneState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__DroneState__Sequence__destroy(aura_msgs__msg__DroneState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__DroneState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__DroneState__Sequence__are_equal(const aura_msgs__msg__DroneState__Sequence * lhs, const aura_msgs__msg__DroneState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__DroneState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__DroneState__Sequence__copy(
  const aura_msgs__msg__DroneState__Sequence * input,
  aura_msgs__msg__DroneState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__DroneState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__DroneState * data =
      (aura_msgs__msg__DroneState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__DroneState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__DroneState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__DroneState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
