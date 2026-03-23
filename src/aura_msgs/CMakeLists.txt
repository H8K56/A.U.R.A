cmake_minimum_required(VERSION 3.8)
project(aura_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  # Messages
  "msg/DroneState.msg"
  "msg/SwarmState.msg"
  "msg/TrajectoryBroadcast.msg"
  "msg/NetworkMetrics.msg"
  "msg/CoverageGoal.msg"
  "msg/CoverageMap.msg"
  "msg/WeatherZone.msg"
  "msg/MissionStatus.msg"
  # Services
  "srv/RequestTrajectory.srv"
  "srv/EmergencyStop.srv"
  "srv/SetFormation.srv"
  "srv/GetNetworkStatus.srv"
  # Actions
  "action/ExecuteMission.action"
  DEPENDENCIES std_msgs geometry_msgs builtin_interfaces
)

ament_package()
