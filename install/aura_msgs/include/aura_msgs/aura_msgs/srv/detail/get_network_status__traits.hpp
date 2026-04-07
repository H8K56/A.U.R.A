// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:srv/GetNetworkStatus.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__TRAITS_HPP_
#define AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/srv/detail/get_network_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetNetworkStatus_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: include_coverage_map
  {
    out << "include_coverage_map: ";
    rosidl_generator_traits::value_to_yaml(msg.include_coverage_map, out);
    out << ", ";
  }

  // member: include_link_details
  {
    out << "include_link_details: ";
    rosidl_generator_traits::value_to_yaml(msg.include_link_details, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetNetworkStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: include_coverage_map
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "include_coverage_map: ";
    rosidl_generator_traits::value_to_yaml(msg.include_coverage_map, out);
    out << "\n";
  }

  // member: include_link_details
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "include_link_details: ";
    rosidl_generator_traits::value_to_yaml(msg.include_link_details, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetNetworkStatus_Request & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::GetNetworkStatus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::GetNetworkStatus_Request & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::GetNetworkStatus_Request>()
{
  return "aura_msgs::srv::GetNetworkStatus_Request";
}

template<>
inline const char * name<aura_msgs::srv::GetNetworkStatus_Request>()
{
  return "aura_msgs/srv/GetNetworkStatus_Request";
}

template<>
struct has_fixed_size<aura_msgs::srv::GetNetworkStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<aura_msgs::srv::GetNetworkStatus_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<aura_msgs::srv::GetNetworkStatus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'metrics'
#include "aura_msgs/msg/detail/network_metrics__traits.hpp"

namespace aura_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetNetworkStatus_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: metrics
  {
    out << "metrics: ";
    to_flow_style_yaml(msg.metrics, out);
    out << ", ";
  }

  // member: overall_health
  {
    out << "overall_health: ";
    rosidl_generator_traits::value_to_yaml(msg.overall_health, out);
    out << ", ";
  }

  // member: issues
  {
    if (msg.issues.size() == 0) {
      out << "issues: []";
    } else {
      out << "issues: [";
      size_t pending_items = msg.issues.size();
      for (auto item : msg.issues) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const GetNetworkStatus_Response & msg,
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

  // member: metrics
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "metrics:\n";
    to_block_style_yaml(msg.metrics, out, indentation + 2);
  }

  // member: overall_health
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overall_health: ";
    rosidl_generator_traits::value_to_yaml(msg.overall_health, out);
    out << "\n";
  }

  // member: issues
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.issues.size() == 0) {
      out << "issues: []\n";
    } else {
      out << "issues:\n";
      for (auto item : msg.issues) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetNetworkStatus_Response & msg, bool use_flow_style = false)
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
  const aura_msgs::srv::GetNetworkStatus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::srv::GetNetworkStatus_Response & msg)
{
  return aura_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::srv::GetNetworkStatus_Response>()
{
  return "aura_msgs::srv::GetNetworkStatus_Response";
}

template<>
inline const char * name<aura_msgs::srv::GetNetworkStatus_Response>()
{
  return "aura_msgs/srv/GetNetworkStatus_Response";
}

template<>
struct has_fixed_size<aura_msgs::srv::GetNetworkStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::srv::GetNetworkStatus_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::srv::GetNetworkStatus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::srv::GetNetworkStatus>()
{
  return "aura_msgs::srv::GetNetworkStatus";
}

template<>
inline const char * name<aura_msgs::srv::GetNetworkStatus>()
{
  return "aura_msgs/srv/GetNetworkStatus";
}

template<>
struct has_fixed_size<aura_msgs::srv::GetNetworkStatus>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::srv::GetNetworkStatus_Request>::value &&
    has_fixed_size<aura_msgs::srv::GetNetworkStatus_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::srv::GetNetworkStatus>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::srv::GetNetworkStatus_Request>::value &&
    has_bounded_size<aura_msgs::srv::GetNetworkStatus_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::srv::GetNetworkStatus>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::srv::GetNetworkStatus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::srv::GetNetworkStatus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__SRV__DETAIL__GET_NETWORK_STATUS__TRAITS_HPP_
