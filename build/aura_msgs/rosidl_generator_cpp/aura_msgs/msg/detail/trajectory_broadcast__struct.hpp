// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_HPP_

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
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'waypoints'
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__TrajectoryBroadcast __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__TrajectoryBroadcast __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrajectoryBroadcast_
{
  using Type = TrajectoryBroadcast_<ContainerAllocator>;

  explicit TrajectoryBroadcast_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    start_time(_init),
    goal_position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->total_duration = 0.0;
      this->num_pieces = 0;
      this->is_valid = false;
      this->max_velocity = 0.0f;
      this->clearance = 0.0f;
      this->goal_reached = false;
    }
  }

  explicit TrajectoryBroadcast_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    start_time(_alloc, _init),
    goal_position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->total_duration = 0.0;
      this->num_pieces = 0;
      this->is_valid = false;
      this->max_velocity = 0.0f;
      this->clearance = 0.0f;
      this->goal_reached = false;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _drone_id_type =
    uint8_t;
  _drone_id_type drone_id;
  using _start_time_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _start_time_type start_time;
  using _waypoints_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _waypoints_type waypoints;
  using _time_allocation_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _time_allocation_type time_allocation;
  using _total_duration_type =
    double;
  _total_duration_type total_duration;
  using _num_pieces_type =
    uint8_t;
  _num_pieces_type num_pieces;
  using _is_valid_type =
    bool;
  _is_valid_type is_valid;
  using _max_velocity_type =
    float;
  _max_velocity_type max_velocity;
  using _clearance_type =
    float;
  _clearance_type clearance;
  using _goal_position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _goal_position_type goal_position;
  using _goal_reached_type =
    bool;
  _goal_reached_type goal_reached;

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
  Type & set__start_time(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->start_time = _arg;
    return *this;
  }
  Type & set__waypoints(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->waypoints = _arg;
    return *this;
  }
  Type & set__time_allocation(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->time_allocation = _arg;
    return *this;
  }
  Type & set__total_duration(
    const double & _arg)
  {
    this->total_duration = _arg;
    return *this;
  }
  Type & set__num_pieces(
    const uint8_t & _arg)
  {
    this->num_pieces = _arg;
    return *this;
  }
  Type & set__is_valid(
    const bool & _arg)
  {
    this->is_valid = _arg;
    return *this;
  }
  Type & set__max_velocity(
    const float & _arg)
  {
    this->max_velocity = _arg;
    return *this;
  }
  Type & set__clearance(
    const float & _arg)
  {
    this->clearance = _arg;
    return *this;
  }
  Type & set__goal_position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->goal_position = _arg;
    return *this;
  }
  Type & set__goal_reached(
    const bool & _arg)
  {
    this->goal_reached = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__TrajectoryBroadcast
    std::shared_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__TrajectoryBroadcast
    std::shared_ptr<aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrajectoryBroadcast_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->start_time != other.start_time) {
      return false;
    }
    if (this->waypoints != other.waypoints) {
      return false;
    }
    if (this->time_allocation != other.time_allocation) {
      return false;
    }
    if (this->total_duration != other.total_duration) {
      return false;
    }
    if (this->num_pieces != other.num_pieces) {
      return false;
    }
    if (this->is_valid != other.is_valid) {
      return false;
    }
    if (this->max_velocity != other.max_velocity) {
      return false;
    }
    if (this->clearance != other.clearance) {
      return false;
    }
    if (this->goal_position != other.goal_position) {
      return false;
    }
    if (this->goal_reached != other.goal_reached) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrajectoryBroadcast_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrajectoryBroadcast_

// alias to use template instance with default allocator
using TrajectoryBroadcast =
  aura_msgs::msg::TrajectoryBroadcast_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__STRUCT_HPP_
