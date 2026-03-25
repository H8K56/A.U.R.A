// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice
#include "aura_msgs/msg/detail/network_metrics__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "aura_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "aura_msgs/msg/detail/network_metrics__struct.h"
#include "aura_msgs/msg/detail/network_metrics__functions.h"
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
#include "geometry_msgs/msg/detail/point__functions.h"  // origin
#include "rosidl_runtime_c/primitives_sequence.h"  // coverage_mask, latency_ms, link_from_drone, link_latency_ms, link_rssi_dbm, link_throughput_mbps, link_to_drone, signal_strength_dbm, throughput_mbps
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // coverage_mask, latency_ms, link_from_drone, link_latency_ms, link_rssi_dbm, link_throughput_mbps, link_to_drone, signal_strength_dbm, throughput_mbps
#include "std_msgs/msg/detail/header__functions.h"  // header

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
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t get_serialized_size_geometry_msgs__msg__Point(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t max_serialized_size_geometry_msgs__msg__Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_aura_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _NetworkMetrics__ros_msg_type = aura_msgs__msg__NetworkMetrics;

static bool _NetworkMetrics__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _NetworkMetrics__ros_msg_type * ros_message = static_cast<const _NetworkMetrics__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

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

  // Field name: grid_size_x
  {
    cdr << ros_message->grid_size_x;
  }

  // Field name: grid_size_y
  {
    cdr << ros_message->grid_size_y;
  }

  // Field name: cell_size_meters
  {
    cdr << ros_message->cell_size_meters;
  }

  // Field name: origin
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->origin, cdr))
    {
      return false;
    }
  }

  // Field name: signal_strength_dbm
  {
    size_t size = ros_message->signal_strength_dbm.size;
    auto array_ptr = ros_message->signal_strength_dbm.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: throughput_mbps
  {
    size_t size = ros_message->throughput_mbps.size;
    auto array_ptr = ros_message->throughput_mbps.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: latency_ms
  {
    size_t size = ros_message->latency_ms.size;
    auto array_ptr = ros_message->latency_ms.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: coverage_mask
  {
    size_t size = ros_message->coverage_mask.size;
    auto array_ptr = ros_message->coverage_mask.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: total_coverage_percent
  {
    cdr << ros_message->total_coverage_percent;
  }

  // Field name: avg_signal_strength_dbm
  {
    cdr << ros_message->avg_signal_strength_dbm;
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

  // Field name: link_from_drone
  {
    size_t size = ros_message->link_from_drone.size;
    auto array_ptr = ros_message->link_from_drone.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: link_to_drone
  {
    size_t size = ros_message->link_to_drone.size;
    auto array_ptr = ros_message->link_to_drone.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: link_throughput_mbps
  {
    size_t size = ros_message->link_throughput_mbps.size;
    auto array_ptr = ros_message->link_throughput_mbps.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: link_latency_ms
  {
    size_t size = ros_message->link_latency_ms.size;
    auto array_ptr = ros_message->link_latency_ms.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: link_rssi_dbm
  {
    size_t size = ros_message->link_rssi_dbm.size;
    auto array_ptr = ros_message->link_rssi_dbm.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: backhaul_active
  {
    cdr << (ros_message->backhaul_active ? true : false);
  }

  // Field name: backhaul_throughput_mbps
  {
    cdr << ros_message->backhaul_throughput_mbps;
  }

  // Field name: backhaul_latency_ms
  {
    cdr << ros_message->backhaul_latency_ms;
  }

  return true;
}

static bool _NetworkMetrics__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _NetworkMetrics__ros_msg_type * ros_message = static_cast<_NetworkMetrics__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

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

  // Field name: grid_size_x
  {
    cdr >> ros_message->grid_size_x;
  }

  // Field name: grid_size_y
  {
    cdr >> ros_message->grid_size_y;
  }

  // Field name: cell_size_meters
  {
    cdr >> ros_message->cell_size_meters;
  }

  // Field name: origin
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Point
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->origin))
    {
      return false;
    }
  }

  // Field name: signal_strength_dbm
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

    if (ros_message->signal_strength_dbm.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->signal_strength_dbm);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->signal_strength_dbm, size)) {
      fprintf(stderr, "failed to create array for field 'signal_strength_dbm'");
      return false;
    }
    auto array_ptr = ros_message->signal_strength_dbm.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: throughput_mbps
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

    if (ros_message->throughput_mbps.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->throughput_mbps);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->throughput_mbps, size)) {
      fprintf(stderr, "failed to create array for field 'throughput_mbps'");
      return false;
    }
    auto array_ptr = ros_message->throughput_mbps.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: latency_ms
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

    if (ros_message->latency_ms.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->latency_ms);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->latency_ms, size)) {
      fprintf(stderr, "failed to create array for field 'latency_ms'");
      return false;
    }
    auto array_ptr = ros_message->latency_ms.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: coverage_mask
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

    if (ros_message->coverage_mask.data) {
      rosidl_runtime_c__boolean__Sequence__fini(&ros_message->coverage_mask);
    }
    if (!rosidl_runtime_c__boolean__Sequence__init(&ros_message->coverage_mask, size)) {
      fprintf(stderr, "failed to create array for field 'coverage_mask'");
      return false;
    }
    auto array_ptr = ros_message->coverage_mask.data;
    for (size_t i = 0; i < size; ++i) {
      uint8_t tmp;
      cdr >> tmp;
      array_ptr[i] = tmp ? true : false;
    }
  }

  // Field name: total_coverage_percent
  {
    cdr >> ros_message->total_coverage_percent;
  }

  // Field name: avg_signal_strength_dbm
  {
    cdr >> ros_message->avg_signal_strength_dbm;
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

  // Field name: link_from_drone
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

    if (ros_message->link_from_drone.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->link_from_drone);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->link_from_drone, size)) {
      fprintf(stderr, "failed to create array for field 'link_from_drone'");
      return false;
    }
    auto array_ptr = ros_message->link_from_drone.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: link_to_drone
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

    if (ros_message->link_to_drone.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->link_to_drone);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->link_to_drone, size)) {
      fprintf(stderr, "failed to create array for field 'link_to_drone'");
      return false;
    }
    auto array_ptr = ros_message->link_to_drone.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: link_throughput_mbps
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

    if (ros_message->link_throughput_mbps.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->link_throughput_mbps);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->link_throughput_mbps, size)) {
      fprintf(stderr, "failed to create array for field 'link_throughput_mbps'");
      return false;
    }
    auto array_ptr = ros_message->link_throughput_mbps.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: link_latency_ms
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

    if (ros_message->link_latency_ms.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->link_latency_ms);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->link_latency_ms, size)) {
      fprintf(stderr, "failed to create array for field 'link_latency_ms'");
      return false;
    }
    auto array_ptr = ros_message->link_latency_ms.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: link_rssi_dbm
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

    if (ros_message->link_rssi_dbm.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->link_rssi_dbm);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->link_rssi_dbm, size)) {
      fprintf(stderr, "failed to create array for field 'link_rssi_dbm'");
      return false;
    }
    auto array_ptr = ros_message->link_rssi_dbm.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: backhaul_active
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->backhaul_active = tmp ? true : false;
  }

  // Field name: backhaul_throughput_mbps
  {
    cdr >> ros_message->backhaul_throughput_mbps;
  }

  // Field name: backhaul_latency_ms
  {
    cdr >> ros_message->backhaul_latency_ms;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t get_serialized_size_aura_msgs__msg__NetworkMetrics(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _NetworkMetrics__ros_msg_type * ros_message = static_cast<const _NetworkMetrics__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name timestamp

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->timestamp), current_alignment);
  // field.name grid_size_x
  {
    size_t item_size = sizeof(ros_message->grid_size_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name grid_size_y
  {
    size_t item_size = sizeof(ros_message->grid_size_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name cell_size_meters
  {
    size_t item_size = sizeof(ros_message->cell_size_meters);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name origin

  current_alignment += get_serialized_size_geometry_msgs__msg__Point(
    &(ros_message->origin), current_alignment);
  // field.name signal_strength_dbm
  {
    size_t array_size = ros_message->signal_strength_dbm.size;
    auto array_ptr = ros_message->signal_strength_dbm.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name throughput_mbps
  {
    size_t array_size = ros_message->throughput_mbps.size;
    auto array_ptr = ros_message->throughput_mbps.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name latency_ms
  {
    size_t array_size = ros_message->latency_ms.size;
    auto array_ptr = ros_message->latency_ms.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coverage_mask
  {
    size_t array_size = ros_message->coverage_mask.size;
    auto array_ptr = ros_message->coverage_mask.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name total_coverage_percent
  {
    size_t item_size = sizeof(ros_message->total_coverage_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name avg_signal_strength_dbm
  {
    size_t item_size = sizeof(ros_message->avg_signal_strength_dbm);
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
  // field.name link_from_drone
  {
    size_t array_size = ros_message->link_from_drone.size;
    auto array_ptr = ros_message->link_from_drone.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name link_to_drone
  {
    size_t array_size = ros_message->link_to_drone.size;
    auto array_ptr = ros_message->link_to_drone.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name link_throughput_mbps
  {
    size_t array_size = ros_message->link_throughput_mbps.size;
    auto array_ptr = ros_message->link_throughput_mbps.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name link_latency_ms
  {
    size_t array_size = ros_message->link_latency_ms.size;
    auto array_ptr = ros_message->link_latency_ms.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name link_rssi_dbm
  {
    size_t array_size = ros_message->link_rssi_dbm.size;
    auto array_ptr = ros_message->link_rssi_dbm.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name backhaul_active
  {
    size_t item_size = sizeof(ros_message->backhaul_active);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name backhaul_throughput_mbps
  {
    size_t item_size = sizeof(ros_message->backhaul_throughput_mbps);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name backhaul_latency_ms
  {
    size_t item_size = sizeof(ros_message->backhaul_latency_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _NetworkMetrics__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_aura_msgs__msg__NetworkMetrics(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_aura_msgs
size_t max_serialized_size_aura_msgs__msg__NetworkMetrics(
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

  // member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
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
  // member: grid_size_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: grid_size_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: cell_size_meters
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: origin
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_geometry_msgs__msg__Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: signal_strength_dbm
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: throughput_mbps
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: latency_ms
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: coverage_mask
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: total_coverage_percent
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: avg_signal_strength_dbm
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
  // member: link_from_drone
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: link_to_drone
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: link_throughput_mbps
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: link_latency_ms
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: link_rssi_dbm
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: backhaul_active
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: backhaul_throughput_mbps
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: backhaul_latency_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = aura_msgs__msg__NetworkMetrics;
    is_plain =
      (
      offsetof(DataType, backhaul_latency_ms) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _NetworkMetrics__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_aura_msgs__msg__NetworkMetrics(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_NetworkMetrics = {
  "aura_msgs::msg",
  "NetworkMetrics",
  _NetworkMetrics__cdr_serialize,
  _NetworkMetrics__cdr_deserialize,
  _NetworkMetrics__get_serialized_size,
  _NetworkMetrics__max_serialized_size
};

static rosidl_message_type_support_t _NetworkMetrics__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_NetworkMetrics,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, aura_msgs, msg, NetworkMetrics)() {
  return &_NetworkMetrics__type_support;
}

#if defined(__cplusplus)
}
#endif
