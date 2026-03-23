cmake_minimum_required(VERSION 3.8)
project(aura_px4_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(aura_msgs REQUIRED)
find_package(px4_msgs REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
)

# --------------------------------------------------------------------------
# Build shared library
# --------------------------------------------------------------------------
add_library(px4_interface
  src/px4_interface.cpp
  src/offboard_controller.cpp
  src/vehicle_state.cpp
)

target_link_libraries(px4_interface
)

ament_target_dependencies(px4_interface
  rclcpp
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  aura_msgs
  px4_msgs
  std_srvs
)

# Ensure RPATH is set so installed library will be found by executables
set_target_properties(px4_interface PROPERTIES
  BUILD_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
  INSTALL_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
)

# --------------------------------------------------------------------------
# Build interface node
# --------------------------------------------------------------------------
add_executable(px4_interface_node src/px4_interface_node.cpp)
target_link_libraries(px4_interface_node px4_interface)
ament_target_dependencies(px4_interface_node
  rclcpp
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  aura_msgs
  px4_msgs
  std_srvs
)

set_target_properties(px4_interface_node PROPERTIES
  BUILD_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
  INSTALL_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
)

# --------------------------------------------------------------------------
# Build swarm manager
# --------------------------------------------------------------------------
add_executable(swarm_px4_manager_node src/swarm_px4_manager_node.cpp)
target_link_libraries(swarm_px4_manager_node px4_interface)
ament_target_dependencies(swarm_px4_manager_node
  rclcpp
  std_msgs
  geometry_msgs
  aura_msgs
  px4_msgs
  std_srvs
)

set_target_properties(swarm_px4_manager_node PROPERTIES
  BUILD_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
  INSTALL_RPATH "$ORIGIN/../../lib/${PROJECT_NAME}"
)

# --------------------------------------------------------------------------
# Install targets and resources
# --------------------------------------------------------------------------
install(
  TARGETS
    px4_interface
    px4_interface_node
    swarm_px4_manager_node
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
