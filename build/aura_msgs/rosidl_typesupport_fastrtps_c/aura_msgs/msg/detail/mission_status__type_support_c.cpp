// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/mission_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "aura_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "aura_msgs/msg/detail/mission_status__struct.h"
#include "aura_msgs/msg/detail/mission_status__functions.h"
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

#include "builtin_interfaces/msg/detail/time__functions.h"  // timestamp
#include "rosidl_runtime_c/primitives_sequence.h"  // alert_severities
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // alert_severities
#include "rosidl_runtime_c/string.h"  // active_alerts, mission_id
#include "rosidl_runtime_c/string_functions.h"  // active_alerts, mission_id

// forward declare type support functions
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


using _MissionStatus__ros_msg_type = aura_msgs__msg__MissionStatus;

static bool _MissionStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _MissionStatus__ros_msg_type * ros_message = static_cast<const _MissionStatus__ros_msg_type *>(untyped_ros_message);
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

  // Field name: mission_id
  {
    const rosidl_runtime_c__String * str = &ros_message->mission_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: phase
  {
    cdr << ros_message->phase;
  }

  // Field name: progress_percent
  {
    cdr << ros_message->progress_percent;
  }

  // Field name: elapsed_time_sec
  {
    cdr << ros_message->elapsed_time_sec;
  }

  // Field name: estimated_remaining_sec
  {
    cdr << ros_message->estimated_remaining_sec;
  }

  // Field name: coverage_achieved
  {
    cdr << ros_message->coverage_achieved;
  }

  // Field name: network_quality
  {
    cdr << ros_message->network_quality;
  }

  // Field name: connections_established
  {
    cdr << ros_message->connections_established;
  }

  // Field name: data_transferred_mb
  {
    cdr << ros_message->data_transferred_mb;
  }

  // Field name: active_alerts
  {
    size_t size = ros_message->active_alerts.size;
    auto array_ptr = ros_message->active_alerts.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: alert_severities
  {
    size_t size = ros_message->alert_severities.size;
    auto array_ptr = ros_message->alert_severities.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: drones_operational
  {
    cdr << ros_message->drones_operational;
  }

  // Field name: drones_degraded
  {
    cdr << ros_message->drones_degraded;
  }

  // Field name: drones_failed
  {
    cdr << ros_message->drones_failed;
  }

  return true;
}

static bool _MissionStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _MissionStatus__ros_msg_type * ros_message = static_cast<_MissionStatus__ros_msg_type *>(untyped_ros_message);
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

  // Field name: mission_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->mission_id.data) {
      rosidl_runtime_c__String__init(&ros_message->mission_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->mission_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'mission_id'\n");
      return false;
    }
  }

  // Field name: phase
  {
    cdr >> ros_message->phase;
  }

  // Field name: progress_percent
  {
    cdr >> ros_message->progress_percent;
  }

  // Field name: elapsed_time_sec
  {
    cdr >> ros_message->elapsed_time_sec;
  }

  // Field name: estimated_remaining_sec
  {
    cdr >> ros_message->estimated_remaining_sec;
  }

  // Field name: coverage_achieved
  {
    cdr >> ros_message->coverage_achieved;
  }

  // Field name: network_quality
  {
    cdr >> ros_message->network_quality;
  }

  // Field name: connections_established
  {
    cdr >> ros_message->connections_established;
  }

  // Field name: data_transferred_mb
  {
    cdr >> ros_message->data_transferred_mb;
  }

  // Field name: active_alerts
  {
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

    if (ros_message->active_alerts.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->active_alerts);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->active_alerts, size)) {
      fprintf(stderr, "failed to create array for field 'active_alerts'");
      return false;
    }
    auto array_ptr = ros_message->active_alerts.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'active_alerts'\n");
        return false;
      }
    }
  }

  // Field name: alert_severities
  {
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

    if (ros_message->alert_severities.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->alert_severities);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->alert_severities, size)) {
      fprintf(stderr, "failed to create array for field 'alert_severities'");
      return false;
    }
    auto array_ptr = ros_message->alert_severities.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: drones_operational
  {
    cdr >> ros_message->drones_operational;
  }

  // Field name: drones_degraded
  {
    cdr >> ros_message->drones_degraded;
  }

  // Field name: drones_failed
  {
    cdr >> ros_message->drones_failed;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t get_serialized_size_aura_msgs__msg__MissionStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MissionStatus__ros_msg_type * ros_message = static_cast<const _MissionStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name timestamp

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->timestamp), current_alignment);
  // field.name mission_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->mission_id.size + 1);
  // field.name phase
  {
    size_t item_size = sizeof(ros_message->phase);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name progress_percent
  {
    size_t item_size = sizeof(ros_message->progress_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name elapsed_time_sec
  {
    size_t item_size = sizeof(ros_message->elapsed_time_sec);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name estimated_remaining_sec
  {
    size_t item_size = sizeof(ros_message->estimated_remaining_sec);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coverage_achieved
  {
    size_t item_size = sizeof(ros_message->coverage_achieved);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name network_quality
  {
    size_t item_size = sizeof(ros_message->network_quality);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name connections_established
  {
    size_t item_size = sizeof(ros_message->connections_established);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name data_transferred_mb
  {
    size_t item_size = sizeof(ros_message->data_transferred_mb);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name active_alerts
  {
    size_t array_size = ros_message->active_alerts.size;
    auto array_ptr = ros_message->active_alerts.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name alert_severities
  {
    size_t array_size = ros_message->alert_severities.size;
    auto array_ptr = ros_message->alert_severities.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drones_operational
  {
    size_t item_size = sizeof(ros_message->drones_operational);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drones_degraded
  {
    size_t item_size = sizeof(ros_message->drones_degraded);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drones_failed
  {
    size_t item_size = sizeof(ros_message->drones_failed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _MissionStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_aura_msgs__msg__MissionStatus(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t max_serialized_size_aura_msgs__msg__MissionStatus(
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
  // member: mission_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: phase
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: progress_percent
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: elapsed_time_sec
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: estimated_remaining_sec
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: coverage_achieved
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: network_quality
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: connections_established
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: data_transferred_mb
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: active_alerts
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: alert_severities
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drones_operational
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drones_degraded
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drones_failed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = aura_msgs__msg__MissionStatus;
    is_plain =
      (
      offsetof(DataType, drones_failed) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _MissionStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_aura_msgs__msg__MissionStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_MissionStatus = {
  "aura_msgs::msg",
  "MissionStatus",
  _MissionStatus__cdr_serialize,
  _MissionStatus__cdr_deserialize,
  _MissionStatus__get_serialized_size,
  _MissionStatus__max_serialized_size
};

static rosidl_message_type_support_t _MissionStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MissionStatus,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, aura_msgs, msg, MissionStatus)() {
  return &_MissionStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
