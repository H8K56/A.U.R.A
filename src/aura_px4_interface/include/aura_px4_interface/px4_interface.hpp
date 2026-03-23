#pragma once

#include <rclcpp/rclcpp.hpp>
#include <Eigen/Dense>

#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>
#include <px4_msgs/msg/vehicle_local_position.hpp>
#include <px4_msgs/msg/vehicle_attitude.hpp>
#include <px4_msgs/msg/battery_status.hpp>
#include <px4_msgs/msg/sensor_gps.hpp>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>

#include "aura_msgs/msg/drone_state.hpp"

#include <functional>
#include <memory>

namespace aura {

/**
 * @brief PX4 vehicle arming state
 */
enum class ArmingState {
    DISARMED,
    ARMED,
    ARMING,
    DISARMING
};

/**
 * @brief PX4 flight mode
 */
enum class FlightMode {
    UNKNOWN,
    MANUAL,
    ALTITUDE,
    POSITION,
    OFFBOARD,
    MISSION,
    RETURN_TO_LAUNCH,
    LAND,
    TAKEOFF,
    HOLD
};

/**
 * @brief Vehicle state data from PX4
 */
struct VehicleState {
    // Timestamp
    rclcpp::Time timestamp;
    
    // Position (NED frame from PX4, we convert to ENU)
    Eigen::Vector3d position_enu;      // meters
    Eigen::Vector3d velocity_enu;      // m/s
    Eigen::Quaterniond orientation;    // quaternion
    
    // Raw NED values (for debugging)
    Eigen::Vector3d position_ned;
    Eigen::Vector3d velocity_ned;
    
    // Status
    ArmingState arming_state;
    FlightMode flight_mode;
    bool offboard_enabled;
    
    // Health
    float battery_percent;
    float battery_voltage;
    bool gps_fix;
    int num_satellites;
    
    // Validity flags
    bool position_valid;
    bool velocity_valid;
    bool attitude_valid;
    
    VehicleState()
        : position_enu(Eigen::Vector3d::Zero())
        , velocity_enu(Eigen::Vector3d::Zero())
        , orientation(Eigen::Quaterniond::Identity())
        , position_ned(Eigen::Vector3d::Zero())
        , velocity_ned(Eigen::Vector3d::Zero())
        , arming_state(ArmingState::DISARMED)
        , flight_mode(FlightMode::UNKNOWN)
        , offboard_enabled(false)
        , battery_percent(0.0f)
        , battery_voltage(0.0f)
        , gps_fix(false)
        , num_satellites(0)
        , position_valid(false)
        , velocity_valid(false)
        , attitude_valid(false)
    {}
};

/**
 * @brief Setpoint command for PX4
 */
struct TrajectorySetpoint {
    Eigen::Vector3d position;      // ENU frame, meters
    Eigen::Vector3d velocity;      // ENU frame, m/s
    Eigen::Vector3d acceleration;  // ENU frame, m/s^2
    float yaw;                     // radians
    float yaw_rate;                // rad/s
    
    // Control flags - which fields are valid
    bool position_valid;
    bool velocity_valid;
    bool acceleration_valid;
    bool yaw_valid;
    bool yaw_rate_valid;
    
    TrajectorySetpoint()
        : position(Eigen::Vector3d::Zero())
        , velocity(Eigen::Vector3d::Zero())
        , acceleration(Eigen::Vector3d::Zero())
        , yaw(0.0f)
        , yaw_rate(0.0f)
        , position_valid(true)
        , velocity_valid(false)
        , acceleration_valid(false)
        , yaw_valid(false)
        , yaw_rate_valid(false)
    {}
};

/**
 * @brief Low-level interface to PX4 autopilot via uORB/DDS bridge
 * 
 * Handles:
 * - Coordinate frame conversions (NED <-> ENU)
 * - Offboard control mode management
 * - Arming/disarming commands
 * - Vehicle state aggregation
 */
class PX4Interface {
public:
    using StateCallback = std::function<void(const VehicleState&)>;
    
    explicit PX4Interface(rclcpp::Node* node, int drone_id = 0);
    ~PX4Interface() = default;
    
    // Setpoint commands
    void sendPositionSetpoint(const Eigen::Vector3d& position_enu, float yaw = 0.0f);
    void sendVelocitySetpoint(const Eigen::Vector3d& velocity_enu, float yaw_rate = 0.0f);
    void sendTrajectorySetpoint(const TrajectorySetpoint& setpoint);
    
    // Vehicle commands
    bool arm();
    bool disarm();
    bool takeoff(float altitude = 2.0f);
    bool land();
    bool returnToLaunch();
    bool setOffboardMode();
    bool setHoldMode();
    
    // State access
    const VehicleState& getState() const { return state_; }
    bool isArmed() const { return state_.arming_state == ArmingState::ARMED; }
    bool isOffboardActive() const { return state_.offboard_enabled; }
    bool isPositionValid() const { return state_.position_valid; }
    
    // Callback registration
    void setStateCallback(StateCallback callback) { state_callback_ = callback; }
    
    // Convert to aura_msgs
    aura_msgs::msg::DroneState toDroneStateMsg() const;
    
    // Frame conversions (static utilities)
    static Eigen::Vector3d nedToEnu(const Eigen::Vector3d& ned);
    static Eigen::Vector3d enuToNed(const Eigen::Vector3d& enu);
    static Eigen::Quaterniond nedToEnuQuat(const Eigen::Quaterniond& ned_quat);
    
private:
    rclcpp::Node* node_;
    int drone_id_;
    std::string namespace_;
    
    VehicleState state_;
    StateCallback state_callback_;
    
    // Heartbeat for offboard mode
    rclcpp::TimerBase::SharedPtr offboard_heartbeat_timer_;
    bool offboard_mode_requested_;
    TrajectorySetpoint last_setpoint_;
    
    // Publishers (to PX4)
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_mode_pub_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr setpoint_pub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr command_pub_;
    
    // Subscribers (from PX4)
    rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr status_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleLocalPosition>::SharedPtr local_pos_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleAttitude>::SharedPtr attitude_sub_;
    rclcpp::Subscription<px4_msgs::msg::BatteryStatus>::SharedPtr battery_sub_;
    rclcpp::Subscription<px4_msgs::msg::SensorGps>::SharedPtr gps_sub_;
    
    // Callbacks
    void statusCallback(const px4_msgs::msg::VehicleStatus::SharedPtr msg);
    void localPositionCallback(const px4_msgs::msg::VehicleLocalPosition::SharedPtr msg);
    void attitudeCallback(const px4_msgs::msg::VehicleAttitude::SharedPtr msg);
    void batteryCallback(const px4_msgs::msg::BatteryStatus::SharedPtr msg);
    void gpsCallback(const px4_msgs::msg::SensorGps::SharedPtr msg);
    
    // Offboard heartbeat
    void offboardHeartbeat();
    
    // Send vehicle command
    void sendCommand(uint16_t command, float param1 = 0.0f, float param2 = 0.0f,
                     float param3 = 0.0f, float param4 = 0.0f,
                     float param5 = 0.0f, float param6 = 0.0f, float param7 = 0.0f);
    
    // Get PX4 timestamp
    uint64_t getPX4Timestamp() const;
};

}  // namespace aura
