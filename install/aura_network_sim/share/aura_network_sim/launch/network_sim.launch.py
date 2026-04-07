from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():

    pkg_dir = get_package_share_directory('aura_network_sim')
    config_file = os.path.join(pkg_dir, 'config', 'network_sim_params.yaml')

    # Arguments
    update_rate = LaunchConfiguration('update_rate')
    area_size = LaunchConfiguration('area_size')
    grid_resolution = LaunchConfiguration('grid_resolution')
    enable_viz = LaunchConfiguration('enable_visualization')
    use_sim_time = LaunchConfiguration('use_sim_time')
    namespace = LaunchConfiguration('namespace')

    return LaunchDescription([

        DeclareLaunchArgument('update_rate', default_value='10.0'),
        DeclareLaunchArgument('area_size', default_value='200.0'),
        DeclareLaunchArgument('grid_resolution', default_value='10.0'),
        DeclareLaunchArgument('enable_visualization', default_value='true'),
        DeclareLaunchArgument('use_sim_time', default_value='true'),
        DeclareLaunchArgument('namespace', default_value=''),

        Node(
            package='aura_network_sim',
            executable='network_sim_node',
            name='network_sim',
            namespace=namespace,
            parameters=[
                config_file,
                {
                    'update_rate_hz': update_rate,
                    'grid_resolution_m': grid_resolution,
                    'use_sim_time': use_sim_time,
                }
            ],
            output='screen',
            emulate_tty=True,
        ),

        Node(
            package='aura_network_sim',
            executable='coverage_calculator_node',
            name='coverage_calculator',
            namespace=namespace,
            parameters=[config_file],
            output='screen',
            emulate_tty=True,
        ),

        Node(
            package='aura_network_sim',
            executable='mesh_visualizer_node',
            name='mesh_visualizer',
            namespace=namespace,
            parameters=[config_file],
            output='screen',
            emulate_tty=True,
            condition=IfCondition(enable_viz),
        ),
    ])