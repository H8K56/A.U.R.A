// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/mission_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MissionStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: mission_id
  {
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << ", ";
  }

  // member: phase
  {
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
    out << ", ";
  }

  // member: progress_percent
  {
    out << "progress_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percent, out);
    out << ", ";
  }

  // member: elapsed_time_sec
  {
    out << "elapsed_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_time_sec, out);
    out << ", ";
  }

  // member: estimated_remaining_sec
  {
    out << "estimated_remaining_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_remaining_sec, out);
    out << ", ";
  }

  // member: coverage_achieved
  {
    out << "coverage_achieved: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_achieved, out);
    out << ", ";
  }

  // member: network_quality
  {
    out << "network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.network_quality, out);
    out << ", ";
  }

  // member: connections_established
  {
    out << "connections_established: ";
    rosidl_generator_traits::value_to_yaml(msg.connections_established, out);
    out << ", ";
  }

  // member: data_transferred_mb
  {
    out << "data_transferred_mb: ";
    rosidl_generator_traits::value_to_yaml(msg.data_transferred_mb, out);
    out << ", ";
  }

  // member: active_alerts
  {
    if (msg.active_alerts.size() == 0) {
      out << "active_alerts: []";
    } else {
      out << "active_alerts: [";
      size_t pending_items = msg.active_alerts.size();
      for (auto item : msg.active_alerts) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: alert_severities
  {
    if (msg.alert_severities.size() == 0) {
      out << "alert_severities: []";
    } else {
      out << "alert_severities: [";
      size_t pending_items = msg.alert_severities.size();
      for (auto item : msg.alert_severities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: drones_operational
  {
    out << "drones_operational: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_operational, out);
    out << ", ";
  }

  // member: drones_degraded
  {
    out << "drones_degraded: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_degraded, out);
    out << ", ";
  }

  // member: drones_failed
  {
    out << "drones_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_failed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MissionStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp:\n";
    to_block_style_yaml(msg.timestamp, out, indentation + 2);
  }

  // member: mission_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << "\n";
  }

  // member: phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
    out << "\n";
  }

  // member: progress_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percent, out);
    out << "\n";
  }

  // member: elapsed_time_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "elapsed_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_time_sec, out);
    out << "\n";
  }

  // member: estimated_remaining_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_remaining_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_remaining_sec, out);
    out << "\n";
  }

  // member: coverage_achieved
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage_achieved: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_achieved, out);
    out << "\n";
  }

  // member: network_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.network_quality, out);
    out << "\n";
  }

  // member: connections_established
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "connections_established: ";
    rosidl_generator_traits::value_to_yaml(msg.connections_established, out);
    out << "\n";
  }

  // member: data_transferred_mb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_transferred_mb: ";
    rosidl_generator_traits::value_to_yaml(msg.data_transferred_mb, out);
    out << "\n";
  }

  // member: active_alerts
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.active_alerts.size() == 0) {
      out << "active_alerts: []\n";
    } else {
      out << "active_alerts:\n";
      for (auto item : msg.active_alerts) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: alert_severities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.alert_severities.size() == 0) {
      out << "alert_severities: []\n";
    } else {
      out << "alert_severities:\n";
      for (auto item : msg.alert_severities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: drones_operational
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drones_operational: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_operational, out);
    out << "\n";
  }

  // member: drones_degraded
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drones_degraded: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_degraded, out);
    out << "\n";
  }

  // member: drones_failed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drones_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_failed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MissionStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::msg::MissionStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::MissionStatus & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::MissionStatus>()
{
  return "aura_msgs::msg::MissionStatus";
}

template<>
inline const char * name<aura_msgs::msg::MissionStatus>()
{
  return "aura_msgs/msg/MissionStatus";
}

template<>
struct has_fixed_size<aura_msgs::msg::MissionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::msg::MissionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::msg::MissionStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_
