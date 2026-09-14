"""
Reward Functions for A.U.R.A. Strategic RL

Multi-objective reward combining:
- Coverage maximization
- Network quality (connectivity, throughput)
- Energy efficiency
- Safety constraints
"""

import numpy as np
from dataclasses import dataclass
from typing import Dict, List, Tuple, Optional


@dataclass
class RewardConfig:
    """Configuration for reward computation"""

    # Coverage rewards
    coverage_weight: float = 2.0
    coverage_target: float = 80.0           # Target coverage %
    coverage_bonus_threshold: float = 90.0  # Bonus above this

    # Network quality rewards
    connectivity_weight: float = 3.0        # Mesh connectivity (binary) — high to keep swarm linked
    throughput_weight: float = 0.3
    latency_weight: float = 0.1
    signal_weight: float = 0.2

    # Energy/movement penalties
    movement_penalty_weight: float = 0.05
    hover_bonus: float = 0.01               # Small bonus for staying still

    # Safety penalties
    collision_penalty: float = 2.0         # Drones too close
    boundary_penalty: float = 0.5           # Near area boundary (mild — clip prevents escape)
    altitude_penalty: float = 2.0           # Outside altitude bounds

    # Safety thresholds
    min_separation_m: float = 5.0           # Minimum drone separation
    boundary_margin_m: float = 20.0         # Warn zone near boundary
    area_bound: float = 250.0               # Max distance from world center (m)
    min_altitude: float = 15.0
    max_altitude: float = 80.0

    # World center — disaster zone centroid (must match ObservationBuilder)
    world_center_x: float = 120.0
    world_center_y: float = -170.0

    # Shaping
    coverage_improvement_bonus: float = 0.5  # Bonus for improving coverage

    # Proximity reward — incentivize moving toward disaster zone
    proximity_weight: float = 0.5            # Max proximity reward per step
    proximity_scale_m: float = 300.0         # Distance at which reward reaches zero

    # Priority zones
    priority_zone_weight: float = 1.5       # Extra weight for priority areas


class RewardCalculator:
    """
    Computes multi-objective reward for swarm positioning.

    Total reward = coverage_reward + network_reward - penalties + bonuses
    """

    def __init__(self, config: RewardConfig = None):
        self.config = config or RewardConfig()
        self.prev_coverage = 0.0

    def reset(self):
        """Reset state for new episode"""
        self.prev_coverage = 0.0

    def compute_reward(self,
                       coverage_percent: float,
                       mesh_connected: bool,
                       avg_signal_dbm: float,
                       avg_throughput_mbps: float,
                       avg_latency_ms: float,
                       drone_positions: List[Tuple[float, float, float]],
                       movement_magnitudes: Optional[List[float]] = None,
                       priority_zone_coverage: Optional[float] = None,
                       ) -> Tuple[float, Dict[str, float]]:
        """
        Compute total reward and component breakdown.

        Returns:
            total_reward: Scalar reward value
            components: Dictionary of reward components for logging
        """
        components = {}

        # 1. Coverage reward
        coverage_reward = self._compute_coverage_reward(coverage_percent)
        components['coverage'] = coverage_reward

        # 2. Network quality rewards
        connectivity_reward = self._compute_connectivity_reward(mesh_connected)
        signal_reward = self._compute_signal_reward(avg_signal_dbm)
        throughput_reward = self._compute_throughput_reward(avg_throughput_mbps)
        latency_reward = self._compute_latency_reward(avg_latency_ms)

        components['connectivity'] = connectivity_reward
        components['signal'] = signal_reward
        components['throughput'] = throughput_reward
        components['latency'] = latency_reward

        # 3. Movement penalty
        movement_penalty = 0.0
        if movement_magnitudes:
            movement_penalty = self._compute_movement_penalty(movement_magnitudes)
        components['movement_penalty'] = -movement_penalty

        # 4. Safety penalties
        safety_penalty = self._compute_safety_penalties(drone_positions)
        components['safety_penalty'] = -safety_penalty

        # 5. Coverage improvement bonus (reward shaping)
        improvement_bonus = self._compute_improvement_bonus(coverage_percent)
        components['improvement_bonus'] = improvement_bonus

        # 6. Priority zone bonus
        priority_bonus = 0.0
        if priority_zone_coverage is not None:
            priority_bonus = (priority_zone_coverage / 100.0) * self.config.priority_zone_weight
        components['priority_bonus'] = priority_bonus

        # 7. Proximity reward — guide drones toward disaster zone
        proximity_reward = self._compute_proximity_reward(drone_positions)
        components['proximity'] = proximity_reward

        # Total reward
        total = (
            coverage_reward +
            connectivity_reward +
            signal_reward +
            throughput_reward +
            latency_reward +
            improvement_bonus +
            priority_bonus +
            proximity_reward -
            movement_penalty -
            safety_penalty
        )

        components['total'] = total

        # Update state for next step
        self.prev_coverage = coverage_percent

        return total, components

    def _compute_coverage_reward(self, coverage_percent: float) -> float:
        """Reward based on coverage percentage"""
        normalized = coverage_percent / 100.0
        reward = normalized * self.config.coverage_weight

        # Bonus for exceeding target
        if coverage_percent >= self.config.coverage_target:
            reward += 0.2 * self.config.coverage_weight

        # Extra bonus for high coverage
        if coverage_percent >= self.config.coverage_bonus_threshold:
            excess = (coverage_percent - self.config.coverage_bonus_threshold) / 10.0
            reward += excess * 0.1 * self.config.coverage_weight

        return reward

    def _compute_connectivity_reward(self, mesh_connected: bool) -> float:
        """Binary reward for mesh connectivity"""
        if mesh_connected:
            return self.config.connectivity_weight
        else:
            return -self.config.connectivity_weight

    def _compute_signal_reward(self, avg_signal_dbm: float) -> float:
        """Reward based on average signal strength"""
        normalized = (avg_signal_dbm + 90) / 40.0
        normalized = np.clip(normalized, 0, 1)
        return normalized * self.config.signal_weight

    def _compute_throughput_reward(self, avg_throughput_mbps: float) -> float:
        """Reward based on network throughput"""
        normalized = avg_throughput_mbps / 100.0
        normalized = np.clip(normalized, 0, 1)
        return normalized * self.config.throughput_weight

    def _compute_latency_reward(self, avg_latency_ms: float) -> float:
        """Reward based on latency (lower is better)"""
        normalized = 1.0 - (avg_latency_ms / 100.0)
        normalized = np.clip(normalized, 0, 1)
        return normalized * self.config.latency_weight

    def _compute_movement_penalty(self, movement_magnitudes: List[float]) -> float:
        """Penalty for large movements (energy cost)"""
        if not movement_magnitudes:
            return 0.0

        avg_movement = np.mean(movement_magnitudes)
        penalty = (avg_movement ** 2) * self.config.movement_penalty_weight

        # Small bonus for hovering (stability)
        if avg_movement < 0.5:
            penalty -= self.config.hover_bonus

        return max(0.0, penalty)

    def _compute_safety_penalties(self,
                                  drone_positions: List[Tuple[float, float, float]]
                                  ) -> float:
        """Compute safety-related penalties"""
        penalty = 0.0
        n = len(drone_positions)
        if n == 0:
            return penalty

        # Note: the pairwise collision loop below is naturally empty for a
        # single drone. Returning early on n < 2 would also skip the per-drone
        # altitude and boundary checks, so a swarm degraded to one surviving
        # drone would fly unconstrained.

        for i in range(n):
            pos_i = np.array(drone_positions[i])

            # Collision penalty (pairwise)
            for j in range(i + 1, n):
                pos_j = np.array(drone_positions[j])
                dist = np.linalg.norm(pos_i - pos_j)

                if dist < self.config.min_separation_m:
                    severity = 1.0 - (dist / self.config.min_separation_m)
                    penalty += severity * self.config.collision_penalty

            # Boundary penalty (distance from world center, not origin)
            center_2d = np.array([self.config.world_center_x, self.config.world_center_y])
            dist_from_center = np.linalg.norm(pos_i[:2] - center_2d)
            boundary_dist = self.config.area_bound - dist_from_center
            if boundary_dist < self.config.boundary_margin_m:
                # Clamped to [0,1] — circular clip in ActionProcessor prevents escape,
                # but ROS inference can still send drones near the edge.
                severity = np.clip(1.0 - (boundary_dist / self.config.boundary_margin_m), 0.0, 1.0)
                penalty += severity * self.config.boundary_penalty

            # Altitude penalty
            alt = pos_i[2]
            if alt < self.config.min_altitude:
                penalty += (self.config.min_altitude - alt) / 10.0 * self.config.altitude_penalty
            elif alt > self.config.max_altitude:
                penalty += (alt - self.config.max_altitude) / 10.0 * self.config.altitude_penalty

        return penalty

    def _compute_improvement_bonus(self, coverage_percent: float) -> float:
        """Bonus for improving coverage over previous step"""
        improvement = coverage_percent - self.prev_coverage
        if improvement > 0:
            return improvement / 100.0 * self.config.coverage_improvement_bonus
        return 0.0

    def _compute_proximity_reward(self,
                                  drone_positions: List[Tuple[float, float, float]]
                                  ) -> float:
        """Reward for being near the disaster zone — guides transit phase learning."""
        if not drone_positions:
            return 0.0
        center = np.array([self.config.world_center_x, self.config.world_center_y])
        avg_dist = np.mean([
            np.linalg.norm(np.array(p[:2]) - center)
            for p in drone_positions
        ])
        return self.config.proximity_weight * max(0.0, 1.0 - avg_dist / self.config.proximity_scale_m)
