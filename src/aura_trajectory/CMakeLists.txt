cmake_minimum_required(VERSION 3.8)
project(aura_trajectory)

# Compiler settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3 -march=native)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(aura_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(Eigen3 REQUIRED)

# LBFGS-Lite (header-only)
include_directories(/opt/LBFGS-Lite/include)

# Include directories
include_directories(include)

# MINCO trajectory library
add_library(minco_trajectory SHARED
  src/minco_trajectory.cpp
  src/trajectory_optimizer.cpp
  src/penalty_functions.cpp
  src/safety_checker.cpp
)
target_include_directories(minco_trajectory PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(minco_trajectory Eigen3::Eigen)

# Trajectory planner node
add_executable(trajectory_node src/trajectory_node.cpp)
target_link_libraries(trajectory_node minco_trajectory)
ament_target_dependencies(trajectory_node
  rclcpp std_msgs geometry_msgs aura_msgs tf2 tf2_ros
)

# Swarm coordinator node (manages trajectory broadcasts)
add_executable(swarm_coordinator_node src/swarm_coordinator_node.cpp)
target_link_libraries(swarm_coordinator_node minco_trajectory)
ament_target_dependencies(swarm_coordinator_node
  rclcpp std_msgs geometry_msgs aura_msgs tf2 tf2_ros
)

# Install
install(TARGETS
  minco_trajectory
  trajectory_node
  swarm_coordinator_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
