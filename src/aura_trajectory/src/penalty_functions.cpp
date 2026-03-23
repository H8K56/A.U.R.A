#include "aura_trajectory/penalty_functions.hpp"
#include <cmath>

namespace aura {
namespace penalties {

double velocity_penalty(const MincoTrajectory& traj, double v_max, 
                        int num_samples_per_piece) {
    double penalty = 0.0;
    double v_max_sq = v_max * v_max;
    
    for (int p = 0; p < traj.getNumPieces(); ++p) {
        const auto& piece = traj.getPieces()[p];
        double dt = piece.duration / num_samples_per_piece;
        
        for (int s = 0; s <= num_samples_per_piece; ++s) {
            double t = s * dt;
            Eigen::Vector3d v = piece.velocity(t);
            double v_sq = v.squaredNorm();
            penalty += cubic_penalty(v_sq - v_max_sq);
        }
    }
    
    return penalty;
}

double acceleration_penalty(const MincoTrajectory& traj, double a_max,
                            int num_samples_per_piece) {
    double penalty = 0.0;
    double a_max_sq = a_max * a_max;
    
    for (int p = 0; p < traj.getNumPieces(); ++p) {
        const auto& piece = traj.getPieces()[p];
        double dt = piece.duration / num_samples_per_piece;
        
        for (int s = 0; s <= num_samples_per_piece; ++s) {
            double t = s * dt;
            Eigen::Vector3d a = piece.acceleration(t);
            double a_sq = a.squaredNorm();
            penalty += cubic_penalty(a_sq - a_max_sq);
        }
    }
    
    return penalty;
}

double jerk_penalty(const MincoTrajectory& traj, double j_max,
                    int num_samples_per_piece) {
    double penalty = 0.0;
    double j_max_sq = j_max * j_max;
    
    for (int p = 0; p < traj.getNumPieces(); ++p) {
        const auto& piece = traj.getPieces()[p];
        double dt = piece.duration / num_samples_per_piece;
        
        for (int s = 0; s <= num_samples_per_piece; ++s) {
            double t = s * dt;
            Eigen::Vector3d j = piece.jerk(t);
            double j_sq = j.squaredNorm();
            penalty += cubic_penalty(j_sq - j_max_sq);
        }
    }
    
    return penalty;
}

double obstacle_penalty(const MincoTrajectory& traj,
                        const Eigen::Vector3d& point,
                        const Eigen::Vector3d& normal,
                        double clearance,
                        int num_samples_per_piece) {
    double penalty = 0.0;
    
    for (int p = 0; p < traj.getNumPieces(); ++p) {
        const auto& piece = traj.getPieces()[p];
        double dt = piece.duration / num_samples_per_piece;
        
        for (int s = 0; s <= num_samples_per_piece; ++s) {
            double t = s * dt;
            Eigen::Vector3d pos = piece.position(t);
            
            // Signed distance to plane (positive = free side)
            double dist = (pos - point).dot(normal);
            
            // Penalize if closer than clearance
            penalty += cubic_penalty(clearance - dist);
        }
    }
    
    return penalty;
}

double swarm_penalty(const MincoTrajectory& self_traj,
                     const MincoTrajectory& other_traj,
                     double time_offset,
                     double clearance,
                     int num_samples_per_piece) {
    double penalty = 0.0;
    
    double self_duration = self_traj.getTotalDuration();
    double other_duration = other_traj.getTotalDuration();
    
    // Sample along self trajectory
    double total_samples = self_traj.getNumPieces() * num_samples_per_piece;
    double dt = self_duration / total_samples;
    
    for (int s = 0; s <= static_cast<int>(total_samples); ++s) {
        double t_self = s * dt;
        double t_other = t_self + time_offset;
        
        // Check if other trajectory is valid at this time
        if (t_other < 0 || t_other > other_duration) {
            continue;
        }
        
        Eigen::Vector3d pos_self = self_traj.getPosition(t_self);
        Eigen::Vector3d pos_other = other_traj.getPosition(t_other);
        
        double dist = (pos_self - pos_other).norm();
        penalty += cubic_penalty(clearance - dist);
    }
    
    return penalty;
}

double smoothness_penalty(const MincoTrajectory& traj) {
    // Smoothness = integral of squared jerk
    // For polynomial trajectories, this has a closed form
    double total = 0.0;
    
    for (const auto& piece : traj.getPieces()) {
        // For a 5th order polynomial, the jerk is quadratic
        // integral(jerk^2) can be computed analytically
        
        // Simplified: sample and integrate
        double T = piece.duration;
        int num_samples = 32;
        double dt = T / num_samples;
        
        for (int s = 0; s <= num_samples; ++s) {
            double t = s * dt;
            Eigen::Vector3d j = piece.jerk(t);
            total += j.squaredNorm() * dt;
        }
    }
    
    return total;
}

double time_penalty(const MincoTrajectory& traj) {
    return traj.getTotalDuration();
}

double formation_penalty(const MincoTrajectory& traj,
                         const Eigen::Vector3d& target_position) {
    // Penalize distance from final position to target
    Eigen::Vector3d final_pos = traj.getPosition(traj.getTotalDuration());
    return (final_pos - target_position).squaredNorm();
}

// Gradient implementations (numerical for now)
void velocity_penalty_gradient(const MincoTrajectory& traj, double v_max,
                               int num_samples_per_piece,
                               Eigen::MatrixXd& grad_coeffs) {
    // Placeholder - implement analytical gradients for production
    (void)traj; (void)v_max; (void)num_samples_per_piece;
    grad_coeffs.setZero();
}

void acceleration_penalty_gradient(const MincoTrajectory& traj, double a_max,
                                   int num_samples_per_piece,
                                   Eigen::MatrixXd& grad_coeffs) {
    (void)traj; (void)a_max; (void)num_samples_per_piece;
    grad_coeffs.setZero();
}

void obstacle_penalty_gradient(const MincoTrajectory& traj,
                               const Eigen::Vector3d& point,
                               const Eigen::Vector3d& normal,
                               double clearance,
                               int num_samples_per_piece,
                               Eigen::MatrixXd& grad_coeffs) {
    (void)traj; (void)point; (void)normal; (void)clearance;
    (void)num_samples_per_piece;
    grad_coeffs.setZero();
}

void swarm_penalty_gradient(const MincoTrajectory& self_traj,
                            const MincoTrajectory& other_traj,
                            double time_offset,
                            double clearance,
                            int num_samples_per_piece,
                            Eigen::MatrixXd& grad_coeffs) {
    (void)self_traj; (void)other_traj; (void)time_offset;
    (void)clearance; (void)num_samples_per_piece;
    grad_coeffs.setZero();
}

}  // namespace penalties
}  // namespace aura
