#include "aura_trajectory/minco_trajectory.hpp"
#include <stdexcept>

namespace aura {

// ============================================================================
// TrajectoryPiece Implementation
// ============================================================================

Eigen::Matrix<double, 6, 1> TrajectoryPiece::basis(double t) {
    Eigen::Matrix<double, 6, 1> b;
    b << 1.0, t, t*t, t*t*t, t*t*t*t, t*t*t*t*t;
    return b;
}

Eigen::Matrix<double, 6, 1> TrajectoryPiece::basis_derivative(double t, int order) {
    Eigen::Matrix<double, 6, 1> b = Eigen::Matrix<double, 6, 1>::Zero();
    
    switch (order) {
        case 0:
            return basis(t);
        case 1:  // velocity
            b << 0, 1, 2*t, 3*t*t, 4*t*t*t, 5*t*t*t*t;
            break;
        case 2:  // acceleration
            b << 0, 0, 2, 6*t, 12*t*t, 20*t*t*t;
            break;
        case 3:  // jerk
            b << 0, 0, 0, 6, 24*t, 60*t*t;
            break;
        default:
            throw std::invalid_argument("Order must be 0-3");
    }
    return b;
}

Eigen::Vector3d TrajectoryPiece::position(double t) const {
    return coefficients.transpose() * basis(t);
}

Eigen::Vector3d TrajectoryPiece::velocity(double t) const {
    return coefficients.transpose() * basis_derivative(t, 1);
}

Eigen::Vector3d TrajectoryPiece::acceleration(double t) const {
    return coefficients.transpose() * basis_derivative(t, 2);
}

Eigen::Vector3d TrajectoryPiece::jerk(double t) const {
    return coefficients.transpose() * basis_derivative(t, 3);
}

// ============================================================================
// MincoTrajectory Implementation
// ============================================================================

MincoTrajectory::MincoTrajectory(
    const Waypoints& waypoints, 
    const TimeAlloc& times,
    const Eigen::Vector3d& start_pos, 
    const Eigen::Vector3d& start_vel,
    const Eigen::Vector3d& end_pos, 
    const Eigen::Vector3d& end_vel) 
{
    setBoundaryConditions(start_pos, start_vel, end_pos, end_vel);
    setParameters(waypoints, times);
}

void MincoTrajectory::setBoundaryConditions(
    const Eigen::Vector3d& start_pos, 
    const Eigen::Vector3d& start_vel,
    const Eigen::Vector3d& end_pos, 
    const Eigen::Vector3d& end_vel) 
{
    start_pos_ = start_pos;
    start_vel_ = start_vel;
    end_pos_ = end_pos;
    end_vel_ = end_vel;
}

void MincoTrajectory::setParameters(const Waypoints& waypoints, const TimeAlloc& times) {
    // Validate inputs
    int M = static_cast<int>(times.size());  // Number of pieces
    
    if (M < 1) {
        is_valid_ = false;
        return;
    }
    
    if (waypoints.cols() != M - 1) {
        is_valid_ = false;
        return;
    }
    
    // Check all times are positive
    for (int i = 0; i < M; ++i) {
        if (times(i) <= 0) {
            is_valid_ = false;
            return;
        }
    }
    
    waypoints_ = waypoints;
    time_alloc_ = times;
    
    computeCoefficients();
    is_valid_ = true;
}

void MincoTrajectory::computeCoefficients() {
    int M = static_cast<int>(time_alloc_.size());
    pieces_.resize(M);
    
    if (M == 1) {
        // Single piece: simple quintic polynomial
        double T = time_alloc_(0);
        
        // Solve for coefficients given boundary conditions
        // p(0) = start_pos, p'(0) = start_vel, p''(0) = 0
        // p(T) = end_pos, p'(T) = end_vel, p''(T) = 0
        
        Eigen::Matrix<double, 6, 6> A;
        A << 1, 0, 0, 0, 0, 0,                           // p(0)
             0, 1, 0, 0, 0, 0,                           // p'(0)
             0, 0, 2, 0, 0, 0,                           // p''(0)
             1, T, T*T, T*T*T, T*T*T*T, T*T*T*T*T,       // p(T)
             0, 1, 2*T, 3*T*T, 4*T*T*T, 5*T*T*T*T,       // p'(T)
             0, 0, 2, 6*T, 12*T*T, 20*T*T*T;             // p''(T)
        
        Eigen::Matrix<double, 6, 3> b;
        b.row(0) = start_pos_.transpose();
        b.row(1) = start_vel_.transpose();
        b.row(2) = Eigen::Vector3d::Zero().transpose();  // Zero initial acceleration
        b.row(3) = end_pos_.transpose();
        b.row(4) = end_vel_.transpose();
        b.row(5) = Eigen::Vector3d::Zero().transpose();  // Zero final acceleration
        
        pieces_[0].coefficients = A.colPivHouseholderQr().solve(b);
        pieces_[0].duration = T;
    } else {
        // Multi-piece: use MINCO formulation
        // For simplicity, we use a basic spline interpolation here
        // Full MINCO implementation would use banded PLU factorization
        
        // Build waypoint sequence including start and end
        std::vector<Eigen::Vector3d> all_points;
        all_points.push_back(start_pos_);
        for (int i = 0; i < waypoints_.cols(); ++i) {
            all_points.push_back(waypoints_.col(i));
        }
        all_points.push_back(end_pos_);
        
        // Generate each piece with continuity constraints
        Eigen::Vector3d prev_vel = start_vel_;
        Eigen::Vector3d prev_acc = Eigen::Vector3d::Zero();
        
        for (int i = 0; i < M; ++i) {
            double T = time_alloc_(i);
            pieces_[i].duration = T;
            
            // Boundary conditions for this piece
            Eigen::Vector3d p0 = all_points[i];
            Eigen::Vector3d p1 = all_points[i + 1];
            Eigen::Vector3d v0 = prev_vel;
            Eigen::Vector3d a0 = prev_acc;
            
            // Estimate end velocity (simple linear interpolation of direction)
            Eigen::Vector3d v1;
            if (i == M - 1) {
                v1 = end_vel_;
            } else {
                Eigen::Vector3d dir = (all_points[i + 2] - p1).normalized();
                v1 = dir * prev_vel.norm();  // Maintain speed, change direction
            }
            Eigen::Vector3d a1 = Eigen::Vector3d::Zero();
            
            // Solve quintic
            Eigen::Matrix<double, 6, 6> A;
            A << 1, 0, 0, 0, 0, 0,
                 0, 1, 0, 0, 0, 0,
                 0, 0, 2, 0, 0, 0,
                 1, T, T*T, T*T*T, T*T*T*T, T*T*T*T*T,
                 0, 1, 2*T, 3*T*T, 4*T*T*T, 5*T*T*T*T,
                 0, 0, 2, 6*T, 12*T*T, 20*T*T*T;
            
            Eigen::Matrix<double, 6, 3> b;
            b.row(0) = p0.transpose();
            b.row(1) = v0.transpose();
            b.row(2) = a0.transpose();
            b.row(3) = p1.transpose();
            b.row(4) = v1.transpose();
            b.row(5) = a1.transpose();
            
            pieces_[i].coefficients = A.colPivHouseholderQr().solve(b);
            
            // Update for next piece
            prev_vel = pieces_[i].velocity(T);
            prev_acc = pieces_[i].acceleration(T);
        }
    }
}

int MincoTrajectory::getPieceIndex(double t) const {
    if (pieces_.empty() || t < 0) return -1;
    
    double accumulated_time = 0;
    for (size_t i = 0; i < pieces_.size(); ++i) {
        if (t <= accumulated_time + pieces_[i].duration) {
            return static_cast<int>(i);
        }
        accumulated_time += pieces_[i].duration;
    }
    
    return static_cast<int>(pieces_.size()) - 1;  // Clamp to last piece
}

Eigen::Vector3d MincoTrajectory::getPosition(double t) const {
    if (!is_valid_ || pieces_.empty()) {
        return Eigen::Vector3d::Zero();
    }
    
    int idx = getPieceIndex(t);
    if (idx < 0) return start_pos_;
    
    // Convert to local time within piece
    double local_t = t;
    for (int i = 0; i < idx; ++i) {
        local_t -= pieces_[i].duration;
    }
    local_t = std::max(0.0, std::min(local_t, pieces_[idx].duration));
    
    return pieces_[idx].position(local_t);
}

Eigen::Vector3d MincoTrajectory::getVelocity(double t) const {
    if (!is_valid_ || pieces_.empty()) {
        return Eigen::Vector3d::Zero();
    }
    
    int idx = getPieceIndex(t);
    if (idx < 0) return start_vel_;
    
    double local_t = t;
    for (int i = 0; i < idx; ++i) {
        local_t -= pieces_[i].duration;
    }
    local_t = std::max(0.0, std::min(local_t, pieces_[idx].duration));
    
    return pieces_[idx].velocity(local_t);
}

Eigen::Vector3d MincoTrajectory::getAcceleration(double t) const {
    if (!is_valid_ || pieces_.empty()) {
        return Eigen::Vector3d::Zero();
    }
    
    int idx = getPieceIndex(t);
    if (idx < 0) return Eigen::Vector3d::Zero();
    
    double local_t = t;
    for (int i = 0; i < idx; ++i) {
        local_t -= pieces_[i].duration;
    }
    local_t = std::max(0.0, std::min(local_t, pieces_[idx].duration));
    
    return pieces_[idx].acceleration(local_t);
}

double MincoTrajectory::getTotalDuration() const {
    double total = 0;
    for (const auto& piece : pieces_) {
        total += piece.duration;
    }
    return total;
}

void MincoTrajectory::getGradients(
    Eigen::MatrixXd& grad_q, 
    Eigen::VectorXd& grad_T,
    const Eigen::MatrixXd& grad_coeffs) const 
{
    // Simplified gradient propagation
    // Full implementation would use the MINCO mapping derivatives
    int M = getNumPieces();
    grad_q = Eigen::MatrixXd::Zero(3, M - 1);
    grad_T = Eigen::VectorXd::Zero(M);
    
    // Placeholder - actual implementation needs MINCO gradient formulas
    (void)grad_coeffs;  // Suppress unused warning
}

}  // namespace aura
