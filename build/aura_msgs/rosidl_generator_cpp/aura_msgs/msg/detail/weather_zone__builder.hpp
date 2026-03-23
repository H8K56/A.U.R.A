// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/WeatherZone.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/weather_zone__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_WeatherZone_is_active
{
public:
  explicit Init_WeatherZone_is_active(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::WeatherZone is_active(::aura_msgs::msg::WeatherZone::_is_active_type arg)
  {
    msg_.is_active = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_end_time
{
public:
  explicit Init_WeatherZone_end_time(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_is_active end_time(::aura_msgs::msg::WeatherZone::_end_time_type arg)
  {
    msg_.end_time = std::move(arg);
    return Init_WeatherZone_is_active(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_start_time
{
public:
  explicit Init_WeatherZone_start_time(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_end_time start_time(::aura_msgs::msg::WeatherZone::_start_time_type arg)
  {
    msg_.start_time = std::move(arg);
    return Init_WeatherZone_end_time(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_no_fly
{
public:
  explicit Init_WeatherZone_no_fly(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_start_time no_fly(::aura_msgs::msg::WeatherZone::_no_fly_type arg)
  {
    msg_.no_fly = std::move(arg);
    return Init_WeatherZone_start_time(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_signal_attenuation_db
{
public:
  explicit Init_WeatherZone_signal_attenuation_db(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_no_fly signal_attenuation_db(::aura_msgs::msg::WeatherZone::_signal_attenuation_db_type arg)
  {
    msg_.signal_attenuation_db = std::move(arg);
    return Init_WeatherZone_no_fly(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_wind_direction_rad
{
public:
  explicit Init_WeatherZone_wind_direction_rad(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_signal_attenuation_db wind_direction_rad(::aura_msgs::msg::WeatherZone::_wind_direction_rad_type arg)
  {
    msg_.wind_direction_rad = std::move(arg);
    return Init_WeatherZone_signal_attenuation_db(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_wind_speed_ms
{
public:
  explicit Init_WeatherZone_wind_speed_ms(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_wind_direction_rad wind_speed_ms(::aura_msgs::msg::WeatherZone::_wind_speed_ms_type arg)
  {
    msg_.wind_speed_ms = std::move(arg);
    return Init_WeatherZone_wind_direction_rad(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_severity
{
public:
  explicit Init_WeatherZone_severity(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_wind_speed_ms severity(::aura_msgs::msg::WeatherZone::_severity_type arg)
  {
    msg_.severity = std::move(arg);
    return Init_WeatherZone_wind_speed_ms(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_weather_type
{
public:
  explicit Init_WeatherZone_weather_type(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_severity weather_type(::aura_msgs::msg::WeatherZone::_weather_type_type arg)
  {
    msg_.weather_type = std::move(arg);
    return Init_WeatherZone_severity(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_max_altitude
{
public:
  explicit Init_WeatherZone_max_altitude(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_weather_type max_altitude(::aura_msgs::msg::WeatherZone::_max_altitude_type arg)
  {
    msg_.max_altitude = std::move(arg);
    return Init_WeatherZone_weather_type(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_min_altitude
{
public:
  explicit Init_WeatherZone_min_altitude(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_max_altitude min_altitude(::aura_msgs::msg::WeatherZone::_min_altitude_type arg)
  {
    msg_.min_altitude = std::move(arg);
    return Init_WeatherZone_max_altitude(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_radius_meters
{
public:
  explicit Init_WeatherZone_radius_meters(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_min_altitude radius_meters(::aura_msgs::msg::WeatherZone::_radius_meters_type arg)
  {
    msg_.radius_meters = std::move(arg);
    return Init_WeatherZone_min_altitude(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_center
{
public:
  explicit Init_WeatherZone_center(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_radius_meters center(::aura_msgs::msg::WeatherZone::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_WeatherZone_radius_meters(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_zone_id
{
public:
  explicit Init_WeatherZone_zone_id(::aura_msgs::msg::WeatherZone & msg)
  : msg_(msg)
  {}
  Init_WeatherZone_center zone_id(::aura_msgs::msg::WeatherZone::_zone_id_type arg)
  {
    msg_.zone_id = std::move(arg);
    return Init_WeatherZone_center(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

class Init_WeatherZone_timestamp
{
public:
  Init_WeatherZone_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WeatherZone_zone_id timestamp(::aura_msgs::msg::WeatherZone::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_WeatherZone_zone_id(msg_);
  }

private:
  ::aura_msgs::msg::WeatherZone msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::WeatherZone>()
{
  return aura_msgs::msg::builder::Init_WeatherZone_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__WEATHER_ZONE__BUILDER_HPP_
