// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__TRAITS_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/msg/detail/coverage_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'origin'
// Member 'priority_zone_centers'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CoverageMap & msg,
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

  // member: is_covered
  {
    if (msg.is_covered.size() == 0) {
      out << "is_covered: []";
    } else {
      out << "is_covered: [";
      size_t pending_items = msg.is_covered.size();
      for (auto item : msg.is_covered) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: is_target
  {
    if (msg.is_target.size() == 0) {
      out << "is_target: []";
    } else {
      out << "is_target: [";
      size_t pending_items = msg.is_target.size();
      for (auto item : msg.is_target) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: demand_level
  {
    if (msg.demand_level.size() == 0) {
      out << "demand_level: []";
    } else {
      out << "demand_level: [";
      size_t pending_items = msg.demand_level.size();
      for (auto item : msg.demand_level) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: coverage_quality
  {
    if (msg.coverage_quality.size() == 0) {
      out << "coverage_quality: []";
    } else {
      out << "coverage_quality: [";
      size_t pending_items = msg.coverage_quality.size();
      for (auto item : msg.coverage_quality) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: priority_zone_centers
  {
    if (msg.priority_zone_centers.size() == 0) {
      out << "priority_zone_centers: []";
    } else {
      out << "priority_zone_centers: [";
      size_t pending_items = msg.priority_zone_centers.size();
      for (auto item : msg.priority_zone_centers) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: priority_zone_radii
  {
    if (msg.priority_zone_radii.size() == 0) {
      out << "priority_zone_radii: []";
    } else {
      out << "priority_zone_radii: [";
      size_t pending_items = msg.priority_zone_radii.size();
      for (auto item : msg.priority_zone_radii) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: priority_zone_weights
  {
    if (msg.priority_zone_weights.size() == 0) {
      out << "priority_zone_weights: []";
    } else {
      out << "priority_zone_weights: [";
      size_t pending_items = msg.priority_zone_weights.size();
      for (auto item : msg.priority_zone_weights) {
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
  const CoverageMap & msg,
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

  // member: is_covered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.is_covered.size() == 0) {
      out << "is_covered: []\n";
    } else {
      out << "is_covered:\n";
      for (auto item : msg.is_covered) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: is_target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.is_target.size() == 0) {
      out << "is_target: []\n";
    } else {
      out << "is_target:\n";
      for (auto item : msg.is_target) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: demand_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.demand_level.size() == 0) {
      out << "demand_level: []\n";
    } else {
      out << "demand_level:\n";
      for (auto item : msg.demand_level) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: coverage_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.coverage_quality.size() == 0) {
      out << "coverage_quality: []\n";
    } else {
      out << "coverage_quality:\n";
      for (auto item : msg.coverage_quality) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: priority_zone_centers
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.priority_zone_centers.size() == 0) {
      out << "priority_zone_centers: []\n";
    } else {
      out << "priority_zone_centers:\n";
      for (auto item : msg.priority_zone_centers) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: priority_zone_radii
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.priority_zone_radii.size() == 0) {
      out << "priority_zone_radii: []\n";
    } else {
      out << "priority_zone_radii:\n";
      for (auto item : msg.priority_zone_radii) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: priority_zone_weights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.priority_zone_weights.size() == 0) {
      out << "priority_zone_weights: []\n";
    } else {
      out << "priority_zone_weights:\n";
      for (auto item : msg.priority_zone_weights) {
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

inline std::string to_yaml(const CoverageMap & msg, bool use_flow_style = false)
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
  const aura_msgs::msg::CoverageMap & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::msg::CoverageMap & msg)
{
  return aura_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::msg::CoverageMap>()
{
  return "aura_msgs::msg::CoverageMap";
}

template<>
inline const char * name<aura_msgs::msg::CoverageMap>()
{
  return "aura_msgs/msg/CoverageMap";
}

template<>
struct has_fixed_size<aura_msgs::msg::CoverageMap>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::msg::CoverageMap>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::msg::CoverageMap>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__TRAITS_HPP_
