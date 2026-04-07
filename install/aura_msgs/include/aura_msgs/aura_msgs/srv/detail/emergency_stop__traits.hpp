// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:srv/EmergencyStop.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__TRAITS_HPP_
#define AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/srv/detail/emergency_stop__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EmergencyStop_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: drone_id
  {
    out << "drone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.drone_id, out);
    out << ", ";
  }

  // member: stop_type
  {
    out << "stop_type: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_type, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EmergencyStop_Request & msg,
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

  // member: stop_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stop_type: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_type, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EmergencyStop_Request & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::EmergencyStop_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::EmergencyStop_Request & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::EmergencyStop_Request>()
{
  return "aura_msgs::srv::EmergencyStop_Request";
}

template<>
inline const char * name<aura_msgs::srv::EmergencyStop_Request>()
{
  return "aura_msgs/srv/EmergencyStop_Request";
}

template<>
struct has_fixed_size<aura_msgs::srv::EmergencyStop_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::EmergencyStop_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::EmergencyStop_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EmergencyStop_Response & msg,
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

  // member: drones_affected
  {
    out << "drones_affected: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_affected, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EmergencyStop_Response & msg,
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

  // member: drones_affected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drones_affected: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_affected, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EmergencyStop_Response & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::EmergencyStop_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::EmergencyStop_Response & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::EmergencyStop_Response>()
{
  return "aura_msgs::srv::EmergencyStop_Response";
}

template<>
inline const char * name<aura_msgs::srv::EmergencyStop_Response>()
{
  return "aura_msgs/srv/EmergencyStop_Response";
}

template<>
struct has_fixed_size<aura_msgs::srv::EmergencyStop_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::EmergencyStop_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::EmergencyStop_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::srv::EmergencyStop>()
{
  return "aura_msgs::srv::EmergencyStop";
}

template<>
inline const char * name<aura_msgs::srv::EmergencyStop>()
{
  return "aura_msgs/srv/EmergencyStop";
}

template<>
struct has_fixed_size<aura_msgs::srv::EmergencyStop>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::srv::EmergencyStop_Request>::value &&
    has_fixed_size<aura_msgs::srv::EmergencyStop_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::srv::EmergencyStop>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::srv::EmergencyStop_Request>::value &&
    has_bounded_size<aura_msgs::srv::EmergencyStop_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::srv::EmergencyStop>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::srv::EmergencyStop_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::srv::EmergencyStop_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__SRV__DETAIL__EMERGENCY_STOP__TRAITS_HPP_
