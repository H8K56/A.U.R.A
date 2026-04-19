#!/bin/bash
echo "Killing all simulation processes..."
pkill -9 -f gzserver 2>/dev/null
pkill -9 -f gzclient 2>/dev/null
pkill -9 -f px4 2>/dev/null
pkill -9 -f MicroXRCE 2>/dev/null
pkill -9 -f "sitl_multiple" 2>/dev/null
pkill -f "sim_swarm\|network_sim\|coverage_calc\|mission_control\|dead_zone\|strategic_rl_node" 2>/dev/null

# Kill any zombie gazebo processes
pkill -9 -f "gz\b" 2>/dev/null

# Wait for ports to release
sleep 3

# Verify nothing is left
remaining=$(pgrep -c -f "gzserver|px4|MicroXRCE" 2>/dev/null || echo "0")
if [ "$remaining" -gt "0" ]; then
    echo "WARNING: $remaining processes still running, force killing..."
    pkill -9 -f "gzserver|px4|MicroXRCE"
    sleep 2
fi

# Check the specific port Gazebo uses (11345)
if ss -tlnp 2>/dev/null | grep -q ":11345"; then
    echo "WARNING: Port 11345 still in use, waiting..."
    sleep 5
fi

echo "Clean. Ready to launch."