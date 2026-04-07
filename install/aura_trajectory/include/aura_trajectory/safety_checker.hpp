#pragma once

#include "aura_trajectory/minco_trajectory.hpp"
#include "aura_trajectory/trajectory_optimizer.hpp"
#include <vector>

namespace aura {

/**
 * @brief Hierarchical safety guarantee system
 * 
 * Implements the safety checking from the paper:
 * 1. Post-check after planning
 * 2. Continuous background checking
 * 3. Emergency stop generation
 */
class SafetyChecker {
public:
    struct Config {
        double obstacle_clearance;
        double swarm_clearance;
        double emergency_stop_threshold;
        double velocity_limit;
        double acceleration_limit;
        int check_samples_per_piece;
        
        // Default constructor with default values
        Config() 
            : obstacle_clearance(0.5)
            , swarm_clearance(0.8)
            , emergency_stop_threshold(0.5)
            , velocity_limit(3.0)
            , acceleration_limit(5.0)
            , check_samples_per_piece(32)
        {}
    };
    
    enum class SafetyStatus {
        SAFE,
        REPLANNING_NEEDED,
        EMERGENCY_STOP_REQUIRED
    };
    
    struct CheckResult {
        SafetyStatus status;
        double time_to_collision;  // seconds, -1 if safe
        std::string violation_type;
        Eigen::Vector3d violation_point;
    };
    
    explicit SafetyChecker(const Config& config = Config());
    
    /**
     * @brief Check if trajectory is feasible (post-planning check)
     */
    CheckResult checkTrajectory(
        const MincoTrajectory& traj,
        const std::vector<Obstacle>& obstacles,
        const std::vector<MincoTrajectory>& other_trajectories
    );
    
    /**
     * @brief Continuous safety check at current time
     * Call this in the background at high frequency
     */
    CheckResult checkAtTime(
        const MincoTrajectory& traj,
        double current_time,  // Time along trajectory
        const std::vector<Obstacle>& obstacles,
        const std::vector<MincoTrajectory>& other_trajectories
    );
    
    /**
     * @brief Generate emergency stop trajectory
     * Creates a minimum-jerk trajectory that brings the drone to hover
     */
    MincoTrajectory generateEmergencyStop(
        const Eigen::Vector3d& current_pos,
        const Eigen::Vector3d& current_vel,
        const Eigen::Vector3d& current_acc
    );
    
    /**
     * @brief Check dynamics feasibility
     */
    bool checkDynamicsFeasibility(const MincoTrajectory& traj);
    
    void setConfig(const Config& config) { config_ = config; }
    
private:
    Config config_;
    
    // Check individual constraints
    double checkObstacleDistance(const Eigen::Vector3d& pos,
                                 const std::vector<Obstacle>& obstacles);
    
    double checkSwarmDistance(const Eigen::Vector3d& pos, double time,
                              const std::vector<MincoTrajectory>& other_trajectories);
};

}  // namespace aura