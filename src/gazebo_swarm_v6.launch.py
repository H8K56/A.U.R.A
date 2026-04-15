"""
A.U.R.A. Gazebo + PX4 SITL Launch (v6 — microDDS, no MAVROS)

Uses MicroXRCE-DDS agent for PX4 ↔ ROS 2 communication.
No MAVROS dependency. PX4 publishes directly as ROS 2 topics
via px4_msgs.

Components:
    1. PX4 multi-drone SITL (Gazebo Classic)
    2. MicroXRCE-DDS agent (bridges PX4 to ROS 2)
    3. PX4 DDS Bridge (translates px4_msgs ↔ aura_msgs)
    4. A.U.R.A. stack (network_sim, coverage, RL, mission_control)

PX4 topic scheme per instance N (1-based):
    /px4_N/fmu/out/vehicle_local_position_v1
    /px4_N/fmu/out/vehicle_status_v1
    /px4_N/fmu/in/vehicle_command
    /px4_N/fmu/in/trajectory_setpoint

Prerequisites:
    pkill -9 -f gzserver; pkill -9 -f px4; pkill -9 -f MicroXRCE; sleep 5

Usage:
    ros2 launch aura_simulation gazebo_swarm.launch.py
    ros2 launch aura_simulation gazebo_swarm.launch.py num_drones:=3
"""

import os
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    ExecuteProcess,
    TimerAction,
    OpaqueFunction,
)
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('num_drones', default_value='5'),
        DeclareLaunchArgument('world', default_value='earthquake_city'),
        OpaqueFunction(function=launch_setup),
    ])


def launch_setup(context, *args, **kwargs):
    num_drones = int(context.launch_configurations.get('num_drones', '5'))
    world = context.launch_configurations.get('world', 'earthquake_city')

    px4_dir = os.path.expanduser('~/PX4-Autopilot')
    multi_script = os.path.join(
        px4_dir, 'Tools', 'simulation', 'gazebo-classic',
        'sitl_multiple_run.sh')

    # Symlink world into PX4 worlds directory
    px4_worlds = os.path.join(
        px4_dir, 'Tools', 'simulation', 'gazebo-classic',
        'sitl_gazebo-classic', 'worlds')
    aura_world = os.path.expanduser(f'~/ws/worlds/{world}.world')
    px4_world = os.path.join(px4_worlds, f'{world}.world')
    if os.path.exists(aura_world) and not os.path.exists(px4_world):
        try:
            os.symlink(aura_world, px4_world)
        except OSError:
            pass

    # Config helper
    def _cfg(pkg_name, config_name):
        try:
            d = get_package_share_directory(pkg_name)
            p = os.path.join(d, 'config', config_name)
            if os.path.exists(p):
                return p
        except Exception:
            pass
        return ''

    sim_config = _cfg('aura_simulation', 'sim_params.yaml')

    actions = []

    # ═══ 1. PX4 MULTI-DRONE SITL ═════════════════════════
    actions.append(ExecuteProcess(
        cmd=[
            'bash', multi_script,
            '-n', str(num_drones),
            '-m', 'iris',
            '-w', world,
        ],
        output='screen',
        additional_env={
            'PX4_HOME_LAT': '0.0',
            'PX4_HOME_LON': '0.0',
            'PX4_HOME_ALT': '0.0',
        },
    ))

    # ═══ 2. MicroXRCE-DDS AGENT ══════════════════════════
    #
    # PX4's uxrce_dds_client connects to agent on UDP port 8888.
    # The agent bridges PX4 uORB topics to ROS 2 DDS.
    # All PX4 instances share the same agent.
    actions.append(TimerAction(
        period=15.0,
        actions=[ExecuteProcess(
            cmd=['MicroXRCEAgent', 'udp4', '-p', '8888'],
            output='screen',
        )],
    ))

    # ═══ 3. PX4 DDS BRIDGE ═══════════════════════════════
    #
    # Wait for PX4 + agent to establish topics (~25s)
    actions.append(TimerAction(
        period=35.0,
        actions=[Node(
            package='aura_simulation',
            executable='px4_dds_bridge',
            name='px4_dds_bridge',
            output='screen',
            parameters=[
                sim_config,
                {'num_drones': num_drones},
            ],
        )],
    ))

    # ═══ 4. A.U.R.A. STACK ═══════════════════════════════
    aura_start = 38.0

    aura_nodes = [
        ('aura_simulation', 'dead_zone_publisher', 'dead_zone_publisher', 0.0),
        ('aura_network_sim', 'network_sim_node', 'network_sim', 0.5),
        ('aura_network_sim', 'coverage_calculator_node', 'coverage_calculator', 1.0),
        ('aura_strategic_rl', 'strategic_rl_node', 'strategic_rl', 1.5),
        ('aura_mission_control', 'mission_control_node', 'mission_control', 2.0),
    ]

    for pkg, exe, name, offset in aura_nodes:
        actions.append(TimerAction(
            period=aura_start + offset,
            actions=[Node(
                package=pkg,
                executable=exe,
                name=name,
                output='screen',
                parameters=[
                    sim_config,
                    {'num_drones': num_drones},
                ],
            )],
        ))

    return actions
