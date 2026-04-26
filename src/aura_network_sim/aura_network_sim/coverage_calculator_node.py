#!/usr/bin/env python3
"""
Coverage Calculator Node

Processes network metrics and provides coverage statistics.
Can define priority zones for weighted coverage calculation.
"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy

import numpy as np
from typing import List, Dict, Optional

from geometry_msgs.msg import Point
from std_msgs.msg import Header

try:
    from aura_msgs.msg import NetworkMetrics, CoverageMap, CoverageGoal
except ImportError:
    NetworkMetrics = None
    CoverageMap = None
    CoverageGoal = None


class PriorityZone:
    """A priority zone for weighted coverage (e.g., hospital, rescue staging)"""
    
    def __init__(self, x: float, y: float, radius: float, weight: float = 2.0, name: str = ""):
        self.x = x
        self.y = y
        self.radius = radius
        self.weight = weight
        self.name = name
    
    def contains(self, px: float, py: float) -> bool:
        """Check if point is inside zone"""
        return (px - self.x)**2 + (py - self.y)**2 <= self.radius**2


class CoverageCalculatorNode(Node):
    """
    Coverage statistics and analysis node.
    
    Subscribes:
        /network/metrics (NetworkMetrics): Network metrics from simulator
        
    Publishes:
        /network/coverage_stats (statistics as log messages for now)
    """
    
    def __init__(self):
        super().__init__('coverage_calculator')
        
        # Declare global parameters (from /**:)
        self.declare_parameter('tx_power_dbm', 20.0)
        self.declare_parameter('noise_floor_dbm', -100.0)
        self.declare_parameter('min_snr_db', 10.0)
        
        # Declare node-specific parameters
        self.declare_parameter('target_coverage_percent', 80.0)
        self.declare_parameter('critical_signal_threshold_dbm', -75.0)
        self.declare_parameter('log_interval_sec', 5.0)
        self.declare_parameter('coverage_decay_rate', 0.02)
        
        # Get parameters
        self.target_coverage = self.get_parameter('target_coverage_percent').value
        self.critical_threshold = self.get_parameter('critical_signal_threshold_dbm').value
        log_interval = self.get_parameter('log_interval_sec').value
        self.coverage_decay_rate = self.get_parameter('coverage_decay_rate').value
        
        # Compute minimum acceptable signal from global params
        noise_floor = self.get_parameter('noise_floor_dbm').value
        min_snr = self.get_parameter('min_snr_db').value
        self.min_acceptable_signal = noise_floor + min_snr
        
        # State
        self.latest_metrics: Optional[NetworkMetrics] = None
        self.priority_zones: List[PriorityZone] = []
        
        # Statistics history with decay
        self.coverage_history: List[float] = []
        self.smoothed_coverage: float = 0.0
        self.max_history_len = 100
        
        # QoS
        qos = QoSProfile(reliability=ReliabilityPolicy.RELIABLE, depth=10)
        
        # Subscribers
        if NetworkMetrics is not None:
            self.metrics_sub = self.create_subscription(
                NetworkMetrics, '/network/metrics',
                self.metrics_callback, qos
            )
        else:
            self.get_logger().warn('NetworkMetrics not available')
        
        # Timers
        self.stats_timer = self.create_timer(log_interval, self.log_statistics)
        
        self.get_logger().info(
            f'Coverage calculator started (target: {self.target_coverage}%)'
        )
    
    def add_priority_zone(self, x: float, y: float, radius: float, 
                          weight: float = 2.0, name: str = ""):
        """Add a priority zone for weighted coverage calculation"""
        zone = PriorityZone(x, y, radius, weight, name)
        self.priority_zones.append(zone)
        self.get_logger().info(
            f'Added priority zone "{name}" at ({x}, {y}) radius {radius}m, weight {weight}'
        )
    
    def metrics_callback(self, msg: NetworkMetrics):
        """Process incoming network metrics"""
        self.latest_metrics = msg
        
        # Track coverage history
        self.coverage_history.append(msg.total_coverage_percent)
        if len(self.coverage_history) > self.max_history_len:
            self.coverage_history.pop(0)
        
        # Apply exponential smoothing for stable coverage estimate
        if self.smoothed_coverage == 0.0:
            self.smoothed_coverage = msg.total_coverage_percent
        else:
            alpha = 1.0 - self.coverage_decay_rate
            self.smoothed_coverage = (alpha * self.smoothed_coverage + 
                                       (1 - alpha) * msg.total_coverage_percent)
    
    def compute_weighted_coverage(self) -> Dict:
        """Compute weighted coverage considering priority zones"""
        if self.latest_metrics is None:
            return {'weighted_coverage': 0.0, 'priority_coverage': {}}
        
        msg = self.latest_metrics
        
        if not msg.coverage_mask or msg.grid_size_x == 0:
            return {'weighted_coverage': 0.0, 'priority_coverage': {}}
        
        # Reshape coverage mask
        try:
            coverage = np.array(msg.coverage_mask).reshape(
                msg.grid_size_y, msg.grid_size_x
            )
            signal = np.array(msg.signal_strength_dbm).reshape(
                msg.grid_size_y, msg.grid_size_x
            )
        except ValueError:
            return {'weighted_coverage': 0.0, 'priority_coverage': {}}
        
        # Create weight map
        weights = np.ones_like(coverage, dtype=float)
        
        # Compute grid coordinates
        xs = msg.origin.x + np.arange(msg.grid_size_x) * msg.cell_size_meters
        ys = msg.origin.y + np.arange(msg.grid_size_y) * msg.cell_size_meters
        
        # Apply priority zone weights
        priority_coverage = {}
        
        for zone in self.priority_zones:
            zone_covered = 0
            zone_total = 0
            
            for iy, y in enumerate(ys):
                for ix, x in enumerate(xs):
                    if zone.contains(x, y):
                        weights[iy, ix] = zone.weight
                        zone_total += 1
                        if coverage[iy, ix]:
                            zone_covered += 1
            
            if zone_total > 0:
                priority_coverage[zone.name] = 100.0 * zone_covered / zone_total
        
        # Compute weighted coverage
        weighted_coverage = np.sum(coverage * weights) / np.sum(weights) * 100.0
        
        return {
            'weighted_coverage': float(weighted_coverage),
            'priority_coverage': priority_coverage,
        }
    
    def compute_coverage_gaps(self) -> List[Dict]:
        """Find areas with no coverage (coverage gaps)"""
        if self.latest_metrics is None:
            return []
        
        msg = self.latest_metrics
        
        if not msg.coverage_mask or msg.grid_size_x == 0:
            return []
        
        try:
            coverage = np.array(msg.coverage_mask).reshape(
                msg.grid_size_y, msg.grid_size_x
            )
        except ValueError:
            return []
        
        gaps = []
        xs = msg.origin.x + np.arange(msg.grid_size_x) * msg.cell_size_meters
        ys = msg.origin.y + np.arange(msg.grid_size_y) * msg.cell_size_meters
        
        # Find uncovered cells
        uncovered = np.where(~coverage)
        
        # Cluster nearby gaps (simplified - just report centers of uncovered regions)
        if len(uncovered[0]) > 0:
            # Take up to 5 representative gap points
            indices = np.linspace(0, len(uncovered[0]) - 1, min(5, len(uncovered[0]))).astype(int)
            
            for idx in indices:
                iy, ix = uncovered[0][idx], uncovered[1][idx]
                gaps.append({
                    'x': float(xs[ix]),
                    'y': float(ys[iy]),
                    'severity': 'high' if len(uncovered[0]) > 100 else 'low'
                })
        
        return gaps
    
    def log_statistics(self):
        """Log coverage statistics periodically"""
        if self.latest_metrics is None:
            self.get_logger().info('Waiting for network metrics...')
            return
        
        msg = self.latest_metrics
        weighted = self.compute_weighted_coverage()
        gaps = self.compute_coverage_gaps()
        
        # Basic stats with smoothed coverage
        self.get_logger().info(
            f'Coverage: {msg.total_coverage_percent:.1f}% '
            f'(smoothed: {self.smoothed_coverage:.1f}%, '
            f'weighted: {weighted["weighted_coverage"]:.1f}%) | '
            f'Signal: {msg.avg_signal_strength_dbm:.1f} dBm | '
            f'Throughput: {msg.avg_throughput_mbps:.1f} Mbps | '
            f'Latency: {msg.avg_latency_ms:.1f} ms | '
            f'Links: {len(msg.link_from_drone)}'
        )
        
        # Priority zone stats
        for zone_name, zone_cov in weighted['priority_coverage'].items():
            self.get_logger().info(f'  Priority "{zone_name}": {zone_cov:.1f}%')
        
        # Coverage gap warning
        if gaps:
            self.get_logger().warn(
                f'Coverage gaps detected: {len(gaps)} uncovered regions'
            )
        
        # Target check
        if msg.total_coverage_percent < self.target_coverage:
            deficit = self.target_coverage - msg.total_coverage_percent
            self.get_logger().warn(
                f'Below target coverage! Deficit: {deficit:.1f}%'
            )
        
        # Mesh connectivity check
        if not msg.mesh_connected:
            self.get_logger().error('MESH DISCONNECTED - Swarm not fully connected!')
        
        # Trend analysis
        if len(self.coverage_history) >= 10:
            recent = self.coverage_history[-10:]
            trend = recent[-1] - recent[0]
            if abs(trend) > 5:
                direction = "improving" if trend > 0 else "degrading"
                self.get_logger().info(f'Coverage trend: {direction} ({trend:+.1f}%)')


def main(args=None):
    rclpy.init(args=args)
    
    node = CoverageCalculatorNode()
    
    # Add some example priority zones
    node.add_priority_zone(99, -155, 40, weight=3.0, name="School Zone")
    node.add_priority_zone(170, -165, 50, weight=2.0, name="Residential Zone")
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
