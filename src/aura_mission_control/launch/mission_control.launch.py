"""
Launch file for A.U.R.A. Mission Control

Usage:
    ros2 launch aura_mission_control mission_control.launch.py
    ros2 launch aura_mission_control mission_control.launch.py auto_start:=true
    ros2 launch aura_mission_control mission_control.launch.py num_drones:=3
"""

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_dir = get_package_share_directory('aura_mission_control')
    config_file = os.path.join(pkg_dir, 'config', 'mission_control_params.yaml')

    return LaunchDescription([
        # ── Launch arguments ────────────────────────
        DeclareLaunchArgument(
            'auto_start', default_value='false',
            description='Auto-start mission on node launch'),

        DeclareLaunchArgument(
            'num_drones', default_value='5',
            description='Expected number of drones'),

        DeclareLaunchArgument(
            'ops_duration', default_value='600.0',
            description='Operations duration in seconds (0=unlimited)'),

        # ── Mission Control Node ────────────────────
        Node(
            package='aura_mission_control',
            executable='mission_control_node',
            name='mission_control',
            output='screen',
            parameters=[
                config_file,
                {
                    'auto_start': LaunchConfiguration('auto_start'),
                    'num_drones': LaunchConfiguration('num_drones'),
                    'operations_duration_sec': LaunchConfiguration('ops_duration'),
                },
            ],
        ),

        # ── Mission Monitor (optional dashboard) ───
        Node(
            package='aura_mission_control',
            executable='mission_monitor',
            name='mission_monitor',
            output='screen',
            # Monitor is passive — no parameters needed
        ),
    ])
