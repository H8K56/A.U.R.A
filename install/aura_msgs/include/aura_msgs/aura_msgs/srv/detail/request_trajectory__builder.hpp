// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:srv/RequestTrajectory.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__BUILDER_HPP_
#define AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/srv/detail/request_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_RequestTrajectory_Request_avoid_weather_zones
{
public:
  explicit Init_RequestTrajectory_Request_avoid_weather_zones(::aura_msgs::srv::RequestTrajectory_Request & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::RequestTrajectory_Request avoid_weather_zones(::aura_msgs::srv::RequestTrajectory_Request::_avoid_weather_zones_type arg)
  {
    msg_.avoid_weather_zones = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Request msg_;
};

class Init_RequestTrajectory_Request_max_time
{
public:
  explicit Init_RequestTrajectory_Request_max_time(::aura_msgs::srv::RequestTrajectory_Request & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Request_avoid_weather_zones max_time(::aura_msgs::srv::RequestTrajectory_Request::_max_time_type arg)
  {
    msg_.max_time = std::move(arg);
    return Init_RequestTrajectory_Request_avoid_weather_zones(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Request msg_;
};

class Init_RequestTrajectory_Request_max_velocity
{
public:
  explicit Init_RequestTrajectory_Request_max_velocity(::aura_msgs::srv::RequestTrajectory_Request & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Request_max_time max_velocity(::aura_msgs::srv::RequestTrajectory_Request::_max_velocity_type arg)
  {
    msg_.max_velocity = std::move(arg);
    return Init_RequestTrajectory_Request_max_time(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Request msg_;
};

class Init_RequestTrajectory_Request_goal_position
{
public:
  explicit Init_RequestTrajectory_Request_goal_position(::aura_msgs::srv::RequestTrajectory_Request & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Request_max_velocity goal_position(::aura_msgs::srv::RequestTrajectory_Request::_goal_position_type arg)
  {
    msg_.goal_position = std::move(arg);
    return Init_RequestTrajectory_Request_max_velocity(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Request msg_;
};

class Init_RequestTrajectory_Request_drone_id
{
public:
  Init_RequestTrajectory_Request_drone_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RequestTrajectory_Request_goal_position drone_id(::aura_msgs::srv::RequestTrajectory_Request::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_RequestTrajectory_Request_goal_position(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::RequestTrajectory_Request>()
{
  return aura_msgs::srv::builder::Init_RequestTrajectory_Request_drone_id();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_RequestTrajectory_Response_estimated_energy
{
public:
  explicit Init_RequestTrajectory_Response_estimated_energy(::aura_msgs::srv::RequestTrajectory_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::RequestTrajectory_Response estimated_energy(::aura_msgs::srv::RequestTrajectory_Response::_estimated_energy_type arg)
  {
    msg_.estimated_energy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Response msg_;
};

class Init_RequestTrajectory_Response_estimated_time
{
public:
  explicit Init_RequestTrajectory_Response_estimated_time(::aura_msgs::srv::RequestTrajectory_Response & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Response_estimated_energy estimated_time(::aura_msgs::srv::RequestTrajectory_Response::_estimated_time_type arg)
  {
    msg_.estimated_time = std::move(arg);
    return Init_RequestTrajectory_Response_estimated_energy(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Response msg_;
};

class Init_RequestTrajectory_Response_trajectory
{
public:
  explicit Init_RequestTrajectory_Response_trajectory(::aura_msgs::srv::RequestTrajectory_Response & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Response_estimated_time trajectory(::aura_msgs::srv::RequestTrajectory_Response::_trajectory_type arg)
  {
    msg_.trajectory = std::move(arg);
    return Init_RequestTrajectory_Response_estimated_time(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Response msg_;
};

class Init_RequestTrajectory_Response_message
{
public:
  explicit Init_RequestTrajectory_Response_message(::aura_msgs::srv::RequestTrajectory_Response & msg)
  : msg_(msg)
  {}
  Init_RequestTrajectory_Response_trajectory message(::aura_msgs::srv::RequestTrajectory_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_RequestTrajectory_Response_trajectory(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Response msg_;
};

class Init_RequestTrajectory_Response_success
{
public:
  Init_RequestTrajectory_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RequestTrajectory_Response_message success(::aura_msgs::srv::RequestTrajectory_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_RequestTrajectory_Response_message(msg_);
  }

private:
  ::aura_msgs::srv::RequestTrajectory_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::RequestTrajectory_Response>()
{
  return aura_msgs::srv::builder::Init_RequestTrajectory_Response_success();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__BUILDER_HPP_
