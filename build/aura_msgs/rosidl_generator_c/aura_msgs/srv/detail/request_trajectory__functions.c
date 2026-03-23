// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:srv/RequestTrajectory.idl
// generated code does not contain a copyright notice
#include "aura_msgs/srv/detail/request_trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `goal_position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
aura_msgs__srv__RequestTrajectory_Request__init(aura_msgs__srv__RequestTrajectory_Request * msg)
{
  if (!msg) {
    return false;
  }
  // drone_id
  // goal_position
  if (!geometry_msgs__msg__Point__init(&msg->goal_position)) {
    aura_msgs__srv__RequestTrajectory_Request__fini(msg);
    return false;
  }
  // max_velocity
  // max_time
  // avoid_weather_zones
  return true;
}

void
aura_msgs__srv__RequestTrajectory_Request__fini(aura_msgs__srv__RequestTrajectory_Request * msg)
{
  if (!msg) {
    return;
  }
  // drone_id
  // goal_position
  geometry_msgs__msg__Point__fini(&msg->goal_position);
  // max_velocity
  // max_time
  // avoid_weather_zones
}

bool
aura_msgs__srv__RequestTrajectory_Request__are_equal(const aura_msgs__srv__RequestTrajectory_Request * lhs, const aura_msgs__srv__RequestTrajectory_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // drone_id
  if (lhs->drone_id != rhs->drone_id) {
    return false;
  }
  // goal_position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->goal_position), &(rhs->goal_position)))
  {
    return false;
  }
  // max_velocity
  if (lhs->max_velocity != rhs->max_velocity) {
    return false;
  }
  // max_time
  if (lhs->max_time != rhs->max_time) {
    return false;
  }
  // avoid_weather_zones
  if (lhs->avoid_weather_zones != rhs->avoid_weather_zones) {
    return false;
  }
  return true;
}

bool
aura_msgs__srv__RequestTrajectory_Request__copy(
  const aura_msgs__srv__RequestTrajectory_Request * input,
  aura_msgs__srv__RequestTrajectory_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // drone_id
  output->drone_id = input->drone_id;
  // goal_position
  if (!geometry_msgs__msg__Point__copy(
      &(input->goal_position), &(output->goal_position)))
  {
    return false;
  }
  // max_velocity
  output->max_velocity = input->max_velocity;
  // max_time
  output->max_time = input->max_time;
  // avoid_weather_zones
  output->avoid_weather_zones = input->avoid_weather_zones;
  return true;
}

aura_msgs__srv__RequestTrajectory_Request *
aura_msgs__srv__RequestTrajectory_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Request * msg = (aura_msgs__srv__RequestTrajectory_Request *)allocator.allocate(sizeof(aura_msgs__srv__RequestTrajectory_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__srv__RequestTrajectory_Request));
  bool success = aura_msgs__srv__RequestTrajectory_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__srv__RequestTrajectory_Request__destroy(aura_msgs__srv__RequestTrajectory_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__srv__RequestTrajectory_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__srv__RequestTrajectory_Request__Sequence__init(aura_msgs__srv__RequestTrajectory_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Request * data = NULL;

  if (size) {
    data = (aura_msgs__srv__RequestTrajectory_Request *)allocator.zero_allocate(size, sizeof(aura_msgs__srv__RequestTrajectory_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__srv__RequestTrajectory_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__srv__RequestTrajectory_Request__fini(&data[i - 1]);
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
aura_msgs__srv__RequestTrajectory_Request__Sequence__fini(aura_msgs__srv__RequestTrajectory_Request__Sequence * array)
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
      aura_msgs__srv__RequestTrajectory_Request__fini(&array->data[i]);
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

aura_msgs__srv__RequestTrajectory_Request__Sequence *
aura_msgs__srv__RequestTrajectory_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Request__Sequence * array = (aura_msgs__srv__RequestTrajectory_Request__Sequence *)allocator.allocate(sizeof(aura_msgs__srv__RequestTrajectory_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__srv__RequestTrajectory_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__srv__RequestTrajectory_Request__Sequence__destroy(aura_msgs__srv__RequestTrajectory_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__srv__RequestTrajectory_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__srv__RequestTrajectory_Request__Sequence__are_equal(const aura_msgs__srv__RequestTrajectory_Request__Sequence * lhs, const aura_msgs__srv__RequestTrajectory_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__srv__RequestTrajectory_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__srv__RequestTrajectory_Request__Sequence__copy(
  const aura_msgs__srv__RequestTrajectory_Request__Sequence * input,
  aura_msgs__srv__RequestTrajectory_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__srv__RequestTrajectory_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__srv__RequestTrajectory_Request * data =
      (aura_msgs__srv__RequestTrajectory_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__srv__RequestTrajectory_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__srv__RequestTrajectory_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__srv__RequestTrajectory_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `trajectory`
#include "aura_msgs/msg/detail/trajectory_broadcast__functions.h"

bool
aura_msgs__srv__RequestTrajectory_Response__init(aura_msgs__srv__RequestTrajectory_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    aura_msgs__srv__RequestTrajectory_Response__fini(msg);
    return false;
  }
  // trajectory
  if (!aura_msgs__msg__TrajectoryBroadcast__init(&msg->trajectory)) {
    aura_msgs__srv__RequestTrajectory_Response__fini(msg);
    return false;
  }
  // estimated_time
  // estimated_energy
  return true;
}

void
aura_msgs__srv__RequestTrajectory_Response__fini(aura_msgs__srv__RequestTrajectory_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // trajectory
  aura_msgs__msg__TrajectoryBroadcast__fini(&msg->trajectory);
  // estimated_time
  // estimated_energy
}

bool
aura_msgs__srv__RequestTrajectory_Response__are_equal(const aura_msgs__srv__RequestTrajectory_Response * lhs, const aura_msgs__srv__RequestTrajectory_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // trajectory
  if (!aura_msgs__msg__TrajectoryBroadcast__are_equal(
      &(lhs->trajectory), &(rhs->trajectory)))
  {
    return false;
  }
  // estimated_time
  if (lhs->estimated_time != rhs->estimated_time) {
    return false;
  }
  // estimated_energy
  if (lhs->estimated_energy != rhs->estimated_energy) {
    return false;
  }
  return true;
}

bool
aura_msgs__srv__RequestTrajectory_Response__copy(
  const aura_msgs__srv__RequestTrajectory_Response * input,
  aura_msgs__srv__RequestTrajectory_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // trajectory
  if (!aura_msgs__msg__TrajectoryBroadcast__copy(
      &(input->trajectory), &(output->trajectory)))
  {
    return false;
  }
  // estimated_time
  output->estimated_time = input->estimated_time;
  // estimated_energy
  output->estimated_energy = input->estimated_energy;
  return true;
}

aura_msgs__srv__RequestTrajectory_Response *
aura_msgs__srv__RequestTrajectory_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Response * msg = (aura_msgs__srv__RequestTrajectory_Response *)allocator.allocate(sizeof(aura_msgs__srv__RequestTrajectory_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__srv__RequestTrajectory_Response));
  bool success = aura_msgs__srv__RequestTrajectory_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__srv__RequestTrajectory_Response__destroy(aura_msgs__srv__RequestTrajectory_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__srv__RequestTrajectory_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__srv__RequestTrajectory_Response__Sequence__init(aura_msgs__srv__RequestTrajectory_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Response * data = NULL;

  if (size) {
    data = (aura_msgs__srv__RequestTrajectory_Response *)allocator.zero_allocate(size, sizeof(aura_msgs__srv__RequestTrajectory_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__srv__RequestTrajectory_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__srv__RequestTrajectory_Response__fini(&data[i - 1]);
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
aura_msgs__srv__RequestTrajectory_Response__Sequence__fini(aura_msgs__srv__RequestTrajectory_Response__Sequence * array)
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
      aura_msgs__srv__RequestTrajectory_Response__fini(&array->data[i]);
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

aura_msgs__srv__RequestTrajectory_Response__Sequence *
aura_msgs__srv__RequestTrajectory_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__RequestTrajectory_Response__Sequence * array = (aura_msgs__srv__RequestTrajectory_Response__Sequence *)allocator.allocate(sizeof(aura_msgs__srv__RequestTrajectory_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__srv__RequestTrajectory_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__srv__RequestTrajectory_Response__Sequence__destroy(aura_msgs__srv__RequestTrajectory_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__srv__RequestTrajectory_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__srv__RequestTrajectory_Response__Sequence__are_equal(const aura_msgs__srv__RequestTrajectory_Response__Sequence * lhs, const aura_msgs__srv__RequestTrajectory_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__srv__RequestTrajectory_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__srv__RequestTrajectory_Response__Sequence__copy(
  const aura_msgs__srv__RequestTrajectory_Response__Sequence * input,
  aura_msgs__srv__RequestTrajectory_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__srv__RequestTrajectory_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__srv__RequestTrajectory_Response * data =
      (aura_msgs__srv__RequestTrajectory_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__srv__RequestTrajectory_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__srv__RequestTrajectory_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__srv__RequestTrajectory_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
