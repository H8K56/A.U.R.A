// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:srv/SetFormation.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__SET_FORMATION__TRAITS_HPP_
#define AURA_MSGS__SRV__DETAIL__SET_FORMATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/srv/detail/set_formation__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'custom_positions'
// Member 'center'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetFormation_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: formation_type
  {
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << ", ";
  }

  // member: custom_positions
  {
    if (msg.custom_positions.size() == 0) {
      out << "custom_positions: []";
    } else {
      out << "custom_positions: [";
      size_t pending_items = msg.custom_positions.size();
      for (auto item : msg.custom_positions) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: spacing_meters
  {
    out << "spacing_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.spacing_meters, out);
    out << ", ";
  }

  // member: altitude_meters
  {
    out << "altitude_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_meters, out);
    out << ", ";
  }

  // member: center
  {
    out << "center: ";
    to_flow_style_yaml(msg.center, out);
    out << ", ";
  }

  // member: heading_rad
  {
    out << "heading_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_rad, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetFormation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: formation_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "formation_type: ";
    rosidl_generator_traits::value_to_yaml(msg.formation_type, out);
    out << "\n";
  }

  // member: custom_positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.custom_positions.size() == 0) {
      out << "custom_positions: []\n";
    } else {
      out << "custom_positions:\n";
      for (auto item : msg.custom_positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: spacing_meters
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spacing_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.spacing_meters, out);
    out << "\n";
  }

  // member: altitude_meters
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "altitude_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.altitude_meters, out);
    out << "\n";
  }

  // member: center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center:\n";
    to_block_style_yaml(msg.center, out, indentation + 2);
  }

  // member: heading_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.heading_rad, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetFormation_Request & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::SetFormation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::SetFormation_Request & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::SetFormation_Request>()
{
  return "aura_msgs::srv::SetFormation_Request";
}

template<>
inline const char * name<aura_msgs::srv::SetFormation_Request>()
{
  return "aura_msgs/srv/SetFormation_Request";
}

template<>
struct has_fixed_size<aura_msgs::srv::SetFormation_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::SetFormation_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::SetFormation_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetFormation_Response & msg,
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

  // member: estimated_transition_time
  {
    out << "estimated_transition_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_transition_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetFormation_Response & msg,
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

  // member: estimated_transition_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_transition_time: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_transition_time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetFormation_Response & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::SetFormation_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::SetFormation_Response & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::SetFormation_Response>()
{
  return "aura_msgs::srv::SetFormation_Response";
}

template<>
inline const char * name<aura_msgs::srv::SetFormation_Response>()
{
  return "aura_msgs/srv/SetFormation_Response";
}

template<>
struct has_fixed_size<aura_msgs::srv::SetFormation_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::SetFormation_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::SetFormation_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::srv::SetFormation>()
{
  return "aura_msgs::srv::SetFormation";
}

template<>
inline const char * name<aura_msgs::srv::SetFormation>()
{
  return "aura_msgs/srv/SetFormation";
}

template<>
struct has_fixed_size<aura_msgs::srv::SetFormation>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::srv::SetFormation_Request>::value &&
    has_fixed_size<aura_msgs::srv::SetFormation_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::srv::SetFormation>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::srv::SetFormation_Request>::value &&
    has_bounded_size<aura_msgs::srv::SetFormation_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::srv::SetFormation>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::srv::SetFormation_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::srv::SetFormation_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__SRV__DETAIL__SET_FORMATION__TRAITS_HPP_
