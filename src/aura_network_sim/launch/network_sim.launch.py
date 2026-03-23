"""
Network Simulation Launch File

Launches all network simulation nodes:
- network_sim_node: Main simulation
- coverage_calculator_node: Statistics and analysis
- mesh_visualizer_node: RViz2 visualization
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get package directory
    pkg_dir = get_package_share_directory('aura_network_sim')
    config_file = os.path.join(pkg_dir, 'config', 'network_sim_params.yaml')
    
    # Launch arguments
    update_rate_arg = DeclareLaunchArgument(
        'update_rate',
        default_value='10.0',
        description='Network simulation update rate (Hz)'
    )
    
    area_size_arg = DeclareLaunchArgument(
        'area_size',
        default_value='200.0',
        description='Coverage area half-size (meters)'
    )
    
    grid_res_arg = DeclareLaunchArgument(
        'grid_resolution',
        default_value='10.0',
        description='Coverage grid resolution (meters)'
    )
    
    enable_viz_arg = DeclareLaunchArgument(
        'enable_visualization',
        default_value='true',
        description='Enable RViz2 visualization markers'
    )
    
    # Main network simulation node
    network_sim_node = Node(
        package='aura_network_sim',
        executable='network_sim_node',
        name='network_sim',
        parameters=[
            config_file,
            {
                'update_rate_hz': LaunchConfiguration('update_rate'),
            }
        ],
        output='screen',
        emulate_tty=True,
    )
    
    # Coverage calculator node
    coverage_calc_node = Node(
        package='aura_network_sim',
        executable='coverage_calculator_node',
        name='coverage_calculator',
        parameters=[config_file],
        output='screen',
        emulate_tty=True,
    )
    
    # Mesh visualizer node (optional)
    mesh_viz_node = Node(
        package='aura_network_sim',
        executable='mesh_visualizer_node',
        name='mesh_visualizer',
        parameters=[config_file],
        output='screen',
        emulate_tty=True,
        condition=None,  # Always run for now
    )
    
    return LaunchDescription([
        update_rate_arg,
        area_size_arg,
        grid_res_arg,
        enable_viz_arg,
        network_sim_node,
        coverage_calc_node,
        mesh_viz_node,
    ])
