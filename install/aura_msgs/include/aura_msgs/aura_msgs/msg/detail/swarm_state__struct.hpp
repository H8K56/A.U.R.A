// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_HPP_

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
// Member 'drones'
#include "aura_msgs/msg/detail/drone_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__SwarmState __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__SwarmState __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SwarmState_
{
  using Type = SwarmState_<ContainerAllocator>;

  explicit SwarmState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_drones_total = 0;
      this->num_drones_active = 0;
      this->num_hubs = 0;
      this->num_leaves = 0;
      this->mission_state = 0;
      this->coverage_percent = 0.0f;
      this->coverage_quality = 0.0f;
      this->avg_throughput_mbps = 0.0f;
      this->avg_latency_ms = 0.0f;
      this->packet_loss_percent = 0.0f;
      this->mesh_connected = false;
      this->backhaul_connected = false;
    }
  }

  explicit SwarmState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_drones_total = 0;
      this->num_drones_active = 0;
      this->num_hubs = 0;
      this->num_leaves = 0;
      this->mission_state = 0;
      this->coverage_percent = 0.0f;
      this->coverage_quality = 0.0f;
      this->avg_throughput_mbps = 0.0f;
      this->avg_latency_ms = 0.0f;
      this->packet_loss_percent = 0.0f;
      this->mesh_connected = false;
      this->backhaul_connected = false;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _num_drones_total_type =
    uint8_t;
  _num_drones_total_type num_drones_total;
  using _num_drones_active_type =
    uint8_t;
  _num_drones_active_type num_drones_active;
  using _num_hubs_type =
    uint8_t;
  _num_hubs_type num_hubs;
  using _num_leaves_type =
    uint8_t;
  _num_leaves_type num_leaves;
  using _mission_state_type =
    uint8_t;
  _mission_state_type mission_state;
  using _coverage_percent_type =
    float;
  _coverage_percent_type coverage_percent;
  using _coverage_quality_type =
    float;
  _coverage_quality_type coverage_quality;
  using _avg_throughput_mbps_type =
    float;
  _avg_throughput_mbps_type avg_throughput_mbps;
  using _avg_latency_ms_type =
    float;
  _avg_latency_ms_type avg_latency_ms;
  using _packet_loss_percent_type =
    float;
  _packet_loss_percent_type packet_loss_percent;
  using _mesh_connected_type =
    bool;
  _mesh_connected_type mesh_connected;
  using _backhaul_connected_type =
    bool;
  _backhaul_connected_type backhaul_connected;
  using _drones_type =
    std::vector<aura_msgs::msg::DroneState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aura_msgs::msg::DroneState_<ContainerAllocator>>>;
  _drones_type drones;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__num_drones_total(
    const uint8_t & _arg)
  {
    this->num_drones_total = _arg;
    return *this;
  }
  Type & set__num_drones_active(
    const uint8_t & _arg)
  {
    this->num_drones_active = _arg;
    return *this;
  }
  Type & set__num_hubs(
    const uint8_t & _arg)
  {
    this->num_hubs = _arg;
    return *this;
  }
  Type & set__num_leaves(
    const uint8_t & _arg)
  {
    this->num_leaves = _arg;
    return *this;
  }
  Type & set__mission_state(
    const uint8_t & _arg)
  {
    this->mission_state = _arg;
    return *this;
  }
  Type & set__coverage_percent(
    const float & _arg)
  {
    this->coverage_percent = _arg;
    return *this;
  }
  Type & set__coverage_quality(
    const float & _arg)
  {
    this->coverage_quality = _arg;
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
  Type & set__mesh_connected(
    const bool & _arg)
  {
    this->mesh_connected = _arg;
    return *this;
  }
  Type & set__backhaul_connected(
    const bool & _arg)
  {
    this->backhaul_connected = _arg;
    return *this;
  }
  Type & set__drones(
    const std::vector<aura_msgs::msg::DroneState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aura_msgs::msg::DroneState_<ContainerAllocator>>> & _arg)
  {
    this->drones = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MISSION_IDLE =
    0u;
  static constexpr uint8_t MISSION_PREFLIGHT =
    1u;
  static constexpr uint8_t MISSION_TAKEOFF =
    2u;
  static constexpr uint8_t MISSION_TRANSIT =
    3u;
  static constexpr uint8_t MISSION_FORMATION =
    4u;
  static constexpr uint8_t MISSION_OPERATIONS =
    5u;
  static constexpr uint8_t MISSION_RTL =
    6u;
  static constexpr uint8_t MISSION_COMPLETE =
    7u;
  static constexpr uint8_t MISSION_ABORT =
    8u;

  // pointer types
  using RawPtr =
    aura_msgs::msg::SwarmState_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::SwarmState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::SwarmState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::SwarmState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__SwarmState
    std::shared_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__SwarmState
    std::shared_ptr<aura_msgs::msg::SwarmState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SwarmState_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->num_drones_total != other.num_drones_total) {
      return false;
    }
    if (this->num_drones_active != other.num_drones_active) {
      return false;
    }
    if (this->num_hubs != other.num_hubs) {
      return false;
    }
    if (this->num_leaves != other.num_leaves) {
      return false;
    }
    if (this->mission_state != other.mission_state) {
      return false;
    }
    if (this->coverage_percent != other.coverage_percent) {
      return false;
    }
    if (this->coverage_quality != other.coverage_quality) {
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
    if (this->mesh_connected != other.mesh_connected) {
      return false;
    }
    if (this->backhaul_connected != other.backhaul_connected) {
      return false;
    }
    if (this->drones != other.drones) {
      return false;
    }
    return true;
  }
  bool operator!=(const SwarmState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SwarmState_

// alias to use template instance with default allocator
using SwarmState =
  aura_msgs::msg::SwarmState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_PREFLIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_TAKEOFF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_TRANSIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_FORMATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_OPERATIONS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_RTL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_COMPLETE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SwarmState_<ContainerAllocator>::MISSION_ABORT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__SWARM_STATE__STRUCT_HPP_
