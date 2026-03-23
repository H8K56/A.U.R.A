// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/trajectory_broadcast__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_TrajectoryBroadcast_goal_reached
{
public:
  explicit Init_TrajectoryBroadcast_goal_reached(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::TrajectoryBroadcast goal_reached(::aura_msgs::msg::TrajectoryBroadcast::_goal_reached_type arg)
  {
    msg_.goal_reached = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_goal_position
{
public:
  explicit Init_TrajectoryBroadcast_goal_position(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_goal_reached goal_position(::aura_msgs::msg::TrajectoryBroadcast::_goal_position_type arg)
  {
    msg_.goal_position = std::move(arg);
    return Init_TrajectoryBroadcast_goal_reached(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_clearance
{
public:
  explicit Init_TrajectoryBroadcast_clearance(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_goal_position clearance(::aura_msgs::msg::TrajectoryBroadcast::_clearance_type arg)
  {
    msg_.clearance = std::move(arg);
    return Init_TrajectoryBroadcast_goal_position(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_max_velocity
{
public:
  explicit Init_TrajectoryBroadcast_max_velocity(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_clearance max_velocity(::aura_msgs::msg::TrajectoryBroadcast::_max_velocity_type arg)
  {
    msg_.max_velocity = std::move(arg);
    return Init_TrajectoryBroadcast_clearance(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_is_valid
{
public:
  explicit Init_TrajectoryBroadcast_is_valid(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_max_velocity is_valid(::aura_msgs::msg::TrajectoryBroadcast::_is_valid_type arg)
  {
    msg_.is_valid = std::move(arg);
    return Init_TrajectoryBroadcast_max_velocity(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_num_pieces
{
public:
  explicit Init_TrajectoryBroadcast_num_pieces(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_is_valid num_pieces(::aura_msgs::msg::TrajectoryBroadcast::_num_pieces_type arg)
  {
    msg_.num_pieces = std::move(arg);
    return Init_TrajectoryBroadcast_is_valid(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_total_duration
{
public:
  explicit Init_TrajectoryBroadcast_total_duration(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_num_pieces total_duration(::aura_msgs::msg::TrajectoryBroadcast::_total_duration_type arg)
  {
    msg_.total_duration = std::move(arg);
    return Init_TrajectoryBroadcast_num_pieces(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_time_allocation
{
public:
  explicit Init_TrajectoryBroadcast_time_allocation(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_total_duration time_allocation(::aura_msgs::msg::TrajectoryBroadcast::_time_allocation_type arg)
  {
    msg_.time_allocation = std::move(arg);
    return Init_TrajectoryBroadcast_total_duration(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_waypoints
{
public:
  explicit Init_TrajectoryBroadcast_waypoints(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_time_allocation waypoints(::aura_msgs::msg::TrajectoryBroadcast::_waypoints_type arg)
  {
    msg_.waypoints = std::move(arg);
    return Init_TrajectoryBroadcast_time_allocation(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_start_time
{
public:
  explicit Init_TrajectoryBroadcast_start_time(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_waypoints start_time(::aura_msgs::msg::TrajectoryBroadcast::_start_time_type arg)
  {
    msg_.start_time = std::move(arg);
    return Init_TrajectoryBroadcast_waypoints(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_drone_id
{
public:
  explicit Init_TrajectoryBroadcast_drone_id(::aura_msgs::msg::TrajectoryBroadcast & msg)
  : msg_(msg)
  {}
  Init_TrajectoryBroadcast_start_time drone_id(::aura_msgs::msg::TrajectoryBroadcast::_drone_id_type arg)
  {
    msg_.drone_id = std::move(arg);
    return Init_TrajectoryBroadcast_start_time(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

class Init_TrajectoryBroadcast_timestamp
{
public:
  Init_TrajectoryBroadcast_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TrajectoryBroadcast_drone_id timestamp(::aura_msgs::msg::TrajectoryBroadcast::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_TrajectoryBroadcast_drone_id(msg_);
  }

private:
  ::aura_msgs::msg::TrajectoryBroadcast msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::TrajectoryBroadcast>()
{
  return aura_msgs::msg::builder::Init_TrajectoryBroadcast_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__BUILDER_HPP_
