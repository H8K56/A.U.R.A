#!/bin/bash
set -eo pipefail

NUM_DRONES=${1:-4}
WORLD=${2:-earthquake_city}

echo "=== A.U.R.A. Gazebo Launch (${NUM_DRONES} drones) ==="

cleanup() {
  echo ""
  echo "[Cleanup] Stopping processes..."
  pkill -9 -f "gzserver|gzclient|px4|MicroXRCEAgent|px4_dds_bridge|mission_control_node|network_sim_node|coverage_calculator_node|dead_zone_publisher" 2>/dev/null || true
}
trap cleanup SIGINT SIGTERM EXIT

# Clean old state
~/ws/scripts/clean_sim.sh || true

# Source env
source /opt/ros/humble/setup.bash
source ~/ws/install/setup.bash
source ~/PX4-Autopilot/Tools/simulation/gazebo-classic/setup_gazebo.bash \
  ~/PX4-Autopilot ~/PX4-Autopilot/build/px4_sitl_default

export OPENBLAS_NUM_THREADS=1
export OMP_NUM_THREADS=1
export __NV_PRIME_RENDER_OFFLOAD=1
export __GLX_VENDOR_LIBRARY_NAME=nvidia

cd ~/PX4-Autopilot

# ═══ Phase 1: gzserver only ═══
echo "[Phase 1] Starting gzserver..."
gzserver --verbose \
  Tools/simulation/gazebo-classic/sitl_gazebo-classic/worlds/${WORLD}.world \
  > /tmp/gzserver.log 2>&1 &

for t in $(seq 1 120); do
  if pgrep -x gzserver >/dev/null 2>&1; then
    echo "[Phase 1] Gazebo ready (${t}s)"
    break
  fi
  if [ $t -eq 120 ]; then
    echo "ERROR: gzserver failed to start"
    exit 1
  fi
  sleep 1
done

sleep 3

# ═══ Phase 2: Generate ALL SDFs first ═══
echo "[Phase 2] Generating drone models..."
for i in $(seq 1 $NUM_DRONES); do
  python3 Tools/simulation/gazebo-classic/sitl_gazebo-classic/scripts/jinja_gen.py \
    Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/iris/iris.sdf.jinja \
    Tools/simulation/gazebo-classic/sitl_gazebo-classic \
    --mavlink_tcp_port $((4560+i)) \
    --mavlink_udp_port $((14560+i)) \
    --mavlink_id $i \
    --output-file /tmp/iris_${i}.sdf
  echo "  Generated iris_${i}.sdf (TCP:$((4560+i)))"
done

# ═══ Phase 3: Spawn + PX4 one at a time ═══
echo "[Phase 3] Spawning drones sequentially..."
for i in $(seq 1 $NUM_DRONES); do
  echo "  [Drone $i] Spawning model..."
  gz model --spawn-file /tmp/iris_${i}.sdf \
    --model-name iris_${i} \
    -x $((i*3)) -y $((i*3)) -z 0.2
  
  # Wait for MAVLink plugin to start listening
  sleep 2

  echo "  [Drone $i] Starting PX4 (instance $i, TCP:$((4560+i)))..."
  ROOTFS="build/px4_sitl_default/rootfs/$((i-1))"
  mkdir -p "$ROOTFS"
  
  PX4_SYS_AUTOSTART=10015 \
  PX4_SIM_MODEL=gazebo-classic_iris \
  ./build/px4_sitl_default/bin/px4 \
    -i $i \
    -d /home/aura/PX4-Autopilot/build/px4_sitl_default/etc \
    -w /home/aura/PX4-Autopilot/build/px4_sitl_default/rootfs/$((i-1)) \
    < /dev/null > /tmp/px4_${i}.log 2>&1 &
  
  # Wait for PX4 to connect and lockstep to sync
  echo "  [Drone $i] Waiting for lockstep sync..."
  for t in $(seq 1 15); do
    if grep -q "Simulator connected" /tmp/px4_${i}.log 2>/dev/null; then
      echo "  [Drone $i] Connected! (${t}s)"
      break
    fi
    sleep 1
  done
  
  sleep 2
done

echo "[Phase 3] All ${NUM_DRONES} drones spawned and connected"
echo "[Phase 3] Waiting for EKF convergence..."
sleep 15

# ═══ Phase 4: MicroXRCE Agent ═══
echo "[Phase 4] Starting DDS agent..."
MicroXRCEAgent udp4 -p 8888 > /tmp/xrce.log 2>&1 &
sleep 5

# ═══ Phase 5: AURA stack ═══
echo "[Phase 5] Starting A.U.R.A. nodes..."
CFG=~/ws/install/aura_simulation/share/aura_simulation/config/sim_params.yaml

ros2 run aura_simulation px4_dds_bridge \
  --ros-args -p num_drones:=$NUM_DRONES \
  --params-file $CFG > /tmp/bridge.log 2>&1 &
sleep 5

ros2 run aura_simulation dead_zone_publisher \
  --ros-args --params-file $CFG > /tmp/deadzone.log 2>&1 &
ros2 run aura_network_sim network_sim_node \
  --ros-args --params-file $CFG > /tmp/network.log 2>&1 &
ros2 run aura_network_sim coverage_calculator_node \
  --ros-args --params-file $CFG > /tmp/coverage.log 2>&1 &
ros2 run aura_mission_control mission_control_node \
  --ros-args --params-file $CFG > /tmp/mission.log 2>&1 &
sleep 5

# ═══ Phase 6: GUI last ═══
echo "[Phase 6] Starting Gazebo GUI..."
gzclient > /tmp/gzclient.log 2>&1 &
sleep 3

# ═══ Status check ═══
echo ""
echo "=================================="
echo " A.U.R.A. SYSTEM READY"
echo " Drones: $NUM_DRONES"
echo " World:  $WORLD"
echo "=================================="
echo ""
echo "Check status:"
echo "  ros2 topic echo /mission/status --once"
echo ""
echo "Start RL (separate terminal):"
echo "  source ~/ws/install/setup.bash"
echo "  ros2 run aura_strategic_rl strategic_rl_node \\"
echo "    --ros-args -p num_drones:=$NUM_DRONES -p use_baseline:=true \\"
echo "    --params-file $CFG"
echo ""

# Check PX4 status
echo "PX4 instances: $(pgrep -c px4 || echo 0)"
for i in $(seq 1 $NUM_DRONES); do
  if grep -q "Ready for takeoff" /tmp/px4_${i}.log 2>/dev/null; then
    echo "  Drone $i: READY"
  elif grep -q "Simulator connected" /tmp/px4_${i}.log 2>/dev/null; then
    echo "  Drone $i: Connected - EKF converging"
  else
    echo "  Drone $i: Waiting..."
  fi
done

wait
