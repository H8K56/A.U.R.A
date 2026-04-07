// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/mission_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_MissionStatus_drones_failed
{
public:
  explicit Init_MissionStatus_drones_failed(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::MissionStatus drones_failed(::aura_msgs::msg::MissionStatus::_drones_failed_type arg)
  {
    msg_.drones_failed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_drones_degraded
{
public:
  explicit Init_MissionStatus_drones_degraded(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_drones_failed drones_degraded(::aura_msgs::msg::MissionStatus::_drones_degraded_type arg)
  {
    msg_.drones_degraded = std::move(arg);
    return Init_MissionStatus_drones_failed(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_drones_operational
{
public:
  explicit Init_MissionStatus_drones_operational(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_drones_degraded drones_operational(::aura_msgs::msg::MissionStatus::_drones_operational_type arg)
  {
    msg_.drones_operational = std::move(arg);
    return Init_MissionStatus_drones_degraded(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_alert_severities
{
public:
  explicit Init_MissionStatus_alert_severities(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_drones_operational alert_severities(::aura_msgs::msg::MissionStatus::_alert_severities_type arg)
  {
    msg_.alert_severities = std::move(arg);
    return Init_MissionStatus_drones_operational(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_active_alerts
{
public:
  explicit Init_MissionStatus_active_alerts(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_alert_severities active_alerts(::aura_msgs::msg::MissionStatus::_active_alerts_type arg)
  {
    msg_.active_alerts = std::move(arg);
    return Init_MissionStatus_alert_severities(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_data_transferred_mb
{
public:
  explicit Init_MissionStatus_data_transferred_mb(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_active_alerts data_transferred_mb(::aura_msgs::msg::MissionStatus::_data_transferred_mb_type arg)
  {
    msg_.data_transferred_mb = std::move(arg);
    return Init_MissionStatus_active_alerts(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_connections_established
{
public:
  explicit Init_MissionStatus_connections_established(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_data_transferred_mb connections_established(::aura_msgs::msg::MissionStatus::_connections_established_type arg)
  {
    msg_.connections_established = std::move(arg);
    return Init_MissionStatus_data_transferred_mb(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_network_quality
{
public:
  explicit Init_MissionStatus_network_quality(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_connections_established network_quality(::aura_msgs::msg::MissionStatus::_network_quality_type arg)
  {
    msg_.network_quality = std::move(arg);
    return Init_MissionStatus_connections_established(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_coverage_achieved
{
public:
  explicit Init_MissionStatus_coverage_achieved(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_network_quality coverage_achieved(::aura_msgs::msg::MissionStatus::_coverage_achieved_type arg)
  {
    msg_.coverage_achieved = std::move(arg);
    return Init_MissionStatus_network_quality(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_estimated_remaining_sec
{
public:
  explicit Init_MissionStatus_estimated_remaining_sec(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_coverage_achieved estimated_remaining_sec(::aura_msgs::msg::MissionStatus::_estimated_remaining_sec_type arg)
  {
    msg_.estimated_remaining_sec = std::move(arg);
    return Init_MissionStatus_coverage_achieved(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_elapsed_time_sec
{
public:
  explicit Init_MissionStatus_elapsed_time_sec(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_estimated_remaining_sec elapsed_time_sec(::aura_msgs::msg::MissionStatus::_elapsed_time_sec_type arg)
  {
    msg_.elapsed_time_sec = std::move(arg);
    return Init_MissionStatus_estimated_remaining_sec(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_progress_percent
{
public:
  explicit Init_MissionStatus_progress_percent(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_elapsed_time_sec progress_percent(::aura_msgs::msg::MissionStatus::_progress_percent_type arg)
  {
    msg_.progress_percent = std::move(arg);
    return Init_MissionStatus_elapsed_time_sec(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_phase
{
public:
  explicit Init_MissionStatus_phase(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_progress_percent phase(::aura_msgs::msg::MissionStatus::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return Init_MissionStatus_progress_percent(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_mission_id
{
public:
  explicit Init_MissionStatus_mission_id(::aura_msgs::msg::MissionStatus & msg)
  : msg_(msg)
  {}
  Init_MissionStatus_phase mission_id(::aura_msgs::msg::MissionStatus::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_MissionStatus_phase(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

class Init_MissionStatus_timestamp
{
public:
  Init_MissionStatus_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MissionStatus_mission_id timestamp(::aura_msgs::msg::MissionStatus::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_MissionStatus_mission_id(msg_);
  }

private:
  ::aura_msgs::msg::MissionStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::MissionStatus>()
{
  return aura_msgs::msg::builder::Init_MissionStatus_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__MISSION_STATUS__BUILDER_HPP_
