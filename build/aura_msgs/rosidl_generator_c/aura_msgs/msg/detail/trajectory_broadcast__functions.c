// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/trajectory_broadcast__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
// Member `start_time`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `waypoints`
// Member `goal_position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `time_allocation`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
aura_msgs__msg__TrajectoryBroadcast__init(aura_msgs__msg__TrajectoryBroadcast * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
    return false;
  }
  // drone_id
  // start_time
  if (!builtin_interfaces__msg__Time__init(&msg->start_time)) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
    return false;
  }
  // waypoints
  if (!geometry_msgs__msg__Point__Sequence__init(&msg->waypoints, 0)) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
    return false;
  }
  // time_allocation
  if (!rosidl_runtime_c__double__Sequence__init(&msg->time_allocation, 0)) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
    return false;
  }
  // total_duration
  // num_pieces
  // is_valid
  // max_velocity
  // clearance
  // goal_position
  if (!geometry_msgs__msg__Point__init(&msg->goal_position)) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
    return false;
  }
  // goal_reached
  return true;
}

void
aura_msgs__msg__TrajectoryBroadcast__fini(aura_msgs__msg__TrajectoryBroadcast * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // drone_id
  // start_time
  builtin_interfaces__msg__Time__fini(&msg->start_time);
  // waypoints
  geometry_msgs__msg__Point__Sequence__fini(&msg->waypoints);
  // time_allocation
  rosidl_runtime_c__double__Sequence__fini(&msg->time_allocation);
  // total_duration
  // num_pieces
  // is_valid
  // max_velocity
  // clearance
  // goal_position
  geometry_msgs__msg__Point__fini(&msg->goal_position);
  // goal_reached
}

bool
aura_msgs__msg__TrajectoryBroadcast__are_equal(const aura_msgs__msg__TrajectoryBroadcast * lhs, const aura_msgs__msg__TrajectoryBroadcast * rhs)
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
  // start_time
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->start_time), &(rhs->start_time)))
  {
    return false;
  }
  // waypoints
  if (!geometry_msgs__msg__Point__Sequence__are_equal(
      &(lhs->waypoints), &(rhs->waypoints)))
  {
    return false;
  }
  // time_allocation
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->time_allocation), &(rhs->time_allocation)))
  {
    return false;
  }
  // total_duration
  if (lhs->total_duration != rhs->total_duration) {
    return false;
  }
  // num_pieces
  if (lhs->num_pieces != rhs->num_pieces) {
    return false;
  }
  // is_valid
  if (lhs->is_valid != rhs->is_valid) {
    return false;
  }
  // max_velocity
  if (lhs->max_velocity != rhs->max_velocity) {
    return false;
  }
  // clearance
  if (lhs->clearance != rhs->clearance) {
    return false;
  }
  // goal_position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->goal_position), &(rhs->goal_position)))
  {
    return false;
  }
  // goal_reached
  if (lhs->goal_reached != rhs->goal_reached) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__TrajectoryBroadcast__copy(
  const aura_msgs__msg__TrajectoryBroadcast * input,
  aura_msgs__msg__TrajectoryBroadcast * output)
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
  // start_time
  if (!builtin_interfaces__msg__Time__copy(
      &(input->start_time), &(output->start_time)))
  {
    return false;
  }
  // waypoints
  if (!geometry_msgs__msg__Point__Sequence__copy(
      &(input->waypoints), &(output->waypoints)))
  {
    return false;
  }
  // time_allocation
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->time_allocation), &(output->time_allocation)))
  {
    return false;
  }
  // total_duration
  output->total_duration = input->total_duration;
  // num_pieces
  output->num_pieces = input->num_pieces;
  // is_valid
  output->is_valid = input->is_valid;
  // max_velocity
  output->max_velocity = input->max_velocity;
  // clearance
  output->clearance = input->clearance;
  // goal_position
  if (!geometry_msgs__msg__Point__copy(
      &(input->goal_position), &(output->goal_position)))
  {
    return false;
  }
  // goal_reached
  output->goal_reached = input->goal_reached;
  return true;
}

aura_msgs__msg__TrajectoryBroadcast *
aura_msgs__msg__TrajectoryBroadcast__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__TrajectoryBroadcast * msg = (aura_msgs__msg__TrajectoryBroadcast *)allocator.allocate(sizeof(aura_msgs__msg__TrajectoryBroadcast), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__TrajectoryBroadcast));
  bool success = aura_msgs__msg__TrajectoryBroadcast__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__TrajectoryBroadcast__destroy(aura_msgs__msg__TrajectoryBroadcast * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__TrajectoryBroadcast__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__init(aura_msgs__msg__TrajectoryBroadcast__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__TrajectoryBroadcast * data = NULL;

  if (size) {
    data = (aura_msgs__msg__TrajectoryBroadcast *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__TrajectoryBroadcast), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__TrajectoryBroadcast__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__TrajectoryBroadcast__fini(&data[i - 1]);
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
aura_msgs__msg__TrajectoryBroadcast__Sequence__fini(aura_msgs__msg__TrajectoryBroadcast__Sequence * array)
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
      aura_msgs__msg__TrajectoryBroadcast__fini(&array->data[i]);
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

aura_msgs__msg__TrajectoryBroadcast__Sequence *
aura_msgs__msg__TrajectoryBroadcast__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__TrajectoryBroadcast__Sequence * array = (aura_msgs__msg__TrajectoryBroadcast__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__TrajectoryBroadcast__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__TrajectoryBroadcast__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__TrajectoryBroadcast__Sequence__destroy(aura_msgs__msg__TrajectoryBroadcast__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__TrajectoryBroadcast__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__are_equal(const aura_msgs__msg__TrajectoryBroadcast__Sequence * lhs, const aura_msgs__msg__TrajectoryBroadcast__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__TrajectoryBroadcast__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__copy(
  const aura_msgs__msg__TrajectoryBroadcast__Sequence * input,
  aura_msgs__msg__TrajectoryBroadcast__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__TrajectoryBroadcast);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__TrajectoryBroadcast * data =
      (aura_msgs__msg__TrajectoryBroadcast *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__TrajectoryBroadcast__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__TrajectoryBroadcast__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__TrajectoryBroadcast__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
