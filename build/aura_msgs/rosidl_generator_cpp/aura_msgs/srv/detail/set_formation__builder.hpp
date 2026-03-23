// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:srv/SetFormation.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__SET_FORMATION__BUILDER_HPP_
#define AURA_MSGS__SRV__DETAIL__SET_FORMATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/srv/detail/set_formation__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_SetFormation_Request_heading_rad
{
public:
  explicit Init_SetFormation_Request_heading_rad(::aura_msgs::srv::SetFormation_Request & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::SetFormation_Request heading_rad(::aura_msgs::srv::SetFormation_Request::_heading_rad_type arg)
  {
    msg_.heading_rad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

class Init_SetFormation_Request_center
{
public:
  explicit Init_SetFormation_Request_center(::aura_msgs::srv::SetFormation_Request & msg)
  : msg_(msg)
  {}
  Init_SetFormation_Request_heading_rad center(::aura_msgs::srv::SetFormation_Request::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_SetFormation_Request_heading_rad(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

class Init_SetFormation_Request_altitude_meters
{
public:
  explicit Init_SetFormation_Request_altitude_meters(::aura_msgs::srv::SetFormation_Request & msg)
  : msg_(msg)
  {}
  Init_SetFormation_Request_center altitude_meters(::aura_msgs::srv::SetFormation_Request::_altitude_meters_type arg)
  {
    msg_.altitude_meters = std::move(arg);
    return Init_SetFormation_Request_center(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

class Init_SetFormation_Request_spacing_meters
{
public:
  explicit Init_SetFormation_Request_spacing_meters(::aura_msgs::srv::SetFormation_Request & msg)
  : msg_(msg)
  {}
  Init_SetFormation_Request_altitude_meters spacing_meters(::aura_msgs::srv::SetFormation_Request::_spacing_meters_type arg)
  {
    msg_.spacing_meters = std::move(arg);
    return Init_SetFormation_Request_altitude_meters(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

class Init_SetFormation_Request_custom_positions
{
public:
  explicit Init_SetFormation_Request_custom_positions(::aura_msgs::srv::SetFormation_Request & msg)
  : msg_(msg)
  {}
  Init_SetFormation_Request_spacing_meters custom_positions(::aura_msgs::srv::SetFormation_Request::_custom_positions_type arg)
  {
    msg_.custom_positions = std::move(arg);
    return Init_SetFormation_Request_spacing_meters(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

class Init_SetFormation_Request_formation_type
{
public:
  Init_SetFormation_Request_formation_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetFormation_Request_custom_positions formation_type(::aura_msgs::srv::SetFormation_Request::_formation_type_type arg)
  {
    msg_.formation_type = std::move(arg);
    return Init_SetFormation_Request_custom_positions(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::SetFormation_Request>()
{
  return aura_msgs::srv::builder::Init_SetFormation_Request_formation_type();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_SetFormation_Response_estimated_transition_time
{
public:
  explicit Init_SetFormation_Response_estimated_transition_time(::aura_msgs::srv::SetFormation_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::SetFormation_Response estimated_transition_time(::aura_msgs::srv::SetFormation_Response::_estimated_transition_time_type arg)
  {
    msg_.estimated_transition_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Response msg_;
};

class Init_SetFormation_Response_message
{
public:
  explicit Init_SetFormation_Response_message(::aura_msgs::srv::SetFormation_Response & msg)
  : msg_(msg)
  {}
  Init_SetFormation_Response_estimated_transition_time message(::aura_msgs::srv::SetFormation_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_SetFormation_Response_estimated_transition_time(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Response msg_;
};

class Init_SetFormation_Response_success
{
public:
  Init_SetFormation_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetFormation_Response_message success(::aura_msgs::srv::SetFormation_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetFormation_Response_message(msg_);
  }

private:
  ::aura_msgs::srv::SetFormation_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::SetFormation_Response>()
{
  return aura_msgs::srv::builder::Init_SetFormation_Response_success();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__SET_FORMATION__BUILDER_HPP_
