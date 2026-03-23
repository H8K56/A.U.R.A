#include "aura_px4_interface/offboard_controller.hpp"
#include <cmath>

namespace aura {

OffboardController::OffboardController(PX4Interface* px4, const OffboardConfig& config)
    : px4_(px4)
    , config_(config)
    , state_(OffboardState::IDLE)
    , target_position_(Eigen::Vector3d::Zero())
    , target_velocity_(Eigen::Vector3d::Zero())
    , target_acceleration_(Eigen::Vector3d::Zero())
    , target_yaw_(0.0)
    , target_yaw_rate_(0.0)
    , use_trajectory_mode_(false)
    , takeoff_start_z_(0.0)
    , takeoff_target_z_(0.0)
    , velocity_integral_(Eigen::Vector3d::Zero())
    , last_velocity_error_(Eigen::Vector3d::Zero())
{
}

void OffboardController::update() {
    switch (state_) {
        case OffboardState::IDLE:
            handleIdle();
            break;
        case OffboardState::ARMING:
            handleArming();
            break;
        case OffboardState::TAKING_OFF:
            handleTakingOff();
            break;
        case OffboardState::HOVERING:
            handleHovering();
            break;
        case OffboardState::FOLLOWING_TRAJECTORY:
            handleFollowingTrajectory();
            break;
        case OffboardState::HOLDING:
            handleHolding();
            break;
        case OffboardState::LANDING:
            handleLanding();
            break;
        case OffboardState::LANDED:
            handleLanded();
            break;
        case OffboardState::EMERGENCY:
            handleEmergency();
            break;
    }
}

std::string OffboardController::getStateName() const {
    switch (state_) {
        case OffboardState::IDLE: return "IDLE";
        case OffboardState::ARMING: return "ARMING";
        case OffboardState::TAKING_OFF: return "TAKING_OFF";
        case OffboardState::HOVERING: return "HOVERING";
        case OffboardState::FOLLOWING_TRAJECTORY: return "FOLLOWING_TRAJECTORY";
        case OffboardState::HOLDING: return "HOLDING";
        case OffboardState::LANDING: return "LANDING";
        case OffboardState::LANDED: return "LANDED";
        case OffboardState::EMERGENCY: return "EMERGENCY";
        default: return "UNKNOWN";
    }
}

void OffboardController::requestArm() {
    if (state_ == OffboardState::IDLE || state_ == OffboardState::LANDED) {
        transitionTo(OffboardState::ARMING);
    }
}

void OffboardController::requestDisarm() {
    px4_->disarm();
    transitionTo(OffboardState::IDLE);
}

void OffboardController::requestTakeoff(double altitude) {
    if (state_ != OffboardState::ARMING && state_ != OffboardState::IDLE) {
        // Only allow takeoff from ground states
        if (state_ != OffboardState::LANDED) {
            return;
        }
    }
    
    takeoff_start_z_ = px4_->getState().position_enu.z();
    takeoff_target_z_ = takeoff_start_z_ + (altitude > 0 ? altitude : config_.takeoff_altitude);
    
    // Set initial hover target
    target_position_ = px4_->getState().position_enu;
    target_position_.z() = takeoff_target_z_;
    
    if (px4_->isArmed()) {
        transitionTo(OffboardState::TAKING_OFF);
    } else {
        // Need to arm first
        requestArm();
    }
}

void OffboardController::requestLand() {
    if (isReady()) {
        transitionTo(OffboardState::LANDING);
    }
}

void OffboardController::requestHold() {
    if (isReady()) {
        target_position_ = px4_->getState().position_enu;
        transitionTo(OffboardState::HOLDING);
    }
}

void OffboardController::requestEmergencyStop() {
    transitionTo(OffboardState::EMERGENCY);
}

void OffboardController::setPositionTarget(const Eigen::Vector3d& position, double yaw) {
    target_position_ = position;
    target_yaw_ = yaw;
    use_trajectory_mode_ = false;
    
    if (state_ == OffboardState::HOVERING || state_ == OffboardState::HOLDING) {
        transitionTo(OffboardState::FOLLOWING_TRAJECTORY);
    }
}

void OffboardController::setVelocityTarget(const Eigen::Vector3d& velocity, double yaw_rate) {
    target_velocity_ = velocity;
    target_yaw_rate_ = yaw_rate;
    
    // Clamp velocity
    if (target_velocity_.norm() > config_.max_velocity) {
        target_velocity_ = target_velocity_.normalized() * config_.max_velocity;
    }
}

void OffboardController::setTrajectoryTarget(const Eigen::Vector3d& position,
                                             const Eigen::Vector3d& velocity,
                                             const Eigen::Vector3d& acceleration,
                                             double yaw) {
    target_position_ = position;
    target_velocity_ = velocity;
    target_acceleration_ = acceleration;
    target_yaw_ = yaw;
    use_trajectory_mode_ = true;
    
    if (state_ == OffboardState::HOVERING || state_ == OffboardState::HOLDING) {
        transitionTo(OffboardState::FOLLOWING_TRAJECTORY);
    }
}

bool OffboardController::isAtTarget() const {
    return isPositionReached(target_position_);
}

bool OffboardController::isPositionReached(const Eigen::Vector3d& target) const {
    const auto& state = px4_->getState();
    if (!state.position_valid) return false;
    
    double pos_error = (state.position_enu - target).norm();
    double vel_error = state.velocity_enu.norm();
    
    return (pos_error < config_.position_tolerance) && 
           (vel_error < config_.velocity_tolerance);
}

void OffboardController::transitionTo(OffboardState new_state) {
    if (state_ != new_state) {
        state_ = new_state;
        
        // Reset PID state on transition
        velocity_integral_ = Eigen::Vector3d::Zero();
        last_velocity_error_ = Eigen::Vector3d::Zero();
    }
}

void OffboardController::handleIdle() {
    // Nothing to do, waiting for commands
}

void OffboardController::handleArming() {
    if (px4_->isArmed()) {
        // Armed successfully, start takeoff sequence
        px4_->setOffboardMode();
        transitionTo(OffboardState::TAKING_OFF);
        return;
    }
    
    // Need to send setpoints before arming in offboard mode
    // Send current position as setpoint
    const auto& state = px4_->getState();
    if (state.position_valid) {
        target_position_ = state.position_enu;
        target_position_.z() = takeoff_target_z_;  // Target takeoff altitude
        px4_->sendPositionSetpoint(state.position_enu);
    }
    
    // Request arm
    static int arm_counter = 0;
    if (++arm_counter > 20) {  // Every ~1 second at 20Hz update rate
        px4_->setOffboardMode();
        px4_->arm();
        arm_counter = 0;
    }
}

void OffboardController::handleTakingOff() {
    const auto& state = px4_->getState();
    
    if (!px4_->isArmed()) {
        transitionTo(OffboardState::IDLE);
        return;
    }
    
    // Check if reached target altitude
    if (state.position_enu.z() >= takeoff_target_z_ - config_.position_tolerance) {
        target_position_ = state.position_enu;
        target_position_.z() = takeoff_target_z_;
        transitionTo(OffboardState::HOVERING);
        return;
    }
    
    // Climb at constant rate
    Eigen::Vector3d climb_target = state.position_enu;
    climb_target.z() = takeoff_target_z_;
    
    // Use position control with limited climb rate
    Eigen::Vector3d pos_error = climb_target - state.position_enu;
    Eigen::Vector3d vel_cmd = computeVelocityCommand(pos_error);
    
    // Limit climb rate
    vel_cmd.z() = std::min(vel_cmd.z(), config_.takeoff_velocity);
    
    TrajectorySetpoint sp;
    sp.position = climb_target;
    sp.velocity = vel_cmd;
    sp.position_valid = true;
    sp.velocity_valid = true;
    px4_->sendTrajectorySetpoint(sp);
}

void OffboardController::handleHovering() {
    if (!px4_->isArmed()) {
        transitionTo(OffboardState::LANDED);
        return;
    }
    
    // Hold current position
    px4_->sendPositionSetpoint(target_position_, target_yaw_);
}

void OffboardController::handleFollowingTrajectory() {
    const auto& state = px4_->getState();
    
    if (!px4_->isArmed()) {
        transitionTo(OffboardState::LANDED);
        return;
    }
    
    if (use_trajectory_mode_) {
        // Full trajectory setpoint
        TrajectorySetpoint sp;
        sp.position = target_position_;
        sp.velocity = target_velocity_;
        sp.acceleration = target_acceleration_;
        sp.yaw = target_yaw_;
        sp.position_valid = true;
        sp.velocity_valid = true;
        sp.acceleration_valid = true;
        sp.yaw_valid = true;
        px4_->sendTrajectorySetpoint(sp);
    } else {
        // Position-only setpoint with computed velocity
        Eigen::Vector3d pos_error = target_position_ - state.position_enu;
        Eigen::Vector3d vel_cmd = computeVelocityCommand(pos_error);
        
        TrajectorySetpoint sp;
        sp.position = target_position_;
        sp.velocity = vel_cmd;
        sp.yaw = target_yaw_;
        sp.position_valid = true;
        sp.velocity_valid = true;
        sp.yaw_valid = true;
        px4_->sendTrajectorySetpoint(sp);
    }
    
    // Check if reached target
    if (isPositionReached(target_position_)) {
        transitionTo(OffboardState::HOVERING);
    }
}

void OffboardController::handleHolding() {
    if (!px4_->isArmed()) {
        transitionTo(OffboardState::LANDED);
        return;
    }
    
    px4_->sendPositionSetpoint(target_position_, target_yaw_);
}

void OffboardController::handleLanding() {
    const auto& state = px4_->getState();
    
    if (!px4_->isArmed()) {
        transitionTo(OffboardState::LANDED);
        return;
    }
    
    // Descend at constant rate
    Eigen::Vector3d land_target = state.position_enu;
    land_target.z() = 0.0;  // Ground level
    
    Eigen::Vector3d pos_error = land_target - state.position_enu;
    Eigen::Vector3d vel_cmd = computeVelocityCommand(pos_error);
    
    // Limit descent rate
    vel_cmd.z() = std::max(vel_cmd.z(), -config_.landing_velocity);
    
    TrajectorySetpoint sp;
    sp.position = land_target;
    sp.velocity = vel_cmd;
    sp.position_valid = true;
    sp.velocity_valid = true;
    px4_->sendTrajectorySetpoint(sp);
    
    // Check if landed
    if (state.position_enu.z() < 0.2 && std::abs(state.velocity_enu.z()) < 0.1) {
        px4_->disarm();
        transitionTo(OffboardState::LANDED);
    }
}

void OffboardController::handleLanded() {
    // Nothing to do, waiting for new commands
}

void OffboardController::handleEmergency() {
    // Immediate hover/hold at current position
    const auto& state = px4_->getState();
    
    if (px4_->isArmed() && state.position_valid) {
        px4_->sendPositionSetpoint(state.position_enu);
    }
    
    // Could also trigger land or RTL here depending on policy
}

Eigen::Vector3d OffboardController::computeVelocityCommand(const Eigen::Vector3d& position_error) {
    // Simple P controller for velocity command
    Eigen::Vector3d vel_cmd = config_.pos_p_gain * position_error;
    
    // Clamp to max velocity
    if (vel_cmd.norm() > config_.max_velocity) {
        vel_cmd = vel_cmd.normalized() * config_.max_velocity;
    }
    
    return vel_cmd;
}

}  // namespace aura