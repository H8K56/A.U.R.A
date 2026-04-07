// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_

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
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__DroneState __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__DroneState __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneState_
{
  using Type = DroneState_<ContainerAllocator>;

  explicit DroneState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    position(_init),
    velocity(_init),
    orientation(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->role = 0;
      this->flight_mode = 0;
      this->battery_percent = 0.0f;
      this->battery_voltage = 0.0f;
      this->signal_strength_dbm = 0.0f;
      this->gps_fix = false;
      this->num_satellites = 0;
      this->throughput_mbps = 0.0f;
      this->latency_ms = 0.0f;
      this->connected_neighbors = 0;
    }
  }

  explicit DroneState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    position(_alloc, _init),
    velocity(_alloc, _init),
    orientation(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->role = 0;
      this->flight_mode = 0;
      this->battery_percent = 0.0f;
      this->battery_voltage = 0.0f;
      this->signal_strength_dbm = 0.0f;
      this->gps_fix = false;
      this->num_satellites = 0;
      this->throughput_mbps = 0.0f;
      this->latency_ms = 0.0f;
      this->connected_neighbors = 0;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _drone_id_type =
    uint8_t;
  _drone_id_type drone_id;
  using _role_type =
    uint8_t;
  _role_type role;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _orientation_type =
    geometry_msgs::msg::Quaternion_<ContainerAllocator>;
  _orientation_type orientation;
  using _flight_mode_type =
    uint8_t;
  _flight_mode_type flight_mode;
  using _battery_percent_type =
    float;
  _battery_percent_type battery_percent;
  using _battery_voltage_type =
    float;
  _battery_voltage_type battery_voltage;
  using _signal_strength_dbm_type =
    float;
  _signal_strength_dbm_type signal_strength_dbm;
  using _gps_fix_type =
    bool;
  _gps_fix_type gps_fix;
  using _num_satellites_type =
    uint8_t;
  _num_satellites_type num_satellites;
  using _throughput_mbps_type =
    float;
  _throughput_mbps_type throughput_mbps;
  using _latency_ms_type =
    float;
  _latency_ms_type latency_ms;
  using _connected_neighbors_type =
    uint8_t;
  _connected_neighbors_type connected_neighbors;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__drone_id(
    const uint8_t & _arg)
  {
    this->drone_id = _arg;
    return *this;
  }
  Type & set__role(
    const uint8_t & _arg)
  {
    this->role = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__orientation(
    const geometry_msgs::msg::Quaternion_<ContainerAllocator> & _arg)
  {
    this->orientation = _arg;
    return *this;
  }
  Type & set__flight_mode(
    const uint8_t & _arg)
  {
    this->flight_mode = _arg;
    return *this;
  }
  Type & set__battery_percent(
    const float & _arg)
  {
    this->battery_percent = _arg;
    return *this;
  }
  Type & set__battery_voltage(
    const float & _arg)
  {
    this->battery_voltage = _arg;
    return *this;
  }
  Type & set__signal_strength_dbm(
    const float & _arg)
  {
    this->signal_strength_dbm = _arg;
    return *this;
  }
  Type & set__gps_fix(
    const bool & _arg)
  {
    this->gps_fix = _arg;
    return *this;
  }
  Type & set__num_satellites(
    const uint8_t & _arg)
  {
    this->num_satellites = _arg;
    return *this;
  }
  Type & set__throughput_mbps(
    const float & _arg)
  {
    this->throughput_mbps = _arg;
    return *this;
  }
  Type & set__latency_ms(
    const float & _arg)
  {
    this->latency_ms = _arg;
    return *this;
  }
  Type & set__connected_neighbors(
    const uint8_t & _arg)
  {
    this->connected_neighbors = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t ROLE_LEAF =
    0u;
  static constexpr uint8_t ROLE_HUB =
    1u;
  static constexpr uint8_t FLIGHT_MODE_IDLE =
    0u;
  static constexpr uint8_t FLIGHT_MODE_TAKEOFF =
    1u;
  static constexpr uint8_t FLIGHT_MODE_TRANSIT =
    2u;
  static constexpr uint8_t FLIGHT_MODE_FORMATION =
    3u;
  static constexpr uint8_t FLIGHT_MODE_OPERATIONS =
    4u;
  static constexpr uint8_t FLIGHT_MODE_RTL =
    5u;
  static constexpr uint8_t FLIGHT_MODE_EMERGENCY =
    6u;

  // pointer types
  using RawPtr =
    aura_msgs::msg::DroneState_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::DroneState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::DroneState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::DroneState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::DroneState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::DroneState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::DroneState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::DroneState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::DroneState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::DroneState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__DroneState
    std::shared_ptr<aura_msgs::msg::DroneState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__DroneState
    std::shared_ptr<aura_msgs::msg::DroneState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneState_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->role != other.role) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->orientation != other.orientation) {
      return false;
    }
    if (this->flight_mode != other.flight_mode) {
      return false;
    }
    if (this->battery_percent != other.battery_percent) {
      return false;
    }
    if (this->battery_voltage != other.battery_voltage) {
      return false;
    }
    if (this->signal_strength_dbm != other.signal_strength_dbm) {
      return false;
    }
    if (this->gps_fix != other.gps_fix) {
      return false;
    }
    if (this->num_satellites != other.num_satellites) {
      return false;
    }
    if (this->throughput_mbps != other.throughput_mbps) {
      return false;
    }
    if (this->latency_ms != other.latency_ms) {
      return false;
    }
    if (this->connected_neighbors != other.connected_neighbors) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneState_

// alias to use template instance with default allocator
using DroneState =
  aura_msgs::msg::DroneState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::ROLE_LEAF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::ROLE_HUB;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_TAKEOFF;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_TRANSIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_FORMATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_OPERATIONS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_RTL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DroneState_<ContainerAllocator>::FLIGHT_MODE_EMERGENCY;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__DRONE_STATE__STRUCT_HPP_
