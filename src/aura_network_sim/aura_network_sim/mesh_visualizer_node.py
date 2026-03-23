#!/usr/bin/env python3
"""
Mesh Visualizer Node

Publishes visualization markers for RViz2:
- Drone positions as spheres
- Mesh links as lines
- Coverage map as grid
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy

import numpy as np
from typing import Optional

from std_msgs.msg import Header, ColorRGBA
from geometry_msgs.msg import Point, Vector3
from visualization_msgs.msg import Marker, MarkerArray

try:
    from aura_msgs.msg import SwarmState, NetworkMetrics
except ImportError:
    SwarmState = None
    NetworkMetrics = None


class MeshVisualizerNode(Node):
    """
    Visualization node for network state.
    
    Publishes:
        /network/viz/drones (MarkerArray): Drone position markers
        /network/viz/links (MarkerArray): Mesh link lines
        /network/viz/coverage (Marker): Coverage grid visualization
    """
    
    def __init__(self):
        super().__init__('mesh_visualizer')
        
        # Declare global parameters
        self.declare_parameter('critical_signal_threshold_dbm', -75.0)
        
        # Declare node-specific parameters
        self.declare_parameter('update_rate_hz', 5.0)
        self.declare_parameter('drone_marker_scale', 2.0)
        self.declare_parameter('link_line_width', 0.3)
        self.declare_parameter('show_signal_heatmap', True)
        self.declare_parameter('show_mesh_links', True)
        
        # Get parameters
        update_rate = self.get_parameter('update_rate_hz').value
        self.drone_scale = self.get_parameter('drone_marker_scale').value
        self.link_width = self.get_parameter('link_line_width').value
        self.show_heatmap = self.get_parameter('show_signal_heatmap').value
        self.show_links = self.get_parameter('show_mesh_links').value
        self.critical_signal = self.get_parameter('critical_signal_threshold_dbm').value
        
        # QoS
        qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE, depth=10)
        
        # State
        self.latest_swarm: Optional[SwarmState] = None
        self.latest_metrics: Optional[NetworkMetrics] = None
        
        # Subscribers
        if SwarmState is not None:
            self.swarm_sub = self.create_subscription(
                SwarmState, '/swarm/state',
                self.swarm_callback, qos
            )
        
        if NetworkMetrics is not None:
            self.metrics_sub = self.create_subscription(
                NetworkMetrics, '/network/metrics',
                self.metrics_callback, qos
            )
        
        # Publishers
        self.drone_markers_pub = self.create_publisher(
            MarkerArray, '/network/viz/drones', qos
        )
        
        self.link_markers_pub = self.create_publisher(
            MarkerArray, '/network/viz/links', qos
        )
        
        self.coverage_marker_pub = self.create_publisher(
            Marker, '/network/viz/coverage', qos
        )
        
        # Timer
        self.viz_timer = self.create_timer(1.0 / update_rate, self.publish_visualization)
        
        self.get_logger().info('Mesh visualizer started')
    
    def swarm_callback(self, msg: SwarmState):
        self.latest_swarm = msg
    
    def metrics_callback(self, msg: NetworkMetrics):
        self.latest_metrics = msg
    
    def publish_visualization(self):
        """Publish all visualization markers"""
        self._publish_drone_markers()
        
        if self.show_links:
            self._publish_link_markers()
        
        if self.show_heatmap:
            self._publish_coverage_marker()
    
    def _publish_drone_markers(self):
        """Publish drone position markers"""
        if self.latest_swarm is None:
            return
        
        marker_array = MarkerArray()
        
        for drone in self.latest_swarm.drones:
            marker = Marker()
            marker.header = Header()
            marker.header.stamp = self.get_clock().now().to_msg()
            marker.header.frame_id = 'map'
            
            marker.ns = 'drones'
            marker.id = drone.drone_id
            marker.type = Marker.SPHERE
            marker.action = Marker.ADD
            
            marker.pose.position.x = drone.position.x
            marker.pose.position.y = drone.position.y
            marker.pose.position.z = drone.position.z
            marker.pose.orientation.w = 1.0
            
            marker.scale = Vector3(
                x=self.drone_scale,
                y=self.drone_scale,
                z=self.drone_scale
            )
            
            # Color based on role (hub=gold, leaf=blue)
            if drone.role == 1:  # HUB
                marker.color = ColorRGBA(r=1.0, g=0.8, b=0.0, a=1.0)
            else:
                marker.color = ColorRGBA(r=0.2, g=0.6, b=1.0, a=1.0)
            
            marker.lifetime.sec = 1
            
            marker_array.markers.append(marker)
            
            # Add text label
            text_marker = Marker()
            text_marker.header = marker.header
            text_marker.ns = 'drone_labels'
            text_marker.id = drone.drone_id + 100
            text_marker.type = Marker.TEXT_VIEW_FACING
            text_marker.action = Marker.ADD
            
            text_marker.pose.position.x = drone.position.x
            text_marker.pose.position.y = drone.position.y
            text_marker.pose.position.z = drone.position.z + 3.0
            text_marker.pose.orientation.w = 1.0
            
            text_marker.scale.z = 1.5  # Text height
            text_marker.color = ColorRGBA(r=1.0, g=1.0, b=1.0, a=1.0)
            
            role_str = "HUB" if drone.role == 1 else "LEAF"
            text_marker.text = f"D{drone.drone_id} ({role_str})"
            
            text_marker.lifetime.sec = 1
            
            marker_array.markers.append(text_marker)
        
        self.drone_markers_pub.publish(marker_array)
    
    def _publish_link_markers(self):
        """Publish mesh link line markers"""
        if self.latest_metrics is None:
            return
        
        marker_array = MarkerArray()
        
        # Create line list marker for all links
        if len(self.latest_metrics.link_from_drone) > 0:
            links_marker = Marker()
            links_marker.header = Header()
            links_marker.header.stamp = self.get_clock().now().to_msg()
            links_marker.header.frame_id = 'map'
            
            links_marker.ns = 'mesh_links'
            links_marker.id = 0
            links_marker.type = Marker.LINE_LIST
            links_marker.action = Marker.ADD
            
            links_marker.scale.x = self.link_width
            
            links_marker.lifetime.sec = 1
            
            # Build link lines
            for i in range(len(self.latest_metrics.link_from_drone)):
                from_id = self.latest_metrics.link_from_drone[i]
                to_id = self.latest_metrics.link_to_drone[i]
                rssi = self.latest_metrics.link_rssi_dbm[i]
                
                # Find drone positions
                from_pos = None
                to_pos = None
                
                if self.latest_swarm is not None:
                    for drone in self.latest_swarm.drones:
                        if drone.drone_id == from_id:
                            from_pos = drone.position
                        if drone.drone_id == to_id:
                            to_pos = drone.position
                
                if from_pos is not None and to_pos is not None:
                    links_marker.points.append(Point(
                        x=from_pos.x, y=from_pos.y, z=from_pos.z
                    ))
                    links_marker.points.append(Point(
                        x=to_pos.x, y=to_pos.y, z=to_pos.z
                    ))
                    
                    # Color based on signal strength relative to critical threshold
                    # Good (green): > critical + 10 dBm
                    # Medium (yellow): critical to critical + 10 dBm  
                    # Poor (red): < critical
                    good_threshold = self.critical_signal + 10
                    if rssi > good_threshold:
                        color = ColorRGBA(r=0.0, g=1.0, b=0.0, a=0.8)
                    elif rssi > self.critical_signal:
                        color = ColorRGBA(r=1.0, g=1.0, b=0.0, a=0.8)
                    else:
                        color = ColorRGBA(r=1.0, g=0.0, b=0.0, a=0.8)
                    
                    links_marker.colors.append(color)
                    links_marker.colors.append(color)
            
            marker_array.markers.append(links_marker)
        
        self.link_markers_pub.publish(marker_array)
    
    def _publish_coverage_marker(self):
        """Publish coverage grid as cube list"""
        if self.latest_metrics is None:
            return
        
        msg = self.latest_metrics
        
        if not msg.coverage_mask or msg.grid_size_x == 0:
            return
        
        marker = Marker()
        marker.header = Header()
        marker.header.stamp = self.get_clock().now().to_msg()
        marker.header.frame_id = 'map'
        
        marker.ns = 'coverage_grid'
        marker.id = 0
        marker.type = Marker.CUBE_LIST
        marker.action = Marker.ADD
        
        # Grid cell size
        cell_size = msg.cell_size_meters
        marker.scale = Vector3(x=cell_size * 0.9, y=cell_size * 0.9, z=0.5)
        
        marker.lifetime.sec = 1
        
        # Build grid
        try:
            coverage = np.array(msg.coverage_mask).reshape(
                msg.grid_size_y, msg.grid_size_x
            )
            signal = np.array(msg.signal_strength_dbm).reshape(
                msg.grid_size_y, msg.grid_size_x
            )
        except ValueError:
            return
        
        xs = msg.origin.x + np.arange(msg.grid_size_x) * cell_size + cell_size / 2
        ys = msg.origin.y + np.arange(msg.grid_size_y) * cell_size + cell_size / 2
        
        for iy in range(msg.grid_size_y):
            for ix in range(msg.grid_size_x):
                # Only show covered cells (or show all with different colors)
                if coverage[iy, ix]:
                    marker.points.append(Point(
                        x=float(xs[ix]),
                        y=float(ys[iy]),
                        z=0.25  # Slightly above ground
                    ))
                    
                    # Color based on signal strength
                    sig = signal[iy, ix]
                    # Normalize -90 to -50 dBm -> 0 to 1
                    normalized = (sig + 90) / 40
                    normalized = max(0, min(1, normalized))
                    
                    # Green (good) to yellow to red (poor)
                    if normalized > 0.5:
                        r = 2 * (1 - normalized)
                        g = 1.0
                    else:
                        r = 1.0
                        g = 2 * normalized
                    
                    marker.colors.append(ColorRGBA(
                        r=float(r), g=float(g), b=0.0, a=0.5
                    ))
        
        self.coverage_marker_pub.publish(marker)


def main(args=None):
    rclpy.init(args=args)
    
    node = MeshVisualizerNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
