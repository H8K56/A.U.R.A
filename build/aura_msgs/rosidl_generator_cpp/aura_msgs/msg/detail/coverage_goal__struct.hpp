// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/CoverageGoal.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__CoverageGoal __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__CoverageGoal __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CoverageGoal_
{
  using Type = CoverageGoal_<ContainerAllocator>;

  explicit CoverageGoal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->desired_arrival_time = 0.0;
      this->formation_type = 0;
      this->priority = 0.0f;
      this->min_altitude = 0.0f;
      this->max_altitude = 0.0f;
      this->max_velocity = 0.0f;
      this->required_throughput_mbps = 0.0f;
      this->required_coverage_radius = 0.0f;
    }
  }

  explicit CoverageGoal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->desired_arrival_time = 0.0;
      this->formation_type = 0;
      this->priority = 0.0f;
      this->min_altitude = 0.0f;
      this->max_altitude = 0.0f;
      this->max_velocity = 0.0f;
      this->required_throughput_mbps = 0.0f;
      this->required_coverage_radius = 0.0f;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _drone_id_type =
    uint8_t;
  _drone_id_type drone_id;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _desired_arrival_time_type =
    double;
  _desired_arrival_time_type desired_arrival_time;
  using _formation_type_type =
    uint8_t;
  _formation_type_type formation_type;
  using _priority_type =
    float;
  _priority_type priority;
  using _min_altitude_type =
    float;
  _min_altitude_type min_altitude;
  using _max_altitude_type =
    float;
  _max_altitude_type max_altitude;
  using _max_velocity_type =
    float;
  _max_velocity_type max_velocity;
  using _required_throughput_mbps_type =
    float;
  _required_throughput_mbps_type required_throughput_mbps;
  using _required_coverage_radius_type =
    float;
  _required_coverage_radius_type required_coverage_radius;

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
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__desired_arrival_time(
    const double & _arg)
  {
    this->desired_arrival_time = _arg;
    return *this;
  }
  Type & set__formation_type(
    const uint8_t & _arg)
  {
    this->formation_type = _arg;
    return *this;
  }
  Type & set__priority(
    const float & _arg)
  {
    this->priority = _arg;
    return *this;
  }
  Type & set__min_altitude(
    const float & _arg)
  {
    this->min_altitude = _arg;
    return *this;
  }
  Type & set__max_altitude(
    const float & _arg)
  {
    this->max_altitude = _arg;
    return *this;
  }
  Type & set__max_velocity(
    const float & _arg)
  {
    this->max_velocity = _arg;
    return *this;
  }
  Type & set__required_throughput_mbps(
    const float & _arg)
  {
    this->required_throughput_mbps = _arg;
    return *this;
  }
  Type & set__required_coverage_radius(
    const float & _arg)
  {
    this->required_coverage_radius = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t FORMATION_SPREAD =
    0u;
  static constexpr uint8_t FORMATION_CLUSTER =
    1u;
  static constexpr uint8_t FORMATION_LINE =
    2u;
  static constexpr uint8_t FORMATION_ADAPTIVE =
    3u;

  // pointer types
  using RawPtr =
    aura_msgs::msg::CoverageGoal_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::CoverageGoal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::CoverageGoal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::CoverageGoal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__CoverageGoal
    std::shared_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__CoverageGoal
    std::shared_ptr<aura_msgs::msg::CoverageGoal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CoverageGoal_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->desired_arrival_time != other.desired_arrival_time) {
      return false;
    }
    if (this->formation_type != other.formation_type) {
      return false;
    }
    if (this->priority != other.priority) {
      return false;
    }
    if (this->min_altitude != other.min_altitude) {
      return false;
    }
    if (this->max_altitude != other.max_altitude) {
      return false;
    }
    if (this->max_velocity != other.max_velocity) {
      return false;
    }
    if (this->required_throughput_mbps != other.required_throughput_mbps) {
      return false;
    }
    if (this->required_coverage_radius != other.required_coverage_radius) {
      return false;
    }
    return true;
  }
  bool operator!=(const CoverageGoal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CoverageGoal_

// alias to use template instance with default allocator
using CoverageGoal =
  aura_msgs::msg::CoverageGoal_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CoverageGoal_<ContainerAllocator>::FORMATION_SPREAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CoverageGoal_<ContainerAllocator>::FORMATION_CLUSTER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CoverageGoal_<ContainerAllocator>::FORMATION_LINE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CoverageGoal_<ContainerAllocator>::FORMATION_ADAPTIVE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__STRUCT_HPP_
