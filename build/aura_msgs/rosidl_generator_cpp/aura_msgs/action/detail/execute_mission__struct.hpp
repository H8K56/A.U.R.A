// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_HPP_
#define AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'coverage_area_vertices'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_Goal __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_Goal __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_Goal_
{
  using Type = ExecuteMission_Goal_<ContainerAllocator>;

  explicit ExecuteMission_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_id = "";
      this->mission_type = 0;
      this->target_altitude = 0.0f;
      this->target_coverage_percent = 0.0f;
      this->max_duration_sec = 0.0f;
    }
  }

  explicit ExecuteMission_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mission_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mission_id = "";
      this->mission_type = 0;
      this->target_altitude = 0.0f;
      this->target_coverage_percent = 0.0f;
      this->max_duration_sec = 0.0f;
    }
  }

  // field types and members
  using _mission_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mission_id_type mission_id;
  using _mission_type_type =
    uint8_t;
  _mission_type_type mission_type;
  using _coverage_area_vertices_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _coverage_area_vertices_type coverage_area_vertices;
  using _target_altitude_type =
    float;
  _target_altitude_type target_altitude;
  using _target_coverage_percent_type =
    float;
  _target_coverage_percent_type target_coverage_percent;
  using _max_duration_sec_type =
    float;
  _max_duration_sec_type max_duration_sec;

  // setters for named parameter idiom
  Type & set__mission_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mission_id = _arg;
    return *this;
  }
  Type & set__mission_type(
    const uint8_t & _arg)
  {
    this->mission_type = _arg;
    return *this;
  }
  Type & set__coverage_area_vertices(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->coverage_area_vertices = _arg;
    return *this;
  }
  Type & set__target_altitude(
    const float & _arg)
  {
    this->target_altitude = _arg;
    return *this;
  }
  Type & set__target_coverage_percent(
    const float & _arg)
  {
    this->target_coverage_percent = _arg;
    return *this;
  }
  Type & set__max_duration_sec(
    const float & _arg)
  {
    this->max_duration_sec = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MISSION_COVERAGE =
    0u;
  static constexpr uint8_t MISSION_SEARCH =
    1u;
  static constexpr uint8_t MISSION_RELAY =
    2u;

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Goal
    std::shared_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Goal
    std::shared_ptr<aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_Goal_ & other) const
  {
    if (this->mission_id != other.mission_id) {
      return false;
    }
    if (this->mission_type != other.mission_type) {
      return false;
    }
    if (this->coverage_area_vertices != other.coverage_area_vertices) {
      return false;
    }
    if (this->target_altitude != other.target_altitude) {
      return false;
    }
    if (this->target_coverage_percent != other.target_coverage_percent) {
      return false;
    }
    if (this->max_duration_sec != other.max_duration_sec) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_Goal_

// alias to use template instance with default allocator
using ExecuteMission_Goal =
  aura_msgs::action::ExecuteMission_Goal_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExecuteMission_Goal_<ContainerAllocator>::MISSION_COVERAGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExecuteMission_Goal_<ContainerAllocator>::MISSION_SEARCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ExecuteMission_Goal_<ContainerAllocator>::MISSION_RELAY;
#endif  // __cplusplus < 201703L

}  // namespace action

}  // namespace aura_msgs


#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_Result __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_Result __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_Result_
{
  using Type = ExecuteMission_Result_<ContainerAllocator>;

  explicit ExecuteMission_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->coverage_achieved = 0.0f;
      this->total_time_sec = 0.0f;
      this->avg_network_quality = 0.0f;
      this->total_connections_served = 0ul;
    }
  }

  explicit ExecuteMission_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->coverage_achieved = 0.0f;
      this->total_time_sec = 0.0f;
      this->avg_network_quality = 0.0f;
      this->total_connections_served = 0ul;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _coverage_achieved_type =
    float;
  _coverage_achieved_type coverage_achieved;
  using _total_time_sec_type =
    float;
  _total_time_sec_type total_time_sec;
  using _avg_network_quality_type =
    float;
  _avg_network_quality_type avg_network_quality;
  using _total_connections_served_type =
    uint32_t;
  _total_connections_served_type total_connections_served;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__coverage_achieved(
    const float & _arg)
  {
    this->coverage_achieved = _arg;
    return *this;
  }
  Type & set__total_time_sec(
    const float & _arg)
  {
    this->total_time_sec = _arg;
    return *this;
  }
  Type & set__avg_network_quality(
    const float & _arg)
  {
    this->avg_network_quality = _arg;
    return *this;
  }
  Type & set__total_connections_served(
    const uint32_t & _arg)
  {
    this->total_connections_served = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Result
    std::shared_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Result
    std::shared_ptr<aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->coverage_achieved != other.coverage_achieved) {
      return false;
    }
    if (this->total_time_sec != other.total_time_sec) {
      return false;
    }
    if (this->avg_network_quality != other.avg_network_quality) {
      return false;
    }
    if (this->total_connections_served != other.total_connections_served) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_Result_

// alias to use template instance with default allocator
using ExecuteMission_Result =
  aura_msgs::action::ExecuteMission_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs


#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_Feedback __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_Feedback_
{
  using Type = ExecuteMission_Feedback_<ContainerAllocator>;

  explicit ExecuteMission_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress_percent = 0.0f;
      this->current_coverage_percent = 0.0f;
      this->current_network_quality = 0.0f;
      this->drones_active = 0;
      this->current_phase = "";
      this->elapsed_time_sec = 0.0f;
    }
  }

  explicit ExecuteMission_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : current_phase(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress_percent = 0.0f;
      this->current_coverage_percent = 0.0f;
      this->current_network_quality = 0.0f;
      this->drones_active = 0;
      this->current_phase = "";
      this->elapsed_time_sec = 0.0f;
    }
  }

  // field types and members
  using _progress_percent_type =
    float;
  _progress_percent_type progress_percent;
  using _current_coverage_percent_type =
    float;
  _current_coverage_percent_type current_coverage_percent;
  using _current_network_quality_type =
    float;
  _current_network_quality_type current_network_quality;
  using _drones_active_type =
    uint8_t;
  _drones_active_type drones_active;
  using _current_phase_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_phase_type current_phase;
  using _elapsed_time_sec_type =
    float;
  _elapsed_time_sec_type elapsed_time_sec;

  // setters for named parameter idiom
  Type & set__progress_percent(
    const float & _arg)
  {
    this->progress_percent = _arg;
    return *this;
  }
  Type & set__current_coverage_percent(
    const float & _arg)
  {
    this->current_coverage_percent = _arg;
    return *this;
  }
  Type & set__current_network_quality(
    const float & _arg)
  {
    this->current_network_quality = _arg;
    return *this;
  }
  Type & set__drones_active(
    const uint8_t & _arg)
  {
    this->drones_active = _arg;
    return *this;
  }
  Type & set__current_phase(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_phase = _arg;
    return *this;
  }
  Type & set__elapsed_time_sec(
    const float & _arg)
  {
    this->elapsed_time_sec = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Feedback
    std::shared_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_Feedback
    std::shared_ptr<aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_Feedback_ & other) const
  {
    if (this->progress_percent != other.progress_percent) {
      return false;
    }
    if (this->current_coverage_percent != other.current_coverage_percent) {
      return false;
    }
    if (this->current_network_quality != other.current_network_quality) {
      return false;
    }
    if (this->drones_active != other.drones_active) {
      return false;
    }
    if (this->current_phase != other.current_phase) {
      return false;
    }
    if (this->elapsed_time_sec != other.elapsed_time_sec) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_Feedback_

// alias to use template instance with default allocator
using ExecuteMission_Feedback =
  aura_msgs::action::ExecuteMission_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "aura_msgs/action/detail/execute_mission__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_SendGoal_Request_
{
  using Type = ExecuteMission_SendGoal_Request_<ContainerAllocator>;

  explicit ExecuteMission_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit ExecuteMission_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const aura_msgs::action::ExecuteMission_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Request
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Request
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_SendGoal_Request_

// alias to use template instance with default allocator
using ExecuteMission_SendGoal_Request =
  aura_msgs::action::ExecuteMission_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_SendGoal_Response_
{
  using Type = ExecuteMission_SendGoal_Response_<ContainerAllocator>;

  explicit ExecuteMission_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit ExecuteMission_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Response
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_SendGoal_Response
    std::shared_ptr<aura_msgs::action::ExecuteMission_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_SendGoal_Response_

// alias to use template instance with default allocator
using ExecuteMission_SendGoal_Response =
  aura_msgs::action::ExecuteMission_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs

namespace aura_msgs
{

namespace action
{

struct ExecuteMission_SendGoal
{
  using Request = aura_msgs::action::ExecuteMission_SendGoal_Request;
  using Response = aura_msgs::action::ExecuteMission_SendGoal_Response;
};

}  // namespace action

}  // namespace aura_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Request __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_GetResult_Request_
{
  using Type = ExecuteMission_GetResult_Request_<ContainerAllocator>;

  explicit ExecuteMission_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit ExecuteMission_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Request
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Request
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_GetResult_Request_

// alias to use template instance with default allocator
using ExecuteMission_GetResult_Request =
  aura_msgs::action::ExecuteMission_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs


// Include directives for member types
// Member 'result'
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Response __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_GetResult_Response_
{
  using Type = ExecuteMission_GetResult_Response_<ContainerAllocator>;

  explicit ExecuteMission_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit ExecuteMission_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    aura_msgs::action::ExecuteMission_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const aura_msgs::action::ExecuteMission_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Response
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_GetResult_Response
    std::shared_ptr<aura_msgs::action::ExecuteMission_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_GetResult_Response_

// alias to use template instance with default allocator
using ExecuteMission_GetResult_Response =
  aura_msgs::action::ExecuteMission_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs

namespace aura_msgs
{

namespace action
{

struct ExecuteMission_GetResult
{
  using Request = aura_msgs::action::ExecuteMission_GetResult_Request;
  using Response = aura_msgs::action::ExecuteMission_GetResult_Response;
};

}  // namespace action

}  // namespace aura_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "aura_msgs/action/detail/execute_mission__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__action__ExecuteMission_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__action__ExecuteMission_FeedbackMessage __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct ExecuteMission_FeedbackMessage_
{
  using Type = ExecuteMission_FeedbackMessage_<ContainerAllocator>;

  explicit ExecuteMission_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit ExecuteMission_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const aura_msgs::action::ExecuteMission_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_FeedbackMessage
    std::shared_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__action__ExecuteMission_FeedbackMessage
    std::shared_ptr<aura_msgs::action::ExecuteMission_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteMission_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteMission_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteMission_FeedbackMessage_

// alias to use template instance with default allocator
using ExecuteMission_FeedbackMessage =
  aura_msgs::action::ExecuteMission_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace aura_msgs

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace aura_msgs
{

namespace action
{

struct ExecuteMission
{
  /// The goal message defined in the action definition.
  using Goal = aura_msgs::action::ExecuteMission_Goal;
  /// The result message defined in the action definition.
  using Result = aura_msgs::action::ExecuteMission_Result;
  /// The feedback message defined in the action definition.
  using Feedback = aura_msgs::action::ExecuteMission_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = aura_msgs::action::ExecuteMission_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = aura_msgs::action::ExecuteMission_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = aura_msgs::action::ExecuteMission_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct ExecuteMission ExecuteMission;

}  // namespace action

}  // namespace aura_msgs

#endif  // AURA_MSGS__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_HPP_
