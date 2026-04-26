```bash
#!/usr/bin/env bash
set -e

OUTDIR="aura_debug_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$OUTDIR"

echo "Collecting diagnostics into $OUTDIR"

# -------------------------------------------------
# SYSTEM INFO
# -------------------------------------------------
{
echo "===== DATE ====="
date

echo "===== OS ====="
uname -a
cat /etc/os-release 2>/dev/null || true

echo "===== CPU ====="
lscpu 2>/dev/null || true

echo "===== MEMORY ====="
free -h 2>/dev/null || true

echo "===== GPU ====="
nvidia-smi 2>/dev/null || true
glxinfo 2>/dev/null | grep -E "OpenGL vendor|OpenGL renderer" || true

echo "===== DISK ====="
df -h
} > "$OUTDIR/system.txt"

# -------------------------------------------------
# DOCKER
# -------------------------------------------------
{
docker ps -a
docker images
} > "$OUTDIR/docker.txt" 2>/dev/null || true

# -------------------------------------------------
# ROS2 BASICS
# -------------------------------------------------
{
printenv | grep -E "ROS|RMW|GAZEBO|PX4"
} > "$OUTDIR/env_ros.txt"

{
ros2 doctor --report
} > "$OUTDIR/ros2_doctor.txt" 2>/dev/null || true

{
ros2 node list
} > "$OUTDIR/ros2_nodes.txt" 2>/dev/null || true

{
ros2 topic list -t
} > "$OUTDIR/ros2_topics.txt" 2>/dev/null || true

{
ros2 service list
} > "$OUTDIR/ros2_services.txt" 2>/dev/null || true

{
ros2 action list
} > "$OUTDIR/ros2_actions.txt" 2>/dev/null || true

# -------------------------------------------------
# TOPIC RATES
# -------------------------------------------------
timeout 5 ros2 topic hz /swarm/state \
> "$OUTDIR/topic_hz_swarm_state.txt" 2>&1 || true

timeout 5 ros2 topic hz /coverage/goals \
> "$OUTDIR/topic_hz_coverage_goals.txt" 2>&1 || true

# -------------------------------------------------
# SAMPLE MESSAGES
# -------------------------------------------------
timeout 5 ros2 topic echo /swarm/state --once \
> "$OUTDIR/swarm_state_sample.txt" 2>&1 || true

timeout 5 ros2 topic echo /coverage/goals --once \
> "$OUTDIR/coverage_goals_sample.txt" 2>&1 || true

# -------------------------------------------------
# PARAMS
# -------------------------------------------------
mkdir -p "$OUTDIR/params"

ros2 node list 2>/dev/null || true | while read -r node; do
  SAFE=$(echo "$node" | sed 's#/#_#g')
  ros2 param dump "$node" > "$OUTDIR/params/${SAFE}.yaml" 2>/dev/null || true
done

# -------------------------------------------------
# PROCESSES
# -------------------------------------------------
{
ps aux | grep -E "px4|gazebo|gzserver|gzclient|ros2|python" | grep -v grep
} > "$OUTDIR/processes.txt"

# -------------------------------------------------
# NETWORK PORTS
# -------------------------------------------------
{
ss -tulnp
} > "$OUTDIR/ports.txt" 2>/dev/null || true

# -------------------------------------------------
# PROJECT TREE
# -------------------------------------------------
if [ -d ~/ws ]; then
  tree -L 4 ~/ws > "$OUTDIR/ws_tree.txt" 2>/dev/null || find ~/ws -maxdepth 4 > "$OUTDIR/ws_tree.txt"
fi

# -------------------------------------------------
# IMPORTANT FILES
# -------------------------------------------------
mkdir -p "$OUTDIR/project_files"

find ~/ws -type f \( \
-name "*.py" -o \
-name "*.yaml" -o \
-name "*.yml" -o \
-name "*.launch.py" -o \
-name "*.xml" -o \
-name "*.world" -o \
-name "*.sdf" \
\) | while read -r f; do
  cp --parents "$f" "$OUTDIR/project_files/" 2>/dev/null || true
done

# -------------------------------------------------
# COMPRESS
# -------------------------------------------------
tar -czf "${OUTDIR}.tar.gz" "$OUTDIR"

echo "Done."
echo "Archive: ${OUTDIR}.tar.gz"
```