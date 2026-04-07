// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice
#include "aura_msgs/srv/detail/get_network_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
aura_msgs__srv__GetNetworkStatus_Request__init(aura_msgs__srv__GetNetworkStatus_Request * msg)
{
  if (!msg) {
    return false;
  }
  // include_coverage_map
  // include_link_details
  return true;
}

void
aura_msgs__srv__GetNetworkStatus_Request__fini(aura_msgs__srv__GetNetworkStatus_Request * msg)
{
  if (!msg) {
    return;
  }
  // include_coverage_map
  // include_link_details
}

bool
aura_msgs__srv__GetNetworkStatus_Request__are_equal(const aura_msgs__srv__GetNetworkStatus_Request * lhs, const aura_msgs__srv__GetNetworkStatus_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // include_coverage_map
  if (lhs->include_coverage_map != rhs->include_coverage_map) {
    return false;
  }
  // include_link_details
  if (lhs->include_link_details != rhs->include_link_details) {
    return false;
  }
  return true;
}

bool
aura_msgs__srv__GetNetworkStatus_Request__copy(
  const aura_msgs__srv__GetNetworkStatus_Request * input,
  aura_msgs__srv__GetNetworkStatus_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // include_coverage_map
  output->include_coverage_map = input->include_coverage_map;
  // include_link_details
  output->include_link_details = input->include_link_details;
  return true;
}

aura_msgs__srv__GetNetworkStatus_Request *
aura_msgs__srv__GetNetworkStatus_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Request * msg = (aura_msgs__srv__GetNetworkStatus_Request *)allocator.allocate(sizeof(aura_msgs__srv__GetNetworkStatus_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__srv__GetNetworkStatus_Request));
  bool success = aura_msgs__srv__GetNetworkStatus_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__srv__GetNetworkStatus_Request__destroy(aura_msgs__srv__GetNetworkStatus_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__srv__GetNetworkStatus_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__srv__GetNetworkStatus_Request__Sequence__init(aura_msgs__srv__GetNetworkStatus_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Request * data = NULL;

  if (size) {
    data = (aura_msgs__srv__GetNetworkStatus_Request *)allocator.zero_allocate(size, sizeof(aura_msgs__srv__GetNetworkStatus_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__srv__GetNetworkStatus_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__srv__GetNetworkStatus_Request__fini(&data[i - 1]);
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
aura_msgs__srv__GetNetworkStatus_Request__Sequence__fini(aura_msgs__srv__GetNetworkStatus_Request__Sequence * array)
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
      aura_msgs__srv__GetNetworkStatus_Request__fini(&array->data[i]);
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

aura_msgs__srv__GetNetworkStatus_Request__Sequence *
aura_msgs__srv__GetNetworkStatus_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Request__Sequence * array = (aura_msgs__srv__GetNetworkStatus_Request__Sequence *)allocator.allocate(sizeof(aura_msgs__srv__GetNetworkStatus_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__srv__GetNetworkStatus_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__srv__GetNetworkStatus_Request__Sequence__destroy(aura_msgs__srv__GetNetworkStatus_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__srv__GetNetworkStatus_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__srv__GetNetworkStatus_Request__Sequence__are_equal(const aura_msgs__srv__GetNetworkStatus_Request__Sequence * lhs, const aura_msgs__srv__GetNetworkStatus_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__srv__GetNetworkStatus_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__srv__GetNetworkStatus_Request__Sequence__copy(
  const aura_msgs__srv__GetNetworkStatus_Request__Sequence * input,
  aura_msgs__srv__GetNetworkStatus_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__srv__GetNetworkStatus_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__srv__GetNetworkStatus_Request * data =
      (aura_msgs__srv__GetNetworkStatus_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__srv__GetNetworkStatus_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__srv__GetNetworkStatus_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__srv__GetNetworkStatus_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `metrics`
#include "aura_msgs/msg/detail/network_metrics__functions.h"
// Member `issues`
#include "rosidl_runtime_c/string_functions.h"

bool
aura_msgs__srv__GetNetworkStatus_Response__init(aura_msgs__srv__GetNetworkStatus_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // metrics
  if (!aura_msgs__msg__NetworkMetrics__init(&msg->metrics)) {
    aura_msgs__srv__GetNetworkStatus_Response__fini(msg);
    return false;
  }
  // overall_health
  // issues
  if (!rosidl_runtime_c__String__Sequence__init(&msg->issues, 0)) {
    aura_msgs__srv__GetNetworkStatus_Response__fini(msg);
    return false;
  }
  return true;
}

void
aura_msgs__srv__GetNetworkStatus_Response__fini(aura_msgs__srv__GetNetworkStatus_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // metrics
  aura_msgs__msg__NetworkMetrics__fini(&msg->metrics);
  // overall_health
  // issues
  rosidl_runtime_c__String__Sequence__fini(&msg->issues);
}

bool
aura_msgs__srv__GetNetworkStatus_Response__are_equal(const aura_msgs__srv__GetNetworkStatus_Response * lhs, const aura_msgs__srv__GetNetworkStatus_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // metrics
  if (!aura_msgs__msg__NetworkMetrics__are_equal(
      &(lhs->metrics), &(rhs->metrics)))
  {
    return false;
  }
  // overall_health
  if (lhs->overall_health != rhs->overall_health) {
    return false;
  }
  // issues
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->issues), &(rhs->issues)))
  {
    return false;
  }
  return true;
}

bool
aura_msgs__srv__GetNetworkStatus_Response__copy(
  const aura_msgs__srv__GetNetworkStatus_Response * input,
  aura_msgs__srv__GetNetworkStatus_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // metrics
  if (!aura_msgs__msg__NetworkMetrics__copy(
      &(input->metrics), &(output->metrics)))
  {
    return false;
  }
  // overall_health
  output->overall_health = input->overall_health;
  // issues
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->issues), &(output->issues)))
  {
    return false;
  }
  return true;
}

aura_msgs__srv__GetNetworkStatus_Response *
aura_msgs__srv__GetNetworkStatus_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Response * msg = (aura_msgs__srv__GetNetworkStatus_Response *)allocator.allocate(sizeof(aura_msgs__srv__GetNetworkStatus_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__srv__GetNetworkStatus_Response));
  bool success = aura_msgs__srv__GetNetworkStatus_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__srv__GetNetworkStatus_Response__destroy(aura_msgs__srv__GetNetworkStatus_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__srv__GetNetworkStatus_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__srv__GetNetworkStatus_Response__Sequence__init(aura_msgs__srv__GetNetworkStatus_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Response * data = NULL;

  if (size) {
    data = (aura_msgs__srv__GetNetworkStatus_Response *)allocator.zero_allocate(size, sizeof(aura_msgs__srv__GetNetworkStatus_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__srv__GetNetworkStatus_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__srv__GetNetworkStatus_Response__fini(&data[i - 1]);
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
aura_msgs__srv__GetNetworkStatus_Response__Sequence__fini(aura_msgs__srv__GetNetworkStatus_Response__Sequence * array)
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
      aura_msgs__srv__GetNetworkStatus_Response__fini(&array->data[i]);
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

aura_msgs__srv__GetNetworkStatus_Response__Sequence *
aura_msgs__srv__GetNetworkStatus_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__srv__GetNetworkStatus_Response__Sequence * array = (aura_msgs__srv__GetNetworkStatus_Response__Sequence *)allocator.allocate(sizeof(aura_msgs__srv__GetNetworkStatus_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__srv__GetNetworkStatus_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__srv__GetNetworkStatus_Response__Sequence__destroy(aura_msgs__srv__GetNetworkStatus_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__srv__GetNetworkStatus_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__srv__GetNetworkStatus_Response__Sequence__are_equal(const aura_msgs__srv__GetNetworkStatus_Response__Sequence * lhs, const aura_msgs__srv__GetNetworkStatus_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__srv__GetNetworkStatus_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__srv__GetNetworkStatus_Response__Sequence__copy(
  const aura_msgs__srv__GetNetworkStatus_Response__Sequence * input,
  aura_msgs__srv__GetNetworkStatus_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__srv__GetNetworkStatus_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__srv__GetNetworkStatus_Response * data =
      (aura_msgs__srv__GetNetworkStatus_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__srv__GetNetworkStatus_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__srv__GetNetworkStatus_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__srv__GetNetworkStatus_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
