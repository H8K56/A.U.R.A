#!/bin/bash
NUM_DRONES=${1:-5}
USE_BASELINE=${2:-false}

echo "╔══════════════════════════════════════════╗"
echo "║      A.U.R.A. PRESENTATION DEMO          ║"
echo "║  Drones: ${NUM_DRONES}  Baseline: ${USE_BASELINE}         ║"
echo "╚══════════════════════════════════════════╝"

~/ws/scripts/clean_sim.sh
sleep 3

# Terminal 1: Gazebo + PX4 + AURA stack
gnome-terminal --title="A.U.R.A. — Simulation" -- bash -c "
source /opt/ros/humble/setup.bash
source ~/ws/install/setup.bash
ros2 launch aura_simulation gazebo_swarm.launch.py num_drones:=${NUM_DRONES}
exec bash" &

sleep 5

# Terminal 2: RL Controller (auto-waits for drones)
gnome-terminal --title="A.U.R.A. — RL Controller" -- bash -c "
source /opt/ros/humble/setup.bash
source ~/ws/install/setup.bash
CFG=~/ws/install/aura_simulation/share/aura_simulation/config/sim_params.yaml

echo 'Waiting for PX4 topics...'
while true; do
    count=\$(ros2 topic list 2>/dev/null | grep -c vehicle_status_v1 || true)
    if [ \"\$count\" -ge ${NUM_DRONES} ]; then
        echo \"Found \$count PX4 topics\"
        break
    fi
    sleep 2
done

echo 'Waiting for drones to arm...'
while true; do
    armed=0
    for i in \$(seq 1 ${NUM_DRONES}); do
        state=\$(timeout 3 ros2 topic echo /px4_\${i}/fmu/out/vehicle_status_v1 --once 2>/dev/null | grep 'arming_state: 2' || true)
        [ -n \"\$state\" ] && armed=\$((armed + 1))
    done
    echo \"Armed: \${armed}/${NUM_DRONES}\"
    if [ \"\$armed\" -ge \$((${NUM_DRONES} - 1)) ]; then
        echo 'Drones armed!'
        break
    fi
    sleep 5
done

echo 'Waiting for TRANSIT phase...'
while true; do
    phase=\$(timeout 5 ros2 topic echo /mission/status --once 2>/dev/null | grep '^phase:' | awk '{print \$2}' || true)
    case \"\$phase\" in
        3|4|5) echo \"Phase \$phase — starting RL\"; break;;
        8) echo 'ABORT — restarting mission'
           ros2 topic pub /mission/command std_msgs/msg/String \"data: start\" --once 2>/dev/null
           sleep 5;;
        *) echo \"Phase: \${phase:-waiting}\";;
    esac
    sleep 3
done

echo ''
echo '═══ STARTING RL CONTROLLER ═══'
ros2 run aura_strategic_rl strategic_rl_node \
    --ros-args -p num_drones:=${NUM_DRONES} -p use_baseline:=${USE_BASELINE} \
    --params-file \$CFG
exec bash" &

echo "Both terminals launched."
