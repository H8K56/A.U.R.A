#!/bin/bash
# ═══════════════════════════════════════════════════════════
# A.U.R.A. — Migrate from MAVROS to microDDS
# ═══════════════════════════════════════════════════════════
#
# This script:
#   1. Replaces px4_mavros_bridge.py with px4_dds_bridge.py
#   2. Updates setup.py entry points
#   3. Replaces gazebo_swarm.launch.py (no MAVROS)
#   4. Rebuilds aura_simulation
#
# Usage:
#   bash migrate_to_dds.sh
#
set -e

WS=~/ws
SIM_PKG=$WS/src/aura_simulation

echo "═══ A.U.R.A. microDDS Migration ═══"

# 1. Install DDS bridge (replace MAVROS bridge)
echo "[1/4] Installing px4_dds_bridge.py..."
cp px4_dds_bridge.py $SIM_PKG/aura_simulation/px4_dds_bridge.py

# Keep old bridge as backup
if [ -f $SIM_PKG/aura_simulation/px4_mavros_bridge.py ]; then
    mv $SIM_PKG/aura_simulation/px4_mavros_bridge.py \
       $SIM_PKG/aura_simulation/px4_mavros_bridge.py.bak
    echo "  (old bridge backed up as px4_mavros_bridge.py.bak)"
fi

# 2. Update setup.py — replace mavros bridge entry with dds bridge
echo "[2/4] Updating setup.py entry points..."
SETUP=$SIM_PKG/setup.py

# Add px4_dds_bridge if not already present
if grep -q "px4_dds_bridge" $SETUP; then
    echo "  px4_dds_bridge already in setup.py"
else
    # Replace px4_mavros_bridge with px4_dds_bridge, or add if neither exists
    if grep -q "px4_mavros_bridge" $SETUP; then
        sed -i "s|'px4_mavros_bridge = aura_simulation.px4_mavros_bridge:main'|'px4_dds_bridge = aura_simulation.px4_dds_bridge:main',\n            'px4_mavros_bridge = aura_simulation.px4_mavros_bridge:main'|" $SETUP
        echo "  Added px4_dds_bridge entry (kept mavros bridge for backward compat)"
    else
        # Add entry point before the closing bracket
        sed -i "s|'scenario_runner = aura_simulation.scenario_runner:main',|'scenario_runner = aura_simulation.scenario_runner:main',\n            'px4_dds_bridge = aura_simulation.px4_dds_bridge:main',|" $SETUP
        echo "  Added px4_dds_bridge entry point"
    fi
fi

# 3. Install launch file
echo "[3/4] Installing gazebo_swarm.launch.py (v6 — microDDS)..."
cp gazebo_swarm_v6.launch.py $SIM_PKG/launch/gazebo_swarm.launch.py

# 4. Rebuild
echo "[4/4] Rebuilding aura_simulation..."
cd $WS
source /opt/ros/humble/setup.bash
colcon build --packages-select aura_simulation 2>&1 | tail -5
source install/setup.bash

echo ""
echo "═══ Migration complete! ═══"
echo ""
echo "To launch:"
echo "  pkill -9 -f gzserver; pkill -9 -f px4; pkill -9 -f MicroXRCE; sleep 5"
echo "  ros2 launch aura_simulation gazebo_swarm.launch.py num_drones:=2"
echo ""
echo "To verify DDS connection:"
echo "  ros2 topic hz /px4_1/fmu/out/vehicle_local_position_v1"
echo "  ros2 topic echo /swarm/state --once | grep num_drones_active"
