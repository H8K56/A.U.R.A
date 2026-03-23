"""
Launch file for multi-drone PX4 swarm.

Launches:
- px4_interface_node for each drone
- swarm_px4_manager_node for coordinated control
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def launch_setup(context, *args, **kwargs):
    pkg_dir = get_package_share_directory('aura_px4_interface')
    config_file = os.path.join(pkg_dir, 'config', 'px4_interface_params.yaml')
    
    num_drones = int(LaunchConfiguration('num_drones').perform(context))
    
    nodes = []
    
    # Launch individual drone interfaces
    for i in range(num_drones):
        node = Node(
            package='aura_px4_interface',
            executable='px4_interface_node',
            name='px4_interface',
            namespace=f'drone_{i}',
            parameters=[
                config_file,
                {'drone_id': i}
            ],
            output='screen'
        )
        nodes.append(node)
    
    # Swarm manager
    swarm_manager = Node(
        package='aura_px4_interface',
        executable='swarm_px4_manager_node',
        name='swarm_px4_manager',
        parameters=[
            config_file,
            {'num_drones': num_drones}
        ],
        output='screen'
    )
    nodes.append(swarm_manager)
    
    return nodes


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'num_drones',
            default_value='5',
            description='Number of drones in the swarm'
        ),
        OpaqueFunction(function=launch_setup)
    ])