#pragma once

#include <Eigen/Dense>
#include <vector>
#include <memory>

namespace aura {

/**
 * @brief Single piece of a MINCO trajectory (polynomial segment)
 * 
 * MINCO uses 5th-order polynomials (s=3 for jerk control) for smooth trajectories.
 * Each piece connects two waypoints with continuous position, velocity, and acceleration.
 */
struct TrajectoryPiece {
    // Polynomial coefficients: p(t) = c^T * [1, t, t^2, t^3, t^4, t^5]
    Eigen::Matrix<double, 6, 3> coefficients;  // 6 coeffs x 3 dimensions (x,y,z)
    double duration;  // Time duration of this piece (T_i)
    
    // Evaluate trajectory at time t (0 <= t <= duration)
    Eigen::Vector3d position(double t) const;
    Eigen::Vector3d velocity(double t) const;
    Eigen::Vector3d acceleration(double t) const;
    Eigen::Vector3d jerk(double t) const;
    
    // Get polynomial basis vector [1, t, t^2, t^3, t^4, t^5]
    static Eigen::Matrix<double, 6, 1> basis(double t);
    static Eigen::Matrix<double, 6, 1> basis_derivative(double t, int order);
};

/**
 * @brief MINCO trajectory representation
 * 
 * MINCO (Minimum Control) trajectory class that decouples spatial and temporal
 * optimization. Key innovation: O(M) complexity via banded PLU factorization.
 * 
 * Reference: Zhou et al., Science Robotics 2022
 */
class MincoTrajectory {
public:
    using Waypoints = Eigen::Matrix<double, 3, Eigen::Dynamic>;  // 3 x (M-1)
    using TimeAlloc = Eigen::VectorXd;  // M x 1
    
    MincoTrajectory() = default;
    MincoTrajectory(const Waypoints& waypoints, const TimeAlloc& times,
                    const Eigen::Vector3d& start_pos, const Eigen::Vector3d& start_vel,
                    const Eigen::Vector3d& end_pos, const Eigen::Vector3d& end_vel);
    
    // Core MINCO mapping: (q, T) -> polynomial coefficients
    void setParameters(const Waypoints& waypoints, const TimeAlloc& times);
    void setBoundaryConditions(const Eigen::Vector3d& start_pos, 
                               const Eigen::Vector3d& start_vel,
                               const Eigen::Vector3d& end_pos,
                               const Eigen::Vector3d& end_vel);
    
    // Evaluate trajectory at absolute time t
    Eigen::Vector3d getPosition(double t) const;
    Eigen::Vector3d getVelocity(double t) const;
    Eigen::Vector3d getAcceleration(double t) const;
    
    // Get piece index for time t
    int getPieceIndex(double t) const;
    
    // Getters
    double getTotalDuration() const;
    int getNumPieces() const { return static_cast<int>(pieces_.size()); }
    const std::vector<TrajectoryPiece>& getPieces() const { return pieces_; }
    const Waypoints& getWaypoints() const { return waypoints_; }
    const TimeAlloc& getTimeAllocation() const { return time_alloc_; }
    
    // For gradient computation (optimization)
    void getGradients(Eigen::MatrixXd& grad_q, Eigen::VectorXd& grad_T,
                      const Eigen::MatrixXd& grad_coeffs) const;
    
    // Validity check
    bool isValid() const { return is_valid_; }
    
private:
    std::vector<TrajectoryPiece> pieces_;
    Waypoints waypoints_;
    TimeAlloc time_alloc_;
    
    Eigen::Vector3d start_pos_, start_vel_;
    Eigen::Vector3d end_pos_, end_vel_;
    
    bool is_valid_ = false;
    
    // Banded matrix solver for O(M) complexity
    //void solveBandedSystem();
    void computeCoefficients();
};

}  // namespace aura
