// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/weather_zone__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `timestamp`
// Member `start_time`
// Member `end_time`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `center`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
aura_msgs__msg__WeatherZone__init(aura_msgs__msg__WeatherZone * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    aura_msgs__msg__WeatherZone__fini(msg);
    return false;
  }
  // zone_id
  // center
  if (!geometry_msgs__msg__Point__init(&msg->center)) {
    aura_msgs__msg__WeatherZone__fini(msg);
    return false;
  }
  // radius_meters
  // min_altitude
  // max_altitude
  // weather_type
  // severity
  // wind_speed_ms
  // wind_direction_rad
  // signal_attenuation_db
  // no_fly
  // start_time
  if (!builtin_interfaces__msg__Time__init(&msg->start_time)) {
    aura_msgs__msg__WeatherZone__fini(msg);
    return false;
  }
  // end_time
  if (!builtin_interfaces__msg__Time__init(&msg->end_time)) {
    aura_msgs__msg__WeatherZone__fini(msg);
    return false;
  }
  // is_active
  return true;
}

void
aura_msgs__msg__WeatherZone__fini(aura_msgs__msg__WeatherZone * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // zone_id
  // center
  geometry_msgs__msg__Point__fini(&msg->center);
  // radius_meters
  // min_altitude
  // max_altitude
  // weather_type
  // severity
  // wind_speed_ms
  // wind_direction_rad
  // signal_attenuation_db
  // no_fly
  // start_time
  builtin_interfaces__msg__Time__fini(&msg->start_time);
  // end_time
  builtin_interfaces__msg__Time__fini(&msg->end_time);
  // is_active
}

bool
aura_msgs__msg__WeatherZone__are_equal(const aura_msgs__msg__WeatherZone * lhs, const aura_msgs__msg__WeatherZone * rhs)
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
  // zone_id
  if (lhs->zone_id != rhs->zone_id) {
    return false;
  }
  // center
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->center), &(rhs->center)))
  {
    return false;
  }
  // radius_meters
  if (lhs->radius_meters != rhs->radius_meters) {
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
  // weather_type
  if (lhs->weather_type != rhs->weather_type) {
    return false;
  }
  // severity
  if (lhs->severity != rhs->severity) {
    return false;
  }
  // wind_speed_ms
  if (lhs->wind_speed_ms != rhs->wind_speed_ms) {
    return false;
  }
  // wind_direction_rad
  if (lhs->wind_direction_rad != rhs->wind_direction_rad) {
    return false;
  }
  // signal_attenuation_db
  if (lhs->signal_attenuation_db != rhs->signal_attenuation_db) {
    return false;
  }
  // no_fly
  if (lhs->no_fly != rhs->no_fly) {
    return false;
  }
  // start_time
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->start_time), &(rhs->start_time)))
  {
    return false;
  }
  // end_time
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->end_time), &(rhs->end_time)))
  {
    return false;
  }
  // is_active
  if (lhs->is_active != rhs->is_active) {
    return false;
  }
  return true;
}

bool
aura_msgs__msg__WeatherZone__copy(
  const aura_msgs__msg__WeatherZone * input,
  aura_msgs__msg__WeatherZone * output)
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
  // zone_id
  output->zone_id = input->zone_id;
  // center
  if (!geometry_msgs__msg__Point__copy(
      &(input->center), &(output->center)))
  {
    return false;
  }
  // radius_meters
  output->radius_meters = input->radius_meters;
  // min_altitude
  output->min_altitude = input->min_altitude;
  // max_altitude
  output->max_altitude = input->max_altitude;
  // weather_type
  output->weather_type = input->weather_type;
  // severity
  output->severity = input->severity;
  // wind_speed_ms
  output->wind_speed_ms = input->wind_speed_ms;
  // wind_direction_rad
  output->wind_direction_rad = input->wind_direction_rad;
  // signal_attenuation_db
  output->signal_attenuation_db = input->signal_attenuation_db;
  // no_fly
  output->no_fly = input->no_fly;
  // start_time
  if (!builtin_interfaces__msg__Time__copy(
      &(input->start_time), &(output->start_time)))
  {
    return false;
  }
  // end_time
  if (!builtin_interfaces__msg__Time__copy(
      &(input->end_time), &(output->end_time)))
  {
    return false;
  }
  // is_active
  output->is_active = input->is_active;
  return true;
}

aura_msgs__msg__WeatherZone *
aura_msgs__msg__WeatherZone__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__WeatherZone * msg = (aura_msgs__msg__WeatherZone *)allocator.allocate(sizeof(aura_msgs__msg__WeatherZone), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aura_msgs__msg__WeatherZone));
  bool success = aura_msgs__msg__WeatherZone__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aura_msgs__msg__WeatherZone__destroy(aura_msgs__msg__WeatherZone * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aura_msgs__msg__WeatherZone__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aura_msgs__msg__WeatherZone__Sequence__init(aura_msgs__msg__WeatherZone__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__WeatherZone * data = NULL;

  if (size) {
    data = (aura_msgs__msg__WeatherZone *)allocator.zero_allocate(size, sizeof(aura_msgs__msg__WeatherZone), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aura_msgs__msg__WeatherZone__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aura_msgs__msg__WeatherZone__fini(&data[i - 1]);
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
aura_msgs__msg__WeatherZone__Sequence__fini(aura_msgs__msg__WeatherZone__Sequence * array)
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
      aura_msgs__msg__WeatherZone__fini(&array->data[i]);
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

aura_msgs__msg__WeatherZone__Sequence *
aura_msgs__msg__WeatherZone__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aura_msgs__msg__WeatherZone__Sequence * array = (aura_msgs__msg__WeatherZone__Sequence *)allocator.allocate(sizeof(aura_msgs__msg__WeatherZone__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aura_msgs__msg__WeatherZone__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aura_msgs__msg__WeatherZone__Sequence__destroy(aura_msgs__msg__WeatherZone__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aura_msgs__msg__WeatherZone__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aura_msgs__msg__WeatherZone__Sequence__are_equal(const aura_msgs__msg__WeatherZone__Sequence * lhs, const aura_msgs__msg__WeatherZone__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aura_msgs__msg__WeatherZone__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aura_msgs__msg__WeatherZone__Sequence__copy(
  const aura_msgs__msg__WeatherZone__Sequence * input,
  aura_msgs__msg__WeatherZone__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aura_msgs__msg__WeatherZone);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aura_msgs__msg__WeatherZone * data =
      (aura_msgs__msg__WeatherZone *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aura_msgs__msg__WeatherZone__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aura_msgs__msg__WeatherZone__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aura_msgs__msg__WeatherZone__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
