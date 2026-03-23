// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:srv/SetFormation.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_HPP_
#define AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'custom_positions'
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__SetFormation_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__SetFormation_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetFormation_Request_
{
  using Type = SetFormation_Request_<ContainerAllocator>;

  explicit SetFormation_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->formation_type = 0;
      this->spacing_meters = 0.0f;
      this->altitude_meters = 0.0f;
      this->heading_rad = 0.0f;
    }
  }

  explicit SetFormation_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : center(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->formation_type = 0;
      this->spacing_meters = 0.0f;
      this->altitude_meters = 0.0f;
      this->heading_rad = 0.0f;
    }
  }

  // field types and members
  using _formation_type_type =
    uint8_t;
  _formation_type_type formation_type;
  using _custom_positions_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _custom_positions_type custom_positions;
  using _spacing_meters_type =
    float;
  _spacing_meters_type spacing_meters;
  using _altitude_meters_type =
    float;
  _altitude_meters_type altitude_meters;
  using _center_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _center_type center;
  using _heading_rad_type =
    float;
  _heading_rad_type heading_rad;

  // setters for named parameter idiom
  Type & set__formation_type(
    const uint8_t & _arg)
  {
    this->formation_type = _arg;
    return *this;
  }
  Type & set__custom_positions(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->custom_positions = _arg;
    return *this;
  }
  Type & set__spacing_meters(
    const float & _arg)
  {
    this->spacing_meters = _arg;
    return *this;
  }
  Type & set__altitude_meters(
    const float & _arg)
  {
    this->altitude_meters = _arg;
    return *this;
  }
  Type & set__center(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__heading_rad(
    const float & _arg)
  {
    this->heading_rad = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t FORMATION_SPREAD =
    0u;
  static constexpr uint8_t FORMATION_CLUSTER =
    1u;
  static constexpr uint8_t FORMATION_LINE =
    2u;
  static constexpr uint8_t FORMATION_GRID =
    3u;
  static constexpr uint8_t FORMATION_CUSTOM =
    4u;

  // pointer types
  using RawPtr =
    aura_msgs::srv::SetFormation_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::SetFormation_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::SetFormation_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::SetFormation_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__SetFormation_Request
    std::shared_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__SetFormation_Request
    std::shared_ptr<aura_msgs::srv::SetFormation_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetFormation_Request_ & other) const
  {
    if (this->formation_type != other.formation_type) {
      return false;
    }
    if (this->custom_positions != other.custom_positions) {
      return false;
    }
    if (this->spacing_meters != other.spacing_meters) {
      return false;
    }
    if (this->altitude_meters != other.altitude_meters) {
      return false;
    }
    if (this->center != other.center) {
      return false;
    }
    if (this->heading_rad != other.heading_rad) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetFormation_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetFormation_Request_

// alias to use template instance with default allocator
using SetFormation_Request =
  aura_msgs::srv::SetFormation_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetFormation_Request_<ContainerAllocator>::FORMATION_SPREAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetFormation_Request_<ContainerAllocator>::FORMATION_CLUSTER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetFormation_Request_<ContainerAllocator>::FORMATION_LINE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetFormation_Request_<ContainerAllocator>::FORMATION_GRID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetFormation_Request_<ContainerAllocator>::FORMATION_CUSTOM;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace aura_msgs


#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__SetFormation_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__SetFormation_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetFormation_Response_
{
  using Type = SetFormation_Response_<ContainerAllocator>;

  explicit SetFormation_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->estimated_transition_time = 0.0f;
    }
  }

  explicit SetFormation_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->estimated_transition_time = 0.0f;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _estimated_transition_time_type =
    float;
  _estimated_transition_time_type estimated_transition_time;

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
  Type & set__estimated_transition_time(
    const float & _arg)
  {
    this->estimated_transition_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::SetFormation_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::SetFormation_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::SetFormation_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::SetFormation_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__SetFormation_Response
    std::shared_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__SetFormation_Response
    std::shared_ptr<aura_msgs::srv::SetFormation_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetFormation_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->estimated_transition_time != other.estimated_transition_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetFormation_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetFormation_Response_

// alias to use template instance with default allocator
using SetFormation_Response =
  aura_msgs::srv::SetFormation_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs

namespace aura_msgs
{

namespace srv
{

struct SetFormation
{
  using Request = aura_msgs::srv::SetFormation_Request;
  using Response = aura_msgs::srv::SetFormation_Response;
};

}  // namespace srv

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__SET_FORMATION__STRUCT_HPP_
