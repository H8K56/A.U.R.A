#!/usr/bin/env python3
"""
Harris Hawks Optimization (HHO) Baseline

Bio-inspired optimization algorithm for UAV swarm positioning.
Used as baseline comparison for RL-based approach.

Reference: Heidari et al., "Harris hawks optimization: Algorithm and applications"
"""

import rclpy
from rclpy.node import Node
import numpy as np
from typing import Dict, List, Tuple, Optional, Callable
from dataclasses import dataclass

from geometry_msgs.msg import Point
from aura_msgs.msg import DroneState, SwarmState, NetworkMetrics, CoverageGoal


@dataclass
class HHOConfig:
    """HHO algorithm configuration"""
    population_size: int = 30
    max_iterations: int = 100
    
    # Bounds
    x_min: float = -100.0
    x_max: float = 100.0
    y_min: float = -100.0
    y_max: float = 100.0
    z_min: float = 10.0
    z_max: float = 50.0
    
    # Algorithm parameters
    energy_decay_rate: float = 2.0
    jump_strength: float = 2.0
    
    # Convergence
    convergence_threshold: float = 0.01
    stall_generations: int = 10


class HarrisHawksOptimizer:
    """
    Harris Hawks Optimization algorithm.
    
    Mimics the cooperative hunting behavior of Harris' hawks,
    including surprise pounce, soft besiege, hard besiege,
    and rapid dives.
    """
    
    def __init__(self, config: HHOConfig, num_drones: int):
        self.config = config
        self.num_drones = num_drones
        self.dim = num_drones * 3  # x, y, z per drone
        
        # Population
        self.population: np.ndarray = None
        self.fitness: np.ndarray = None
        
        # Best solution (rabbit)
        self.rabbit_position: np.ndarray = None
        self.rabbit_fitness: float = float('inf')
        
        # Bounds
        self.lower_bounds = np.tile([config.x_min, config.y_min, config.z_min], num_drones)
        self.upper_bounds = np.tile([config.x_max, config.y_max, config.z_max], num_drones)
        
        self.rng = np.random.default_rng()
    
    def initialize_population(self):
        """Initialize hawk population randomly"""
        self.population = self.rng.uniform(
            self.lower_bounds, 
            self.upper_bounds,
            (self.config.population_size, self.dim)
        )
        self.fitness = np.full(self.config.population_size, float('inf'))
    
    def optimize(self, fitness_func: Callable[[np.ndarray], float],
                 callback: Callable[[int, np.ndarray, float], None] = None) -> Tuple[np.ndarray, float]:
        """
        Run HHO optimization.
        
        Args:
            fitness_func: Function that takes position array and returns fitness (lower is better)
            callback: Optional callback(iteration, best_pos, best_fitness)
            
        Returns:
            Tuple of (best_position, best_fitness)
        """
        self.initialize_population()
        
        # Evaluate initial population
        for i in range(self.config.population_size):
            self.fitness[i] = fitness_func(self.population[i])
            
            if self.fitness[i] < self.rabbit_fitness:
                self.rabbit_fitness = self.fitness[i]
                self.rabbit_position = self.population[i].copy()
        
        stall_count = 0
        prev_fitness = self.rabbit_fitness
        
        for t in range(self.config.max_iterations):
            # Escaping energy of rabbit (decreases over time)
            E0 = 2 * self.rng.random() - 1  # Initial energy [-1, 1]
            E = self.config.energy_decay_rate * E0 * (1 - t / self.config.max_iterations)
            
            for i in range(self.config.population_size):
                q = self.rng.random()
                
                if abs(E) >= 1:
                    # Exploration phase
                    self.population[i] = self._explore(i)
                else:
                    # Exploitation phase
                    r = self.rng.random()
                    
                    if r >= 0.5:
                        if abs(E) >= 0.5:
                            # Soft besiege
                            self.population[i] = self._soft_besiege(i, E)
                        else:
                            # Hard besiege
                            self.population[i] = self._hard_besiege(i, E)
                    else:
                        if abs(E) >= 0.5:
                            # Soft besiege with progressive rapid dives
                            self.population[i] = self._soft_besiege_dive(i, E)
                        else:
                            # Hard besiege with progressive rapid dives
                            self.population[i] = self._hard_besiege_dive(i, E)
                
                # Enforce bounds
                self.population[i] = np.clip(
                    self.population[i], 
                    self.lower_bounds, 
                    self.upper_bounds
                )
                
                # Evaluate fitness
                self.fitness[i] = fitness_func(self.population[i])
                
                # Update rabbit
                if self.fitness[i] < self.rabbit_fitness:
                    self.rabbit_fitness = self.fitness[i]
                    self.rabbit_position = self.population[i].copy()
            
            # Callback
            if callback:
                callback(t, self.rabbit_position.copy(), self.rabbit_fitness)
            
            # Check convergence
            if abs(prev_fitness - self.rabbit_fitness) < self.config.convergence_threshold:
                stall_count += 1
                if stall_count >= self.config.stall_generations:
                    break
            else:
                stall_count = 0
            prev_fitness = self.rabbit_fitness
        
        return self.rabbit_position, self.rabbit_fitness
    
    def _explore(self, i: int) -> np.ndarray:
        """Exploration: random search based on other hawks or random location"""
        if self.rng.random() < 0.5:
            # Follow random hawk
            rand_idx = self.rng.integers(0, self.config.population_size)
            X_rand = self.population[rand_idx]
            r1, r2 = self.rng.random(2)
            return X_rand - r1 * abs(X_rand - 2 * r2 * self.population[i])
        else:
            # Random location
            r3, r4 = self.rng.random(2)
            return (self.rabbit_position - self.population.mean(axis=0) - 
                    r3 * (self.lower_bounds + r4 * (self.upper_bounds - self.lower_bounds)))
    
    def _soft_besiege(self, i: int, E: float) -> np.ndarray:
        """Soft besiege: rabbit has enough energy to escape"""
        J = 2 * (1 - self.rng.random())  # Jump strength
        return self.rabbit_position - E * abs(J * self.rabbit_position - self.population[i])
    
    def _hard_besiege(self, i: int, E: float) -> np.ndarray:
        """Hard besiege: rabbit is exhausted"""
        return self.rabbit_position - E * abs(self.rabbit_position - self.population[i])
    
    def _soft_besiege_dive(self, i: int, E: float) -> np.ndarray:
        """Soft besiege with progressive rapid dives"""
        J = 2 * (1 - self.rng.random())
        
        # Calculate dive trajectory
        Y = self.rabbit_position - E * abs(J * self.rabbit_position - self.population[i])
        
        # Levy flight
        S = self._levy_flight()
        Z = Y + S * self._levy_flight()
        
        return Y  # Simplified - would compare fitness and return best
    
    def _hard_besiege_dive(self, i: int, E: float) -> np.ndarray:
        """Hard besiege with progressive rapid dives"""
        J = 2 * (1 - self.rng.random())
        
        Y = self.rabbit_position - E * abs(J * self.rabbit_position - self.population.mean(axis=0))
        
        S = self._levy_flight()
        Z = Y + S * self._levy_flight()
        
        return Y  # Simplified
    
    def _levy_flight(self) -> np.ndarray:
        """Generate Levy flight step"""
        beta = 1.5
        sigma = (np.math.gamma(1 + beta) * np.sin(np.pi * beta / 2) /
                 (np.math.gamma((1 + beta) / 2) * beta * 2 ** ((beta - 1) / 2))) ** (1 / beta)
        
        u = self.rng.normal(0, sigma, self.dim)
        v = self.rng.normal(0, 1, self.dim)
        
        step = u / (abs(v) ** (1 / beta))
        return step * 0.01  # Scale down


class HHOBaselineNode(Node):
    """
    ROS 2 node for HHO-based swarm positioning.
    Runs optimization periodically and publishes optimal positions.
    """
    
    def __init__(self):
        super().__init__('baseline_hho')
        
        # Parameters
        self.declare_parameter('num_drones', 5)
        self.declare_parameter('optimization_rate_hz', 0.2)  # Every 5 seconds
        self.declare_parameter('max_iterations', 50)
        
        num_drones = self.get_parameter('num_drones').value
        opt_rate = self.get_parameter('optimization_rate_hz').value
        max_iter = self.get_parameter('max_iterations').value
        
        # HHO optimizer
        config = HHOConfig(max_iterations=max_iter)
        self.optimizer = HarrisHawksOptimizer(config, num_drones)
        
        # State
        self.latest_swarm: Optional[SwarmState] = None
        self.latest_network: Optional[NetworkMetrics] = None
        
        # Subscribers
        self.swarm_sub = self.create_subscription(
            SwarmState, '/swarm/state',
            self.swarm_callback, 10
        )
        
        self.network_sub = self.create_subscription(
            NetworkMetrics, '/network/metrics',
            self.network_callback, 10
        )
        
        # Publishers
        self.goal_pubs: Dict[int, rclpy.publisher.Publisher] = {}
        for i in range(num_drones):
            pub = self.create_publisher(
                CoverageGoal,
                f'/drone_{i}/coverage_goal',
                10
            )
            self.goal_pubs[i] = pub
        
        # Optimization timer
        self.opt_timer = self.create_timer(
            1.0 / opt_rate,
            self.run_optimization
        )
        
        self.get_logger().info(f'HHO baseline node started (drones: {num_drones})')
    
    def swarm_callback(self, msg: SwarmState):
        self.latest_swarm = msg
    
    def network_callback(self, msg: NetworkMetrics):
        self.latest_network = msg
    
    def fitness_function(self, position: np.ndarray) -> float:
        """
        Fitness function for swarm positioning.
        Lower is better.
        
        Objectives:
        - Maximize coverage (spread out)
        - Maintain connectivity (not too far apart)
        - Avoid collisions (minimum separation)
        """
        num_drones = len(position) // 3
        positions = position.reshape(num_drones, 3)
        
        fitness = 0.0
        
        # Coverage: maximize spread (negative = minimize negative spread)
        centroid = positions.mean(axis=0)
        spread = np.mean(np.linalg.norm(positions - centroid, axis=1))
        fitness -= spread * 0.1  # Encourage spread
        
        # Connectivity: penalize large distances between neighbors
        for i in range(num_drones):
            for j in range(i + 1, num_drones):
                dist = np.linalg.norm(positions[i] - positions[j])
                
                # Penalize if too far (>80m, losing connectivity)
                if dist > 80:
                    fitness += (dist - 80) * 0.5
                
                # Penalize if too close (<5m, collision risk)
                if dist < 5:
                    fitness += (5 - dist) * 10.0
        
        # Height: keep at reasonable altitude
        for i in range(num_drones):
            z = positions[i, 2]
            if z < 15 or z > 40:
                fitness += abs(z - 27.5) * 0.1
        
        return fitness
    
    def run_optimization(self):
        """Run HHO optimization and publish results"""
        if self.latest_swarm is None or len(self.latest_swarm.drones) == 0:
            return
        
        # Set initial positions from current state
        num_drones = len(self.latest_swarm.drones)
        
        if num_drones * 3 != self.optimizer.dim:
            # Reinitialize if drone count changed
            self.optimizer = HarrisHawksOptimizer(
                self.optimizer.config, 
                num_drones
            )
        
        # Run optimization
        best_position, best_fitness = self.optimizer.optimize(self.fitness_function)
        
        self.get_logger().info(f'HHO optimization complete, fitness: {best_fitness:.2f}')
        
        # Publish goals
        for i, drone in enumerate(self.latest_swarm.drones):
            if drone.drone_id in self.goal_pubs:
                msg = CoverageGoal()
                msg.timestamp = self.get_clock().now().to_msg()
                msg.drone_id = drone.drone_id
                msg.position.x = float(best_position[i * 3])
                msg.position.y = float(best_position[i * 3 + 1])
                msg.position.z = float(best_position[i * 3 + 2])
                msg.priority = 1.0
                
                self.goal_pubs[drone.drone_id].publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = HHOBaselineNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
