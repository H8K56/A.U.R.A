#!/bin/bash
echo "Killing all simulation processes..."
pkill -9 -f gzserver 2>/dev/null
pkill -9 -f gzclient 2>/dev/null
pkill -9 -f px4 2>/dev/null
pkill -9 -f MicroXRCE 2>/dev/null
pkill -9 -f "gz sim" 2>/dev/null
pkill -9 -f simulator_mavlink 2>/dev/null
pkill -9 -f sitl_multiple 2>/dev/null

# Kill any process on Gazebo ports
for port in 11345 11346; do
    fuser -k ${port}/tcp 2>/dev/null
done

# Kill TCP simulator ports (4560-4565)
for port in $(seq 4560 4570); do
    fuser -k ${port}/tcp 2>/dev/null
done

sleep 2

# Verify
remaining=$(pgrep -f "gzserver|px4|MicroXRCE" 2>/dev/null | wc -l)
if [ "$remaining" -gt "0" ]; then
    echo "Force killing $remaining remaining processes..."
    pkill -9 -f "gzserver|px4|MicroXRCE" 2>/dev/null
    sleep 2
fi

# Wait for ports to release
echo "Waiting for ports..."
sleep 3

# Check ports
if ss -tlnp 2>/dev/null | grep -qE "11345|4560"; then
    echo "WARNING: Ports still in use, waiting 5 more seconds..."
    sleep 5
fi

echo "Clean. Ready to launch."
