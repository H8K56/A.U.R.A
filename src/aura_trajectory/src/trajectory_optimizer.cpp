#include "aura_trajectory/trajectory_optimizer.hpp"
#include "aura_trajectory/penalty_functions.hpp"
#include <iostream>
#include <cmath>

namespace aura {

TrajectoryOptimizer::TrajectoryOptimizer(const OptimizationConfig& config)
    : config_(config) {}

OptimizationResult TrajectoryOptimizer::optimize(
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& start_vel,
    const Eigen::Vector3d& goal_pos,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    current_obstacles_ = obstacles;
    current_other_trajectories_ = other_trajectories;
    trajectory_start_time_ = 0.0;  // Assume starting now
    
    OptimizationResult result;
    
    // Initialize trajectory with straight line
    int M = config_.num_pieces;
    Eigen::Vector3d direction = goal_pos - start_pos;
    double distance = direction.norm();
    
    if (distance < 1e-6) {
        // Already at goal
        result.feasible = true;
        result.message = "Already at goal";
        result.trajectory = MincoTrajectory();
        return result;
    }
    
    // Estimate time based on max velocity
    double estimated_time = distance / config_.max_velocity * 1.5;  // Add buffer
    
    // Create uniform time allocation
    MincoTrajectory::TimeAlloc T = Eigen::VectorXd::Constant(M, estimated_time / M);
    
    // Create waypoints along straight line (will be optimized)
    MincoTrajectory::Waypoints q(3, M - 1);
    for (int i = 0; i < M - 1; ++i) {
        double alpha = static_cast<double>(i + 1) / M;
        q.col(i) = start_pos + alpha * direction;
    }
    
    // Create initial trajectory
    MincoTrajectory traj(q, T, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
    
    if (!traj.isValid()) {
        result.feasible = false;
        result.message = "Failed to create initial trajectory";
        return result;
    }
    
    // Simple gradient descent optimization
    double learning_rate = 0.01;
    double prev_cost = computeTotalCost(traj);
    int num_waypoints = M - 1;
    
    for (int iter = 0; iter < config_.max_iterations; ++iter) {
        // Compute gradients numerically
        double eps = 1e-5;
        
        // Gradient for waypoints
        Eigen::MatrixXd grad_q(3, num_waypoints);
        for (int i = 0; i < num_waypoints; ++i) {
            for (int d = 0; d < 3; ++d) {
                MincoTrajectory::Waypoints q_plus = q;
                q_plus(d, i) += eps;
                MincoTrajectory traj_plus(q_plus, T, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
                double cost_plus = traj_plus.isValid() ? computeTotalCost(traj_plus) : 1e10;
                
                MincoTrajectory::Waypoints q_minus = q;
                q_minus(d, i) -= eps;
                MincoTrajectory traj_minus(q_minus, T, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
                double cost_minus = traj_minus.isValid() ? computeTotalCost(traj_minus) : 1e10;
                
                grad_q(d, i) = (cost_plus - cost_minus) / (2.0 * eps);
            }
        }
        
        // Gradient for time allocation
        Eigen::VectorXd grad_T(M);
        for (int i = 0; i < M; ++i) {
            MincoTrajectory::TimeAlloc T_plus = T;
            T_plus(i) += eps;
            MincoTrajectory traj_plus(q, T_plus, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
            double cost_plus = traj_plus.isValid() ? computeTotalCost(traj_plus) : 1e10;
            
            MincoTrajectory::TimeAlloc T_minus = T;
            T_minus(i) = std::max(0.01, T_minus(i) - eps);
            MincoTrajectory traj_minus(q, T_minus, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
            double cost_minus = traj_minus.isValid() ? computeTotalCost(traj_minus) : 1e10;
            
            grad_T(i) = (cost_plus - cost_minus) / (2.0 * eps);
        }
        
        // Update parameters
        q -= learning_rate * grad_q;
        T -= learning_rate * grad_T;
        
        // Ensure positive time allocation
        for (int i = 0; i < M; ++i) {
            T(i) = std::max(0.01, T(i));
        }
        
        // Update trajectory
        traj = MincoTrajectory(q, T, start_pos, start_vel, goal_pos, Eigen::Vector3d::Zero());
        
        if (!traj.isValid()) {
            // Revert to previous valid state
            break;
        }
        
        double cost = computeTotalCost(traj);
        
        // Check convergence
        if (std::abs(prev_cost - cost) < config_.convergence_tolerance) {
            result.iterations = iter + 1;
            break;
        }
        
        // Adaptive learning rate
        if (cost > prev_cost) {
            learning_rate *= 0.5;
        } else {
            learning_rate *= 1.1;
        }
        learning_rate = std::min(0.1, std::max(0.001, learning_rate));
        
        prev_cost = cost;
        result.iterations = iter + 1;
    }
    
    result.trajectory = traj;
    result.total_cost = computeTotalCost(traj);
    result.feasible = traj.isValid();
    result.message = result.feasible ? "Optimization converged" : "Optimization failed";
    
    // Compute individual costs for debugging
    if (result.trajectory.isValid()) {
        result.cost_smoothness = penalties::smoothness_penalty(result.trajectory);
        result.cost_time = penalties::time_penalty(result.trajectory);
        result.cost_obstacle = computeObstaclePenalty(result.trajectory);
        result.cost_swarm = computeSwarmPenalty(result.trajectory);
        result.cost_dynamics = computeDynamicsPenalty(result.trajectory);
    }
    
    return result;
}

OptimizationResult TrajectoryOptimizer::reoptimize(
    const MincoTrajectory& initial_guess,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    if (!initial_guess.isValid()) {
        OptimizationResult result;
        result.feasible = false;
        result.message = "Invalid initial guess";
        return result;
    }
    
    // Extract boundary conditions from initial guess
    Eigen::Vector3d start_pos = initial_guess.getPosition(0);
    Eigen::Vector3d start_vel = initial_guess.getVelocity(0);
    double total_time = initial_guess.getTotalDuration();
    Eigen::Vector3d goal_pos = initial_guess.getPosition(total_time);
    
    return optimize(start_pos, start_vel, goal_pos, obstacles, other_trajectories);
}

double TrajectoryOptimizer::computeTotalCost(const MincoTrajectory& traj) {
    double cost = 0.0;
    
    cost += config_.weight_smoothness * computeSmoothnessPenalty(traj);
    cost += config_.weight_time * computeTimePenalty(traj);
    cost += config_.weight_obstacle * computeObstaclePenalty(traj);
    cost += config_.weight_swarm * computeSwarmPenalty(traj);
    cost += config_.weight_dynamics * computeDynamicsPenalty(traj);
    
    if (formation_target_.has_value()) {
        cost += config_.weight_formation * computeFormationPenalty(traj);
    }
    
    return cost;
}

double TrajectoryOptimizer::computeSmoothnessPenalty(const MincoTrajectory& traj) {
    return penalties::smoothness_penalty(traj);
}

double TrajectoryOptimizer::computeTimePenalty(const MincoTrajectory& traj) {
    return penalties::time_penalty(traj);
}

double TrajectoryOptimizer::computeObstaclePenalty(const MincoTrajectory& traj) {
    double total = 0.0;
    for (const auto& obs : current_obstacles_) {
        total += penalties::obstacle_penalty(traj, obs.point, obs.normal,
                                             config_.obstacle_clearance,
                                             config_.num_constraint_samples);
    }
    return total;
}

double TrajectoryOptimizer::computeSwarmPenalty(const MincoTrajectory& traj) {
    double total = 0.0;
    for (const auto& other : current_other_trajectories_) {
        total += penalties::swarm_penalty(traj, other, trajectory_start_time_,
                                          config_.swarm_clearance,
                                          config_.num_constraint_samples);
    }
    return total;
}

double TrajectoryOptimizer::computeDynamicsPenalty(const MincoTrajectory& traj) {
    double cost = 0.0;
    cost += penalties::velocity_penalty(traj, config_.max_velocity, 
                                        config_.num_constraint_samples);
    cost += penalties::acceleration_penalty(traj, config_.max_acceleration,
                                            config_.num_constraint_samples);
    cost += penalties::jerk_penalty(traj, config_.max_jerk,
                                    config_.num_constraint_samples);
    return cost;
}

double TrajectoryOptimizer::computeFormationPenalty(const MincoTrajectory& traj) {
    if (!formation_target_.has_value()) return 0.0;
    return penalties::formation_penalty(traj, formation_target_.value());
}

}  // namespace aura