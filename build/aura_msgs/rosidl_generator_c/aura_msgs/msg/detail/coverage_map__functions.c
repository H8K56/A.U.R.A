// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/coverage_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `origin`
// Member `priority_zone_centers`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `is_covered`
// Member `is_target`
// Member `demand_level`
// Member `coverage_quality`
// Member `priority_zone_radii`
// Member `priority_zone_weights`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
aura_msgs__msg__CoverageMap__init(aura_msgs__msg__CoverageMap * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // grid_size_x
  // grid_size_y
  // cell_size_meters
  // origin
  if (!geometry_msgs__msg__Point__init(&msg->origin)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // is_covered
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->is_covered, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // is_target
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->is_target, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // demand_level
  if (!rosidl_runtime_c__float__Sequence__init(&msg->demand_level, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // coverage_quality
  if (!rosidl_runtime_c__float__Sequence__init(&msg->coverage_quality, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // priority_zone_centers
  if (!geometry_msgs__msg__Point__Sequence__init(&msg->priority_zone_centers, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // priority_zone_radii
  if (!rosidl_runtime_c__float__Sequence__init(&msg->priority_zone_radii, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  // priority_zone_weights
  if (!rosidl_runtime_c__float__Sequence__init(&msg->priority_zone_weights, 0)) {
    aura_msgs__msg__CoverageMap__fini(msg);
    return false;
  }
  return true;
}

void
aura_msgs__msg__CoverageMap__fini(aura_msgs__msg__CoverageMap * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // grid_size_x
  // grid_size_y
  // cell_size_meters
  // origin
  geometry_msgs__msg__Point__fini(&msg->origin);
  // is_covered
  rosidl_runtime_c__boolean__Sequence__fini(&msg->is_covered);
  // is_target
  rosidl_runtime_c__boolean__Sequence__fini(&msg->is_target);
  // demand_level
  rosidl_runtime_c__float__Sequence__fini(&msg->demand_level);
  // coverage_quality
  rosidl_runtime_c__float__Sequence__fini(&msg->coverage_quality);
  // priority_zone_centers
  geometry_msgs__msg__Point__Sequence__fini(&msg->priority_zone_centers);
  // priority_zone_radii
  rosidl_runtime_c__float__Sequence__fini(&msg->priority_zone_radii);
  // priority_zone_weights
  rosidl_runtime_c__float__Sequence__fini(&msg->priority_zone_weights);
}

bool
aura_msgs__msg__CoverageMap__are_equal(const aura_msgs__msg__CoverageMap * lhs, const aura_msgs__msg__CoverageMap * rhs)
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
  // is_covered
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->is_covered), &(rhs->is_covered)))
  {
    return false;
  }
  // is_target
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->is_target), &(rhs->is_target)))
  {
    return false;
  }
  // demand_level
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->demand_level), &(rhs->demand_level)))
  {
    return false;
  }
  // coverage_quality
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->coverage_quality), &(rhs->coverage_quality)))
  {
    return false;
  }
  // priority_zone_centers
  if (!geometry_msgs__msg__Point__Sequence__are_equal(
      &(lhs->priority_zone_centers), &(rhs->priority_zone_centers)))
  {
    return false;
  }
  // priority_zone_radii
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->priority_zone_radii), &(rhs->priority_zone_radii)))
  {
    return false;
  }
  // priority_zone_weights
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->priority_zone_weights), &(rhs->priority_zone_weights)))
  {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__CoverageMap__copy(
  const aura_msgs__msg__CoverageMap * input,
  aura_msgs__msg__CoverageMap * output)
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
  // is_covered
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->is_covered), &(output->is_covered)))
  {
    return false;
  }
  // is_target
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->is_target), &(output->is_target)))
  {
    return false;
  }
  // demand_level
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->demand_level), &(output->demand_level)))
  {
    return false;
  }
  // coverage_quality
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->coverage_quality), &(output->coverage_quality)))
  {
    return false;
  }
  // priority_zone_centers
  if (!geometry_msgs__msg__Point__Sequence__copy(
      &(input->priority_zone_centers), &(output->priority_zone_centers)))
  {
    return false;
  }
  // priority_zone_radii
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->priority_zone_radii), &(output->priority_zone_radii)))
  {
    return false;
  }
  // priority_zone_weights
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->priority_zone_weights), &(output->priority_zone_weights)))
  {
    return false;
  }
  return true;
}

aura_msgs__msg__CoverageMap *
aura_msgs__msg__CoverageMap__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageMap * msg = (aura_msgs__msg__CoverageMap *)allocator.allocate(sizeof(aura_msgs__msg__CoverageMap), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__CoverageMap));
  bool success = aura_msgs__msg__CoverageMap__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__CoverageMap__destroy(aura_msgs__msg__CoverageMap * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__CoverageMap__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__CoverageMap__Sequence__init(aura_msgs__msg__CoverageMap__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageMap * data = NULL;

  if (size) {
    data = (aura_msgs__msg__CoverageMap *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__CoverageMap), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__CoverageMap__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__CoverageMap__fini(&data[i - 1]);
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
aura_msgs__msg__CoverageMap__Sequence__fini(aura_msgs__msg__CoverageMap__Sequence * array)
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
      aura_msgs__msg__CoverageMap__fini(&array->data[i]);
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

aura_msgs__msg__CoverageMap__Sequence *
aura_msgs__msg__CoverageMap__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__CoverageMap__Sequence * array = (aura_msgs__msg__CoverageMap__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__CoverageMap__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__CoverageMap__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__CoverageMap__Sequence__destroy(aura_msgs__msg__CoverageMap__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__CoverageMap__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__CoverageMap__Sequence__are_equal(const aura_msgs__msg__CoverageMap__Sequence * lhs, const aura_msgs__msg__CoverageMap__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__CoverageMap__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__CoverageMap__Sequence__copy(
  const aura_msgs__msg__CoverageMap__Sequence * input,
  aura_msgs__msg__CoverageMap__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__CoverageMap);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__CoverageMap * data =
      (aura_msgs__msg__CoverageMap *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__CoverageMap__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__CoverageMap__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__CoverageMap__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
