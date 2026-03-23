// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'timestamp'
// Member 'start_time'
// Member 'end_time'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__WeatherZone __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__WeatherZone __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WeatherZone_
{
  using Type = WeatherZone_<ContainerAllocator>;

  explicit WeatherZone_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    center(_init),
    start_time(_init),
    end_time(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->zone_id = 0ul;
      this->radius_meters = 0.0f;
      this->min_altitude = 0.0f;
      this->max_altitude = 0.0f;
      this->weather_type = 0;
      this->severity = 0.0f;
      this->wind_speed_ms = 0.0f;
      this->wind_direction_rad = 0.0f;
      this->signal_attenuation_db = 0.0f;
      this->no_fly = false;
      this->is_active = false;
    }
  }

  explicit WeatherZone_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    center(_alloc, _init),
    start_time(_alloc, _init),
    end_time(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->zone_id = 0ul;
      this->radius_meters = 0.0f;
      this->min_altitude = 0.0f;
      this->max_altitude = 0.0f;
      this->weather_type = 0;
      this->severity = 0.0f;
      this->wind_speed_ms = 0.0f;
      this->wind_direction_rad = 0.0f;
      this->signal_attenuation_db = 0.0f;
      this->no_fly = false;
      this->is_active = false;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _zone_id_type =
    uint32_t;
  _zone_id_type zone_id;
  using _center_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _center_type center;
  using _radius_meters_type =
    float;
  _radius_meters_type radius_meters;
  using _min_altitude_type =
    float;
  _min_altitude_type min_altitude;
  using _max_altitude_type =
    float;
  _max_altitude_type max_altitude;
  using _weather_type_type =
    uint8_t;
  _weather_type_type weather_type;
  using _severity_type =
    float;
  _severity_type severity;
  using _wind_speed_ms_type =
    float;
  _wind_speed_ms_type wind_speed_ms;
  using _wind_direction_rad_type =
    float;
  _wind_direction_rad_type wind_direction_rad;
  using _signal_attenuation_db_type =
    float;
  _signal_attenuation_db_type signal_attenuation_db;
  using _no_fly_type =
    bool;
  _no_fly_type no_fly;
  using _start_time_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _start_time_type start_time;
  using _end_time_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _end_time_type end_time;
  using _is_active_type =
    bool;
  _is_active_type is_active;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__zone_id(
    const uint32_t & _arg)
  {
    this->zone_id = _arg;
    return *this;
  }
  Type & set__center(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__radius_meters(
    const float & _arg)
  {
    this->radius_meters = _arg;
    return *this;
  }
  Type & set__min_altitude(
    const float & _arg)
  {
    this->min_altitude = _arg;
    return *this;
  }
  Type & set__max_altitude(
    const float & _arg)
  {
    this->max_altitude = _arg;
    return *this;
  }
  Type & set__weather_type(
    const uint8_t & _arg)
  {
    this->weather_type = _arg;
    return *this;
  }
  Type & set__severity(
    const float & _arg)
  {
    this->severity = _arg;
    return *this;
  }
  Type & set__wind_speed_ms(
    const float & _arg)
  {
    this->wind_speed_ms = _arg;
    return *this;
  }
  Type & set__wind_direction_rad(
    const float & _arg)
  {
    this->wind_direction_rad = _arg;
    return *this;
  }
  Type & set__signal_attenuation_db(
    const float & _arg)
  {
    this->signal_attenuation_db = _arg;
    return *this;
  }
  Type & set__no_fly(
    const bool & _arg)
  {
    this->no_fly = _arg;
    return *this;
  }
  Type & set__start_time(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->start_time = _arg;
    return *this;
  }
  Type & set__end_time(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->end_time = _arg;
    return *this;
  }
  Type & set__is_active(
    const bool & _arg)
  {
    this->is_active = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t WEATHER_CLEAR =
    0u;
  static constexpr uint8_t WEATHER_RAIN =
    1u;
  static constexpr uint8_t WEATHER_HEAVY_RAIN =
    2u;
  static constexpr uint8_t WEATHER_WIND =
    3u;
  static constexpr uint8_t WEATHER_SEVERE_WIND =
    4u;
  static constexpr uint8_t WEATHER_DUST =
    5u;

  // pointer types
  using RawPtr =
    aura_msgs::msg::WeatherZone_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::WeatherZone_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::WeatherZone_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::WeatherZone_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__WeatherZone
    std::shared_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__WeatherZone
    std::shared_ptr<aura_msgs::msg::WeatherZone_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeatherZone_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->zone_id != other.zone_id) {
      return false;
    }
    if (this->center != other.center) {
      return false;
    }
    if (this->radius_meters != other.radius_meters) {
      return false;
    }
    if (this->min_altitude != other.min_altitude) {
      return false;
    }
    if (this->max_altitude != other.max_altitude) {
      return false;
    }
    if (this->weather_type != other.weather_type) {
      return false;
    }
    if (this->severity != other.severity) {
      return false;
    }
    if (this->wind_speed_ms != other.wind_speed_ms) {
      return false;
    }
    if (this->wind_direction_rad != other.wind_direction_rad) {
      return false;
    }
    if (this->signal_attenuation_db != other.signal_attenuation_db) {
      return false;
    }
    if (this->no_fly != other.no_fly) {
      return false;
    }
    if (this->start_time != other.start_time) {
      return false;
    }
    if (this->end_time != other.end_time) {
      return false;
    }
    if (this->is_active != other.is_active) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeatherZone_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeatherZone_

// alias to use template instance with default allocator
using WeatherZone =
  aura_msgs::msg::WeatherZone_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_CLEAR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_RAIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_HEAVY_RAIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_WIND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_SEVERE_WIND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeatherZone_<ContainerAllocator>::WEATHER_DUST;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__STRUCT_HPP_
