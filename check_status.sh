# # 1. Show all package.xml files (to check build types and deps)
# for pkg in aura_msgs aura_trajectory aura_px4_interface aura_network_sim aura_strategic_rl; do
#   echo "=== $pkg ===" 
#   cat ~/ws/src/$pkg/package.xml 2>/dev/null || echo "NOT FOUND"
#   echo ""
# done

# # 2. Show setup.py/setup.cfg for Python packages
# for pkg in aura_network_sim aura_strategic_rl; do
#   echo "=== $pkg setup.py ==="
#   cat ~/ws/src/$pkg/setup.py 2>/dev/null || echo "NOT FOUND"
#   echo "=== $pkg setup.cfg ==="
#   cat ~/ws/src/$pkg/setup.cfg 2>/dev/null || echo "NOT FOUND"
#   echo ""
# done

# # 3. Current build attempt
# cd ~/ws && colcon build 2>&1 | tail -60

# # 4. Show message definitions
# ls ~/ws/src/aura_msgs/msg/ ~/ws/src/aura_msgs/srv/ ~/ws/src/aura_msgs/action/ 2>/dev/null

# 1. Check if ament_package is installed but not on path
# python3 -c "import ament_package; print(ament_package.__file__)" 2>&1

# # 2. Check which python3 is being used
# which python3
# python3 --version

# # 3. Check if ROS 2 is sourced
# echo $AMENT_PREFIX_PATH
# echo $ROS_DISTRO

# # 4. Check pip packages
# pip3 list 2>/dev/null | grep ament

# # 5. Check if it's installed in a weird location
# find / -name "ament_package" -type d 2>/dev/null | head -10

# # 6. Source ROS and retry
# source /opt/ros/humble/setup.bash && python3 -c "import ament_package; print('OK')" 2>&1

# 1. Add ROS 2 sourcing to your .bashrc so it's always available
# echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc

# # 2. Source it now for this session
# source /opt/ros/humble/setup.bash

# # 3. Verify
# python3 -c "import ament_package; print('ament_package OK')"

# # 4. Now try building aura_msgs
# cd ~/ws
# rm -rf build/ install/ log/
# colcon build --packages-select aura_msgs 2>&1

# Source the full workspace
# source install/setup.bash

# # 1. Check all packages are registered
# ros2 pkg list | grep aura

# # 2. Check message definitions are available
# ros2 interface list | grep aura

# # 3. Check executables for each package
# ros2 pkg executables aura_trajectory
# ros2 pkg executables aura_px4_interface
# ros2 pkg executables aura_network_sim
# ros2 pkg executables aura_strategic_rl

# # 4. Quick smoke test - try launching a node (will fail without PX4 but should at least start)
# timeout 5 ros2 run aura_network_sim network_sim_node 2>&1 || true
# 1. Show the current NetworkMetrics definition
# ros2 interface show aura_msgs/msg/NetworkMetrics

# # 2. Show what fields the network_sim_node is trying to use
# grep -n 'msg\.' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py | head -40

# # 3. Same for coverage_calculator_node
# grep -n 'msg\.' ~/ws/src/aura_network_sim/aura_network_sim/coverage_calculator_node.py | head -40

# # 4. Check what strategic_rl_node expects from NetworkMetrics
# grep -n 'NetworkMetrics\|network_metrics\|msg\.' ~/ws/src/aura_strategic_rl/aura_strategic_rl/strategic_rl_node.py | head -30

# # 5. Check the SwarmState message too (often mismatched)
# ros2 interface show aura_msgs/msg/SwarmState
# ros2 interface show aura_msgs/msg/DroneState

# # 6. What does the trajectory node expect?
# grep -n 'msg\.' ~/ws/src/aura_trajectory/src/trajectory_node.cpp | head -30
# grep -n 'msg\.' ~/ws/src/aura_trajectory/src/swarm_coordinator_node.cpp | head -30

# 1. Source ROS first (your script missed it)
# source /opt/ros/humble/setup.bash && source ~/ws/install/setup.bash

# # 2. Show all current message definitions
# for msg in NetworkMetrics CoverageMap DroneState SwarmState MissionStatus; do
#   echo "=== $msg ==="
#   cat ~/ws/src/aura_msgs/msg/$msg.msg
#   echo ""
# done

# # 3. Check if SwarmStatus.msg exists (vs SwarmState.msg)
# ls ~/ws/src/aura_msgs/msg/Swarm*

# # 4. Check strategic_rl imports and field usage
# head -30 ~/ws/src/aura_strategic_rl/aura_strategic_rl/strategic_rl_node.py
# grep -n 'mesh_connected\|backhaul\|header\|coverage_quality\|SwarmStatus\|SwarmState' ~/ws/src/aura_strategic_rl/aura_strategic_rl/strategic_rl_node.py

# # 5. Check spaces.py observation builder - what fields does it read?
# grep -n 'msg\.\|metrics\.\|network\.\|swarm\.' ~/ws/src/aura_strategic_rl/aura_strategic_rl/spaces.py | head -30

# # 6. Check the trajectory node's DroneState/SwarmState usage
# grep -n 'DroneState\|SwarmState\|SwarmStatus' ~/ws/src/aura_trajectory/src/trajectory_node.cpp | head -20
# grep -n 'DroneState\|SwarmState\|SwarmStatus' ~/ws/src/aura_trajectory/src/swarm_coordinator_node.cpp | head -20

# # 7. Check PX4 interface expectations
# grep -n 'DroneState\|SwarmState\|aura_msgs' ~/ws/src/aura_px4_interface/src/px4_interface.cpp | head -20
# Confirm spaces.py is actually missing
# ls -la ~/ws/src/aura_strategic_rl/aura_strategic_rl/

# # Check what the CMakeLists for aura_msgs includes (does it list SwarmStatus?)
# cat ~/ws/src/aura_msgs/CMakeLists.txt

# # Check the network_sim_node around the crash line for full context
# sed -n '245,270p' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py

# # 1. Test coverage_calculator_node
# timeout 5 ros2 run aura_network_sim coverage_calculator_node 2>&1 || true

# # 2. Test strategic_rl_node (will warn about missing topics but should start)
# timeout 5 ros2 run aura_strategic_rl strategic_rl_node 2>&1 || true

# # 3. Verify the restored RL files import correctly
# python3 -c "
# from aura_strategic_rl.spaces import ObservationConfig, ActionConfig, ObservationBuilder, ActionProcessor
# from aura_strategic_rl.rewards import RewardConfig, RewardCalculator
# from aura_strategic_rl.policy import MLPPolicy, PolicyCheckpoint, BaselinePolicy
# print(f'ObservationConfig total_obs_dim: {ObservationConfig().total_obs_dim}')
# print(f'ActionConfig action_dim: {ActionConfig().action_dim}')
# print('All imports OK')
# "

# # 4. Test the Gymnasium env (standalone, no ROS)
# python3 -c "
# from aura_strategic_rl.swarm_gym_env import SwarmGymEnv, EnvConfig
# env = SwarmGymEnv(EnvConfig(num_drones=5, max_steps=50))
# obs, info = env.reset(seed=42)
# print(f'Obs shape: {obs.shape}')
# print(f'Coverage: {info[\"coverage_percent\"]:.1f}%')
# print(f'Connected: {info[\"mesh_connected\"]}')
# for i in range(10):
#     obs, r, term, trunc, info = env.step(env.action_space.sample())
# print(f'After 10 steps - Coverage: {info[\"coverage_percent\"]:.1f}%, Reward: {r:.3f}')
# print('Gym env OK')
# "
# # Fix 1: Remove zone_name from dead_zone_publisher
# sed -i 's/msg.zone_name = zone.name/# zone_name not in WeatherZone.msg/' \
#   ~/ws/src/aura_simulation/aura_simulation/dead_zone_publisher.py

# # Fix 2: Update the test
# sed -i "s/assert hasattr(wz, 'zone_name')/# zone_name not in WeatherZone.msg/" \
#   ~/ws/src/aura_simulation/test/test_simulation.py

# # Rebuild
# cd ~/ws && colcon build --packages-select aura_simulation 2>&1 | tail -3
# source install/setup.bash

# # Launch again in background, then check topics
# ros2 launch aura_simulation sim_no_px4.launch.py &
# sleep 5

# # Check what topics exist
# ros2 topic list | grep -E 'drone|swarm|network|mission|coverage'

# # Check who's publishing/subscribing to swarm state
# ros2 topic info /swarm/state -v

# # Check what the network_sim expects
# grep -n 'create_subscription\|Subscription' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py | head -10

# # Kill the launch
# kill %1 2>/dev/null; sleep 2

# # Show the line number
# grep -n 'swarm_pub' ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py

# # Then manually edit just that one line — change sensor_qos to reliable_qos:
# # Find:    self.swarm_pub = self.create_publisher(
# #              SwarmState, '/swarm/state', sensor_qos)
# # Change to:
# #          self.swarm_pub = self.create_publisher(
# #              SwarmState, '/swarm/state', reliable_qos)

# sed -i "s|SwarmState, '/swarm/state', sensor_qos|SwarmState, '/swarm/state', reliable_qos|" \
#   ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py

# # Rebuild and relaunch
# cd ~/ws && colcon build --packages-select aura_simulation 2>&1 | tail -3
# source install/setup.bash
# ros2 launch aura_simulation sim_no_px4.launch.py
# # 1. Check if the sed actually worked
# grep -n 'swarm_pub\|swarm/state' ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py

# # 2. Check what the network_sim subscribes with
# grep -n -A2 'swarm_sub\|create_subscription' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py | head -15

# # 3. Quick live test — publish manually and see if network_sim receives it
# # Terminal 1: start just network_sim
# # Terminal 2: echo the topic to see if anything comes through

# # Actually, simplest diagnostic — check the publisher side:
# ros2 launch aura_simulation sim_no_px4.launch.py &
# sleep 5
# ros2 topic info /swarm/state -v
# ros2 topic echo /swarm/state --once 2>&1 | head -20
# kill %1 2>/dev/null

# # 1. PX4 version and available targets
# cd ~/PX4-Autopilot && git describe --tags 2>/dev/null || git log --oneline -1
# make list_config_targets 2>/dev/null | grep -i "gazebo-classic" | head -10

# # 2. Gazebo Classic version
# gazebo --version 2>/dev/null || dpkg -l | grep gazebo

# # 3. MAVROS availability
# ros2 pkg list 2>/dev/null | grep mavros
# dpkg -l | grep mavros

# # 4. What Gazebo models exist
# ls ~/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/ 2>/dev/null | head -20

# # 5. Current workspace packages
# ls ~/ws/src/

# # 6. Existing world files
# ls ~/ws/worlds/ 2>/dev/null
# ls ~/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/worlds/ 2>/dev/null | head -10
# 1. Are PX4 processes actually running?
# ps aux | grep px4 | grep -v grep

# # 2. Are MAVROS nodes alive?
# ros2 node list 2>/dev/null | grep mavros

# # 3. Is the bridge node alive?
# ros2 node list 2>/dev/null | grep px4_mavros_bridge

# # 4. Are iris models in Gazebo?
# gz model --list 2>/dev/null

# # 5. What topics exist?
# ros2 topic list 2>/dev/null | grep -E "mavros|drone.*mavros" | head -20

# # 6. Check if any PX4 errors in the launch output
# # Re-launch and capture output:
# ros2 launch aura_simulation gazebo_swarm.launch.py 2>&1 | tee /tmp/gazebo_launch.log &
# sleep 30
# # Then check:
# grep -i "error\|fail\|warn" /tmp/gazebo_launch.log | head -30
# Check what the working make target actually sets
# cd ~/PX4-Autopilot
# grep -r "gazebo-classic" Tools/simulation/ ROMFS/px4fmu_common/init.d-posix/ --include="*.sh" -l 2>/dev/null | head -10

# # Check the simulator_mavlink module
# grep -r "SIM_GAZEBO\|GAZEBO_CLASSIC\|simulator_mavlink" ROMFS/px4fmu_common/init.d-posix/rcS | head -20

# # Check what env vars the Makefile sets for gazebo-classic_iris
# grep -A 20 "gazebo-classic_iris" Makefile 2>/dev/null || grep -A 20 "gazebo-classic" cmake/sitl_target.cmake 2>/dev/null | head -30

# # Also check what autostart ID iris uses
# grep -r "iris" ROMFS/px4fmu_common/init.d-posix/airframes/ | grep -i "gazebo-classic\|10016" | head -5

# # 1. Verify the fixes from last session are still applied
# grep 'mesh_connected' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py
# grep 'reliable_qos\|sensor_qos' ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py | head -5
# grep 'drone_id.*state' ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py

# # 2. What launch file are you using?
# # Are you running sim_no_px4.launch.py or a different one with Gazebo?

# # 3. Check if sim_swarm_driver is even in the launch
# # (if you're using Gazebo+PX4, the sim driver shouldn't be there —
# #  PX4 publishes drone state instead)

# # 4. Show me the launch file you're using
# ls ~/ws/src/aura_simulation/launch/
# cat ~/ws/launch/*.py 2>/dev/null | head -30
# 1. Check current coverage baseline
ros2 topic echo /mission/status --once 2>&1 | grep coverage

# 2. Add a random dead zone
ros2 service call /dead_zone_publisher/add_random_zone std_srvs/srv/Trigger

# 3. Wait a few seconds for coverage to update, then check
sleep 5
ros2 topic echo /mission/status --once 2>&1 | grep coverage

# 4. Add another dead zone
ros2 service call /dead_zone_publisher/add_random_zone std_srvs/srv/Trigger
sleep 5
ros2 topic echo /mission/status --once 2>&1 | grep coverage

# 5. Add a third
ros2 service call /dead_zone_publisher/add_random_zone std_srvs/srv/Trigger
sleep 5
ros2 topic echo /mission/status --once 2>&1 | grep coverage

# 6. Check network details
ros2 topic echo /network/metrics --once 2>&1 | grep -E 'coverage|signal|throughput'

# 7. Clear all dead zones and watch recovery
ros2 service call /dead_zone_publisher/clear_zones std_srvs/srv/Trigger
sleep 5
ros2 topic echo /mission/status --once 2>&1 | grep coverage