#!/bin/bash
# A.U.R.A. Integration Fix Script
# Fixes message definition mismatches and missing strategic RL files
#
# Run from anywhere. Assumes workspace at ~/ws
# Usage: bash apply_fixes.sh

set -e

WS="${HOME}/ws"
SRC="${WS}/src"

echo "=============================================="
echo "  A.U.R.A. Integration Fix Script"
echo "=============================================="

# Ensure ROS 2 is sourced
if ! command -v ros2 &>/dev/null; then
    echo "[*] Sourcing ROS 2..."
    source /opt/ros/humble/setup.bash
fi

# ─── Fix 1: NetworkMetrics.msg (add mesh_connected) ───────────
echo ""
echo "[1/5] Fixing NetworkMetrics.msg..."
cp msg_fixes/NetworkMetrics.msg "${SRC}/aura_msgs/msg/NetworkMetrics.msg"
echo "  ✓ Added: mesh_connected field"

# ─── Fix 2: CoverageMap.msg (add Header) ──────────────────────
echo "[2/5] Fixing CoverageMap.msg..."
cp msg_fixes/CoverageMap.msg "${SRC}/aura_msgs/msg/CoverageMap.msg"
echo "  ✓ Added: std_msgs/Header header"

# ─── Fix 3: Remove orphan SwarmStatus.msg ──────────────────────
echo "[3/5] Removing orphan SwarmStatus.msg..."
if [ -f "${SRC}/aura_msgs/msg/SwarmStatus.msg" ]; then
    rm "${SRC}/aura_msgs/msg/SwarmStatus.msg"
    echo "  ✓ Removed SwarmStatus.msg (SwarmState.msg is the canonical one)"
else
    echo "  ✓ Already absent"
fi

# ─── Fix 4: Restore missing strategic RL files ────────────────
echo "[4/5] Restoring missing aura_strategic_rl files..."
RL_DIR="${SRC}/aura_strategic_rl/aura_strategic_rl"

for f in spaces.py rewards.py policy.py swarm_gym_env.py; do
    if [ -f "${RL_DIR}/${f}" ]; then
        echo "  ⚠ ${f} already exists — backing up to ${f}.bak"
        cp "${RL_DIR}/${f}" "${RL_DIR}/${f}.bak"
    fi
    cp "strategic_rl_fixes/${f}" "${RL_DIR}/${f}"
    echo "  ✓ Installed ${f}"
done

# ─── Fix 5: Rebuild ───────────────────────────────────────────
echo ""
echo "[5/5] Rebuilding workspace..."
cd "${WS}"

# Rebuild aura_msgs first (message changes propagate to all dependents)
echo "  Building aura_msgs..."
colcon build --packages-select aura_msgs 2>&1 | tail -3
source install/setup.bash

# Rebuild everything
echo "  Building all packages..."
colcon build 2>&1 | tail -5
source install/setup.bash

echo ""
echo "=============================================="
echo "  All fixes applied!"
echo "=============================================="
echo ""
echo "Verify with:"
echo "  ros2 interface show aura_msgs/msg/NetworkMetrics | grep mesh_connected"
echo "  ros2 interface show aura_msgs/msg/CoverageMap | grep header"
echo "  timeout 5 ros2 run aura_network_sim network_sim_node 2>&1 || true"
echo ""
