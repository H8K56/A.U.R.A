// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__BUILDER_HPP_
#define AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/srv/detail/get_network_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_GetNetworkStatus_Request_include_link_details
{
public:
  explicit Init_GetNetworkStatus_Request_include_link_details(::aura_msgs::srv::GetNetworkStatus_Request & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::GetNetworkStatus_Request include_link_details(::aura_msgs::srv::GetNetworkStatus_Request::_include_link_details_type arg)
  {
    msg_.include_link_details = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Request msg_;
};

class Init_GetNetworkStatus_Request_include_coverage_map
{
public:
  Init_GetNetworkStatus_Request_include_coverage_map()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetNetworkStatus_Request_include_link_details include_coverage_map(::aura_msgs::srv::GetNetworkStatus_Request::_include_coverage_map_type arg)
  {
    msg_.include_coverage_map = std::move(arg);
    return Init_GetNetworkStatus_Request_include_link_details(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::GetNetworkStatus_Request>()
{
  return aura_msgs::srv::builder::Init_GetNetworkStatus_Request_include_coverage_map();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_GetNetworkStatus_Response_issues
{
public:
  explicit Init_GetNetworkStatus_Response_issues(::aura_msgs::srv::GetNetworkStatus_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::GetNetworkStatus_Response issues(::aura_msgs::srv::GetNetworkStatus_Response::_issues_type arg)
  {
    msg_.issues = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Response msg_;
};

class Init_GetNetworkStatus_Response_overall_health
{
public:
  explicit Init_GetNetworkStatus_Response_overall_health(::aura_msgs::srv::GetNetworkStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetNetworkStatus_Response_issues overall_health(::aura_msgs::srv::GetNetworkStatus_Response::_overall_health_type arg)
  {
    msg_.overall_health = std::move(arg);
    return Init_GetNetworkStatus_Response_issues(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Response msg_;
};

class Init_GetNetworkStatus_Response_metrics
{
public:
  explicit Init_GetNetworkStatus_Response_metrics(::aura_msgs::srv::GetNetworkStatus_Response & msg)
  : msg_(msg)
  {}
  Init_GetNetworkStatus_Response_overall_health metrics(::aura_msgs::srv::GetNetworkStatus_Response::_metrics_type arg)
  {
    msg_.metrics = std::move(arg);
    return Init_GetNetworkStatus_Response_overall_health(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Response msg_;
};

class Init_GetNetworkStatus_Response_success
{
public:
  Init_GetNetworkStatus_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetNetworkStatus_Response_metrics success(::aura_msgs::srv::GetNetworkStatus_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetNetworkStatus_Response_metrics(msg_);
  }

private:
  ::aura_msgs::srv::GetNetworkStatus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::GetNetworkStatus_Response>()
{
  return aura_msgs::srv::builder::Init_GetNetworkStatus_Response_success();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__BUILDER_HPP_
