// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__FUNCTIONS_H_
#define AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "aura_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "aura_msgs/msg/detail/trajectory_broadcast__struct.h"

/// Initialize msg/TrajectoryBroadcast message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * aura_msgs__msg__TrajectoryBroadcast
 * )) before or use
 * aura_msgs__msg__TrajectoryBroadcast__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__init(aura_msgs__msg__TrajectoryBroadcast * msg);

/// Finalize msg/TrajectoryBroadcast message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
void
aura_msgs__msg__TrajectoryBroadcast__fini(aura_msgs__msg__TrajectoryBroadcast * msg);

/// Create msg/TrajectoryBroadcast message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * aura_msgs__msg__TrajectoryBroadcast__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
aura_msgs__msg__TrajectoryBroadcast *
aura_msgs__msg__TrajectoryBroadcast__create();

/// Destroy msg/TrajectoryBroadcast message.
/**
 * It calls
 * aura_msgs__msg__TrajectoryBroadcast__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
void
aura_msgs__msg__TrajectoryBroadcast__destroy(aura_msgs__msg__TrajectoryBroadcast * msg);

/// Check for msg/TrajectoryBroadcast message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__are_equal(const aura_msgs__msg__TrajectoryBroadcast * lhs, const aura_msgs__msg__TrajectoryBroadcast * rhs);

/// Copy a msg/TrajectoryBroadcast message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__copy(
  const aura_msgs__msg__TrajectoryBroadcast * input,
  aura_msgs__msg__TrajectoryBroadcast * output);

/// Initialize array of msg/TrajectoryBroadcast messages.
/**
 * It allocates the memory for the number of elements and calls
 * aura_msgs__msg__TrajectoryBroadcast__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__init(aura_msgs__msg__TrajectoryBroadcast__Sequence * array, size_t size);

/// Finalize array of msg/TrajectoryBroadcast messages.
/**
 * It calls
 * aura_msgs__msg__TrajectoryBroadcast__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
void
aura_msgs__msg__TrajectoryBroadcast__Sequence__fini(aura_msgs__msg__TrajectoryBroadcast__Sequence * array);

/// Create array of msg/TrajectoryBroadcast messages.
/**
 * It allocates the memory for the array and calls
 * aura_msgs__msg__TrajectoryBroadcast__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
aura_msgs__msg__TrajectoryBroadcast__Sequence *
aura_msgs__msg__TrajectoryBroadcast__Sequence__create(size_t size);

/// Destroy array of msg/TrajectoryBroadcast messages.
/**
 * It calls
 * aura_msgs__msg__TrajectoryBroadcast__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
void
aura_msgs__msg__TrajectoryBroadcast__Sequence__destroy(aura_msgs__msg__TrajectoryBroadcast__Sequence * array);

/// Check for msg/TrajectoryBroadcast message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__are_equal(const aura_msgs__msg__TrajectoryBroadcast__Sequence * lhs, const aura_msgs__msg__TrajectoryBroadcast__Sequence * rhs);

/// Copy an array of msg/TrajectoryBroadcast messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aura_msgs
bool
aura_msgs__msg__TrajectoryBroadcast__Sequence__copy(
  const aura_msgs__msg__TrajectoryBroadcast__Sequence * input,
  aura_msgs__msg__TrajectoryBroadcast__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__FUNCTIONS_H_
