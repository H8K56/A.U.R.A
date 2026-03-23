#include "aura_trajectory/safety_checker.hpp"
#include <algorithm>
#include <cmath>

namespace aura {

SafetyChecker::SafetyChecker(const Config& config) : config_(config) {}

SafetyChecker::CheckResult SafetyChecker::checkTrajectory(
    const MincoTrajectory& traj,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories) 
{
    CheckResult result;
    result.status = SafetyStatus::SAFE;
    result.time_to_collision = -1;
    
    if (!traj.isValid()) {
        result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
        result.violation_type = "Invalid trajectory";
        return result;
    }
    
    // Check dynamics feasibility
    if (!checkDynamicsFeasibility(traj)) {
        result.status = SafetyStatus::REPLANNING_NEEDED;
        result.violation_type = "Dynamics violation";
        return result;
    }
    
    // Check obstacles and swarm at sampled points
    double total_time = traj.getTotalDuration();
    int total_samples = traj.getNumPieces() * config_.check_samples_per_piece;
    double dt = total_time / total_samples;
    
    for (int s = 0; s <= total_samples; ++s) {
        double t = s * dt;
        Eigen::Vector3d pos = traj.getPosition(t);
        
        // Check obstacles
        double obs_dist = checkObstacleDistance(pos, obstacles);
        if (obs_dist < config_.obstacle_clearance) {
            if (t < config_.emergency_stop_threshold) {
                result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
            } else {
                result.status = SafetyStatus::REPLANNING_NEEDED;
            }
            result.time_to_collision = t;
            result.violation_type = "Obstacle collision";
            result.violation_point = pos;
            return result;
        }
        
        // Check swarm
        double swarm_dist = checkSwarmDistance(pos, t, other_trajectories);
        if (swarm_dist < config_.swarm_clearance) {
            if (t < config_.emergency_stop_threshold) {
                result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
            } else {
                result.status = SafetyStatus::REPLANNING_NEEDED;
            }
            result.time_to_collision = t;
            result.violation_type = "Swarm collision";
            result.violation_point = pos;
            return result;
        }
    }
    
    return result;
}

SafetyChecker::CheckResult SafetyChecker::checkAtTime(
    const MincoTrajectory& traj,
    double current_time,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    CheckResult result;
    result.status = SafetyStatus::SAFE;
    result.time_to_collision = -1;
    
    if (!traj.isValid()) {
        result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
        result.violation_type = "Invalid trajectory";
        return result;
    }
    
    // Check a short horizon ahead
    double check_horizon = 2.0;  // seconds
    double total_time = traj.getTotalDuration();
    double end_time = std::min(current_time + check_horizon, total_time);
    
    int num_samples = 20;
    double dt = (end_time - current_time) / num_samples;
    
    for (int s = 0; s <= num_samples; ++s) {
        double t = current_time + s * dt;
        if (t > total_time) break;
        
        Eigen::Vector3d pos = traj.getPosition(t);
        
        // Check obstacles
        double obs_dist = checkObstacleDistance(pos, obstacles);
        if (obs_dist < config_.obstacle_clearance) {
            double time_until = t - current_time;
            if (time_until < config_.emergency_stop_threshold) {
                result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
            } else {
                result.status = SafetyStatus::REPLANNING_NEEDED;
            }
            result.time_to_collision = time_until;
            result.violation_type = "Obstacle collision imminent";
            result.violation_point = pos;
            return result;
        }
        
        // Check swarm
        double swarm_dist = checkSwarmDistance(pos, t, other_trajectories);
        if (swarm_dist < config_.swarm_clearance) {
            double time_until = t - current_time;
            if (time_until < config_.emergency_stop_threshold) {
                result.status = SafetyStatus::EMERGENCY_STOP_REQUIRED;
            } else {
                result.status = SafetyStatus::REPLANNING_NEEDED;
            }
            result.time_to_collision = time_until;
            result.violation_type = "Swarm collision imminent";
            result.violation_point = pos;
            return result;
        }
    }
    
    return result;
}

MincoTrajectory SafetyChecker::generateEmergencyStop(
    const Eigen::Vector3d& current_pos,
    const Eigen::Vector3d& current_vel,
    const Eigen::Vector3d& /* current_acc */)  // unused but kept for API compatibility
{
    // Generate minimum-jerk trajectory to hover
    // Using a single piece that brings velocity and acceleration to zero
    
    double v_mag = current_vel.norm();
    
    // Estimate stopping time based on max deceleration
    double stop_time = std::max(0.5, v_mag / config_.acceleration_limit * 1.5);
    
    // Final position: current + some deceleration distance
    Eigen::Vector3d final_pos = current_pos;
    if (v_mag > 0.01) {
        // Estimate stopping distance
        double stop_dist = 0.5 * v_mag * stop_time;
        final_pos = current_pos + current_vel.normalized() * stop_dist * 0.5;
    }
    
    // Create single-piece trajectory
    MincoTrajectory::Waypoints q(3, 0);  // No intermediate waypoints
    MincoTrajectory::TimeAlloc T(1);
    T(0) = stop_time;
    
    return MincoTrajectory(q, T, current_pos, current_vel, 
                          final_pos, Eigen::Vector3d::Zero());
}

bool SafetyChecker::checkDynamicsFeasibility(const MincoTrajectory& traj) {
    int total_samples = traj.getNumPieces() * config_.check_samples_per_piece;
    double dt = traj.getTotalDuration() / total_samples;
    
    for (int s = 0; s <= total_samples; ++s) {
        double t = s * dt;
        
        Eigen::Vector3d v = traj.getVelocity(t);
        Eigen::Vector3d a = traj.getAcceleration(t);
        
        if (v.norm() > config_.velocity_limit * 1.1) {  // 10% margin
            return false;
        }
        if (a.norm() > config_.acceleration_limit * 1.1) {
            return false;
        }
    }
    
    return true;
}

double SafetyChecker::checkObstacleDistance(
    const Eigen::Vector3d& pos,
    const std::vector<Obstacle>& obstacles)
{
    double min_dist = std::numeric_limits<double>::max();
    
    for (const auto& obs : obstacles) {
        double dist = obs.distance(pos);
        min_dist = std::min(min_dist, dist);
    }
    
    return min_dist;
}

double SafetyChecker::checkSwarmDistance(
    const Eigen::Vector3d& pos, 
    double time,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    double min_dist = std::numeric_limits<double>::max();
    
    for (const auto& other : other_trajectories) {
        if (!other.isValid()) continue;
        
        // Clamp time to other trajectory's duration
        double other_time = std::min(time, other.getTotalDuration());
        Eigen::Vector3d other_pos = other.getPosition(other_time);
        
        double dist = (pos - other_pos).norm();
        min_dist = std::min(min_dist, dist);
    }
    
    return min_dist;
}

}  // namespace aura