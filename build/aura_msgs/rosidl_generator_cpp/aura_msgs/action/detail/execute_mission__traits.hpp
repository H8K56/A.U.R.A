// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aura_msgs:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__TRAITS_HPP_
#define AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aura_msgs/action/detail/execute_mission__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'coverage_area_vertices'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: mission_id
  {
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << ", ";
  }

  // member: mission_type
  {
    out << "mission_type: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_type, out);
    out << ", ";
  }

  // member: coverage_area_vertices
  {
    if (msg.coverage_area_vertices.size() == 0) {
      out << "coverage_area_vertices: []";
    } else {
      out << "coverage_area_vertices: [";
      size_t pending_items = msg.coverage_area_vertices.size();
      for (auto item : msg.coverage_area_vertices) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: target_altitude
  {
    out << "target_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.target_altitude, out);
    out << ", ";
  }

  // member: target_coverage_percent
  {
    out << "target_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.target_coverage_percent, out);
    out << ", ";
  }

  // member: max_duration_sec
  {
    out << "max_duration_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.max_duration_sec, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mission_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << "\n";
  }

  // member: mission_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_type: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_type, out);
    out << "\n";
  }

  // member: coverage_area_vertices
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.coverage_area_vertices.size() == 0) {
      out << "coverage_area_vertices: []\n";
    } else {
      out << "coverage_area_vertices:\n";
      for (auto item : msg.coverage_area_vertices) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: target_altitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_altitude: ";
    rosidl_generator_traits::value_to_yaml(msg.target_altitude, out);
    out << "\n";
  }

  // member: target_coverage_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.target_coverage_percent, out);
    out << "\n";
  }

  // member: max_duration_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_duration_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.max_duration_sec, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_Goal & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_Goal>()
{
  return "aura_msgs::action::ExecuteMission_Goal";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_Goal>()
{
  return "aura_msgs/action/ExecuteMission_Goal";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_Result & msg,
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

  // member: coverage_achieved
  {
    out << "coverage_achieved: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_achieved, out);
    out << ", ";
  }

  // member: total_time_sec
  {
    out << "total_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.total_time_sec, out);
    out << ", ";
  }

  // member: avg_network_quality
  {
    out << "avg_network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_network_quality, out);
    out << ", ";
  }

  // member: total_connections_served
  {
    out << "total_connections_served: ";
    rosidl_generator_traits::value_to_yaml(msg.total_connections_served, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_Result & msg,
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

  // member: coverage_achieved
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage_achieved: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_achieved, out);
    out << "\n";
  }

  // member: total_time_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.total_time_sec, out);
    out << "\n";
  }

  // member: avg_network_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avg_network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.avg_network_quality, out);
    out << "\n";
  }

  // member: total_connections_served
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_connections_served: ";
    rosidl_generator_traits::value_to_yaml(msg.total_connections_served, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_Result & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_Result>()
{
  return "aura_msgs::action::ExecuteMission_Result";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_Result>()
{
  return "aura_msgs/action/ExecuteMission_Result";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: progress_percent
  {
    out << "progress_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percent, out);
    out << ", ";
  }

  // member: current_coverage_percent
  {
    out << "current_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.current_coverage_percent, out);
    out << ", ";
  }

  // member: current_network_quality
  {
    out << "current_network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.current_network_quality, out);
    out << ", ";
  }

  // member: drones_active
  {
    out << "drones_active: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_active, out);
    out << ", ";
  }

  // member: current_phase
  {
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
    out << ", ";
  }

  // member: elapsed_time_sec
  {
    out << "elapsed_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_time_sec, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: progress_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percent, out);
    out << "\n";
  }

  // member: current_coverage_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_coverage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.current_coverage_percent, out);
    out << "\n";
  }

  // member: current_network_quality
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_network_quality: ";
    rosidl_generator_traits::value_to_yaml(msg.current_network_quality, out);
    out << "\n";
  }

  // member: drones_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drones_active: ";
    rosidl_generator_traits::value_to_yaml(msg.drones_active, out);
    out << "\n";
  }

  // member: current_phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
    out << "\n";
  }

  // member: elapsed_time_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "elapsed_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_time_sec, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_Feedback & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_Feedback>()
{
  return "aura_msgs::action::ExecuteMission_Feedback";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_Feedback>()
{
  return "aura_msgs/action/ExecuteMission_Feedback";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "aura_msgs/action/detail/execute_mission__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_SendGoal_Request & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_SendGoal_Request>()
{
  return "aura_msgs::action::ExecuteMission_SendGoal_Request";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_SendGoal_Request>()
{
  return "aura_msgs/action/ExecuteMission_SendGoal_Request";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<aura_msgs::action::ExecuteMission_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<aura_msgs::action::ExecuteMission_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_SendGoal_Response & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_SendGoal_Response>()
{
  return "aura_msgs::action::ExecuteMission_SendGoal_Response";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_SendGoal_Response>()
{
  return "aura_msgs/action/ExecuteMission_SendGoal_Response";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_SendGoal>()
{
  return "aura_msgs::action::ExecuteMission_SendGoal";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_SendGoal>()
{
  return "aura_msgs/action/ExecuteMission_SendGoal";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::action::ExecuteMission_SendGoal_Request>::value &&
    has_fixed_size<aura_msgs::action::ExecuteMission_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::action::ExecuteMission_SendGoal_Request>::value &&
    has_bounded_size<aura_msgs::action::ExecuteMission_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::action::ExecuteMission_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::action::ExecuteMission_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::action::ExecuteMission_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_GetResult_Request & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_GetResult_Request>()
{
  return "aura_msgs::action::ExecuteMission_GetResult_Request";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_GetResult_Request>()
{
  return "aura_msgs/action/ExecuteMission_GetResult_Request";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "aura_msgs/action/detail/execute_mission__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_GetResult_Response & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_GetResult_Response>()
{
  return "aura_msgs::action::ExecuteMission_GetResult_Response";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_GetResult_Response>()
{
  return "aura_msgs/action/ExecuteMission_GetResult_Response";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<aura_msgs::action::ExecuteMission_Result>::value> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<aura_msgs::action::ExecuteMission_Result>::value> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_GetResult>()
{
  return "aura_msgs::action::ExecuteMission_GetResult";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_GetResult>()
{
  return "aura_msgs/action/ExecuteMission_GetResult";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<aura_msgs::action::ExecuteMission_GetResult_Request>::value &&
    has_fixed_size<aura_msgs::action::ExecuteMission_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<aura_msgs::action::ExecuteMission_GetResult_Request>::value &&
    has_bounded_size<aura_msgs::action::ExecuteMission_GetResult_Response>::value
  >
{
};

template<>
struct is_service<aura_msgs::action::ExecuteMission_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<aura_msgs::action::ExecuteMission_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aura_msgs::action::ExecuteMission_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "aura_msgs/action/detail/execute_mission__traits.hpp"

namespace aura_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteMission_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteMission_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteMission_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace aura_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aura_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aura_msgs::action::ExecuteMission_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  aura_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aura_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const aura_msgs::action::ExecuteMission_FeedbackMessage & msg)
{
  return aura_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<aura_msgs::action::ExecuteMission_FeedbackMessage>()
{
  return "aura_msgs::action::ExecuteMission_FeedbackMessage";
}

template<>
inline const char * name<aura_msgs::action::ExecuteMission_FeedbackMessage>()
{
  return "aura_msgs/action/ExecuteMission_FeedbackMessage";
}

template<>
struct has_fixed_size<aura_msgs::action::ExecuteMission_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<aura_msgs::action::ExecuteMission_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<aura_msgs::action::ExecuteMission_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<aura_msgs::action::ExecuteMission_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<aura_msgs::action::ExecuteMission_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<aura_msgs::action::ExecuteMission>
  : std::true_type
{
};

template<>
struct is_action_goal<aura_msgs::action::ExecuteMission_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<aura_msgs::action::ExecuteMission_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<aura_msgs::action::ExecuteMission_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__TRAITS_HPP_
