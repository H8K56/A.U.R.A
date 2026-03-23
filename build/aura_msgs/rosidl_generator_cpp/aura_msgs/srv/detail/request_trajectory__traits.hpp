// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:srv/RequestTrajectory.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__TRAITS_HPP_
#define AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/srv/detail/request_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal_position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RequestTrajectory_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: drone_id
  {
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << ", ";
  }

  // member: goal_position
  {
    out << "goal_position: ";
    to_flow_style_yaml(msg.goal_position, out);
    out << ", ";
  }

  // member: max_velocity
  {
    out << "max_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.max_velocity, out);
    out << ", ";
  }

  // member: max_time
  {
    out << "max_time: ";
    rosidl_generator_traits::value_to_yaml(msg.max_time, out);
    out << ", ";
  }

  // member: avoid_weather_zones
  {
    out << "avoid_weather_zones: ";
    rosidl_generator_traits::value_to_yaml(msg.avoid_weather_zones, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RequestTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: drone_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
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

  // member: max_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.max_velocity, out);
    out << "\n";
  }

  // member: max_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_time: ";
    rosidl_generator_traits::value_to_yaml(msg.max_time, out);
    out << "\n";
  }

  // member: avoid_weather_zones
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avoid_weather_zones: ";
    rosidl_generator_traits::value_to_yaml(msg.avoid_weather_zones, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RequestTrajectory_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::srv::RequestTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::RequestTrajectory_Request & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::RequestTrajectory_Request>()
{
  return "aura_msgs::srv::RequestTrajectory_Request";
}

template<>
inline const char * name<aura_msgs::srv::RequestTrajectory_Request>()
{
  return "aura_msgs/srv/RequestTrajectory_Request";
}

template<>
struct has_fixed_size<aura_msgs::srv::RequestTrajectory_Request>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<aura_msgs::srv::RequestTrajectory_Request>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<aura_msgs::srv::RequestTrajectory_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'trajectory'
#include "aura_msgs/msg/detail/trajectory_broadcast__traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RequestTrajectory_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: trajectory
  {
    out << "trajectory: ";
    to_flow_style_yaml(msg.trajectory, out);
    out << ", ";
  }

  // member: estimated_time
  {
    out << "estimated_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_time, out);
    out << ", ";
  }

  // member: estimated_energy
  {
    out << "estimated_energy: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_energy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RequestTrajectory_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: trajectory
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trajectory:\n";
    to_block_style_yaml(msg.trajectory, out, indentation + 2);
  }

  // member: estimated_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_time, out);
    out << "\n";
  }

  // member: estimated_energy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_energy: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_energy, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RequestTrajectory_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::srv::RequestTrajectory_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::RequestTrajectory_Response & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::RequestTrajectory_Response>()
{
  return "aura_msgs::srv::RequestTrajectory_Response";
}

template<>
inline const char * name<aura_msgs::srv::RequestTrajectory_Response>()
{
  return "aura_msgs/srv/RequestTrajectory_Response";
}

template<>
struct has_fixed_size<aura_msgs::srv::RequestTrajectory_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::RequestTrajectory_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::RequestTrajectory_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::srv::RequestTrajectory>()
{
  return "aura_msgs::srv::RequestTrajectory";
}

template<>
inline const char * name<aura_msgs::srv::RequestTrajectory>()
{
  return "aura_msgs/srv/RequestTrajectory";
}

template<>
struct has_fixed_size<aura_msgs::srv::RequestTrajectory>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::srv::RequestTrajectory_Request>::value &&
    has_fixed_size<aura_msgs::srv::RequestTrajectory_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::srv::RequestTrajectory>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::srv::RequestTrajectory_Request>::value &&
    has_bounded_size<aura_msgs::srv::RequestTrajectory_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::srv::RequestTrajectory>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::srv::RequestTrajectory_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::srv::RequestTrajectory_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__SRV__DETAIL__REQUEST_TRAJECTORY__TRAITS_HPP_
