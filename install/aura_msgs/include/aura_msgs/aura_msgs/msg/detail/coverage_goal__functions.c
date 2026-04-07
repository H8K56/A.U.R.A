// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/CoverageGoal.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/coverage_goal__functions.h"

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

bool
aura_msgs__msg__CoverageGoal__init(aura_msgs__msg__CoverageGoal * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__CoverageGoal__fini(msg);
    return false;
  }
  // drone_id
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    aura_msgs__msg__CoverageGoal__fini(msg);
    return false;
  }
  // desired_arrival_time
  // formation_type
  // priority
  // min_altitude
  // max_altitude
  // max_velocity
  // required_throughput_mbps
  // required_coverage_radius
  return true;
}

void
aura_msgs__msg__CoverageGoal__fini(aura_msgs__msg__CoverageGoal * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // drone_id
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // desired_arrival_time
  // formation_type
  // priority
  // min_altitude
  // max_altitude
  // max_velocity
  // required_throughput_mbps
  // required_coverage_radius
}

bool
aura_msgs__msg__CoverageGoal__are_equal(const aura_msgs__msg__CoverageGoal * lhs, const aura_msgs__msg__CoverageGoal * rhs)
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
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // desired_arrival_time
  if (lhs->desired_arrival_time != rhs->desired_arrival_time) {
    return false;
  }
  // formation_type
  if (lhs->formation_type != rhs->formation_type) {
    return false;
  }
  // priority
  if (lhs->priority != rhs->priority) {
    return false;
  }
  // min_altitude
  if (lhs->min_altitude != rhs->min_altitude) {
    return false;
  }
  // max_altitude
  if (lhs->max_altitude != rhs->max_altitude) {
    return false;
  }
  // max_velocity
  if (lhs->max_velocity != rhs->max_velocity) {
    return false;
  }
  // required_throughput_mbps
  if (lhs->required_throughput_mbps != rhs->required_throughput_mbps) {
    return false;
  }
  // required_coverage_radius
  if (lhs->required_coverage_radius != rhs->required_coverage_radius) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__CoverageGoal__copy(
  const aura_msgs__msg__CoverageGoal * input,
  aura_msgs__msg__CoverageGoal * output)
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
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // desired_arrival_time
  output->desired_arrival_time = input->desired_arrival_time;
  // formation_type
  output->formation_type = input->formation_type;
  // priority
  output->priority = input->priority;
  // min_altitude
  output->min_altitude = input->min_altitude;
  // max_altitude
  output->max_altitude = input->max_altitude;
  // max_velocity
  output->max_velocity = input->max_velocity;
  // required_throughput_mbps
  output->required_throughput_mbps = input->required_throughput_mbps;
  // required_coverage_radius
  output->required_coverage_radius = input->required_coverage_radius;
  return true;
}

aura_msgs__msg__CoverageGoal *
aura_msgs__msg__CoverageGoal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageGoal * msg = (aura_msgs__msg__CoverageGoal *)allocator.allocate(sizeof(aura_msgs__msg__CoverageGoal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__CoverageGoal));
  bool success = aura_msgs__msg__CoverageGoal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__CoverageGoal__destroy(aura_msgs__msg__CoverageGoal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__CoverageGoal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__CoverageGoal__Sequence__init(aura_msgs__msg__CoverageGoal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageGoal * data = NULL;

  if (size) {
    data = (aura_msgs__msg__CoverageGoal *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__CoverageGoal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__CoverageGoal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__CoverageGoal__fini(&data[i - 1]);
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
aura_msgs__msg__CoverageGoal__Sequence__fini(aura_msgs__msg__CoverageGoal__Sequence * array)
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
      aura_msgs__msg__CoverageGoal__fini(&array->data[i]);
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

aura_msgs__msg__CoverageGoal__Sequence *
aura_msgs__msg__CoverageGoal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageGoal__Sequence * array = (aura_msgs__msg__CoverageGoal__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__CoverageGoal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__CoverageGoal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__CoverageGoal__Sequence__destroy(aura_msgs__msg__CoverageGoal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__CoverageGoal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__CoverageGoal__Sequence__are_equal(const aura_msgs__msg__CoverageGoal__Sequence * lhs, const aura_msgs__msg__CoverageGoal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__CoverageGoal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__CoverageGoal__Sequence__copy(
  const aura_msgs__msg__CoverageGoal__Sequence * input,
  aura_msgs__msg__CoverageGoal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__CoverageGoal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__CoverageGoal * data =
      (aura_msgs__msg__CoverageGoal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__CoverageGoal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__CoverageGoal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__CoverageGoal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
