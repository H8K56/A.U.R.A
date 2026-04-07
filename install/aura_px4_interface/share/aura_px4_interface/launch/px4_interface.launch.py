"""
Launch file for single drone PX4 interface.
"""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_dir = get_package_share_directory('aura_px4_interface')
    config_file = os.path.join(pkg_dir, 'config', 'px4_interface_params.yaml')
    
    # Declare arguments
    drone_id_arg = DeclareLaunchArgument(
        'drone_id',
        default_value='0',
        description='Drone ID'
    )
    
    drone_id = LaunchConfiguration('drone_id')
    
    # PX4 interface node
    px4_interface_node = Node(
        package='aura_px4_interface',
        executable='px4_interface_node',
        name='px4_interface',
        namespace=['drone_', drone_id],
        parameters=[
            config_file,
            {'drone_id': drone_id}
        ],
        output='screen'
    )
    
    return LaunchDescription([
        drone_id_arg,
        px4_interface_node
    ])