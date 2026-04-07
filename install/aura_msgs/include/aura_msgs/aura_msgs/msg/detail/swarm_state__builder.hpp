// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__SWARM_STATE__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__SWARM_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/swarm_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_SwarmState_drones
{
public:
  explicit Init_SwarmState_drones(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::SwarmState drones(::aura_msgs::msg::SwarmState::_drones_type arg)
  {
    msg_.drones = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_backhaul_connected
{
public:
  explicit Init_SwarmState_backhaul_connected(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_drones backhaul_connected(::aura_msgs::msg::SwarmState::_backhaul_connected_type arg)
  {
    msg_.backhaul_connected = std::move(arg);
    return Init_SwarmState_drones(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_mesh_connected
{
public:
  explicit Init_SwarmState_mesh_connected(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_backhaul_connected mesh_connected(::aura_msgs::msg::SwarmState::_mesh_connected_type arg)
  {
    msg_.mesh_connected = std::move(arg);
    return Init_SwarmState_backhaul_connected(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_packet_loss_percent
{
public:
  explicit Init_SwarmState_packet_loss_percent(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_mesh_connected packet_loss_percent(::aura_msgs::msg::SwarmState::_packet_loss_percent_type arg)
  {
    msg_.packet_loss_percent = std::move(arg);
    return Init_SwarmState_mesh_connected(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_avg_latency_ms
{
public:
  explicit Init_SwarmState_avg_latency_ms(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_packet_loss_percent avg_latency_ms(::aura_msgs::msg::SwarmState::_avg_latency_ms_type arg)
  {
    msg_.avg_latency_ms = std::move(arg);
    return Init_SwarmState_packet_loss_percent(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_avg_throughput_mbps
{
public:
  explicit Init_SwarmState_avg_throughput_mbps(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_avg_latency_ms avg_throughput_mbps(::aura_msgs::msg::SwarmState::_avg_throughput_mbps_type arg)
  {
    msg_.avg_throughput_mbps = std::move(arg);
    return Init_SwarmState_avg_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_coverage_quality
{
public:
  explicit Init_SwarmState_coverage_quality(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_avg_throughput_mbps coverage_quality(::aura_msgs::msg::SwarmState::_coverage_quality_type arg)
  {
    msg_.coverage_quality = std::move(arg);
    return Init_SwarmState_avg_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_coverage_percent
{
public:
  explicit Init_SwarmState_coverage_percent(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_coverage_quality coverage_percent(::aura_msgs::msg::SwarmState::_coverage_percent_type arg)
  {
    msg_.coverage_percent = std::move(arg);
    return Init_SwarmState_coverage_quality(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_mission_state
{
public:
  explicit Init_SwarmState_mission_state(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_coverage_percent mission_state(::aura_msgs::msg::SwarmState::_mission_state_type arg)
  {
    msg_.mission_state = std::move(arg);
    return Init_SwarmState_coverage_percent(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_num_leaves
{
public:
  explicit Init_SwarmState_num_leaves(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_mission_state num_leaves(::aura_msgs::msg::SwarmState::_num_leaves_type arg)
  {
    msg_.num_leaves = std::move(arg);
    return Init_SwarmState_mission_state(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_num_hubs
{
public:
  explicit Init_SwarmState_num_hubs(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_num_leaves num_hubs(::aura_msgs::msg::SwarmState::_num_hubs_type arg)
  {
    msg_.num_hubs = std::move(arg);
    return Init_SwarmState_num_leaves(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_num_drones_active
{
public:
  explicit Init_SwarmState_num_drones_active(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_num_hubs num_drones_active(::aura_msgs::msg::SwarmState::_num_drones_active_type arg)
  {
    msg_.num_drones_active = std::move(arg);
    return Init_SwarmState_num_hubs(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_num_drones_total
{
public:
  explicit Init_SwarmState_num_drones_total(::aura_msgs::msg::SwarmState & msg)
  : msg_(msg)
  {}
  Init_SwarmState_num_drones_active num_drones_total(::aura_msgs::msg::SwarmState::_num_drones_total_type arg)
  {
    msg_.num_drones_total = std::move(arg);
    return Init_SwarmState_num_drones_active(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

class Init_SwarmState_timestamp
{
public:
  Init_SwarmState_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SwarmState_num_drones_total timestamp(::aura_msgs::msg::SwarmState::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_SwarmState_num_drones_total(msg_);
  }

private:
  ::aura_msgs::msg::SwarmState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::SwarmState>()
{
  return aura_msgs::msg::builder::Init_SwarmState_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__SWARM_STATE__BUILDER_HPP_
