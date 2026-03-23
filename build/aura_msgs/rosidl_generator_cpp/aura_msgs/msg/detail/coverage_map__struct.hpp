// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aura_msgs:msg/CoverageMap.idl
// generated code does not contain a copyright notice

#ifndef AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_HPP_
#define AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_HPP_

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
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'origin'
// Member 'priority_zone_centers'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aura_msgs__msg__CoverageMap __attribute__((deprecated))
#else
# define DEPRECATED__aura_msgs__msg__CoverageMap __declspec(deprecated)
#endif

namespace aura_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CoverageMap_
{
  using Type = CoverageMap_<ContainerAllocator>;

  explicit CoverageMap_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init),
    origin(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size_x = 0ul;
      this->grid_size_y = 0ul;
      this->cell_size_meters = 0.0f;
    }
  }

  explicit CoverageMap_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_alloc, _init),
    origin(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->grid_size_x = 0ul;
      this->grid_size_y = 0ul;
      this->cell_size_meters = 0.0f;
    }
  }

  // field types and members
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _grid_size_x_type =
    uint32_t;
  _grid_size_x_type grid_size_x;
  using _grid_size_y_type =
    uint32_t;
  _grid_size_y_type grid_size_y;
  using _cell_size_meters_type =
    float;
  _cell_size_meters_type cell_size_meters;
  using _origin_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _origin_type origin;
  using _is_covered_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _is_covered_type is_covered;
  using _is_target_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _is_target_type is_target;
  using _demand_level_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _demand_level_type demand_level;
  using _coverage_quality_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _coverage_quality_type coverage_quality;
  using _priority_zone_centers_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _priority_zone_centers_type priority_zone_centers;
  using _priority_zone_radii_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _priority_zone_radii_type priority_zone_radii;
  using _priority_zone_weights_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _priority_zone_weights_type priority_zone_weights;

  // setters for named parameter idiom
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__grid_size_x(
    const uint32_t & _arg)
  {
    this->grid_size_x = _arg;
    return *this;
  }
  Type & set__grid_size_y(
    const uint32_t & _arg)
  {
    this->grid_size_y = _arg;
    return *this;
  }
  Type & set__cell_size_meters(
    const float & _arg)
  {
    this->cell_size_meters = _arg;
    return *this;
  }
  Type & set__origin(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->origin = _arg;
    return *this;
  }
  Type & set__is_covered(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->is_covered = _arg;
    return *this;
  }
  Type & set__is_target(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->is_target = _arg;
    return *this;
  }
  Type & set__demand_level(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->demand_level = _arg;
    return *this;
  }
  Type & set__coverage_quality(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->coverage_quality = _arg;
    return *this;
  }
  Type & set__priority_zone_centers(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->priority_zone_centers = _arg;
    return *this;
  }
  Type & set__priority_zone_radii(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->priority_zone_radii = _arg;
    return *this;
  }
  Type & set__priority_zone_weights(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->priority_zone_weights = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aura_msgs::msg::CoverageMap_<ContainerAllocator> *;
  using ConstRawPtr =
    const aura_msgs::msg::CoverageMap_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::CoverageMap_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aura_msgs::msg::CoverageMap_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aura_msgs__msg__CoverageMap
    std::shared_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aura_msgs__msg__CoverageMap
    std::shared_ptr<aura_msgs::msg::CoverageMap_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CoverageMap_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->grid_size_x != other.grid_size_x) {
      return false;
    }
    if (this->grid_size_y != other.grid_size_y) {
      return false;
    }
    if (this->cell_size_meters != other.cell_size_meters) {
      return false;
    }
    if (this->origin != other.origin) {
      return false;
    }
    if (this->is_covered != other.is_covered) {
      return false;
    }
    if (this->is_target != other.is_target) {
      return false;
    }
    if (this->demand_level != other.demand_level) {
      return false;
    }
    if (this->coverage_quality != other.coverage_quality) {
      return false;
    }
    if (this->priority_zone_centers != other.priority_zone_centers) {
      return false;
    }
    if (this->priority_zone_radii != other.priority_zone_radii) {
      return false;
    }
    if (this->priority_zone_weights != other.priority_zone_weights) {
      return false;
    }
    return true;
  }
  bool operator!=(const CoverageMap_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CoverageMap_

// alias to use template instance with default allocator
using CoverageMap =
  aura_msgs::msg::CoverageMap_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aura_msgs

#endif  // AURA_MSGS__MSG__DETAIL__COVERAGE_MAP__STRUCT_HPP_
