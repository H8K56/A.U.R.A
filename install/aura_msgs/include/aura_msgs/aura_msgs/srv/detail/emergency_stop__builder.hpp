// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:srv/EmergencyStop.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__BUILDER_HPP_
#define AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/srv/detail/emergency_stop__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_EmergencyStop_Request_reason
{
public:
  explicit Init_EmergencyStop_Request_reason(::aura_msgs::srv::EmergencyStop_Request & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::EmergencyStop_Request reason(::aura_msgs::srv::EmergencyStop_Request::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Request msg_;
};

class Init_EmergencyStop_Request_stop_type
{
public:
  explicit Init_EmergencyStop_Request_stop_type(::aura_msgs::srv::EmergencyStop_Request & msg)
  : msg_(msg)
  {}
  Init_EmergencyStop_Request_reason stop_type(::aura_msgs::srv::EmergencyStop_Request::_stop_type_type arg)
  {
    msg_.stop_type = std::move(arg);
    return Init_EmergencyStop_Request_reason(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Request msg_;
};

class Init_EmergencyStop_Request_drone_id
{
public:
  Init_EmergencyStop_Request_drone_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EmergencyStop_Request_stop_type drone_id(::aura_msgs::srv::EmergencyStop_Request::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_EmergencyStop_Request_stop_type(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::EmergencyStop_Request>()
{
  return aura_msgs::srv::builder::Init_EmergencyStop_Request_drone_id();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace srv
{

namespace builder
{

class Init_EmergencyStop_Response_drones_affected
{
public:
  explicit Init_EmergencyStop_Response_drones_affected(::aura_msgs::srv::EmergencyStop_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::srv::EmergencyStop_Response drones_affected(::aura_msgs::srv::EmergencyStop_Response::_drones_affected_type arg)
  {
    msg_.drones_affected = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Response msg_;
};

class Init_EmergencyStop_Response_message
{
public:
  explicit Init_EmergencyStop_Response_message(::aura_msgs::srv::EmergencyStop_Response & msg)
  : msg_(msg)
  {}
  Init_EmergencyStop_Response_drones_affected message(::aura_msgs::srv::EmergencyStop_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_EmergencyStop_Response_drones_affected(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Response msg_;
};

class Init_EmergencyStop_Response_success
{
public:
  Init_EmergencyStop_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EmergencyStop_Response_message success(::aura_msgs::srv::EmergencyStop_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_EmergencyStop_Response_message(msg_);
  }

private:
  ::aura_msgs::srv::EmergencyStop_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::srv::EmergencyStop_Response>()
{
  return aura_msgs::srv::builder::Init_EmergencyStop_Response_success();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__BUILDER_HPP_
