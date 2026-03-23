// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aura_msgs/msg/detail/coverage_map__rosidl_typesupport_introspection_c.h"
#include "aura_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aura_msgs/msg/detail/coverage_map__functions.h"
#include "aura_msgs/msg/detail/coverage_map__struct.h"


// Include directives for member types
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `origin`
// Member `priority_zone_centers`
#include "geometry_msgs/msg/point.h"
// Member `origin`
// Member `priority_zone_centers`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `is_covered`
// Member `is_target`
// Member `demand_level`
// Member `coverage_quality`
// Member `priority_zone_radii`
// Member `priority_zone_weights`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aura_msgs__msg__CoverageMap__init(message_memory);
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_fini_function(void * message_memory)
{
  aura_msgs__msg__CoverageMap__fini(message_memory);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__is_covered(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_covered(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_covered(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__is_covered(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_covered(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__is_covered(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_covered(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__is_covered(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__is_target(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_target(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_target(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__is_target(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_target(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__is_target(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_target(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__is_target(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__demand_level(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__demand_level(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__demand_level(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__demand_level(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__demand_level(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__demand_level(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__demand_level(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__demand_level(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__coverage_quality(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__coverage_quality(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__coverage_quality(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__coverage_quality(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__coverage_quality(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__coverage_quality(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__coverage_quality(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__coverage_quality(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_centers(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_centers(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_centers(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_centers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_centers(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_centers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_centers(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_centers(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_radii(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_radii(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_radii(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_radii(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_radii(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_radii(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_radii(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_radii(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_weights(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_weights(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_weights(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_weights(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_weights(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_weights(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_weights(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_weights(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_member_array[12] = {
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grid_size_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, grid_size_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grid_size_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, grid_size_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cell_size_meters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, cell_size_meters),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "origin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, origin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_covered",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, is_covered),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__is_covered,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_covered,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_covered,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__is_covered,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__is_covered,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__is_covered  // resize(index) function pointer
  },
  {
    "is_target",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, is_target),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__is_target,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__is_target,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__is_target,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__is_target,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__is_target,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__is_target  // resize(index) function pointer
  },
  {
    "demand_level",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, demand_level),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__demand_level,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__demand_level,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__demand_level,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__demand_level,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__demand_level,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__demand_level  // resize(index) function pointer
  },
  {
    "coverage_quality",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, coverage_quality),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__coverage_quality,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__coverage_quality,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__coverage_quality,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__coverage_quality,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__coverage_quality,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__coverage_quality  // resize(index) function pointer
  },
  {
    "priority_zone_centers",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, priority_zone_centers),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_centers,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_centers,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_centers,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_centers,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_centers,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_centers  // resize(index) function pointer
  },
  {
    "priority_zone_radii",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, priority_zone_radii),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_radii,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_radii,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_radii,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_radii,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_radii,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_radii  // resize(index) function pointer
  },
  {
    "priority_zone_weights",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aura_msgs__msg__CoverageMap, priority_zone_weights),  // bytes offset in struct
    NULL,  // default value
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__size_function__CoverageMap__priority_zone_weights,  // size() function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_const_function__CoverageMap__priority_zone_weights,  // get_const(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__get_function__CoverageMap__priority_zone_weights,  // get(index) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__fetch_function__CoverageMap__priority_zone_weights,  // fetch(index, &value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__assign_function__CoverageMap__priority_zone_weights,  // assign(index, value) function pointer
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__resize_function__CoverageMap__priority_zone_weights  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_members = {
  "aura_msgs__msg",  // message namespace
  "CoverageMap",  // message name
  12,  // number of fields
  sizeof(aura_msgs__msg__CoverageMap),
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_member_array,  // message members
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_init_function,  // function to initialize message memory (memory has to be allocated)
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_type_support_handle = {
  0,
  &aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aura_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aura_msgs, msg, CoverageMap)() {
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_member_array[9].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_type_support_handle.typesupport_identifier) {
    aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aura_msgs__msg__CoverageMap__rosidl_typesupport_introspection_c__CoverageMap_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
