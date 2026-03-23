#!/usr/bin/env python3
"""
Standalone Network Simulation Test

Tests the network simulation modules without ROS 2.
Run this to verify the simulation logic before ROS integration.

Usage: python3 test_network_sim.py
"""

import sys
import os

# Add package to path
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import numpy as np
from aura_network_sim.propagation import PropagationModel, D2D_CONFIG, D2G_CONFIG
from aura_network_sim.mesh_simulator import MeshSimulator, DroneNetworkState
from aura_network_sim.coverage_calculator import CoverageCalculator


def test_propagation_model():
    """Test radio propagation calculations"""
    print("\n" + "="*60)
    print("Test 1: Propagation Model")
    print("="*60)
    
    prop = PropagationModel(D2D_CONFIG, seed=42)
    
    # Test max range
    max_range = prop.compute_max_range()
    print(f"  D2D Max Range: {max_range:.1f} m")
    
    # Test link quality at various distances
    print(f"\n  {'Distance':>10} {'RSSI':>10} {'SNR':>10} {'Rate':>12} {'Connected':>10}")
    print(f"  {'(m)':>10} {'(dBm)':>10} {'(dB)':>10} {'(Mbps)':>12} {''}")
    print("  " + "-"*55)
    
    test_distances = [10, 25, 50, 75, 100, 150, 200, 300]
    
    for dist in test_distances:
        metrics = prop.compute_link_metrics(dist)
        connected = "✓" if metrics['connected'] else "✗"
        print(f"  {dist:>10} {metrics['rssi_dbm']:>10.1f} {metrics['snr_db']:>10.1f} "
              f"{metrics['rate_mbps']:>12.1f} {connected:>10}")
    
    return True


def test_mesh_simulator():
    """Test mesh network simulation"""
    print("\n" + "="*60)
    print("Test 2: Mesh Simulator")
    print("="*60)
    
    sim = MeshSimulator(seed=42)
    
    # Create 5-drone circular formation
    num_drones = 5
    radius = 50.0
    altitude = 30.0
    
    print(f"\n  Creating {num_drones}-drone formation (radius={radius}m, alt={altitude}m)")
    
    for i in range(num_drones):
        angle = 2 * np.pi * i / num_drones
        position = np.array([
            radius * np.cos(angle),
            radius * np.sin(angle),
            altitude
        ])
        sim.update_drone(i, position, is_hub=(i == 0))
    
    # Compute connectivity
    connectivity, rssi, rates = sim.compute_connectivity()
    
    print(f"\n  Mesh Status:")
    print(f"    Connected: {'✓' if sim.is_mesh_connected() else '✗'}")
    
    links = sim.get_link_info()
    print(f"    Active Links: {len(links)}")
    
    print(f"\n  Per-Drone Stats:")
    print(f"  {'ID':>4} {'Role':>6} {'Neighbors':>10} {'Best RSSI':>12} {'Throughput':>12} {'Hops to Hub':>12}")
    print("  " + "-"*60)
    
    for drone_id in sorted(sim.drones.keys()):
        drone = sim.drones[drone_id]
        role = "HUB" if drone.is_hub else "LEAF"
        print(f"  {drone_id:>4} {role:>6} {len(drone.neighbors):>10} "
              f"{drone.best_rssi_dbm:>12.1f} {drone.throughput_mbps:>12.1f} "
              f"{drone.hops_to_hub:>12}")
    
    print(f"\n  Link Details:")
    print(f"  {'From':>6} {'To':>6} {'Distance':>10} {'RSSI':>10} {'Rate':>10}")
    print("  " + "-"*45)
    
    for link in links[:5]:  # Show first 5
        print(f"  {link['from_id']:>6} {link['to_id']:>6} "
              f"{link['distance_m']:>10.1f} {link['rssi_dbm']:>10.1f} "
              f"{link['rate_mbps']:>10.1f}")
    
    # Test different formations
    print(f"\n  Formation Comparison:")
    print(f"  {'Radius':>10} {'Connected':>12} {'Links':>8} {'Avg RSSI':>12}")
    print("  " + "-"*45)
    
    for test_radius in [30, 50, 80, 120, 200]:
        for i in range(num_drones):
            angle = 2 * np.pi * i / num_drones
            position = np.array([
                test_radius * np.cos(angle),
                test_radius * np.sin(angle),
                altitude
            ])
            sim.update_drone(i, position, is_hub=(i == 0))
        
        sim.compute_connectivity()
        stats = sim.get_mesh_stats()
        
        connected = "✓" if stats['is_connected'] else "✗"
        print(f"  {test_radius:>10} {connected:>12} {stats['num_links']:>8} "
              f"{stats['avg_rssi_dbm']:>12.1f}")
    
    return True


def test_coverage_calculator():
    """Test ground coverage calculation"""
    print("\n" + "="*60)
    print("Test 3: Coverage Calculator")
    print("="*60)
    
    calc = CoverageCalculator(
        area_bounds=(-100, -100, 100, 100),
        resolution_m=10.0
    )
    
    # Create test drones
    drones = {}
    positions = [
        (0, 0, 30),
        (50, 0, 30),
        (-50, 0, 30),
        (0, 50, 30),
        (0, -50, 30),
    ]
    
    for i, (x, y, z) in enumerate(positions):
        drones[i] = DroneNetworkState(
            drone_id=i,
            position=np.array([x, y, z]),
            is_hub=(i == 0)
        )
    
    print(f"\n  Drones: {len(drones)}")
    print(f"  Grid: {calc.grid_size_x}x{calc.grid_size_y} cells")
    print(f"  Cell size: {calc.resolution}m")
    print(f"  Area: {calc.bounds}")
    
    # Compute coverage
    result = calc.compute_coverage(drones)
    
    print(f"\n  Coverage Results:")
    print(f"    Coverage: {result.coverage_percent:.1f}%")
    print(f"    Avg Signal: {result.avg_signal_dbm:.1f} dBm")
    print(f"    Min Signal: {result.min_signal_dbm:.1f} dBm")
    print(f"    Max Signal: {result.max_signal_dbm:.1f} dBm")
    print(f"    Avg Throughput: {result.avg_throughput_mbps:.1f} Mbps")
    
    # Test point queries
    print(f"\n  Sample Point Queries:")
    test_points = [(0, 0), (50, 50), (-80, -80), (100, 0)]
    
    print(f"  {'Point':>15} {'RSSI':>10} {'Rate':>10} {'Serving':>10} {'Connected':>10}")
    print("  " + "-"*60)
    
    for x, y in test_points:
        info = calc.get_coverage_at_point(x, y, drones)
        connected = "✓" if info['connected'] else "✗"
        print(f"  {f'({x},{y})':>15} {info['rssi_dbm']:>10.1f} "
              f"{info['throughput_mbps']:>10.1f} {info['serving_drone']:>10} "
              f"{connected:>10}")
    
    # Test different altitudes
    print(f"\n  Altitude vs Coverage:")
    print(f"  {'Altitude':>10} {'Coverage':>12} {'Avg Signal':>12}")
    print("  " + "-"*36)
    
    for alt in [20, 30, 50, 80, 100]:
        for i, (x, y, _) in enumerate(positions):
            drones[i].position = np.array([x, y, alt])
        
        result = calc.compute_coverage(drones)
        print(f"  {alt:>10} {result.coverage_percent:>12.1f}% "
              f"{result.avg_signal_dbm:>12.1f}")
    
    return True


def test_ascii_visualization():
    """Print ASCII coverage map"""
    print("\n" + "="*60)
    print("Test 4: ASCII Coverage Visualization")
    print("="*60)
    
    calc = CoverageCalculator(
        area_bounds=(-50, -50, 50, 50),
        resolution_m=5.0
    )
    
    # Create drones
    drones = {}
    positions = [(0, 0, 30), (30, 0, 30), (-30, 0, 30), (0, 30, 30), (0, -30, 30)]
    
    for i, (x, y, z) in enumerate(positions):
        drones[i] = DroneNetworkState(
            drone_id=i,
            position=np.array([x, y, z]),
            is_hub=(i == 0)
        )
    
    result = calc.compute_coverage(drones)
    
    print(f"\n  Coverage: {result.coverage_percent:.1f}%")
    print(f"  Legend: █=covered, ·=uncovered, D=drone")
    print()
    
    # Build ASCII map
    map_chars = []
    for iy in range(result.grid_size_y - 1, -1, -1):  # Reverse Y for display
        row = "  "
        for ix in range(result.grid_size_x):
            # Check if drone is at this cell
            x = calc.grid_x[ix]
            y = calc.grid_y[iy]
            
            is_drone = False
            for drone in drones.values():
                if (abs(drone.position[0] - x) < calc.resolution and
                    abs(drone.position[1] - y) < calc.resolution):
                    is_drone = True
                    break
            
            if is_drone:
                row += "D"
            elif result.coverage_mask[iy, ix]:
                row += "█"
            else:
                row += "·"
        
        map_chars.append(row)
    
    # Print map
    for row in map_chars:
        print(row)
    
    print()
    return True


def run_all_tests():
    """Run all tests"""
    print("\n" + "="*60)
    print("A.U.R.A. Network Simulation - Standalone Tests")
    print("="*60)
    
    tests = [
        ("Propagation Model", test_propagation_model),
        ("Mesh Simulator", test_mesh_simulator),
        ("Coverage Calculator", test_coverage_calculator),
        ("ASCII Visualization", test_ascii_visualization),
    ]
    
    results = []
    for name, test_func in tests:
        try:
            passed = test_func()
            results.append((name, passed))
        except Exception as e:
            print(f"\n  ERROR in {name}: {e}")
            import traceback
            traceback.print_exc()
            results.append((name, False))
    
    # Summary
    print("\n" + "="*60)
    print("Test Summary")
    print("="*60)
    
    all_passed = True
    for name, passed in results:
        status = "✓ PASS" if passed else "✗ FAIL"
        print(f"  {name}: {status}")
        if not passed:
            all_passed = False
    
    print()
    if all_passed:
        print("All tests passed! Network simulation is ready for ROS 2 integration.")
    else:
        print("Some tests failed. Please check the output above.")
    
    return all_passed


if __name__ == '__main__':
    success = run_all_tests()
    sys.exit(0 if success else 1)
