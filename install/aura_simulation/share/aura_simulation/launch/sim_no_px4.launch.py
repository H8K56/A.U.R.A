"""
A.U.R.A. Software-in-the-Loop Simulation Launch

Launches the complete A.U.R.A. stack using simulated drones
(no PX4 SITL or Gazebo required). This is the primary
development and testing launch file.

Nodes launched:
  1. sim_swarm_driver      — Simulated drone swarm
  2. dead_zone_publisher   — Network dead zones
  3. network_sim_node      — Network coverage simulation
  4. coverage_calculator   — Coverage map computation
  5. strategic_rl_node     — RL/baseline positioning policy
  6. mission_control_node  — Mission state machine
  7. mission_monitor       — CLI dashboard (optional)
  8. scenario_runner       — Automated test driver (optional)

Usage:
    # Basic run (auto-starts mission):
    ros2 launch aura_simulation sim_no_px4.launch.py

    # With dead zone injection test:
    ros2 launch aura_simulation sim_no_px4.launch.py inject_dead_zone:=true

    # Custom drone count:
    ros2 launch aura_simulation sim_no_px4.launch.py num_drones:=3

    # Without auto-start (manual trigger via service):
    ros2 launch aura_simulation sim_no_px4.launch.py auto_start:=false
"""

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    sim_pkg = get_package_share_directory('aura_simulation')
    config_file = os.path.join(sim_pkg, 'config', 'sim_params.yaml')

    # Also load package-specific configs if they exist
    net_pkg = get_package_share_directory('aura_network_sim')
    net_config = os.path.join(net_pkg, 'config', 'network_sim_params.yaml')

    mc_pkg = get_package_share_directory('aura_mission_control')
    mc_config = os.path.join(mc_pkg, 'config', 'mission_control_params.yaml')

    return LaunchDescription([
        # ── Launch arguments ────────────────────────────────
        DeclareLaunchArgument('num_drones', default_value='5'),
        DeclareLaunchArgument('auto_start', default_value='true'),
        DeclareLaunchArgument('inject_dead_zone', default_value='false'),
        DeclareLaunchArgument('ops_duration', default_value='300.0'),
        DeclareLaunchArgument('use_baseline', default_value='true'),
        DeclareLaunchArgument('enable_monitor', default_value='false'),
        DeclareLaunchArgument('enable_scenario_runner', default_value='false'),

        # ── 1. Sim Swarm Driver ─────────────────────────────
        Node(
            package='aura_simulation',
            executable='sim_swarm_driver',
            name='sim_swarm_driver',
            output='screen',
            parameters=[
                config_file,
                {'num_drones': LaunchConfiguration('num_drones')},
            ],
        ),

        # ── 2. Dead Zone Publisher ──────────────────────────
        Node(
            package='aura_simulation',
            executable='dead_zone_publisher',
            name='dead_zone_publisher',
            output='screen',
            parameters=[config_file],
        ),

        # ── 3. Network Simulation ───────────────────────────
        # Delayed slightly to let swarm driver start first
        TimerAction(
            period=1.0,
            actions=[
                Node(
                    package='aura_network_sim',
                    executable='network_sim_node',
                    name='network_sim',
                    output='screen',
                    parameters=[config_file],
                ),
            ],
        ),

        # ── 4. Coverage Calculator ──────────────────────────
        TimerAction(
            period=1.5,
            actions=[
                Node(
                    package='aura_network_sim',
                    executable='coverage_calculator_node',
                    name='coverage_calculator',
                    output='screen',
                    parameters=[config_file],
                ),
            ],
        ),

        # ── 5. Strategic RL / Baseline ──────────────────────
        TimerAction(
            period=2.0,
            actions=[
                Node(
                    package='aura_strategic_rl',
                    executable='strategic_rl_node',
                    name='strategic_rl',
                    output='screen',
                    parameters=[
                        config_file,
                        {'use_baseline': LaunchConfiguration('use_baseline')},
                    ],
                ),
            ],
        ),

        # ── 6. Mission Control ──────────────────────────────
        TimerAction(
            period=2.5,
            actions=[
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
            ],
        ),

        # ── 7. Scenario Runner (optional) ───────────────────
        # Only useful for automated testing
        # TimerAction(
        #     period=3.0,
        #     actions=[
        #         Node(
        #             package='aura_simulation',
        #             executable='scenario_runner',
        #             name='scenario_runner',
        #             output='screen',
        #             parameters=[
        #                 config_file,
        #                 {'inject_dead_zone': LaunchConfiguration('inject_dead_zone')},
        #             ],
        #             condition=IfCondition(LaunchConfiguration('enable_scenario_runner')),
        #         ),
        #     ],
        # ),
    ])
