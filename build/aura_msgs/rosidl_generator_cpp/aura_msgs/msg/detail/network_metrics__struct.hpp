// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'origin'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__NetworkMetrics __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__NetworkMetrics __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NetworkMetrics_
{
  using Type = NetworkMetrics_<ContainerAllocator>;

  explicit NetworkMetrics_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    origin(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size_x = 0ul;
      this->grid_size_y = 0ul;
      this->cell_size_meters = 0.0f;
      this->total_coverage_percent = 0.0f;
      this->avg_signal_strength_dbm = 0.0f;
      this->avg_throughput_mbps = 0.0f;
      this->avg_latency_ms = 0.0f;
      this->packet_loss_percent = 0.0f;
      this->backhaul_active = false;
      this->backhaul_throughput_mbps = 0.0f;
      this->backhaul_latency_ms = 0.0f;
    }
  }

  explicit NetworkMetrics_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    origin(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size_x = 0ul;
      this->grid_size_y = 0ul;
      this->cell_size_meters = 0.0f;
      this->total_coverage_percent = 0.0f;
      this->avg_signal_strength_dbm = 0.0f;
      this->avg_throughput_mbps = 0.0f;
      this->avg_latency_ms = 0.0f;
      this->packet_loss_percent = 0.0f;
      this->backhaul_active = false;
      this->backhaul_throughput_mbps = 0.0f;
      this->backhaul_latency_ms = 0.0f;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _grid_size_x_type =
    uint32_t;
  _grid_size_x_type grid_size_x;
  using _grid_size_y_type =
    uint32_t;
  _grid_size_y_type grid_size_y;
  using _cell_size_meters_type =
    float;
  _cell_size_meters_type cell_size_meters;
  using _origin_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _origin_type origin;
  using _signal_strength_dbm_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _signal_strength_dbm_type signal_strength_dbm;
  using _throughput_mbps_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _throughput_mbps_type throughput_mbps;
  using _latency_ms_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _latency_ms_type latency_ms;
  using _coverage_mask_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _coverage_mask_type coverage_mask;
  using _total_coverage_percent_type =
    float;
  _total_coverage_percent_type total_coverage_percent;
  using _avg_signal_strength_dbm_type =
    float;
  _avg_signal_strength_dbm_type avg_signal_strength_dbm;
  using _avg_throughput_mbps_type =
    float;
  _avg_throughput_mbps_type avg_throughput_mbps;
  using _avg_latency_ms_type =
    float;
  _avg_latency_ms_type avg_latency_ms;
  using _packet_loss_percent_type =
    float;
  _packet_loss_percent_type packet_loss_percent;
  using _link_from_drone_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _link_from_drone_type link_from_drone;
  using _link_to_drone_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _link_to_drone_type link_to_drone;
  using _link_throughput_mbps_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _link_throughput_mbps_type link_throughput_mbps;
  using _link_latency_ms_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _link_latency_ms_type link_latency_ms;
  using _link_rssi_dbm_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _link_rssi_dbm_type link_rssi_dbm;
  using _backhaul_active_type =
    bool;
  _backhaul_active_type backhaul_active;
  using _backhaul_throughput_mbps_type =
    float;
  _backhaul_throughput_mbps_type backhaul_throughput_mbps;
  using _backhaul_latency_ms_type =
    float;
  _backhaul_latency_ms_type backhaul_latency_ms;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__grid_size_x(
    const uint32_t & _arg)
  {
    this->grid_size_x = _arg;
    return *this;
  }
  Type & set__grid_size_y(
    const uint32_t & _arg)
  {
    this->grid_size_y = _arg;
    return *this;
  }
  Type & set__cell_size_meters(
    const float & _arg)
  {
    this->cell_size_meters = _arg;
    return *this;
  }
  Type & set__origin(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->origin = _arg;
    return *this;
  }
  Type & set__signal_strength_dbm(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->signal_strength_dbm = _arg;
    return *this;
  }
  Type & set__throughput_mbps(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->throughput_mbps = _arg;
    return *this;
  }
  Type & set__latency_ms(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->latency_ms = _arg;
    return *this;
  }
  Type & set__coverage_mask(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->coverage_mask = _arg;
    return *this;
  }
  Type & set__total_coverage_percent(
    const float & _arg)
  {
    this->total_coverage_percent = _arg;
    return *this;
  }
  Type & set__avg_signal_strength_dbm(
    const float & _arg)
  {
    this->avg_signal_strength_dbm = _arg;
    return *this;
  }
  Type & set__avg_throughput_mbps(
    const float & _arg)
  {
    this->avg_throughput_mbps = _arg;
    return *this;
  }
  Type & set__avg_latency_ms(
    const float & _arg)
  {
    this->avg_latency_ms = _arg;
    return *this;
  }
  Type & set__packet_loss_percent(
    const float & _arg)
  {
    this->packet_loss_percent = _arg;
    return *this;
  }
  Type & set__link_from_drone(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->link_from_drone = _arg;
    return *this;
  }
  Type & set__link_to_drone(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->link_to_drone = _arg;
    return *this;
  }
  Type & set__link_throughput_mbps(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->link_throughput_mbps = _arg;
    return *this;
  }
  Type & set__link_latency_ms(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->link_latency_ms = _arg;
    return *this;
  }
  Type & set__link_rssi_dbm(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->link_rssi_dbm = _arg;
    return *this;
  }
  Type & set__backhaul_active(
    const bool & _arg)
  {
    this->backhaul_active = _arg;
    return *this;
  }
  Type & set__backhaul_throughput_mbps(
    const float & _arg)
  {
    this->backhaul_throughput_mbps = _arg;
    return *this;
  }
  Type & set__backhaul_latency_ms(
    const float & _arg)
  {
    this->backhaul_latency_ms = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::msg::NetworkMetrics_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::NetworkMetrics_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::NetworkMetrics_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::NetworkMetrics_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__NetworkMetrics
    std::shared_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__NetworkMetrics
    std::shared_ptr<aura_msgs::msg::NetworkMetrics_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NetworkMetrics_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->grid_size_x != other.grid_size_x) {
      return false;
    }
    if (this->grid_size_y != other.grid_size_y) {
      return false;
    }
    if (this->cell_size_meters != other.cell_size_meters) {
      return false;
    }
    if (this->origin != other.origin) {
      return false;
    }
    if (this->signal_strength_dbm != other.signal_strength_dbm) {
      return false;
    }
    if (this->throughput_mbps != other.throughput_mbps) {
      return false;
    }
    if (this->latency_ms != other.latency_ms) {
      return false;
    }
    if (this->coverage_mask != other.coverage_mask) {
      return false;
    }
    if (this->total_coverage_percent != other.total_coverage_percent) {
      return false;
    }
    if (this->avg_signal_strength_dbm != other.avg_signal_strength_dbm) {
      return false;
    }
    if (this->avg_throughput_mbps != other.avg_throughput_mbps) {
      return false;
    }
    if (this->avg_latency_ms != other.avg_latency_ms) {
      return false;
    }
    if (this->packet_loss_percent != other.packet_loss_percent) {
      return false;
    }
    if (this->link_from_drone != other.link_from_drone) {
      return false;
    }
    if (this->link_to_drone != other.link_to_drone) {
      return false;
    }
    if (this->link_throughput_mbps != other.link_throughput_mbps) {
      return false;
    }
    if (this->link_latency_ms != other.link_latency_ms) {
      return false;
    }
    if (this->link_rssi_dbm != other.link_rssi_dbm) {
      return false;
    }
    if (this->backhaul_active != other.backhaul_active) {
      return false;
    }
    if (this->backhaul_throughput_mbps != other.backhaul_throughput_mbps) {
      return false;
    }
    if (this->backhaul_latency_ms != other.backhaul_latency_ms) {
      return false;
    }
    return true;
  }
  bool operator!=(const NetworkMetrics_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NetworkMetrics_

// alias to use template instance with default allocator
using NetworkMetrics =
  aura_msgs::msg::NetworkMetrics_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__STRUCT_HPP_
