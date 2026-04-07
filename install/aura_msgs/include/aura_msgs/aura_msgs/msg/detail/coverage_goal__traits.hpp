// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/CoverageGoal.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/coverage_goal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CoverageGoal & msg,
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

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: desired_arrival_time
  {
    out << "desired_arrival_time: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_arrival_time, out);
    out << ", ";
  }

  // member: formation_type
  {
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << ", ";
  }

  // member: priority
  {
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << ", ";
  }

  // member: min_altitude
  {
    out << "min_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.min_altitude, out);
    out << ", ";
  }

  // member: max_altitude
  {
    out << "max_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.max_altitude, out);
    out << ", ";
  }

  // member: max_velocity
  {
    out << "max_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.max_velocity, out);
    out << ", ";
  }

  // member: required_throughput_mbps
  {
    out << "required_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.required_throughput_mbps, out);
    out << ", ";
  }

  // member: required_coverage_radius
  {
    out << "required_coverage_radius: ";
    rosidl_generator_traits::value_to_yaml(msg.required_coverage_radius, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CoverageGoal & msg,
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

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: desired_arrival_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "desired_arrival_time: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_arrival_time, out);
    out << "\n";
  }

  // member: formation_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << "\n";
  }

  // member: priority
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << "\n";
  }

  // member: min_altitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.min_altitude, out);
    out << "\n";
  }

  // member: max_altitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.max_altitude, out);
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

  // member: required_throughput_mbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "required_throughput_mbps: ";
    rosidl_generator_traits::value_to_yaml(msg.required_throughput_mbps, out);
    out << "\n";
  }

  // member: required_coverage_radius
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "required_coverage_radius: ";
    rosidl_generator_traits::value_to_yaml(msg.required_coverage_radius, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CoverageGoal & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::CoverageGoal & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::CoverageGoal & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::CoverageGoal>()
{
  return "aura_msgs::msg::CoverageGoal";
}

template<>
inline const char * name<aura_msgs::msg::CoverageGoal>()
{
  return "aura_msgs/msg/CoverageGoal";
}

template<>
struct has_fixed_size<aura_msgs::msg::CoverageGoal>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value && has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<aura_msgs::msg::CoverageGoal>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value && has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<aura_msgs::msg::CoverageGoal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_GOAL__TRAITS_HPP_
