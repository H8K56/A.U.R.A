// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/network_metrics__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_NetworkMetrics_backhaul_latency_ms
{
public:
  explicit Init_NetworkMetrics_backhaul_latency_ms(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::NetworkMetrics backhaul_latency_ms(::aura_msgs::msg::NetworkMetrics::_backhaul_latency_ms_type arg)
  {
    msg_.backhaul_latency_ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_backhaul_throughput_mbps
{
public:
  explicit Init_NetworkMetrics_backhaul_throughput_mbps(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_backhaul_latency_ms backhaul_throughput_mbps(::aura_msgs::msg::NetworkMetrics::_backhaul_throughput_mbps_type arg)
  {
    msg_.backhaul_throughput_mbps = std::move(arg);
    return Init_NetworkMetrics_backhaul_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_backhaul_active
{
public:
  explicit Init_NetworkMetrics_backhaul_active(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_backhaul_throughput_mbps backhaul_active(::aura_msgs::msg::NetworkMetrics::_backhaul_active_type arg)
  {
    msg_.backhaul_active = std::move(arg);
    return Init_NetworkMetrics_backhaul_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_mesh_connected
{
public:
  explicit Init_NetworkMetrics_mesh_connected(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_backhaul_active mesh_connected(::aura_msgs::msg::NetworkMetrics::_mesh_connected_type arg)
  {
    msg_.mesh_connected = std::move(arg);
    return Init_NetworkMetrics_backhaul_active(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_link_rssi_dbm
{
public:
  explicit Init_NetworkMetrics_link_rssi_dbm(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_mesh_connected link_rssi_dbm(::aura_msgs::msg::NetworkMetrics::_link_rssi_dbm_type arg)
  {
    msg_.link_rssi_dbm = std::move(arg);
    return Init_NetworkMetrics_mesh_connected(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_link_latency_ms
{
public:
  explicit Init_NetworkMetrics_link_latency_ms(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_link_rssi_dbm link_latency_ms(::aura_msgs::msg::NetworkMetrics::_link_latency_ms_type arg)
  {
    msg_.link_latency_ms = std::move(arg);
    return Init_NetworkMetrics_link_rssi_dbm(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_link_throughput_mbps
{
public:
  explicit Init_NetworkMetrics_link_throughput_mbps(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_link_latency_ms link_throughput_mbps(::aura_msgs::msg::NetworkMetrics::_link_throughput_mbps_type arg)
  {
    msg_.link_throughput_mbps = std::move(arg);
    return Init_NetworkMetrics_link_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_link_to_drone
{
public:
  explicit Init_NetworkMetrics_link_to_drone(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_link_throughput_mbps link_to_drone(::aura_msgs::msg::NetworkMetrics::_link_to_drone_type arg)
  {
    msg_.link_to_drone = std::move(arg);
    return Init_NetworkMetrics_link_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_link_from_drone
{
public:
  explicit Init_NetworkMetrics_link_from_drone(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_link_to_drone link_from_drone(::aura_msgs::msg::NetworkMetrics::_link_from_drone_type arg)
  {
    msg_.link_from_drone = std::move(arg);
    return Init_NetworkMetrics_link_to_drone(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_packet_loss_percent
{
public:
  explicit Init_NetworkMetrics_packet_loss_percent(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_link_from_drone packet_loss_percent(::aura_msgs::msg::NetworkMetrics::_packet_loss_percent_type arg)
  {
    msg_.packet_loss_percent = std::move(arg);
    return Init_NetworkMetrics_link_from_drone(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_avg_latency_ms
{
public:
  explicit Init_NetworkMetrics_avg_latency_ms(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_packet_loss_percent avg_latency_ms(::aura_msgs::msg::NetworkMetrics::_avg_latency_ms_type arg)
  {
    msg_.avg_latency_ms = std::move(arg);
    return Init_NetworkMetrics_packet_loss_percent(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_avg_throughput_mbps
{
public:
  explicit Init_NetworkMetrics_avg_throughput_mbps(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_avg_latency_ms avg_throughput_mbps(::aura_msgs::msg::NetworkMetrics::_avg_throughput_mbps_type arg)
  {
    msg_.avg_throughput_mbps = std::move(arg);
    return Init_NetworkMetrics_avg_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_avg_signal_strength_dbm
{
public:
  explicit Init_NetworkMetrics_avg_signal_strength_dbm(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_avg_throughput_mbps avg_signal_strength_dbm(::aura_msgs::msg::NetworkMetrics::_avg_signal_strength_dbm_type arg)
  {
    msg_.avg_signal_strength_dbm = std::move(arg);
    return Init_NetworkMetrics_avg_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_total_coverage_percent
{
public:
  explicit Init_NetworkMetrics_total_coverage_percent(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_avg_signal_strength_dbm total_coverage_percent(::aura_msgs::msg::NetworkMetrics::_total_coverage_percent_type arg)
  {
    msg_.total_coverage_percent = std::move(arg);
    return Init_NetworkMetrics_avg_signal_strength_dbm(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_coverage_mask
{
public:
  explicit Init_NetworkMetrics_coverage_mask(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_total_coverage_percent coverage_mask(::aura_msgs::msg::NetworkMetrics::_coverage_mask_type arg)
  {
    msg_.coverage_mask = std::move(arg);
    return Init_NetworkMetrics_total_coverage_percent(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_latency_ms
{
public:
  explicit Init_NetworkMetrics_latency_ms(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_coverage_mask latency_ms(::aura_msgs::msg::NetworkMetrics::_latency_ms_type arg)
  {
    msg_.latency_ms = std::move(arg);
    return Init_NetworkMetrics_coverage_mask(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_throughput_mbps
{
public:
  explicit Init_NetworkMetrics_throughput_mbps(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_latency_ms throughput_mbps(::aura_msgs::msg::NetworkMetrics::_throughput_mbps_type arg)
  {
    msg_.throughput_mbps = std::move(arg);
    return Init_NetworkMetrics_latency_ms(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_signal_strength_dbm
{
public:
  explicit Init_NetworkMetrics_signal_strength_dbm(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_throughput_mbps signal_strength_dbm(::aura_msgs::msg::NetworkMetrics::_signal_strength_dbm_type arg)
  {
    msg_.signal_strength_dbm = std::move(arg);
    return Init_NetworkMetrics_throughput_mbps(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_origin
{
public:
  explicit Init_NetworkMetrics_origin(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_signal_strength_dbm origin(::aura_msgs::msg::NetworkMetrics::_origin_type arg)
  {
    msg_.origin = std::move(arg);
    return Init_NetworkMetrics_signal_strength_dbm(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_cell_size_meters
{
public:
  explicit Init_NetworkMetrics_cell_size_meters(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_origin cell_size_meters(::aura_msgs::msg::NetworkMetrics::_cell_size_meters_type arg)
  {
    msg_.cell_size_meters = std::move(arg);
    return Init_NetworkMetrics_origin(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_grid_size_y
{
public:
  explicit Init_NetworkMetrics_grid_size_y(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_cell_size_meters grid_size_y(::aura_msgs::msg::NetworkMetrics::_grid_size_y_type arg)
  {
    msg_.grid_size_y = std::move(arg);
    return Init_NetworkMetrics_cell_size_meters(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_grid_size_x
{
public:
  explicit Init_NetworkMetrics_grid_size_x(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_grid_size_y grid_size_x(::aura_msgs::msg::NetworkMetrics::_grid_size_x_type arg)
  {
    msg_.grid_size_x = std::move(arg);
    return Init_NetworkMetrics_grid_size_y(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_timestamp
{
public:
  explicit Init_NetworkMetrics_timestamp(::aura_msgs::msg::NetworkMetrics & msg)
  : msg_(msg)
  {}
  Init_NetworkMetrics_grid_size_x timestamp(::aura_msgs::msg::NetworkMetrics::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_NetworkMetrics_grid_size_x(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

class Init_NetworkMetrics_header
{
public:
  Init_NetworkMetrics_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NetworkMetrics_timestamp header(::aura_msgs::msg::NetworkMetrics::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_NetworkMetrics_timestamp(msg_);
  }

private:
  ::aura_msgs::msg::NetworkMetrics msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::NetworkMetrics>()
{
  return aura_msgs::msg::builder::Init_NetworkMetrics_header();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__BUILDER_HPP_
