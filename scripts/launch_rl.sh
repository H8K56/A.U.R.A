#!/bin/bash
# A.U.R.A. — Strategic RL auto-launcher
#
# Polls /mission/status and launches the RL node the moment OPERATIONS
# phase (5) is detected. The RL node already self-gates on phase internally,
# so starting this script before the launch file is also safe — it will
# just idle until the right phase arrives.
#
# Usage:
#   bash ~/ws/scripts/launch_rl.sh              # defaults to 5 drones
#   bash ~/ws/scripts/launch_rl.sh 3            # 3 drones

set -e

source /opt/ros/humble/setup.bash
source ~/ws/install/setup.bash

NUM_DRONES="${1:-5}"
PARAMS=~/ws/install/aura_simulation/share/aura_simulation/config/sim_params.yaml
PHASE_NAMES=(IDLE PREFLIGHT TAKEOFF TRANSIT FORMATION OPERATIONS RTL COMPLETE ABORT)

echo "[AURA RL] Waiting for OPERATIONS phase — polling /mission/status"
echo "[AURA RL] Ctrl-C to cancel."
echo ""

while true; do
    # /mission/status publishes at 1 Hz — grab one message and extract phase int
    PHASE=$(timeout 3 ros2 topic echo --once /mission/status aura_msgs/msg/MissionStatus \
                2>/dev/null | awk '/^phase:/ { print $2; exit }')

    if [ "$PHASE" = "5" ]; then
        break
    fi

    NAME="${PHASE_NAMES[$PHASE]:-unknown}"
    printf "\r[AURA RL] Phase: %-12s  (waiting for OPERATIONS)" "$NAME"
    sleep 1
done

echo ""
echo "[AURA RL] OPERATIONS detected — launching strategic_rl_node (drones=$NUM_DRONES)"

exec ros2 run aura_strategic_rl strategic_rl_node \
    --ros-args \
    -p num_drones:="$NUM_DRONES" \
    --params-file "$PARAMS"
