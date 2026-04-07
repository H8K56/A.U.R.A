// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:srv/RequestTrajectory.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_HPP_
#define AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__RequestTrajectory_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__RequestTrajectory_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RequestTrajectory_Request_
{
  using Type = RequestTrajectory_Request_<ContainerAllocator>;

  explicit RequestTrajectory_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->max_velocity = 0.0;
      this->max_time = 0.0;
      this->avoid_weather_zones = false;
    }
  }

  explicit RequestTrajectory_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->max_velocity = 0.0;
      this->max_time = 0.0;
      this->avoid_weather_zones = false;
    }
  }

  // field types and members
  using _drone_id_type =
    uint8_t;
  _drone_id_type drone_id;
  using _goal_position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _goal_position_type goal_position;
  using _max_velocity_type =
    double;
  _max_velocity_type max_velocity;
  using _max_time_type =
    double;
  _max_time_type max_time;
  using _avoid_weather_zones_type =
    bool;
  _avoid_weather_zones_type avoid_weather_zones;

  // setters for named parameter idiom
  Type & set__drone_id(
    const uint8_t & _arg)
  {
    this->drone_id = _arg;
    return *this;
  }
  Type & set__goal_position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->goal_position = _arg;
    return *this;
  }
  Type & set__max_velocity(
    const double & _arg)
  {
    this->max_velocity = _arg;
    return *this;
  }
  Type & set__max_time(
    const double & _arg)
  {
    this->max_time = _arg;
    return *this;
  }
  Type & set__avoid_weather_zones(
    const bool & _arg)
  {
    this->avoid_weather_zones = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__RequestTrajectory_Request
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__RequestTrajectory_Request
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RequestTrajectory_Request_ & other) const
  {
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->goal_position != other.goal_position) {
      return false;
    }
    if (this->max_velocity != other.max_velocity) {
      return false;
    }
    if (this->max_time != other.max_time) {
      return false;
    }
    if (this->avoid_weather_zones != other.avoid_weather_zones) {
      return false;
    }
    return true;
  }
  bool operator!=(const RequestTrajectory_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RequestTrajectory_Request_

// alias to use template instance with default allocator
using RequestTrajectory_Request =
  aura_msgs::srv::RequestTrajectory_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs


// Include directives for member types
// Member 'trajectory'
#include "aura_msgs/msg/detail/trajectory_broadcast__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__RequestTrajectory_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__RequestTrajectory_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RequestTrajectory_Response_
{
  using Type = RequestTrajectory_Response_<ContainerAllocator>;

  explicit RequestTrajectory_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : trajectory(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->estimated_time = 0.0;
      this->estimated_energy = 0.0;
    }
  }

  explicit RequestTrajectory_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    trajectory(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->estimated_time = 0.0;
      this->estimated_energy = 0.0;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _trajectory_type =
    aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator>;
  _trajectory_type trajectory;
  using _estimated_time_type =
    double;
  _estimated_time_type estimated_time;
  using _estimated_energy_type =
    double;
  _estimated_energy_type estimated_energy;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__trajectory(
    const aura_msgs::msg::TrajectoryBroadcast_<ContainerAllocator> & _arg)
  {
    this->trajectory = _arg;
    return *this;
  }
  Type & set__estimated_time(
    const double & _arg)
  {
    this->estimated_time = _arg;
    return *this;
  }
  Type & set__estimated_energy(
    const double & _arg)
  {
    this->estimated_energy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__RequestTrajectory_Response
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__RequestTrajectory_Response
    std::shared_ptr<aura_msgs::srv::RequestTrajectory_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RequestTrajectory_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->trajectory != other.trajectory) {
      return false;
    }
    if (this->estimated_time != other.estimated_time) {
      return false;
    }
    if (this->estimated_energy != other.estimated_energy) {
      return false;
    }
    return true;
  }
  bool operator!=(const RequestTrajectory_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RequestTrajectory_Response_

// alias to use template instance with default allocator
using RequestTrajectory_Response =
  aura_msgs::srv::RequestTrajectory_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs

namespace aura_msgs
{

namespace srv
{

struct RequestTrajectory
{
  using Request = aura_msgs::srv::RequestTrajectory_Request;
  using Response = aura_msgs::srv::RequestTrajectory_Response;
};

}  // namespace srv

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__STRUCT_HPP_
