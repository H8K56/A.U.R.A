#pragma once

#include "aura_px4_interface/px4_interface.hpp"
#include <deque>
#include <mutex>

namespace aura {

/**
 * @brief Vehicle state estimator with filtering
 * 
 * Provides:
 * - State buffering for latency compensation
 * - Simple low-pass filtering
 * - Velocity estimation from position if needed
 */
class VehicleStateEstimator {
public:
    struct Config {
        double position_filter_alpha;  // Low-pass filter coefficient (0-1)
        double velocity_filter_alpha;
        size_t buffer_size;            // Number of states to keep
        double max_state_age;          // Maximum age in seconds
        
        Config()
            : position_filter_alpha(0.8)
            , velocity_filter_alpha(0.7)
            , buffer_size(100)
            , max_state_age(1.0)
        {}
    };
    
    explicit VehicleStateEstimator(const Config& config = Config());
    
    // Update with new state
    void update(const VehicleState& state);
    
    // Get current (filtered) state
    VehicleState getState() const;
    
    // Get state at specific time (interpolated)
    VehicleState getStateAtTime(const rclcpp::Time& time) const;
    
    // Get predicted state (simple linear extrapolation)
    VehicleState predictState(double dt) const;
    
    // Validity
    bool isValid() const;
    double getStateAge() const;  // seconds since last update
    
private:
    Config config_;
    mutable std::mutex mutex_;
    
    VehicleState filtered_state_;
    std::deque<VehicleState> state_buffer_;
    rclcpp::Time last_update_time_;
    bool initialized_;
    
    void applyFilter(const VehicleState& new_state);
    void pruneBuffer();
};

}  // namespace aura
