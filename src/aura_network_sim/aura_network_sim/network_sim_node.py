#!/usr/bin/env python3
"""
Network Simulation Node

Main ROS 2 node for A.U.R.A. network simulation.
Subscribes to drone states, computes network metrics, publishes results.
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy

import numpy as np
from typing import Dict, List, Optional

from geometry_msgs.msg import Point
from std_msgs.msg import Header

# Import our simulation modules
from .propagation import RadioConfig, D2D_CONFIG, D2G_CONFIG
from .mesh_simulator import MeshSimulator, DroneNetworkState
from .coverage_calculator import CoverageCalculator

# Import A.U.R.A. messages
try:
    from aura_msgs.msg import DroneState, SwarmState, NetworkMetrics, CoverageMap
except ImportError:
    # Define minimal message stubs for standalone testing
    DroneState = None
    SwarmState = None
    NetworkMetrics = None
    CoverageMap = None


class NetworkSimNode(Node):
    """
    Main network simulation node.
    
    Subscribes:
        /swarm/state (SwarmState): Current drone positions and states
        
    Publishes:
        /network/metrics (NetworkMetrics): Network performance metrics
        /network/coverage_map (CoverageMap): Ground coverage data
    """
    
    def __init__(self):
        super().__init__('network_sim')
        
        # Declare global parameters (from /**:)
        self.declare_parameter('tx_power_dbm', 20.0)
        self.declare_parameter('noise_floor_dbm', -100.0)
        self.declare_parameter('path_loss_exponent', 2.7)
        self.declare_parameter('reference_distance_m', 1.0)
        self.declare_parameter('max_mesh_distance_m', 150.0)
        self.declare_parameter('min_snr_db', 10.0)
        self.declare_parameter('signal_noise_std_db', 2.0)
        
        # Declare node-specific parameters
        self.declare_parameter('update_rate_hz', 10.0)
        self.declare_parameter('area_x_min', -200.0)
        self.declare_parameter('area_x_max', 200.0)
        self.declare_parameter('area_y_min', -200.0)
        self.declare_parameter('area_y_max', 200.0)
        self.declare_parameter('grid_resolution_m', 10.0)
        self.declare_parameter('hub_drone_id', 0)
        self.declare_parameter('ground_height_m', 0.0)
        self.declare_parameter('routing_strategy', 'hub_leaf')
        
        # Get global parameters
        tx_power = self.get_parameter('tx_power_dbm').value
        noise_floor = self.get_parameter('noise_floor_dbm').value
        path_loss_exp = self.get_parameter('path_loss_exponent').value
        ref_distance = self.get_parameter('reference_distance_m').value
        max_mesh_dist = self.get_parameter('max_mesh_distance_m').value
        min_snr = self.get_parameter('min_snr_db').value
        signal_noise = self.get_parameter('signal_noise_std_db').value
        
        # Get node-specific parameters
        update_rate = self.get_parameter('update_rate_hz').value
        x_min = self.get_parameter('area_x_min').value
        x_max = self.get_parameter('area_x_max').value
        y_min = self.get_parameter('area_y_min').value
        y_max = self.get_parameter('area_y_max').value
        grid_res = self.get_parameter('grid_resolution_m').value
        self.hub_drone_id = self.get_parameter('hub_drone_id').value
        ground_height = self.get_parameter('ground_height_m').value
        self.routing_strategy = self.get_parameter('routing_strategy').value
        
        # Create radio configs from parameters
        d2d_config = RadioConfig.from_ros_params(
            tx_power_dbm=tx_power,
            noise_floor_dbm=noise_floor,
            path_loss_exponent=path_loss_exp,
            reference_distance_m=ref_distance,
            max_mesh_distance_m=max_mesh_dist,
            min_snr_db=min_snr,
            signal_noise_std_db=signal_noise,
            frequency_ghz=5.8,  # D2D uses 5 GHz
        )
        
        d2g_config = RadioConfig.from_ros_params(
            tx_power_dbm=tx_power,
            noise_floor_dbm=noise_floor,
            path_loss_exponent=path_loss_exp + 0.3,  # Slightly worse for air-to-ground
            reference_distance_m=ref_distance,
            max_mesh_distance_m=max_mesh_dist * 1.5,  # Ground coverage can be larger
            min_snr_db=min_snr,
            signal_noise_std_db=signal_noise + 1.0,  # More variable
            frequency_ghz=2.4,  # D2G uses 2.4 GHz
        )
        
        # Initialize simulators with configured parameters
        self.mesh_sim = MeshSimulator(config=d2d_config)
        self.coverage_calc = CoverageCalculator(
            config=d2g_config,
            area_bounds=(x_min, y_min, x_max, y_max),
            resolution_m=grid_res,
            ground_height=ground_height
        )
        
        # QoS profile
        qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            durability=DurabilityPolicy.VOLATILE,
            depth=10
        )
        
        # Subscribers
        if SwarmState is not None:
            self.swarm_sub = self.create_subscription(
                SwarmState, '/swarm/state',
                self.swarm_state_callback, qos
            )
        else:
            self.get_logger().warn('SwarmState message not available, using test data')
            self.swarm_sub = None
        
        # Publishers
        if NetworkMetrics is not None:
            self.metrics_pub = self.create_publisher(
                NetworkMetrics, '/network/metrics', qos
            )
        else:
            self.metrics_pub = None
        
        if CoverageMap is not None:
            self.coverage_pub = self.create_publisher(
                CoverageMap, '/network/coverage_map', qos
            )
        else:
            self.coverage_pub = None
        
        # Timer for periodic updates
        self.update_timer = self.create_timer(
            1.0 / update_rate, self.update_callback
        )
        
        # State
        self.latest_swarm_state = None
        self.update_count = 0
        
        self.get_logger().info(
            f'Network simulation node started '
            f'(rate: {update_rate} Hz, grid: {grid_res}m, '
            f'area: {x_min},{y_min} to {x_max},{y_max})'
        )
    
    def swarm_state_callback(self, msg):
        """Handle incoming swarm state"""
        self.latest_swarm_state = msg
        
        # Update mesh simulator with drone positions
        for drone in msg.drones:
            position = np.array([
                drone.position.x,
                drone.position.y,
                drone.position.z
            ])
            
            is_hub = (drone.drone_id == self.hub_drone_id or 
                      drone.role == DroneState.ROLE_HUB)
            
            self.mesh_sim.update_drone(
                drone.drone_id, position, is_hub
            )
    
    def update_callback(self):
        """Periodic network simulation update"""
        self.update_count += 1
        
        # Compute mesh connectivity
        self.mesh_sim.compute_connectivity()
        mesh_stats = self.mesh_sim.get_mesh_stats()
        
        # Compute ground coverage
        coverage_result = self.coverage_calc.compute_coverage(self.mesh_sim.drones)
        
        # Log stats periodically
        if self.update_count % 50 == 0:
            self.get_logger().info(
                f'Network: {mesh_stats["num_drones"]} drones, '
                f'{mesh_stats["num_links"]} links, '
                f'mesh={"OK" if mesh_stats["is_connected"] else "BROKEN"}, '
                f'coverage={coverage_result.coverage_percent:.1f}%'
            )
        
        # Publish metrics
        if self.metrics_pub is not None:
            self._publish_metrics(mesh_stats, coverage_result)
        
        # Publish coverage map
        if self.coverage_pub is not None:
            self._publish_coverage_map(coverage_result)
    
    def _publish_metrics(self, mesh_stats: Dict, coverage_result):
        """Build and publish NetworkMetrics message"""
        msg = NetworkMetrics()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'map'
        
        # Grid info
        msg.grid_size_x = coverage_result.grid_size_x
        msg.grid_size_y = coverage_result.grid_size_y
        msg.cell_size_meters = coverage_result.cell_size_m
        msg.origin = Point(
            x=coverage_result.origin_x,
            y=coverage_result.origin_y,
            z=0.0
        )
        
        # Flatten coverage data
        msg.signal_strength_dbm = coverage_result.signal_strength.flatten().tolist()
        msg.throughput_mbps = coverage_result.throughput.flatten().tolist()
        msg.coverage_mask = coverage_result.coverage_mask.flatten().tolist()
        
        # Aggregate stats
        msg.total_coverage_percent = coverage_result.coverage_percent
        msg.avg_signal_strength_dbm = coverage_result.avg_signal_dbm
        msg.avg_throughput_mbps = mesh_stats['avg_throughput_mbps']
        msg.avg_latency_ms = mesh_stats['avg_latency_ms']
        
        # Link info
        links = self.mesh_sim.get_link_info()
        for link in links:
            msg.link_from_drone.append(link['from_id'])
            msg.link_to_drone.append(link['to_id'])
            msg.link_rssi_dbm.append(link['rssi_dbm'])
            msg.link_throughput_mbps.append(link['rate_mbps'])
            msg.link_latency_ms.append(5.0)  # Simplified per-hop latency
        
        # Mesh status
        msg.mesh_connected = bool(mesh_stats['is_connected'])
        msg.backhaul_active = any(d.is_hub and d.hops_to_hub == 0 
                                   for d in self.mesh_sim.drones.values())
        
        self.metrics_pub.publish(msg)
    
    def _publish_coverage_map(self, coverage_result):
        """Build and publish CoverageMap message"""
        msg = CoverageMap()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'map'
        
        msg.grid_size_x = coverage_result.grid_size_x
        msg.grid_size_y = coverage_result.grid_size_y
        msg.cell_size_meters = coverage_result.cell_size_m
        msg.origin = Point(
            x=coverage_result.origin_x,
            y=coverage_result.origin_y,
            z=0.0
        )
        
        msg.is_covered = coverage_result.coverage_mask.flatten().tolist()
        msg.coverage_quality = (
            (coverage_result.signal_strength + 100) / 50  # Normalize -100 to -50 -> 0 to 1
        ).clip(0, 1).flatten().tolist()
        
        # Demand level (uniform for now)
        msg.demand_level = [1.0] * (coverage_result.grid_size_x * coverage_result.grid_size_y)
        
        # Target area (all cells)
        msg.is_target = [True] * (coverage_result.grid_size_x * coverage_result.grid_size_y)
        
        self.coverage_pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    
    node = NetworkSimNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
