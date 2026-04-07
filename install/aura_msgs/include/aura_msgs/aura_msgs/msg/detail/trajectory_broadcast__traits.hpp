// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/TrajectoryBroadcast.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/trajectory_broadcast__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
// Member 'start_time'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'waypoints'
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const TrajectoryBroadcast & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: drone_id
  {
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << ", ";
  }

  // member: start_time
  {
    out << "start_time: ";
    to_flow_style_yaml(msg.start_time, out);
    out << ", ";
  }

  // member: waypoints
  {
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []";
    } else {
      out << "waypoints: [";
      size_t pending_items = msg.waypoints.size();
      for (auto item : msg.waypoints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: time_allocation
  {
    if (msg.time_allocation.size() == 0) {
      out << "time_allocation: []";
    } else {
      out << "time_allocation: [";
      size_t pending_items = msg.time_allocation.size();
      for (auto item : msg.time_allocation) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: total_duration
  {
    out << "total_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.total_duration, out);
    out << ", ";
  }

  // member: num_pieces
  {
    out << "num_pieces: ";
    rosidl_generator_traits::value_to_yaml(msg.num_pieces, out);
    out << ", ";
  }

  // member: is_valid
  {
    out << "is_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.is_valid, out);
    out << ", ";
  }

  // member: max_velocity
  {
    out << "max_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.max_velocity, out);
    out << ", ";
  }

  // member: clearance
  {
    out << "clearance: ";
    rosidl_generator_traits::value_to_yaml(msg.clearance, out);
    out << ", ";
  }

  // member: goal_position
  {
    out << "goal_position: ";
    to_flow_style_yaml(msg.goal_position, out);
    out << ", ";
  }

  // member: goal_reached
  {
    out << "goal_reached: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_reached, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TrajectoryBroadcast & msg,
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

  // member: drone_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << "\n";
  }

  // member: start_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_time:\n";
    to_block_style_yaml(msg.start_time, out, indentation + 2);
  }

  // member: waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []\n";
    } else {
      out << "waypoints:\n";
      for (auto item : msg.waypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: time_allocation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.time_allocation.size() == 0) {
      out << "time_allocation: []\n";
    } else {
      out << "time_allocation:\n";
      for (auto item : msg.time_allocation) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: total_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.total_duration, out);
    out << "\n";
  }

  // member: num_pieces
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_pieces: ";
    rosidl_generator_traits::value_to_yaml(msg.num_pieces, out);
    out << "\n";
  }

  // member: is_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.is_valid, out);
    out << "\n";
  }

  // member: max_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.max_velocity, out);
    out << "\n";
  }

  // member: clearance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "clearance: ";
    rosidl_generator_traits::value_to_yaml(msg.clearance, out);
    out << "\n";
  }

  // member: goal_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_position:\n";
    to_block_style_yaml(msg.goal_position, out, indentation + 2);
  }

  // member: goal_reached
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_reached: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_reached, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TrajectoryBroadcast & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::TrajectoryBroadcast & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::TrajectoryBroadcast & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::TrajectoryBroadcast>()
{
  return "aura_msgs::msg::TrajectoryBroadcast";
}

template<>
inline const char * name<aura_msgs::msg::TrajectoryBroadcast>()
{
  return "aura_msgs/msg/TrajectoryBroadcast";
}

template<>
struct has_fixed_size<aura_msgs::msg::TrajectoryBroadcast>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::msg::TrajectoryBroadcast>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::msg::TrajectoryBroadcast>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__TRAJECTORY_BROADCAST__TRAITS_HPP_
