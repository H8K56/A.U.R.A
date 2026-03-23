// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__MissionStatus __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__MissionStatus __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MissionStatus_
{
  using Type = MissionStatus_<ContainerAllocator>;

  explicit MissionStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_id = "";
      this->phase = 0;
      this->progress_percent = 0.0f;
      this->elapsed_time_sec = 0.0f;
      this->estimated_remaining_sec = 0.0f;
      this->coverage_achieved = 0.0f;
      this->network_quality = 0.0f;
      this->connections_established = 0ul;
      this->data_transferred_mb = 0ul;
      this->drones_operational = 0;
      this->drones_degraded = 0;
      this->drones_failed = 0;
    }
  }

  explicit MissionStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    mission_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_id = "";
      this->phase = 0;
      this->progress_percent = 0.0f;
      this->elapsed_time_sec = 0.0f;
      this->estimated_remaining_sec = 0.0f;
      this->coverage_achieved = 0.0f;
      this->network_quality = 0.0f;
      this->connections_established = 0ul;
      this->data_transferred_mb = 0ul;
      this->drones_operational = 0;
      this->drones_degraded = 0;
      this->drones_failed = 0;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _phase_type =
    uint8_t;
  _phase_type phase;
  using _progress_percent_type =
    float;
  _progress_percent_type progress_percent;
  using _elapsed_time_sec_type =
    float;
  _elapsed_time_sec_type elapsed_time_sec;
  using _estimated_remaining_sec_type =
    float;
  _estimated_remaining_sec_type estimated_remaining_sec;
  using _coverage_achieved_type =
    float;
  _coverage_achieved_type coverage_achieved;
  using _network_quality_type =
    float;
  _network_quality_type network_quality;
  using _connections_established_type =
    uint32_t;
  _connections_established_type connections_established;
  using _data_transferred_mb_type =
    uint32_t;
  _data_transferred_mb_type data_transferred_mb;
  using _active_alerts_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _active_alerts_type active_alerts;
  using _alert_severities_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _alert_severities_type alert_severities;
  using _drones_operational_type =
    uint8_t;
  _drones_operational_type drones_operational;
  using _drones_degraded_type =
    uint8_t;
  _drones_degraded_type drones_degraded;
  using _drones_failed_type =
    uint8_t;
  _drones_failed_type drones_failed;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__mission_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_id = _arg;
    return *this;
  }
  Type & set__phase(
    const uint8_t & _arg)
  {
    this->phase = _arg;
    return *this;
  }
  Type & set__progress_percent(
    const float & _arg)
  {
    this->progress_percent = _arg;
    return *this;
  }
  Type & set__elapsed_time_sec(
    const float & _arg)
  {
    this->elapsed_time_sec = _arg;
    return *this;
  }
  Type & set__estimated_remaining_sec(
    const float & _arg)
  {
    this->estimated_remaining_sec = _arg;
    return *this;
  }
  Type & set__coverage_achieved(
    const float & _arg)
  {
    this->coverage_achieved = _arg;
    return *this;
  }
  Type & set__network_quality(
    const float & _arg)
  {
    this->network_quality = _arg;
    return *this;
  }
  Type & set__connections_established(
    const uint32_t & _arg)
  {
    this->connections_established = _arg;
    return *this;
  }
  Type & set__data_transferred_mb(
    const uint32_t & _arg)
  {
    this->data_transferred_mb = _arg;
    return *this;
  }
  Type & set__active_alerts(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->active_alerts = _arg;
    return *this;
  }
  Type & set__alert_severities(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->alert_severities = _arg;
    return *this;
  }
  Type & set__drones_operational(
    const uint8_t & _arg)
  {
    this->drones_operational = _arg;
    return *this;
  }
  Type & set__drones_degraded(
    const uint8_t & _arg)
  {
    this->drones_degraded = _arg;
    return *this;
  }
  Type & set__drones_failed(
    const uint8_t & _arg)
  {
    this->drones_failed = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t PHASE_INIT =
    0u;
  static constexpr uint8_t PHASE_PREFLIGHT =
    1u;
  static constexpr uint8_t PHASE_LAUNCH =
    2u;
  static constexpr uint8_t PHASE_TRANSIT =
    3u;
  static constexpr uint8_t PHASE_DEPLOY =
    4u;
  static constexpr uint8_t PHASE_OPERATIONS =
    5u;
  static constexpr uint8_t PHASE_RECOVERY =
    6u;
  static constexpr uint8_t PHASE_COMPLETE =
    7u;
  static constexpr uint8_t PHASE_ABORT =
    8u;

  // pointer types
  using RawPtr =
    aura_msgs::msg::MissionStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::MissionStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::MissionStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::MissionStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__MissionStatus
    std::shared_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__MissionStatus
    std::shared_ptr<aura_msgs::msg::MissionStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MissionStatus_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->mission_id != other.mission_id) {
      return false;
    }
    if (this->phase != other.phase) {
      return false;
    }
    if (this->progress_percent != other.progress_percent) {
      return false;
    }
    if (this->elapsed_time_sec != other.elapsed_time_sec) {
      return false;
    }
    if (this->estimated_remaining_sec != other.estimated_remaining_sec) {
      return false;
    }
    if (this->coverage_achieved != other.coverage_achieved) {
      return false;
    }
    if (this->network_quality != other.network_quality) {
      return false;
    }
    if (this->connections_established != other.connections_established) {
      return false;
    }
    if (this->data_transferred_mb != other.data_transferred_mb) {
      return false;
    }
    if (this->active_alerts != other.active_alerts) {
      return false;
    }
    if (this->alert_severities != other.alert_severities) {
      return false;
    }
    if (this->drones_operational != other.drones_operational) {
      return false;
    }
    if (this->drones_degraded != other.drones_degraded) {
      return false;
    }
    if (this->drones_failed != other.drones_failed) {
      return false;
    }
    return true;
  }
  bool operator!=(const MissionStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MissionStatus_

// alias to use template instance with default allocator
using MissionStatus =
  aura_msgs::msg::MissionStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_INIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_PREFLIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_LAUNCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_TRANSIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_DEPLOY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_OPERATIONS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_RECOVERY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_COMPLETE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MissionStatus_<ContainerAllocator>::PHASE_ABORT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__MISSION_STATUS__STRUCT_HPP_
