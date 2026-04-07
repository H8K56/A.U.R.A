// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_
#define AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/action/detail/execute_mission__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Goal_max_duration_sec
{
public:
  explicit Init_ExecuteMission_Goal_max_duration_sec(::aura_msgs::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_Goal max_duration_sec(::aura_msgs::action::ExecuteMission_Goal::_max_duration_sec_type arg)
  {
    msg_.max_duration_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_target_coverage_percent
{
public:
  explicit Init_ExecuteMission_Goal_target_coverage_percent(::aura_msgs::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Goal_max_duration_sec target_coverage_percent(::aura_msgs::action::ExecuteMission_Goal::_target_coverage_percent_type arg)
  {
    msg_.target_coverage_percent = std::move(arg);
    return Init_ExecuteMission_Goal_max_duration_sec(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_target_altitude
{
public:
  explicit Init_ExecuteMission_Goal_target_altitude(::aura_msgs::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Goal_target_coverage_percent target_altitude(::aura_msgs::action::ExecuteMission_Goal::_target_altitude_type arg)
  {
    msg_.target_altitude = std::move(arg);
    return Init_ExecuteMission_Goal_target_coverage_percent(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_coverage_area_vertices
{
public:
  explicit Init_ExecuteMission_Goal_coverage_area_vertices(::aura_msgs::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Goal_target_altitude coverage_area_vertices(::aura_msgs::action::ExecuteMission_Goal::_coverage_area_vertices_type arg)
  {
    msg_.coverage_area_vertices = std::move(arg);
    return Init_ExecuteMission_Goal_target_altitude(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_mission_type
{
public:
  explicit Init_ExecuteMission_Goal_mission_type(::aura_msgs::action::ExecuteMission_Goal & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Goal_coverage_area_vertices mission_type(::aura_msgs::action::ExecuteMission_Goal::_mission_type_type arg)
  {
    msg_.mission_type = std::move(arg);
    return Init_ExecuteMission_Goal_coverage_area_vertices(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

class Init_ExecuteMission_Goal_mission_id
{
public:
  Init_ExecuteMission_Goal_mission_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_Goal_mission_type mission_id(::aura_msgs::action::ExecuteMission_Goal::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_ExecuteMission_Goal_mission_type(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_Goal>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_Goal_mission_id();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Result_total_connections_served
{
public:
  explicit Init_ExecuteMission_Result_total_connections_served(::aura_msgs::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_Result total_connections_served(::aura_msgs::action::ExecuteMission_Result::_total_connections_served_type arg)
  {
    msg_.total_connections_served = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_avg_network_quality
{
public:
  explicit Init_ExecuteMission_Result_avg_network_quality(::aura_msgs::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_total_connections_served avg_network_quality(::aura_msgs::action::ExecuteMission_Result::_avg_network_quality_type arg)
  {
    msg_.avg_network_quality = std::move(arg);
    return Init_ExecuteMission_Result_total_connections_served(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_total_time_sec
{
public:
  explicit Init_ExecuteMission_Result_total_time_sec(::aura_msgs::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_avg_network_quality total_time_sec(::aura_msgs::action::ExecuteMission_Result::_total_time_sec_type arg)
  {
    msg_.total_time_sec = std::move(arg);
    return Init_ExecuteMission_Result_avg_network_quality(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_coverage_achieved
{
public:
  explicit Init_ExecuteMission_Result_coverage_achieved(::aura_msgs::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_total_time_sec coverage_achieved(::aura_msgs::action::ExecuteMission_Result::_coverage_achieved_type arg)
  {
    msg_.coverage_achieved = std::move(arg);
    return Init_ExecuteMission_Result_total_time_sec(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_message
{
public:
  explicit Init_ExecuteMission_Result_message(::aura_msgs::action::ExecuteMission_Result & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Result_coverage_achieved message(::aura_msgs::action::ExecuteMission_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ExecuteMission_Result_coverage_achieved(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

class Init_ExecuteMission_Result_success
{
public:
  Init_ExecuteMission_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_Result_message success(::aura_msgs::action::ExecuteMission_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ExecuteMission_Result_message(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_Result>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_Result_success();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_Feedback_elapsed_time_sec
{
public:
  explicit Init_ExecuteMission_Feedback_elapsed_time_sec(::aura_msgs::action::ExecuteMission_Feedback & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_Feedback elapsed_time_sec(::aura_msgs::action::ExecuteMission_Feedback::_elapsed_time_sec_type arg)
  {
    msg_.elapsed_time_sec = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

class Init_ExecuteMission_Feedback_current_phase
{
public:
  explicit Init_ExecuteMission_Feedback_current_phase(::aura_msgs::action::ExecuteMission_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Feedback_elapsed_time_sec current_phase(::aura_msgs::action::ExecuteMission_Feedback::_current_phase_type arg)
  {
    msg_.current_phase = std::move(arg);
    return Init_ExecuteMission_Feedback_elapsed_time_sec(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

class Init_ExecuteMission_Feedback_drones_active
{
public:
  explicit Init_ExecuteMission_Feedback_drones_active(::aura_msgs::action::ExecuteMission_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Feedback_current_phase drones_active(::aura_msgs::action::ExecuteMission_Feedback::_drones_active_type arg)
  {
    msg_.drones_active = std::move(arg);
    return Init_ExecuteMission_Feedback_current_phase(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

class Init_ExecuteMission_Feedback_current_network_quality
{
public:
  explicit Init_ExecuteMission_Feedback_current_network_quality(::aura_msgs::action::ExecuteMission_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Feedback_drones_active current_network_quality(::aura_msgs::action::ExecuteMission_Feedback::_current_network_quality_type arg)
  {
    msg_.current_network_quality = std::move(arg);
    return Init_ExecuteMission_Feedback_drones_active(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

class Init_ExecuteMission_Feedback_current_coverage_percent
{
public:
  explicit Init_ExecuteMission_Feedback_current_coverage_percent(::aura_msgs::action::ExecuteMission_Feedback & msg)
  : msg_(msg)
  {}
  Init_ExecuteMission_Feedback_current_network_quality current_coverage_percent(::aura_msgs::action::ExecuteMission_Feedback::_current_coverage_percent_type arg)
  {
    msg_.current_coverage_percent = std::move(arg);
    return Init_ExecuteMission_Feedback_current_network_quality(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

class Init_ExecuteMission_Feedback_progress_percent
{
public:
  Init_ExecuteMission_Feedback_progress_percent()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_Feedback_current_coverage_percent progress_percent(::aura_msgs::action::ExecuteMission_Feedback::_progress_percent_type arg)
  {
    msg_.progress_percent = std::move(arg);
    return Init_ExecuteMission_Feedback_current_coverage_percent(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_Feedback>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_Feedback_progress_percent();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_SendGoal_Request_goal
{
public:
  explicit Init_ExecuteMission_SendGoal_Request_goal(::aura_msgs::action::ExecuteMission_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_SendGoal_Request goal(::aura_msgs::action::ExecuteMission_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_SendGoal_Request msg_;
};

class Init_ExecuteMission_SendGoal_Request_goal_id
{
public:
  Init_ExecuteMission_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_SendGoal_Request_goal goal_id(::aura_msgs::action::ExecuteMission_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteMission_SendGoal_Request_goal(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_SendGoal_Request>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_SendGoal_Request_goal_id();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_SendGoal_Response_stamp
{
public:
  explicit Init_ExecuteMission_SendGoal_Response_stamp(::aura_msgs::action::ExecuteMission_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_SendGoal_Response stamp(::aura_msgs::action::ExecuteMission_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_SendGoal_Response msg_;
};

class Init_ExecuteMission_SendGoal_Response_accepted
{
public:
  Init_ExecuteMission_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_SendGoal_Response_stamp accepted(::aura_msgs::action::ExecuteMission_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_ExecuteMission_SendGoal_Response_stamp(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_SendGoal_Response>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_SendGoal_Response_accepted();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_GetResult_Request_goal_id
{
public:
  Init_ExecuteMission_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aura_msgs::action::ExecuteMission_GetResult_Request goal_id(::aura_msgs::action::ExecuteMission_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_GetResult_Request>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_GetResult_Request_goal_id();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_GetResult_Response_result
{
public:
  explicit Init_ExecuteMission_GetResult_Response_result(::aura_msgs::action::ExecuteMission_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_GetResult_Response result(::aura_msgs::action::ExecuteMission_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_GetResult_Response msg_;
};

class Init_ExecuteMission_GetResult_Response_status
{
public:
  Init_ExecuteMission_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_GetResult_Response_result status(::aura_msgs::action::ExecuteMission_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ExecuteMission_GetResult_Response_result(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_GetResult_Response>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_GetResult_Response_status();
}

}  // namespace aura_msgs


namespace aura_msgs
{

namespace action
{

namespace builder
{

class Init_ExecuteMission_FeedbackMessage_feedback
{
public:
  explicit Init_ExecuteMission_FeedbackMessage_feedback(::aura_msgs::action::ExecuteMission_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::aura_msgs::action::ExecuteMission_FeedbackMessage feedback(::aura_msgs::action::ExecuteMission_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_FeedbackMessage msg_;
};

class Init_ExecuteMission_FeedbackMessage_goal_id
{
public:
  Init_ExecuteMission_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteMission_FeedbackMessage_feedback goal_id(::aura_msgs::action::ExecuteMission_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_ExecuteMission_FeedbackMessage_feedback(msg_);
  }

private:
  ::aura_msgs::action::ExecuteMission_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::action::ExecuteMission_FeedbackMessage>()
{
  return aura_msgs::action::builder::Init_ExecuteMission_FeedbackMessage_goal_id();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__BUILDER_HPP_
