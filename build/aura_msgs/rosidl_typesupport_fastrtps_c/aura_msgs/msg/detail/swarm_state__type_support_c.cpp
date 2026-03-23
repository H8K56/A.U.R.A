// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/swarm_state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "aura_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "aura_msgs/msg/detail/swarm_state__struct.h"
#include "aura_msgs/msg/detail/swarm_state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "aura_msgs/msg/detail/drone_state__functions.h"  // drones
#include "builtin_interfaces/msg/detail/time__functions.h"  // timestamp

// forward declare type support functions
size_t get_serialized_size_aura_msgs__msg__DroneState(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_aura_msgs__msg__DroneState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, aura_msgs, msg, DroneState)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t get_serialized_size_builtin_interfaces__msg__Time(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t max_serialized_size_builtin_interfaces__msg__Time(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time)();


using _SwarmState__ros_msg_type = aura_msgs__msg__SwarmState;

static bool _SwarmState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SwarmState__ros_msg_type * ros_message = static_cast<const _SwarmState__ros_msg_type *>(untyped_ros_message);
  // Field name: timestamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->timestamp, cdr))
    {
      return false;
    }
  }

  // Field name: num_drones_total
  {
    cdr << ros_message->num_drones_total;
  }

  // Field name: num_drones_active
  {
    cdr << ros_message->num_drones_active;
  }

  // Field name: num_hubs
  {
    cdr << ros_message->num_hubs;
  }

  // Field name: num_leaves
  {
    cdr << ros_message->num_leaves;
  }

  // Field name: mission_state
  {
    cdr << ros_message->mission_state;
  }

  // Field name: coverage_percent
  {
    cdr << ros_message->coverage_percent;
  }

  // Field name: coverage_quality
  {
    cdr << ros_message->coverage_quality;
  }

  // Field name: avg_throughput_mbps
  {
    cdr << ros_message->avg_throughput_mbps;
  }

  // Field name: avg_latency_ms
  {
    cdr << ros_message->avg_latency_ms;
  }

  // Field name: packet_loss_percent
  {
    cdr << ros_message->packet_loss_percent;
  }

  // Field name: mesh_connected
  {
    cdr << (ros_message->mesh_connected ? true : false);
  }

  // Field name: backhaul_connected
  {
    cdr << (ros_message->backhaul_connected ? true : false);
  }

  // Field name: drones
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, aura_msgs, msg, DroneState
      )()->data);
    size_t size = ros_message->drones.size;
    auto array_ptr = ros_message->drones.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _SwarmState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SwarmState__ros_msg_type * ros_message = static_cast<_SwarmState__ros_msg_type *>(untyped_ros_message);
  // Field name: timestamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->timestamp))
    {
      return false;
    }
  }

  // Field name: num_drones_total
  {
    cdr >> ros_message->num_drones_total;
  }

  // Field name: num_drones_active
  {
    cdr >> ros_message->num_drones_active;
  }

  // Field name: num_hubs
  {
    cdr >> ros_message->num_hubs;
  }

  // Field name: num_leaves
  {
    cdr >> ros_message->num_leaves;
  }

  // Field name: mission_state
  {
    cdr >> ros_message->mission_state;
  }

  // Field name: coverage_percent
  {
    cdr >> ros_message->coverage_percent;
  }

  // Field name: coverage_quality
  {
    cdr >> ros_message->coverage_quality;
  }

  // Field name: avg_throughput_mbps
  {
    cdr >> ros_message->avg_throughput_mbps;
  }

  // Field name: avg_latency_ms
  {
    cdr >> ros_message->avg_latency_ms;
  }

  // Field name: packet_loss_percent
  {
    cdr >> ros_message->packet_loss_percent;
  }

  // Field name: mesh_connected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->mesh_connected = tmp ? true : false;
  }

  // Field name: backhaul_connected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->backhaul_connected = tmp ? true : false;
  }

  // Field name: drones
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, aura_msgs, msg, DroneState
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->drones.data) {
      aura_msgs__msg__DroneState__Sequence__fini(&ros_message->drones);
    }
    if (!aura_msgs__msg__DroneState__Sequence__init(&ros_message->drones, size)) {
      fprintf(stderr, "failed to create array for field 'drones'");
      return false;
    }
    auto array_ptr = ros_message->drones.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t get_serialized_size_aura_msgs__msg__SwarmState(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SwarmState__ros_msg_type * ros_message = static_cast<const _SwarmState__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name timestamp

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->timestamp), current_alignment);
  // field.name num_drones_total
  {
    size_t item_size = sizeof(ros_message->num_drones_total);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name num_drones_active
  {
    size_t item_size = sizeof(ros_message->num_drones_active);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name num_hubs
  {
    size_t item_size = sizeof(ros_message->num_hubs);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name num_leaves
  {
    size_t item_size = sizeof(ros_message->num_leaves);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mission_state
  {
    size_t item_size = sizeof(ros_message->mission_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coverage_percent
  {
    size_t item_size = sizeof(ros_message->coverage_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coverage_quality
  {
    size_t item_size = sizeof(ros_message->coverage_quality);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name avg_throughput_mbps
  {
    size_t item_size = sizeof(ros_message->avg_throughput_mbps);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name avg_latency_ms
  {
    size_t item_size = sizeof(ros_message->avg_latency_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name packet_loss_percent
  {
    size_t item_size = sizeof(ros_message->packet_loss_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mesh_connected
  {
    size_t item_size = sizeof(ros_message->mesh_connected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name backhaul_connected
  {
    size_t item_size = sizeof(ros_message->backhaul_connected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drones
  {
    size_t array_size = ros_message->drones.size;
    auto array_ptr = ros_message->drones.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_aura_msgs__msg__DroneState(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SwarmState__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_aura_msgs__msg__SwarmState(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t max_serialized_size_aura_msgs__msg__SwarmState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: timestamp
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_builtin_interfaces__msg__Time(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: num_drones_total
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: num_drones_active
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: num_hubs
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: num_leaves
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: mission_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: coverage_percent
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: coverage_quality
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: avg_throughput_mbps
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: avg_latency_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: packet_loss_percent
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mesh_connected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: backhaul_connected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drones
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_aura_msgs__msg__DroneState(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = aura_msgs__msg__SwarmState;
    is_plain =
      (
      offsetof(DataType, drones) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SwarmState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_aura_msgs__msg__SwarmState(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SwarmState = {
  "aura_msgs::msg",
  "SwarmState",
  _SwarmState__cdr_serialize,
  _SwarmState__cdr_deserialize,
  _SwarmState__get_serialized_size,
  _SwarmState__max_serialized_size
};

static rosidl_message_type_support_t _SwarmState__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SwarmState,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, aura_msgs, msg, SwarmState)() {
  return &_SwarmState__type_support;
}

#if defined(__cplusplus)
}
#endif
