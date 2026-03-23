#include "aura_px4_interface/vehicle_state.hpp"

namespace aura {

VehicleStateEstimator::VehicleStateEstimator(const Config& config)
    : config_(config)
    , initialized_(false)
{
}

void VehicleStateEstimator::update(const VehicleState& state) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    last_update_time_ = state.timestamp;
    
    if (!initialized_) {
        filtered_state_ = state;
        initialized_ = true;
    } else {
        applyFilter(state);
    }
    
    // Add to buffer
    state_buffer_.push_back(state);
    pruneBuffer();
}

void VehicleStateEstimator::applyFilter(const VehicleState& new_state) {
    // Exponential moving average filter
    double alpha_pos = config_.position_filter_alpha;
    double alpha_vel = config_.velocity_filter_alpha;
    
    filtered_state_.position_enu = 
        alpha_pos * new_state.position_enu + (1.0 - alpha_pos) * filtered_state_.position_enu;
    
    filtered_state_.velocity_enu = 
        alpha_vel * new_state.velocity_enu + (1.0 - alpha_vel) * filtered_state_.velocity_enu;
    
    // Copy non-filtered values directly
    filtered_state_.timestamp = new_state.timestamp;
    filtered_state_.orientation = new_state.orientation;
    filtered_state_.arming_state = new_state.arming_state;
    filtered_state_.flight_mode = new_state.flight_mode;
    filtered_state_.offboard_enabled = new_state.offboard_enabled;
    filtered_state_.battery_percent = new_state.battery_percent;
    filtered_state_.battery_voltage = new_state.battery_voltage;
    filtered_state_.gps_fix = new_state.gps_fix;
    filtered_state_.num_satellites = new_state.num_satellites;
    filtered_state_.position_valid = new_state.position_valid;
    filtered_state_.velocity_valid = new_state.velocity_valid;
    filtered_state_.attitude_valid = new_state.attitude_valid;
}

void VehicleStateEstimator::pruneBuffer() {
    // Remove old states
    while (state_buffer_.size() > config_.buffer_size) {
        state_buffer_.pop_front();
    }
    
    // Remove states older than max_state_age
    while (!state_buffer_.empty()) {
        double age = (last_update_time_ - state_buffer_.front().timestamp).seconds();
        if (age > config_.max_state_age) {
            state_buffer_.pop_front();
        } else {
            break;
        }
    }
}

VehicleState VehicleStateEstimator::getState() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return filtered_state_;
}

VehicleState VehicleStateEstimator::getStateAtTime(const rclcpp::Time& time) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (state_buffer_.empty()) {
        return filtered_state_;
    }
    
    // Find states bracketing the requested time
    const VehicleState* before = nullptr;
    const VehicleState* after = nullptr;
    
    for (const auto& state : state_buffer_) {
        if (state.timestamp <= time) {
            before = &state;
        } else {
            after = &state;
            break;
        }
    }
    
    // If exact match or only one bound found, return closest
    if (!before) return state_buffer_.front();
    if (!after) return state_buffer_.back();
    
    // Linear interpolation
    double t1 = before->timestamp.seconds();
    double t2 = after->timestamp.seconds();
    double t = time.seconds();
    double alpha = (t - t1) / (t2 - t1);
    
    VehicleState interpolated;
    interpolated.timestamp = time;
    interpolated.position_enu = (1.0 - alpha) * before->position_enu + alpha * after->position_enu;
    interpolated.velocity_enu = (1.0 - alpha) * before->velocity_enu + alpha * after->velocity_enu;
    interpolated.orientation = before->orientation.slerp(alpha, after->orientation);
    
    // Copy other fields from 'after' state
    interpolated.arming_state = after->arming_state;
    interpolated.flight_mode = after->flight_mode;
    interpolated.offboard_enabled = after->offboard_enabled;
    interpolated.battery_percent = after->battery_percent;
    interpolated.battery_voltage = after->battery_voltage;
    interpolated.gps_fix = after->gps_fix;
    interpolated.num_satellites = after->num_satellites;
    interpolated.position_valid = before->position_valid && after->position_valid;
    interpolated.velocity_valid = before->velocity_valid && after->velocity_valid;
    interpolated.attitude_valid = before->attitude_valid && after->attitude_valid;
    
    return interpolated;
}

VehicleState VehicleStateEstimator::predictState(double dt) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    VehicleState predicted = filtered_state_;
    
    // Simple linear extrapolation
    if (filtered_state_.velocity_valid) {
        predicted.position_enu += filtered_state_.velocity_enu * dt;
    }
    
    return predicted;
}

bool VehicleStateEstimator::isValid() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return initialized_ && filtered_state_.position_valid;
}

double VehicleStateEstimator::getStateAge() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_) return std::numeric_limits<double>::max();
    
    // This would need current time passed in, simplified for now
    return 0.0;
}

}  // namespace aura
