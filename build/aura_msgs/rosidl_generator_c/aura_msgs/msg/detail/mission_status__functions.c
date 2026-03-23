// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/mission_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `mission_id`
// Member `active_alerts`
#include "rosidl_runtime_c/string_functions.h"
// Member `alert_severities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
aura_msgs__msg__MissionStatus__init(aura_msgs__msg__MissionStatus * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__MissionStatus__fini(msg);
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__init(&msg->mission_id)) {
    aura_msgs__msg__MissionStatus__fini(msg);
    return false;
  }
  // phase
  // progress_percent
  // elapsed_time_sec
  // estimated_remaining_sec
  // coverage_achieved
  // network_quality
  // connections_established
  // data_transferred_mb
  // active_alerts
  if (!rosidl_runtime_c__String__Sequence__init(&msg->active_alerts, 0)) {
    aura_msgs__msg__MissionStatus__fini(msg);
    return false;
  }
  // alert_severities
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->alert_severities, 0)) {
    aura_msgs__msg__MissionStatus__fini(msg);
    return false;
  }
  // drones_operational
  // drones_degraded
  // drones_failed
  return true;
}

void
aura_msgs__msg__MissionStatus__fini(aura_msgs__msg__MissionStatus * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // mission_id
  rosidl_runtime_c__String__fini(&msg->mission_id);
  // phase
  // progress_percent
  // elapsed_time_sec
  // estimated_remaining_sec
  // coverage_achieved
  // network_quality
  // connections_established
  // data_transferred_mb
  // active_alerts
  rosidl_runtime_c__String__Sequence__fini(&msg->active_alerts);
  // alert_severities
  rosidl_runtime_c__uint8__Sequence__fini(&msg->alert_severities);
  // drones_operational
  // drones_degraded
  // drones_failed
}

bool
aura_msgs__msg__MissionStatus__are_equal(const aura_msgs__msg__MissionStatus * lhs, const aura_msgs__msg__MissionStatus * rhs)
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
  // mission_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_id), &(rhs->mission_id)))
  {
    return false;
  }
  // phase
  if (lhs->phase != rhs->phase) {
    return false;
  }
  // progress_percent
  if (lhs->progress_percent != rhs->progress_percent) {
    return false;
  }
  // elapsed_time_sec
  if (lhs->elapsed_time_sec != rhs->elapsed_time_sec) {
    return false;
  }
  // estimated_remaining_sec
  if (lhs->estimated_remaining_sec != rhs->estimated_remaining_sec) {
    return false;
  }
  // coverage_achieved
  if (lhs->coverage_achieved != rhs->coverage_achieved) {
    return false;
  }
  // network_quality
  if (lhs->network_quality != rhs->network_quality) {
    return false;
  }
  // connections_established
  if (lhs->connections_established != rhs->connections_established) {
    return false;
  }
  // data_transferred_mb
  if (lhs->data_transferred_mb != rhs->data_transferred_mb) {
    return false;
  }
  // active_alerts
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->active_alerts), &(rhs->active_alerts)))
  {
    return false;
  }
  // alert_severities
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->alert_severities), &(rhs->alert_severities)))
  {
    return false;
  }
  // drones_operational
  if (lhs->drones_operational != rhs->drones_operational) {
    return false;
  }
  // drones_degraded
  if (lhs->drones_degraded != rhs->drones_degraded) {
    return false;
  }
  // drones_failed
  if (lhs->drones_failed != rhs->drones_failed) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__MissionStatus__copy(
  const aura_msgs__msg__MissionStatus * input,
  aura_msgs__msg__MissionStatus * output)
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
  // mission_id
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_id), &(output->mission_id)))
  {
    return false;
  }
  // phase
  output->phase = input->phase;
  // progress_percent
  output->progress_percent = input->progress_percent;
  // elapsed_time_sec
  output->elapsed_time_sec = input->elapsed_time_sec;
  // estimated_remaining_sec
  output->estimated_remaining_sec = input->estimated_remaining_sec;
  // coverage_achieved
  output->coverage_achieved = input->coverage_achieved;
  // network_quality
  output->network_quality = input->network_quality;
  // connections_established
  output->connections_established = input->connections_established;
  // data_transferred_mb
  output->data_transferred_mb = input->data_transferred_mb;
  // active_alerts
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->active_alerts), &(output->active_alerts)))
  {
    return false;
  }
  // alert_severities
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->alert_severities), &(output->alert_severities)))
  {
    return false;
  }
  // drones_operational
  output->drones_operational = input->drones_operational;
  // drones_degraded
  output->drones_degraded = input->drones_degraded;
  // drones_failed
  output->drones_failed = input->drones_failed;
  return true;
}

aura_msgs__msg__MissionStatus *
aura_msgs__msg__MissionStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__MissionStatus * msg = (aura_msgs__msg__MissionStatus *)allocator.allocate(sizeof(aura_msgs__msg__MissionStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__MissionStatus));
  bool success = aura_msgs__msg__MissionStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__MissionStatus__destroy(aura_msgs__msg__MissionStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__MissionStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__MissionStatus__Sequence__init(aura_msgs__msg__MissionStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__MissionStatus * data = NULL;

  if (size) {
    data = (aura_msgs__msg__MissionStatus *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__MissionStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__MissionStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__MissionStatus__fini(&data[i - 1]);
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
aura_msgs__msg__MissionStatus__Sequence__fini(aura_msgs__msg__MissionStatus__Sequence * array)
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
      aura_msgs__msg__MissionStatus__fini(&array->data[i]);
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

aura_msgs__msg__MissionStatus__Sequence *
aura_msgs__msg__MissionStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__MissionStatus__Sequence * array = (aura_msgs__msg__MissionStatus__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__MissionStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__MissionStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__MissionStatus__Sequence__destroy(aura_msgs__msg__MissionStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__MissionStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__MissionStatus__Sequence__are_equal(const aura_msgs__msg__MissionStatus__Sequence * lhs, const aura_msgs__msg__MissionStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__MissionStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__MissionStatus__Sequence__copy(
  const aura_msgs__msg__MissionStatus__Sequence * input,
  aura_msgs__msg__MissionStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__MissionStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__MissionStatus * data =
      (aura_msgs__msg__MissionStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__MissionStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__MissionStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__MissionStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
