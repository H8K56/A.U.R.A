// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_HPP_
#define AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__GetNetworkStatus_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__GetNetworkStatus_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetNetworkStatus_Request_
{
  using Type = GetNetworkStatus_Request_<ContainerAllocator>;

  explicit GetNetworkStatus_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->include_coverage_map = false;
      this->include_link_details = false;
    }
  }

  explicit GetNetworkStatus_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->include_coverage_map = false;
      this->include_link_details = false;
    }
  }

  // field types and members
  using _include_coverage_map_type =
    bool;
  _include_coverage_map_type include_coverage_map;
  using _include_link_details_type =
    bool;
  _include_link_details_type include_link_details;

  // setters for named parameter idiom
  Type & set__include_coverage_map(
    const bool & _arg)
  {
    this->include_coverage_map = _arg;
    return *this;
  }
  Type & set__include_link_details(
    const bool & _arg)
  {
    this->include_link_details = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__GetNetworkStatus_Request
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__GetNetworkStatus_Request
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetNetworkStatus_Request_ & other) const
  {
    if (this->include_coverage_map != other.include_coverage_map) {
      return false;
    }
    if (this->include_link_details != other.include_link_details) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetNetworkStatus_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetNetworkStatus_Request_

// alias to use template instance with default allocator
using GetNetworkStatus_Request =
  aura_msgs::srv::GetNetworkStatus_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs


// Include directives for member types
// Member 'metrics'
#include "aura_msgs/msg/detail/network_metrics__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__srv__GetNetworkStatus_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__srv__GetNetworkStatus_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetNetworkStatus_Response_
{
  using Type = GetNetworkStatus_Response_<ContainerAllocator>;

  explicit GetNetworkStatus_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : metrics(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->overall_health = 0.0f;
    }
  }

  explicit GetNetworkStatus_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : metrics(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->overall_health = 0.0f;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _metrics_type =
    aura_msgs::msg::NetworkMetrics_<ContainerAllocator>;
  _metrics_type metrics;
  using _overall_health_type =
    float;
  _overall_health_type overall_health;
  using _issues_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _issues_type issues;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__metrics(
    const aura_msgs::msg::NetworkMetrics_<ContainerAllocator> & _arg)
  {
    this->metrics = _arg;
    return *this;
  }
  Type & set__overall_health(
    const float & _arg)
  {
    this->overall_health = _arg;
    return *this;
  }
  Type & set__issues(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->issues = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__srv__GetNetworkStatus_Response
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__srv__GetNetworkStatus_Response
    std::shared_ptr<aura_msgs::srv::GetNetworkStatus_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetNetworkStatus_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->metrics != other.metrics) {
      return false;
    }
    if (this->overall_health != other.overall_health) {
      return false;
    }
    if (this->issues != other.issues) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetNetworkStatus_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetNetworkStatus_Response_

// alias to use template instance with default allocator
using GetNetworkStatus_Response =
  aura_msgs::srv::GetNetworkStatus_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aura_msgs

namespace aura_msgs
{

namespace srv
{

struct GetNetworkStatus
{
  using Request = aura_msgs::srv::GetNetworkStatus_Request;
  using Response = aura_msgs::srv::GetNetworkStatus_Response;
};

}  // namespace srv

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__STRUCT_HPP_
