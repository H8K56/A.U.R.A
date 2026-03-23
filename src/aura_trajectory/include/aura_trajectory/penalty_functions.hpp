#pragma once

#include "aura_trajectory/minco_trajectory.hpp"
#include <cmath>

namespace aura {

/**
 * @brief Penalty function utilities for trajectory optimization
 * 
 * All penalties use the cubic formulation from the paper:
 *   max(constraint_violation, 0)^3
 * 
 * This is smooth (differentiable), zero when satisfied, and rapidly 
 * increasing when violated.
 */
namespace penalties {

/**
 * @brief Cubic penalty: max(x, 0)^3
 * Smooth, differentiable, zero for x <= 0
 */
inline double cubic_penalty(double x) {
    return (x > 0) ? x * x * x : 0.0;
}

/**
 * @brief Derivative of cubic penalty
 */
inline double cubic_penalty_grad(double x) {
    return (x > 0) ? 3.0 * x * x : 0.0;
}

/**
 * @brief Velocity magnitude penalty
 * J_d,v = sum max(||v(t)||^2 - v_max^2, 0)^3
 */
double velocity_penalty(const MincoTrajectory& traj, double v_max, 
                        int num_samples_per_piece);

/**
 * @brief Acceleration magnitude penalty  
 * J_d,a = sum max(||a(t)||^2 - a_max^2, 0)^3
 */
double acceleration_penalty(const MincoTrajectory& traj, double a_max,
                            int num_samples_per_piece);

/**
 * @brief Jerk magnitude penalty
 * J_d,j = sum max(||j(t)||^2 - j_max^2, 0)^3
 */
double jerk_penalty(const MincoTrajectory& traj, double j_max,
                    int num_samples_per_piece);

/**
 * @brief Obstacle avoidance penalty
 * J_o = sum max(clearance - d_obstacle(p(t)), 0)^3
 * 
 * @param point Point on obstacle plane
 * @param normal Normal vector pointing to free space
 * @param clearance Minimum required distance
 */
double obstacle_penalty(const MincoTrajectory& traj,
                        const Eigen::Vector3d& point,
                        const Eigen::Vector3d& normal,
                        double clearance,
                        int num_samples_per_piece);

/**
 * @brief Swarm collision avoidance penalty
 * J_w = sum max(clearance - ||p_self(t) - p_other(t)||, 0)^3
 * 
 * Time must be synchronized between trajectories.
 */
double swarm_penalty(const MincoTrajectory& self_traj,
                     const MincoTrajectory& other_traj,
                     double time_offset,  // Offset to align trajectories
                     double clearance,
                     int num_samples_per_piece);

/**
 * @brief Smoothness (control effort) penalty
 * J_s = integral ||p'''(t)||^2 dt
 * 
 * This has a closed-form solution for polynomial trajectories.
 */
double smoothness_penalty(const MincoTrajectory& traj);

/**
 * @brief Total time penalty
 * J_t = sum(T_i)
 */
double time_penalty(const MincoTrajectory& traj);

/**
 * @brief Formation penalty (distance to desired relative position)
 * J_f = ||p(T) - target||^2
 */
double formation_penalty(const MincoTrajectory& traj,
                         const Eigen::Vector3d& target_position);

// Gradient computation for each penalty
void velocity_penalty_gradient(const MincoTrajectory& traj, double v_max,
                               int num_samples_per_piece,
                               Eigen::MatrixXd& grad_coeffs);

void acceleration_penalty_gradient(const MincoTrajectory& traj, double a_max,
                                   int num_samples_per_piece,
                                   Eigen::MatrixXd& grad_coeffs);

void obstacle_penalty_gradient(const MincoTrajectory& traj,
                               const Eigen::Vector3d& point,
                               const Eigen::Vector3d& normal,
                               double clearance,
                               int num_samples_per_piece,
                               Eigen::MatrixXd& grad_coeffs);

void swarm_penalty_gradient(const MincoTrajectory& self_traj,
                            const MincoTrajectory& other_traj,
                            double time_offset,
                            double clearance,
                            int num_samples_per_piece,
                            Eigen::MatrixXd& grad_coeffs);

}  // namespace penalties
}  // namespace aura
