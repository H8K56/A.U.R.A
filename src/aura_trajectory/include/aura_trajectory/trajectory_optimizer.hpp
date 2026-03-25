#pragma once

#include "aura_trajectory/minco_trajectory.hpp"
#include <functional>
#include <optional>

namespace aura {

/**
 * @brief Configuration for trajectory optimization
 */
struct OptimizationConfig {
    // Penalty weights (lambda values from paper Eq. 8)
    double weight_smoothness;
    double weight_time;
    double weight_obstacle;
    double weight_swarm;
    double weight_dynamics;
    double weight_formation;
    
    // Physical limits
    double max_velocity;
    double max_acceleration;
    double max_jerk;
    
    // Safety clearances
    double obstacle_clearance;
    double swarm_clearance;
    
    // Solver settings
    int max_iterations;
    double convergence_tolerance;
    int num_constraint_samples;
    
    // Replanning
    double replan_horizon;
    int num_pieces;
    
    // Default constructor
    OptimizationConfig()
        : weight_smoothness(1.0)
        , weight_time(10.0)
        , weight_obstacle(1000.0)
        , weight_swarm(1000.0)
        , weight_dynamics(1000.0)
        , weight_formation(1.0)
        , max_velocity(3.0)
        , max_acceleration(5.0)
        , max_jerk(20.0)
        , obstacle_clearance(0.5)
        , swarm_clearance(0.8)
        , max_iterations(100)
        , convergence_tolerance(1e-4)
        , num_constraint_samples(16)
        , replan_horizon(3.0)
        , num_pieces(8)
    {}
};

/**
 * @brief Obstacle representation (plane in 3D)
 */
struct Obstacle {
    Eigen::Vector3d point;    // Point on the plane
    Eigen::Vector3d normal;   // Normal vector pointing to free space
    
    // Distance from point p to obstacle (positive = free space)
    double distance(const Eigen::Vector3d& p) const {
        return (p - point).dot(normal);
    }
};

/**
 * @brief Result of trajectory optimization
 */
struct OptimizationResult {
    MincoTrajectory trajectory;
    bool feasible;
    double total_cost;
    int iterations;
    std::string message;
    
    // Individual costs for debugging
    double cost_smoothness;
    double cost_time;
    double cost_obstacle;
    double cost_swarm;
    double cost_dynamics;
    
    OptimizationResult()
        : feasible(false)
        , total_cost(0.0)
        , iterations(0)
        , cost_smoothness(0.0)
        , cost_time(0.0)
        , cost_obstacle(0.0)
        , cost_swarm(0.0)
        , cost_dynamics(0.0)
    {}
};

/**
 * @brief Multi-objective trajectory optimizer using gradient descent
 * 
 * Implements the optimization from Eq. 8: min sum(lambda_x * J_x)
 * Uses constraint transcription (soft penalties) for real-time performance.
 */
class TrajectoryOptimizer {
public:
    explicit TrajectoryOptimizer(const OptimizationConfig& config = OptimizationConfig());
    
    /**
     * @brief Optimize trajectory from current state to goal
     * 
     * @param start_pos Current position
     * @param start_vel Current velocity  
     * @param goal_pos Goal position
     * @param obstacles List of obstacles to avoid
     * @param other_trajectories Trajectories of other drones for collision avoidance
     * @return OptimizationResult containing the optimized trajectory
     */
    OptimizationResult optimize(
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& start_vel,
        const Eigen::Vector3d& goal_pos,
        const std::vector<Obstacle>& obstacles,
        const std::vector<MincoTrajectory>& other_trajectories
    );
    
    /**
     * @brief Re-optimize from a previous trajectory (warm start)
     */
    OptimizationResult reoptimize(
        const MincoTrajectory& initial_guess,
        const std::vector<Obstacle>& obstacles,
        const std::vector<MincoTrajectory>& other_trajectories
    );
    
    // Configuration
    void setConfig(const OptimizationConfig& config) { config_ = config; }
    const OptimizationConfig& getConfig() const { return config_; }
    
    // Set formation target (optional)
    void setFormationTarget(const Eigen::Vector3d& target) { 
        formation_target_ = target; 
    }
    
private:
    OptimizationConfig config_;
    std::optional<Eigen::Vector3d> formation_target_;
    
    // Current optimization state
    std::vector<Obstacle> current_obstacles_;
    std::vector<MincoTrajectory> current_other_trajectories_;
    double trajectory_start_time_;
    
    friend double evaluate(
    void* instance,
    const Eigen::VectorXd& x,
    Eigen::VectorXd& grad);

    Eigen::VectorXd last_x_;
    Eigen::VectorXd last_grad_;
    double last_cost_ = 0.0;
    bool grad_valid_ = false;
    // Cost computation
    double computeTotalCost(const MincoTrajectory& traj);
    
    // Individual penalty functions
    double computeSmoothnessPenalty(const MincoTrajectory& traj);
    double computeTimePenalty(const MincoTrajectory& traj);
    double computeObstaclePenalty(const MincoTrajectory& traj);
    double computeSwarmPenalty(const MincoTrajectory& traj);
    double computeDynamicsPenalty(const MincoTrajectory& traj);
    double computeFormationPenalty(const MincoTrajectory& traj);

};

}  // namespace aura