#!/bin/bash
echo "Killing all simulation processes..."
pkill -9 -f gzserver 2>/dev/null
pkill -9 -f gzclient 2>/dev/null
pkill -9 -f px4 2>/dev/null
pkill -9 -f MicroXRCE 2>/dev/null
pkill -f "px4_dds_bridge\|network_sim\|coverage_calc\|mission_control\|dead_zone\|strategic_rl" 2>/dev/null

sleep 2

fuser -k 9090/tcp 2>/dev/null; sleep 2

for port in $(seq 14540 14560) $(seq 18570 18580) $(seq 4560 4570) 11345 8888; do
  fuser -k ${port}/tcp 2>/dev/null
  fuser -k ${port}/udp 2>/dev/null
done

# Force-close any lingering sockets (TIME_WAIT, CLOSE_WAIT) on MAVLink TCP ports
for port in $(seq 4560 4570); do
  ss -K "sport = :${port}" 2>/dev/null || true
  ss -K "dport = :${port}" 2>/dev/null || true
done

sudo sysctl -w net.ipv4.tcp_tw_reuse=1 2>/dev/null
sudo sysctl -w net.ipv4.tcp_fin_timeout=5 2>/dev/null

# Verify all MAVLink ports are actually free before returning
echo "Verifying MAVLink ports are free..."
for port in $(seq 4561 4570); do
  for t in $(seq 1 15); do
    if ! ss -tlnp 2>/dev/null | grep -q ":${port} "; then
      break
    fi
    if [ $t -eq 15 ]; then
      echo "WARNING: Port $port still bound, force-killing owner..."
      fuser -k ${port}/tcp 2>/dev/null || true
      ss -K "sport = :${port}" 2>/dev/null || true
    fi
    sleep 1
  done
done

sleep 3

if pgrep -f "gzserver|px4|MicroXRCE" > /dev/null 2>&1; then
  pkill -9 -f "gzserver|px4|MicroXRCE" 2>/dev/null
  sleep 2
fi

echo "Clean. Ready to launch."
