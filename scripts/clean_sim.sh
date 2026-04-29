#!/bin/bash
echo "Killing all simulation processes..."
pkill -9 -f gzserver 2>/dev/null
pkill -9 -f gzclient 2>/dev/null
pkill -9 -f px4 2>/dev/null
pkill -9 -f MicroXRCE 2>/dev/null
pkill -f "px4_dds_bridge\|network_sim\|coverage_calc\|mission_control\|dead_zone\|strategic_rl" 2>/dev/null

sleep 2

for port in $(seq 14540 14560) $(seq 18570 18580) $(seq 4560 4570) 11345 8888; do
  fuser -k ${port}/tcp 2>/dev/null
  fuser -k ${port}/udp 2>/dev/null
done

sudo sysctl -w net.ipv4.tcp_tw_reuse=1 2>/dev/null
sudo sysctl -w net.ipv4.tcp_fin_timeout=5 2>/dev/null

sleep 8

if pgrep -f "gzserver|px4|MicroXRCE" > /dev/null 2>&1; then
  pkill -9 -f "gzserver|px4|MicroXRCE" 2>/dev/null
  sleep 2
fi

echo "Clean. Ready to launch."
