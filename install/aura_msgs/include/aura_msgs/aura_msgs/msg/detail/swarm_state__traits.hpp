// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/SwarmState.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__SWARM_STATE__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__SWARM_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/swarm_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'drones'
#include "aura_msgs/msg/detail/drone_state__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SwarmState & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: num_drones_total
  {
    out << "num_drones_total: ";
    rosidl_generator_traits::value_to_yaml(msg.num_drones_total, out);
    out << ", ";
  }

  // member: num_drones_active
  {
    out << "num_drones_active: ";
    rosidl_generator_traits::value_to_yaml(msg.num_drones_active, out);
    out << ", ";
  }

  // member: num_hubs
  {
    out << "num_hubs: ";
    rosidl_generator_traits::value_to_yaml(msg.num_hubs, out);
    out << ", ";
  }

  // member: num_leaves
  {
    out << "num_leaves: ";
    rosidl_generator_traits::value_to_yaml(msg.num_leaves, out);
    out << ", ";
  }

  // member: mission_state
  {
    out << "mission_state: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_state, out);
    out << ", ";
  }

  // member: coverage_percent
  {
    out << "coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_percent, out);
    out << ", ";
  }

  // member: coverage_quality
  {
    out << "coverage_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_quality, out);
    out << ", ";
  }

  // member: avg_throughput_mbps
  {
    out << "avg_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_throughput_mbps, out);
    out << ", ";
  }

  // member: avg_latency_ms
  {
    out << "avg_latency_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_latency_ms, out);
    out << ", ";
  }

  // member: packet_loss_percent
  {
    out << "packet_loss_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.packet_loss_percent, out);
    out << ", ";
  }

  // member: mesh_connected
  {
    out << "mesh_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.mesh_connected, out);
    out << ", ";
  }

  // member: backhaul_connected
  {
    out << "backhaul_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_connected, out);
    out << ", ";
  }

  // member: drones
  {
    if (msg.drones.size() == 0) {
      out << "drones: []";
    } else {
      out << "drones: [";
      size_t pending_items = msg.drones.size();
      for (auto item : msg.drones) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SwarmState & msg,
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

  // member: num_drones_total
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_drones_total: ";
    rosidl_generator_traits::value_to_yaml(msg.num_drones_total, out);
    out << "\n";
  }

  // member: num_drones_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_drones_active: ";
    rosidl_generator_traits::value_to_yaml(msg.num_drones_active, out);
    out << "\n";
  }

  // member: num_hubs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_hubs: ";
    rosidl_generator_traits::value_to_yaml(msg.num_hubs, out);
    out << "\n";
  }

  // member: num_leaves
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_leaves: ";
    rosidl_generator_traits::value_to_yaml(msg.num_leaves, out);
    out << "\n";
  }

  // member: mission_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_state: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_state, out);
    out << "\n";
  }

  // member: coverage_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_percent, out);
    out << "\n";
  }

  // member: coverage_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_quality, out);
    out << "\n";
  }

  // member: avg_throughput_mbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avg_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_throughput_mbps, out);
    out << "\n";
  }

  // member: avg_latency_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avg_latency_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_latency_ms, out);
    out << "\n";
  }

  // member: packet_loss_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "packet_loss_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.packet_loss_percent, out);
    out << "\n";
  }

  // member: mesh_connected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mesh_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.mesh_connected, out);
    out << "\n";
  }

  // member: backhaul_connected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backhaul_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_connected, out);
    out << "\n";
  }

  // member: drones
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.drones.size() == 0) {
      out << "drones: []\n";
    } else {
      out << "drones:\n";
      for (auto item : msg.drones) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SwarmState & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::SwarmState & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::SwarmState & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::SwarmState>()
{
  return "aura_msgs::msg::SwarmState";
}

template<>
inline const char * name<aura_msgs::msg::SwarmState>()
{
  return "aura_msgs/msg/SwarmState";
}

template<>
struct has_fixed_size<aura_msgs::msg::SwarmState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::msg::SwarmState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::msg::SwarmState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__SWARM_STATE__TRAITS_HPP_
