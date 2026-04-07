// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/CoverageGoal.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/coverage_goal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_CoverageGoal_required_coverage_radius
{
public:
  explicit Init_CoverageGoal_required_coverage_radius(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::CoverageGoal required_coverage_radius(::aura_msgs::msg::CoverageGoal::_required_coverage_radius_type arg)
  {
    msg_.required_coverage_radius = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_required_throughput_mbps
{
public:
  explicit Init_CoverageGoal_required_throughput_mbps(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_required_coverage_radius required_throughput_mbps(::aura_msgs::msg::CoverageGoal::_required_throughput_mbps_type arg)
  {
    msg_.required_throughput_mbps = std::move(arg);
    return Init_CoverageGoal_required_coverage_radius(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_max_velocity
{
public:
  explicit Init_CoverageGoal_max_velocity(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_required_throughput_mbps max_velocity(::aura_msgs::msg::CoverageGoal::_max_velocity_type arg)
  {
    msg_.max_velocity = std::move(arg);
    return Init_CoverageGoal_required_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_max_altitude
{
public:
  explicit Init_CoverageGoal_max_altitude(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_max_velocity max_altitude(::aura_msgs::msg::CoverageGoal::_max_altitude_type arg)
  {
    msg_.max_altitude = std::move(arg);
    return Init_CoverageGoal_max_velocity(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_min_altitude
{
public:
  explicit Init_CoverageGoal_min_altitude(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_max_altitude min_altitude(::aura_msgs::msg::CoverageGoal::_min_altitude_type arg)
  {
    msg_.min_altitude = std::move(arg);
    return Init_CoverageGoal_max_altitude(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_priority
{
public:
  explicit Init_CoverageGoal_priority(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_min_altitude priority(::aura_msgs::msg::CoverageGoal::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_CoverageGoal_min_altitude(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_formation_type
{
public:
  explicit Init_CoverageGoal_formation_type(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_priority formation_type(::aura_msgs::msg::CoverageGoal::_formation_type_type arg)
  {
    msg_.formation_type = std::move(arg);
    return Init_CoverageGoal_priority(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_desired_arrival_time
{
public:
  explicit Init_CoverageGoal_desired_arrival_time(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_formation_type desired_arrival_time(::aura_msgs::msg::CoverageGoal::_desired_arrival_time_type arg)
  {
    msg_.desired_arrival_time = std::move(arg);
    return Init_CoverageGoal_formation_type(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_position
{
public:
  explicit Init_CoverageGoal_position(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_desired_arrival_time position(::aura_msgs::msg::CoverageGoal::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_CoverageGoal_desired_arrival_time(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_drone_id
{
public:
  explicit Init_CoverageGoal_drone_id(::aura_msgs::msg::CoverageGoal & msg)
  : msg_(msg)
  {}
  Init_CoverageGoal_position drone_id(::aura_msgs::msg::CoverageGoal::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_CoverageGoal_position(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

class Init_CoverageGoal_timestamp
{
public:
  Init_CoverageGoal_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CoverageGoal_drone_id timestamp(::aura_msgs::msg::CoverageGoal::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_CoverageGoal_drone_id(msg_);
  }

private:
  ::aura_msgs::msg::CoverageGoal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::CoverageGoal>()
{
  return aura_msgs::msg::builder::Init_CoverageGoal_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__BUILDER_HPP_
