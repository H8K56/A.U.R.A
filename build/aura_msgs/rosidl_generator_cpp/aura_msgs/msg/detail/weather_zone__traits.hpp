// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/weather_zone__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
// Member 'start_time'
// Member 'end_time'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'center'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const WeatherZone & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: zone_id
  {
    out << "zone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.zone_id, out);
    out << ", ";
  }

  // member: center
  {
    out << "center: ";
    to_flow_style_yaml(msg.center, out);
    out << ", ";
  }

  // member: radius_meters
  {
    out << "radius_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_meters, out);
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

  // member: weather_type
  {
    out << "weather_type: ";
    rosidl_generator_traits::value_to_yaml(msg.weather_type, out);
    out << ", ";
  }

  // member: severity
  {
    out << "severity: ";
    rosidl_generator_traits::value_to_yaml(msg.severity, out);
    out << ", ";
  }

  // member: wind_speed_ms
  {
    out << "wind_speed_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.wind_speed_ms, out);
    out << ", ";
  }

  // member: wind_direction_rad
  {
    out << "wind_direction_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.wind_direction_rad, out);
    out << ", ";
  }

  // member: signal_attenuation_db
  {
    out << "signal_attenuation_db: ";
    rosidl_generator_traits::value_to_yaml(msg.signal_attenuation_db, out);
    out << ", ";
  }

  // member: no_fly
  {
    out << "no_fly: ";
    rosidl_generator_traits::value_to_yaml(msg.no_fly, out);
    out << ", ";
  }

  // member: start_time
  {
    out << "start_time: ";
    to_flow_style_yaml(msg.start_time, out);
    out << ", ";
  }

  // member: end_time
  {
    out << "end_time: ";
    to_flow_style_yaml(msg.end_time, out);
    out << ", ";
  }

  // member: is_active
  {
    out << "is_active: ";
    rosidl_generator_traits::value_to_yaml(msg.is_active, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WeatherZone & msg,
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

  // member: zone_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zone_id: ";
    rosidl_generator_traits::value_to_yaml(msg.zone_id, out);
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

  // member: radius_meters
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "radius_meters: ";
    rosidl_generator_traits::value_to_yaml(msg.radius_meters, out);
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

  // member: weather_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weather_type: ";
    rosidl_generator_traits::value_to_yaml(msg.weather_type, out);
    out << "\n";
  }

  // member: severity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "severity: ";
    rosidl_generator_traits::value_to_yaml(msg.severity, out);
    out << "\n";
  }

  // member: wind_speed_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wind_speed_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.wind_speed_ms, out);
    out << "\n";
  }

  // member: wind_direction_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wind_direction_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.wind_direction_rad, out);
    out << "\n";
  }

  // member: signal_attenuation_db
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "signal_attenuation_db: ";
    rosidl_generator_traits::value_to_yaml(msg.signal_attenuation_db, out);
    out << "\n";
  }

  // member: no_fly
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "no_fly: ";
    rosidl_generator_traits::value_to_yaml(msg.no_fly, out);
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

  // member: end_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "end_time:\n";
    to_block_style_yaml(msg.end_time, out, indentation + 2);
  }

  // member: is_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_active: ";
    rosidl_generator_traits::value_to_yaml(msg.is_active, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WeatherZone & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::WeatherZone & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::WeatherZone & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::WeatherZone>()
{
  return "aura_msgs::msg::WeatherZone";
}

template<>
inline const char * name<aura_msgs::msg::WeatherZone>()
{
  return "aura_msgs/msg/WeatherZone";
}

template<>
struct has_fixed_size<aura_msgs::msg::WeatherZone>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value && has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<aura_msgs::msg::WeatherZone>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value && has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<aura_msgs::msg::WeatherZone>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__TRAITS_HPP_
