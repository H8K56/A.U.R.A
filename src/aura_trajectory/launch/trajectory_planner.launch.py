"""
Launch file for A.U.R.A. trajectory planning system.

Launches:
- trajectory_node for each drone
- swarm_coordinator (single instance)
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    # Get package directory
    pkg_dir = get_package_share_directory('aura_trajectory')
    config_file = os.path.join(pkg_dir, 'config', 'trajectory_params.yaml')
    
    # Launch arguments
    num_drones_arg = DeclareLaunchArgument(
        'num_drones',
        default_value='5',
        description='Number of drones in the swarm'
    )
    
    # Swarm coordinator (single instance)
    swarm_coordinator = Node(
        package='aura_trajectory',
        executable='swarm_coordinator_node',
        name='swarm_coordinator',
        parameters=[config_file],
        output='screen'
    )
    
    # Create trajectory nodes for each drone
    trajectory_nodes = []
    for i in range(5):  # Default 5 drones
        node = Node(
            package='aura_trajectory',
            executable='trajectory_node',
            name=f'trajectory_planner_{i}',
            namespace=f'drone_{i}',
            parameters=[
                config_file,
                {'drone_id': i}
            ],
            remappings=[
                ('coverage_goal', f'/drone_{i}/coverage_goal'),
                ('drone_state', f'/drone_{i}/drone_state'),
                ('trajectory_setpoint', f'/drone_{i}/trajectory_setpoint'),
            ],
            output='screen'
        )
        trajectory_nodes.append(node)
    
    return LaunchDescription([
        num_drones_arg,
        swarm_coordinator,
        *trajectory_nodes
    ])
