// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_H_
#define AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'origin'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'signal_strength_dbm'
// Member 'throughput_mbps'
// Member 'latency_ms'
// Member 'coverage_mask'
// Member 'link_from_drone'
// Member 'link_to_drone'
// Member 'link_throughput_mbps'
// Member 'link_latency_ms'
// Member 'link_rssi_dbm'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/NetworkMetrics in the package aura_msgs.
/**
  * NetworkMetrics.msg
  * Network simulation metrics from NS-3 bridge
 */
typedef struct aura_msgs__msg__NetworkMetrics
{
  std_msgs__msg__Header header;
  builtin_interfaces__msg__Time timestamp;
  /// Grid-based coverage map
  /// Number of cells in X
  uint32_t grid_size_x;
  /// Number of cells in Y
  uint32_t grid_size_y;
  /// Size of each cell
  float cell_size_meters;
  /// World position of grid origin
  geometry_msgs__msg__Point origin;
  /// Coverage data (flattened grid_size_x * grid_size_y arrays)
  /// Access with: data
  /// Signal strength at each cell
  rosidl_runtime_c__float__Sequence signal_strength_dbm;
  /// Available throughput at each cell
  rosidl_runtime_c__float__Sequence throughput_mbps;
  /// Expected latency at each cell
  rosidl_runtime_c__float__Sequence latency_ms;
  /// True if cell has usable coverage
  rosidl_runtime_c__boolean__Sequence coverage_mask;
  /// Aggregate metrics
  /// Percent of target area covered
  float total_coverage_percent;
  float avg_signal_strength_dbm;
  float avg_throughput_mbps;
  float avg_latency_ms;
  float packet_loss_percent;
  /// Per-link metrics (between drones)
  /// Source drone ID
  rosidl_runtime_c__uint8__Sequence link_from_drone;
  /// Destination drone ID
  rosidl_runtime_c__uint8__Sequence link_to_drone;
  /// Throughput on this link
  rosidl_runtime_c__float__Sequence link_throughput_mbps;
  /// Latency on this link
  rosidl_runtime_c__float__Sequence link_latency_ms;
  /// Signal strength on this link
  rosidl_runtime_c__float__Sequence link_rssi_dbm;
  /// Backhaul status (Hub to command post)
  bool backhaul_active;
  float backhaul_throughput_mbps;
  float backhaul_latency_ms;
} aura_msgs__msg__NetworkMetrics;

// Struct for a sequence of aura_msgs__msg__NetworkMetrics.
typedef struct aura_msgs__msg__NetworkMetrics__Sequence
{
  aura_msgs__msg__NetworkMetrics * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aura_msgs__msg__NetworkMetrics__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_H_
