// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/NetworkMetrics.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/network_metrics__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'origin'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const NetworkMetrics & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: grid_size_x
  {
    out << "grid_size_x: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size_x, out);
    out << ", ";
  }

  // member: grid_size_y
  {
    out << "grid_size_y: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size_y, out);
    out << ", ";
  }

  // member: cell_size_meters
  {
    out << "cell_size_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_size_meters, out);
    out << ", ";
  }

  // member: origin
  {
    out << "origin: ";
    to_flow_style_yaml(msg.origin, out);
    out << ", ";
  }

  // member: signal_strength_dbm
  {
    if (msg.signal_strength_dbm.size() == 0) {
      out << "signal_strength_dbm: []";
    } else {
      out << "signal_strength_dbm: [";
      size_t pending_items = msg.signal_strength_dbm.size();
      for (auto item : msg.signal_strength_dbm) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: throughput_mbps
  {
    if (msg.throughput_mbps.size() == 0) {
      out << "throughput_mbps: []";
    } else {
      out << "throughput_mbps: [";
      size_t pending_items = msg.throughput_mbps.size();
      for (auto item : msg.throughput_mbps) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: latency_ms
  {
    if (msg.latency_ms.size() == 0) {
      out << "latency_ms: []";
    } else {
      out << "latency_ms: [";
      size_t pending_items = msg.latency_ms.size();
      for (auto item : msg.latency_ms) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: coverage_mask
  {
    if (msg.coverage_mask.size() == 0) {
      out << "coverage_mask: []";
    } else {
      out << "coverage_mask: [";
      size_t pending_items = msg.coverage_mask.size();
      for (auto item : msg.coverage_mask) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: total_coverage_percent
  {
    out << "total_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.total_coverage_percent, out);
    out << ", ";
  }

  // member: avg_signal_strength_dbm
  {
    out << "avg_signal_strength_dbm: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_signal_strength_dbm, out);
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

  // member: link_from_drone
  {
    if (msg.link_from_drone.size() == 0) {
      out << "link_from_drone: []";
    } else {
      out << "link_from_drone: [";
      size_t pending_items = msg.link_from_drone.size();
      for (auto item : msg.link_from_drone) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: link_to_drone
  {
    if (msg.link_to_drone.size() == 0) {
      out << "link_to_drone: []";
    } else {
      out << "link_to_drone: [";
      size_t pending_items = msg.link_to_drone.size();
      for (auto item : msg.link_to_drone) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: link_throughput_mbps
  {
    if (msg.link_throughput_mbps.size() == 0) {
      out << "link_throughput_mbps: []";
    } else {
      out << "link_throughput_mbps: [";
      size_t pending_items = msg.link_throughput_mbps.size();
      for (auto item : msg.link_throughput_mbps) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: link_latency_ms
  {
    if (msg.link_latency_ms.size() == 0) {
      out << "link_latency_ms: []";
    } else {
      out << "link_latency_ms: [";
      size_t pending_items = msg.link_latency_ms.size();
      for (auto item : msg.link_latency_ms) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: link_rssi_dbm
  {
    if (msg.link_rssi_dbm.size() == 0) {
      out << "link_rssi_dbm: []";
    } else {
      out << "link_rssi_dbm: [";
      size_t pending_items = msg.link_rssi_dbm.size();
      for (auto item : msg.link_rssi_dbm) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: backhaul_active
  {
    out << "backhaul_active: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_active, out);
    out << ", ";
  }

  // member: backhaul_throughput_mbps
  {
    out << "backhaul_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_throughput_mbps, out);
    out << ", ";
  }

  // member: backhaul_latency_ms
  {
    out << "backhaul_latency_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_latency_ms, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NetworkMetrics & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp:\n";
    to_block_style_yaml(msg.timestamp, out, indentation + 2);
  }

  // member: grid_size_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_size_x: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size_x, out);
    out << "\n";
  }

  // member: grid_size_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grid_size_y: ";
    rosidl_generator_traits::value_to_yaml(msg.grid_size_y, out);
    out << "\n";
  }

  // member: cell_size_meters
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cell_size_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.cell_size_meters, out);
    out << "\n";
  }

  // member: origin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "origin:\n";
    to_block_style_yaml(msg.origin, out, indentation + 2);
  }

  // member: signal_strength_dbm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.signal_strength_dbm.size() == 0) {
      out << "signal_strength_dbm: []\n";
    } else {
      out << "signal_strength_dbm:\n";
      for (auto item : msg.signal_strength_dbm) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: throughput_mbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.throughput_mbps.size() == 0) {
      out << "throughput_mbps: []\n";
    } else {
      out << "throughput_mbps:\n";
      for (auto item : msg.throughput_mbps) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: latency_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.latency_ms.size() == 0) {
      out << "latency_ms: []\n";
    } else {
      out << "latency_ms:\n";
      for (auto item : msg.latency_ms) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: coverage_mask
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.coverage_mask.size() == 0) {
      out << "coverage_mask: []\n";
    } else {
      out << "coverage_mask:\n";
      for (auto item : msg.coverage_mask) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: total_coverage_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.total_coverage_percent, out);
    out << "\n";
  }

  // member: avg_signal_strength_dbm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avg_signal_strength_dbm: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_signal_strength_dbm, out);
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

  // member: link_from_drone
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.link_from_drone.size() == 0) {
      out << "link_from_drone: []\n";
    } else {
      out << "link_from_drone:\n";
      for (auto item : msg.link_from_drone) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: link_to_drone
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.link_to_drone.size() == 0) {
      out << "link_to_drone: []\n";
    } else {
      out << "link_to_drone:\n";
      for (auto item : msg.link_to_drone) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: link_throughput_mbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.link_throughput_mbps.size() == 0) {
      out << "link_throughput_mbps: []\n";
    } else {
      out << "link_throughput_mbps:\n";
      for (auto item : msg.link_throughput_mbps) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: link_latency_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.link_latency_ms.size() == 0) {
      out << "link_latency_ms: []\n";
    } else {
      out << "link_latency_ms:\n";
      for (auto item : msg.link_latency_ms) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: link_rssi_dbm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.link_rssi_dbm.size() == 0) {
      out << "link_rssi_dbm: []\n";
    } else {
      out << "link_rssi_dbm:\n";
      for (auto item : msg.link_rssi_dbm) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: backhaul_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backhaul_active: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_active, out);
    out << "\n";
  }

  // member: backhaul_throughput_mbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backhaul_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_throughput_mbps, out);
    out << "\n";
  }

  // member: backhaul_latency_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backhaul_latency_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.backhaul_latency_ms, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NetworkMetrics & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::NetworkMetrics & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::NetworkMetrics & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::NetworkMetrics>()
{
  return "aura_msgs::msg::NetworkMetrics";
}

template<>
inline const char * name<aura_msgs::msg::NetworkMetrics>()
{
  return "aura_msgs/msg/NetworkMetrics";
}

template<>
struct has_fixed_size<aura_msgs::msg::NetworkMetrics>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::msg::NetworkMetrics>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::msg::NetworkMetrics>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__NETWORK_METRICS__TRAITS_HPP_
