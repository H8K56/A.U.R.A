// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__BUILDER_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aura_msgs/msg/detail/coverage_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aura_msgs
{

namespace msg
{

namespace builder
{

class Init_CoverageMap_priority_zone_weights
{
public:
  explicit Init_CoverageMap_priority_zone_weights(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  ::aura_msgs::msg::CoverageMap priority_zone_weights(::aura_msgs::msg::CoverageMap::_priority_zone_weights_type arg)
  {
    msg_.priority_zone_weights = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_priority_zone_radii
{
public:
  explicit Init_CoverageMap_priority_zone_radii(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_priority_zone_weights priority_zone_radii(::aura_msgs::msg::CoverageMap::_priority_zone_radii_type arg)
  {
    msg_.priority_zone_radii = std::move(arg);
    return Init_CoverageMap_priority_zone_weights(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_priority_zone_centers
{
public:
  explicit Init_CoverageMap_priority_zone_centers(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_priority_zone_radii priority_zone_centers(::aura_msgs::msg::CoverageMap::_priority_zone_centers_type arg)
  {
    msg_.priority_zone_centers = std::move(arg);
    return Init_CoverageMap_priority_zone_radii(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_coverage_quality
{
public:
  explicit Init_CoverageMap_coverage_quality(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_priority_zone_centers coverage_quality(::aura_msgs::msg::CoverageMap::_coverage_quality_type arg)
  {
    msg_.coverage_quality = std::move(arg);
    return Init_CoverageMap_priority_zone_centers(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_demand_level
{
public:
  explicit Init_CoverageMap_demand_level(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_coverage_quality demand_level(::aura_msgs::msg::CoverageMap::_demand_level_type arg)
  {
    msg_.demand_level = std::move(arg);
    return Init_CoverageMap_coverage_quality(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_is_target
{
public:
  explicit Init_CoverageMap_is_target(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_demand_level is_target(::aura_msgs::msg::CoverageMap::_is_target_type arg)
  {
    msg_.is_target = std::move(arg);
    return Init_CoverageMap_demand_level(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_is_covered
{
public:
  explicit Init_CoverageMap_is_covered(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_is_target is_covered(::aura_msgs::msg::CoverageMap::_is_covered_type arg)
  {
    msg_.is_covered = std::move(arg);
    return Init_CoverageMap_is_target(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_origin
{
public:
  explicit Init_CoverageMap_origin(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_is_covered origin(::aura_msgs::msg::CoverageMap::_origin_type arg)
  {
    msg_.origin = std::move(arg);
    return Init_CoverageMap_is_covered(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_cell_size_meters
{
public:
  explicit Init_CoverageMap_cell_size_meters(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_origin cell_size_meters(::aura_msgs::msg::CoverageMap::_cell_size_meters_type arg)
  {
    msg_.cell_size_meters = std::move(arg);
    return Init_CoverageMap_origin(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_grid_size_y
{
public:
  explicit Init_CoverageMap_grid_size_y(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_cell_size_meters grid_size_y(::aura_msgs::msg::CoverageMap::_grid_size_y_type arg)
  {
    msg_.grid_size_y = std::move(arg);
    return Init_CoverageMap_cell_size_meters(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_grid_size_x
{
public:
  explicit Init_CoverageMap_grid_size_x(::aura_msgs::msg::CoverageMap & msg)
  : msg_(msg)
  {}
  Init_CoverageMap_grid_size_y grid_size_x(::aura_msgs::msg::CoverageMap::_grid_size_x_type arg)
  {
    msg_.grid_size_x = std::move(arg);
    return Init_CoverageMap_grid_size_y(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

class Init_CoverageMap_timestamp
{
public:
  Init_CoverageMap_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CoverageMap_grid_size_x timestamp(::aura_msgs::msg::CoverageMap::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_CoverageMap_grid_size_x(msg_);
  }

private:
  ::aura_msgs::msg::CoverageMap msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aura_msgs::msg::CoverageMap>()
{
  return aura_msgs::msg::builder::Init_CoverageMap_timestamp();
}

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__BUILDER_HPP_
