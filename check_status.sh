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
# 1. Check if the sed actually worked
grep -n 'swarm_pub\|swarm/state' ~/ws/src/aura_simulation/aura_simulation/sim_swarm_driver.py

# 2. Check what the network_sim subscribes with
grep -n -A2 'swarm_sub\|create_subscription' ~/ws/src/aura_network_sim/aura_network_sim/network_sim_node.py | head -15

# 3. Quick live test — publish manually and see if network_sim receives it
# Terminal 1: start just network_sim
# Terminal 2: echo the topic to see if anything comes through

# Actually, simplest diagnostic — check the publisher side:
ros2 launch aura_simulation sim_no_px4.launch.py &
sleep 5
ros2 topic info /swarm/state -v
ros2 topic echo /swarm/state --once 2>&1 | head -20
kill %1 2>/dev/null