// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:srv/EmergencyStop.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_HPP_
#define AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__EmergencyStop_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__EmergencyStop_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EmergencyStop_Request_
{
  using Type = EmergencyStop_Request_<ContainerAllocator>;

  explicit EmergencyStop_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->stop_type = 0;
      this->reason = "";
    }
  }

  explicit EmergencyStop_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->drone_id = 0;
      this->stop_type = 0;
      this->reason = "";
    }
  }

  // field types and members
  using _drone_id_type =
    uint8_t;
  _drone_id_type drone_id;
  using _stop_type_type =
    uint8_t;
  _stop_type_type stop_type;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__drone_id(
    const uint8_t & _arg)
  {
    this->drone_id = _arg;
    return *this;
  }
  Type & set__stop_type(
    const uint8_t & _arg)
  {
    this->stop_type = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t ALL_DRONES =
    255u;
  static constexpr uint8_t STOP_HOVER =
    0u;
  static constexpr uint8_t STOP_LAND =
    1u;
  static constexpr uint8_t STOP_RTL =
    2u;

  // pointer types
  using RawPtr =
    aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__EmergencyStop_Request
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__EmergencyStop_Request
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EmergencyStop_Request_ & other) const
  {
    if (this->drone_id != other.drone_id) {
      return false;
    }
    if (this->stop_type != other.stop_type) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const EmergencyStop_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EmergencyStop_Request_

// alias to use template instance with default allocator
using EmergencyStop_Request =
  aura_msgs::srv::EmergencyStop_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EmergencyStop_Request_<ContainerAllocator>::ALL_DRONES;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EmergencyStop_Request_<ContainerAllocator>::STOP_HOVER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EmergencyStop_Request_<ContainerAllocator>::STOP_LAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t EmergencyStop_Request_<ContainerAllocator>::STOP_RTL;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace aura_msgs


#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__EmergencyStop_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__EmergencyStop_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EmergencyStop_Response_
{
  using Type = EmergencyStop_Response_<ContainerAllocator>;

  explicit EmergencyStop_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->drones_affected = 0;
    }
  }

  explicit EmergencyStop_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->drones_affected = 0;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _drones_affected_type =
    uint8_t;
  _drones_affected_type drones_affected;

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
  Type & set__drones_affected(
    const uint8_t & _arg)
  {
    this->drones_affected = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__EmergencyStop_Response
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__EmergencyStop_Response
    std::shared_ptr<aura_msgs::srv::EmergencyStop_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EmergencyStop_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->drones_affected != other.drones_affected) {
      return false;
    }
    return true;
  }
  bool operator!=(const EmergencyStop_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EmergencyStop_Response_

// alias to use template instance with default allocator
using EmergencyStop_Response =
  aura_msgs::srv::EmergencyStop_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs

namespace aura_msgs
{

namespace srv
{

struct EmergencyStop
{
  using Request = aura_msgs::srv::EmergencyStop_Request;
  using Response = aura_msgs::srv::EmergencyStop_Response;
};

}  // namespace srv

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__STRUCT_HPP_
