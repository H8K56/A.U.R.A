// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/DroneState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/drone_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_DroneState_connected_neighbors
{
public:
  explicit Init_DroneState_connected_neighbors(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::DroneState connected_neighbors(::aura_msgs::msg::DroneState::_connected_neighbors_type arg)
  {
    msg_.connected_neighbors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_latency_ms
{
public:
  explicit Init_DroneState_latency_ms(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_connected_neighbors latency_ms(::aura_msgs::msg::DroneState::_latency_ms_type arg)
  {
    msg_.latency_ms = std::move(arg);
    return Init_DroneState_connected_neighbors(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_throughput_mbps
{
public:
  explicit Init_DroneState_throughput_mbps(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_latency_ms throughput_mbps(::aura_msgs::msg::DroneState::_throughput_mbps_type arg)
  {
    msg_.throughput_mbps = std::move(arg);
    return Init_DroneState_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_num_satellites
{
public:
  explicit Init_DroneState_num_satellites(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_throughput_mbps num_satellites(::aura_msgs::msg::DroneState::_num_satellites_type arg)
  {
    msg_.num_satellites = std::move(arg);
    return Init_DroneState_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_gps_fix
{
public:
  explicit Init_DroneState_gps_fix(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_num_satellites gps_fix(::aura_msgs::msg::DroneState::_gps_fix_type arg)
  {
    msg_.gps_fix = std::move(arg);
    return Init_DroneState_num_satellites(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_signal_strength_dbm
{
public:
  explicit Init_DroneState_signal_strength_dbm(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_gps_fix signal_strength_dbm(::aura_msgs::msg::DroneState::_signal_strength_dbm_type arg)
  {
    msg_.signal_strength_dbm = std::move(arg);
    return Init_DroneState_gps_fix(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_battery_voltage
{
public:
  explicit Init_DroneState_battery_voltage(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_signal_strength_dbm battery_voltage(::aura_msgs::msg::DroneState::_battery_voltage_type arg)
  {
    msg_.battery_voltage = std::move(arg);
    return Init_DroneState_signal_strength_dbm(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_battery_percent
{
public:
  explicit Init_DroneState_battery_percent(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_battery_voltage battery_percent(::aura_msgs::msg::DroneState::_battery_percent_type arg)
  {
    msg_.battery_percent = std::move(arg);
    return Init_DroneState_battery_voltage(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_flight_mode
{
public:
  explicit Init_DroneState_flight_mode(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_battery_percent flight_mode(::aura_msgs::msg::DroneState::_flight_mode_type arg)
  {
    msg_.flight_mode = std::move(arg);
    return Init_DroneState_battery_percent(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_orientation
{
public:
  explicit Init_DroneState_orientation(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_flight_mode orientation(::aura_msgs::msg::DroneState::_orientation_type arg)
  {
    msg_.orientation = std::move(arg);
    return Init_DroneState_flight_mode(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_velocity
{
public:
  explicit Init_DroneState_velocity(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_orientation velocity(::aura_msgs::msg::DroneState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_DroneState_orientation(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_position
{
public:
  explicit Init_DroneState_position(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_velocity position(::aura_msgs::msg::DroneState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_DroneState_velocity(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_role
{
public:
  explicit Init_DroneState_role(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_position role(::aura_msgs::msg::DroneState::_role_type arg)
  {
    msg_.role = std::move(arg);
    return Init_DroneState_position(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_drone_id
{
public:
  explicit Init_DroneState_drone_id(::aura_msgs::msg::DroneState & msg)
  : msg_(msg)
  {}
  Init_DroneState_role drone_id(::aura_msgs::msg::DroneState::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_DroneState_role(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

class Init_DroneState_timestamp
{
public:
  Init_DroneState_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneState_drone_id timestamp(::aura_msgs::msg::DroneState::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_DroneState_drone_id(msg_);
  }

private:
  ::aura_msgs::msg::DroneState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::DroneState>()
{
  return aura_msgs::msg::builder::Init_DroneState_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__DRONE_STATE__BUILDER_HPP_
