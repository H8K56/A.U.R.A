#pragma once

#include "aura_px4_interface/px4_interface.hpp"
#include <Eigen/Dense>
#include <deque>

namespace aura {

/**
 * @brief Offboard flight controller configuration
 */
struct OffboardConfig {
    // Position control gains
    double pos_p_gain;
    double vel_p_gain;
    double vel_i_gain;
    double vel_d_gain;
    
    // Limits
    double max_velocity;
    double max_acceleration;
    double max_yaw_rate;
    
    // Tolerances
    double position_tolerance;
    double velocity_tolerance;
    double yaw_tolerance;
    
    // Takeoff/landing
    double takeoff_altitude;
    double takeoff_velocity;
    double landing_velocity;
    
    OffboardConfig()
        : pos_p_gain(1.0)
        , vel_p_gain(1.5)
        , vel_i_gain(0.1)
        , vel_d_gain(0.05)
        , max_velocity(3.0)
        , max_acceleration(5.0)
        , max_yaw_rate(1.0)
        , position_tolerance(0.3)
        , velocity_tolerance(0.2)
        , yaw_tolerance(0.1)
        , takeoff_altitude(2.0)
        , takeoff_velocity(1.0)
        , landing_velocity(0.5)
    {}
};

/**
 * @brief Flight state machine states
 */
enum class OffboardState {
    IDLE,
    ARMING,
    TAKING_OFF,
    HOVERING,
    FOLLOWING_TRAJECTORY,
    HOLDING,
    LANDING,
    LANDED,
    EMERGENCY
};

/**
 * @brief High-level offboard flight controller
 * 
 * Manages:
 * - Automatic arming and takeoff sequence
 * - Position/velocity setpoint tracking
 * - Trajectory following
 * - Safe landing sequence
 * - Emergency handling
 */
class OffboardController {
public:
    explicit OffboardController(PX4Interface* px4, const OffboardConfig& config = OffboardConfig());
    
    // State machine control
    void update();  // Call at regular intervals (e.g., 50Hz)
    
    // Commands
    void requestArm();
    void requestDisarm();
    void requestTakeoff(double altitude = -1.0);  // -1 = use config default
    void requestLand();
    void requestHold();
    void requestEmergencyStop();
    
    // Setpoint control
    void setPositionTarget(const Eigen::Vector3d& position, double yaw = 0.0);
    void setVelocityTarget(const Eigen::Vector3d& velocity, double yaw_rate = 0.0);
    void setTrajectoryTarget(const Eigen::Vector3d& position,
                             const Eigen::Vector3d& velocity,
                             const Eigen::Vector3d& acceleration,
                             double yaw = 0.0);
    
    // State queries
    OffboardState getState() const { return state_; }
    std::string getStateName() const;
    bool isReady() const { return state_ == OffboardState::HOVERING || 
                                  state_ == OffboardState::FOLLOWING_TRAJECTORY ||
                                  state_ == OffboardState::HOLDING; }
    bool isAtTarget() const;
    
    // Configuration
    void setConfig(const OffboardConfig& config) { config_ = config; }
    const OffboardConfig& getConfig() const { return config_; }
    
private:
    PX4Interface* px4_;
    OffboardConfig config_;
    OffboardState state_;
    
    // Target setpoints
    Eigen::Vector3d target_position_;
    Eigen::Vector3d target_velocity_;
    Eigen::Vector3d target_acceleration_;
    double target_yaw_;
    double target_yaw_rate_;
    bool use_trajectory_mode_;
    
    // Takeoff tracking
    double takeoff_start_z_;
    double takeoff_target_z_;
    
    // PID state for velocity control
    Eigen::Vector3d velocity_integral_;
    Eigen::Vector3d last_velocity_error_;
    rclcpp::Time last_update_time_;
    
    // State machine handlers
    void handleIdle();
    void handleArming();
    void handleTakingOff();
    void handleHovering();
    void handleFollowingTrajectory();
    void handleHolding();
    void handleLanding();
    void handleLanded();
    void handleEmergency();
    
    // Control computation
    Eigen::Vector3d computeVelocityCommand(const Eigen::Vector3d& position_error);
    void sendSetpoint();
    
    // Utility
    void transitionTo(OffboardState new_state);
    bool isPositionReached(const Eigen::Vector3d& target) const;
};

}  // namespace aura
