"""
A.U.R.A. Simulation Package

Provides software-in-the-loop simulation for the full A.U.R.A. stack
without requiring PX4 SITL or Gazebo. Includes:

  - sim_swarm_driver:     Simulated drone swarm that responds to CoverageGoal
  - dead_zone_publisher:  Configurable network dead zones
  - scenario_runner:      Automated test scenarios
  - Launch files for full-stack and lightweight sim modes
"""

__version__ = '0.1.0'
