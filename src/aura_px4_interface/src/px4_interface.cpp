#include "aura_px4_interface/px4_interface.hpp"
#include <chrono>

namespace aura {

PX4Interface::PX4Interface(rclcpp::Node* node, int drone_id)
    : node_(node)
    , drone_id_(drone_id)
    , offboard_mode_requested_(false)
{
    // Build namespace for multi-drone support
    // PX4 SITL uses /px4_N/ namespace for drone N
    if (drone_id_ == 0) {
        namespace_ = "";  // Single drone, no namespace
    } else {
        namespace_ = "/px4_" + std::to_string(drone_id_);
    }
    
    auto qos = rclcpp::QoS(10);
    qos.best_effort();  // PX4 uses best effort QoS
    
    // Publishers
    offboard_mode_pub_ = node_->create_publisher<px4_msgs::msg::OffboardControlMode>(
        namespace_ + "/fmu/in/offboard_control_mode", 10);
    
    setpoint_pub_ = node_->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
        namespace_ + "/fmu/in/trajectory_setpoint", 10);
    
    command_pub_ = node_->create_publisher<px4_msgs::msg::VehicleCommand>(
        namespace_ + "/fmu/in/vehicle_command", 10);
    
    // Subscribers
    status_sub_ = node_->create_subscription<px4_msgs::msg::VehicleStatus>(
        namespace_ + "/fmu/out/vehicle_status", qos,
        std::bind(&PX4Interface::statusCallback, this, std::placeholders::_1));
    
    local_pos_sub_ = node_->create_subscription<px4_msgs::msg::VehicleLocalPosition>(
        namespace_ + "/fmu/out/vehicle_local_position", qos,
        std::bind(&PX4Interface::localPositionCallback, this, std::placeholders::_1));
    
    attitude_sub_ = node_->create_subscription<px4_msgs::msg::VehicleAttitude>(
        namespace_ + "/fmu/out/vehicle_attitude", qos,
        std::bind(&PX4Interface::attitudeCallback, this, std::placeholders::_1));
    
    battery_sub_ = node_->create_subscription<px4_msgs::msg::BatteryStatus>(
        namespace_ + "/fmu/out/battery_status", qos,
        std::bind(&PX4Interface::batteryCallback, this, std::placeholders::_1));
    
    gps_sub_ = node_->create_subscription<px4_msgs::msg::SensorGps>(
        namespace_ + "/fmu/out/vehicle_gps_position", qos,
        std::bind(&PX4Interface::gpsCallback, this, std::placeholders::_1));
    
    // Offboard heartbeat timer (must send commands at >2Hz to stay in offboard mode)
    offboard_heartbeat_timer_ = node_->create_wall_timer(
        std::chrono::milliseconds(50),  // 20Hz
        std::bind(&PX4Interface::offboardHeartbeat, this));
    
    RCLCPP_INFO(node_->get_logger(), "PX4Interface initialized for drone %d (namespace: %s)",
                drone_id_, namespace_.empty() ? "/" : namespace_.c_str());
}

// Frame conversions
Eigen::Vector3d PX4Interface::nedToEnu(const Eigen::Vector3d& ned) {
    // NED (x=North, y=East, z=Down) to ENU (x=East, y=North, z=Up)
    return Eigen::Vector3d(ned.y(), ned.x(), -ned.z());
}

Eigen::Vector3d PX4Interface::enuToNed(const Eigen::Vector3d& enu) {
    // ENU to NED
    return Eigen::Vector3d(enu.y(), enu.x(), -enu.z());
}

Eigen::Quaterniond PX4Interface::nedToEnuQuat(const Eigen::Quaterniond& ned_quat) {
    // Rotation from NED to ENU frame
    // This involves a 180° rotation about the x-axis followed by frame swap
    Eigen::Quaterniond frame_rotation(0.7071068, 0.7071068, 0.0, 0.0);  // 90° about z
    return frame_rotation * ned_quat;
}

void PX4Interface::sendPositionSetpoint(const Eigen::Vector3d& position_enu, float yaw) {
    TrajectorySetpoint sp;
    sp.position = position_enu;
    sp.yaw = yaw;
    sp.position_valid = true;
    sp.yaw_valid = true;
    sendTrajectorySetpoint(sp);
}

void PX4Interface::sendVelocitySetpoint(const Eigen::Vector3d& velocity_enu, float yaw_rate) {
    TrajectorySetpoint sp;
    sp.velocity = velocity_enu;
    sp.yaw_rate = yaw_rate;
    sp.position_valid = false;
    sp.velocity_valid = true;
    sp.yaw_rate_valid = true;
    sendTrajectorySetpoint(sp);
}

void PX4Interface::sendTrajectorySetpoint(const TrajectorySetpoint& setpoint) {
    last_setpoint_ = setpoint;
    
    // Convert to PX4 message (NED frame)
    px4_msgs::msg::TrajectorySetpoint msg;
    msg.timestamp = getPX4Timestamp();
    
    if (setpoint.position_valid) {
        Eigen::Vector3d pos_ned = enuToNed(setpoint.position);
        msg.position[0] = pos_ned.x();
        msg.position[1] = pos_ned.y();
        msg.position[2] = pos_ned.z();
    } else {
        msg.position[0] = std::nanf("");
        msg.position[1] = std::nanf("");
        msg.position[2] = std::nanf("");
    }
    
    if (setpoint.velocity_valid) {
        Eigen::Vector3d vel_ned = enuToNed(setpoint.velocity);
        msg.velocity[0] = vel_ned.x();
        msg.velocity[1] = vel_ned.y();
        msg.velocity[2] = vel_ned.z();
    } else {
        msg.velocity[0] = std::nanf("");
        msg.velocity[1] = std::nanf("");
        msg.velocity[2] = std::nanf("");
    }
    
    if (setpoint.acceleration_valid) {
        Eigen::Vector3d acc_ned = enuToNed(setpoint.acceleration);
        msg.acceleration[0] = acc_ned.x();
        msg.acceleration[1] = acc_ned.y();
        msg.acceleration[2] = acc_ned.z();
    } else {
        msg.acceleration[0] = std::nanf("");
        msg.acceleration[1] = std::nanf("");
        msg.acceleration[2] = std::nanf("");
    }
    
    // Yaw in NED frame (same direction as ENU)
    msg.yaw = setpoint.yaw_valid ? setpoint.yaw : std::nanf("");
    msg.yawspeed = setpoint.yaw_rate_valid ? setpoint.yaw_rate : std::nanf("");
    
    setpoint_pub_->publish(msg);
}

bool PX4Interface::arm() {
    RCLCPP_INFO(node_->get_logger(), "Sending ARM command");
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM, 1.0f);
    return true;
}

bool PX4Interface::disarm() {
    RCLCPP_INFO(node_->get_logger(), "Sending DISARM command");
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM, 0.0f);
    return true;
}

bool PX4Interface::takeoff(float altitude) {
    RCLCPP_INFO(node_->get_logger(), "Sending TAKEOFF command (alt: %.1f m)", altitude);
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_TAKEOFF,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, altitude);
    return true;
}

bool PX4Interface::land() {
    RCLCPP_INFO(node_->get_logger(), "Sending LAND command");
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_LAND);
    return true;
}

bool PX4Interface::returnToLaunch() {
    RCLCPP_INFO(node_->get_logger(), "Sending RTL command");
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_RETURN_TO_LAUNCH);
    return true;
}

bool PX4Interface::setOffboardMode() {
    RCLCPP_INFO(node_->get_logger(), "Requesting OFFBOARD mode");
    offboard_mode_requested_ = true;
    
    // Send mode change command
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE,
                1.0f, 6.0f);  // 6 = OFFBOARD mode
    return true;
}

bool PX4Interface::setHoldMode() {
    RCLCPP_INFO(node_->get_logger(), "Requesting HOLD mode");
    offboard_mode_requested_ = false;
    
    sendCommand(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE,
                1.0f, 4.0f);  // 4 = HOLD mode
    return true;
}

void PX4Interface::offboardHeartbeat() {
    if (!offboard_mode_requested_) return;
    
    // Must continuously send offboard control mode to stay in offboard
    px4_msgs::msg::OffboardControlMode mode_msg;
    mode_msg.timestamp = getPX4Timestamp();
    mode_msg.position = true;
    mode_msg.velocity = false;
    mode_msg.acceleration = false;
    mode_msg.attitude = false;
    mode_msg.body_rate = false;
    
    offboard_mode_pub_->publish(mode_msg);
    
    // Also resend last setpoint
    if (last_setpoint_.position_valid || last_setpoint_.velocity_valid) {
        sendTrajectorySetpoint(last_setpoint_);
    }
}

void PX4Interface::sendCommand(uint16_t command, float param1, float param2,
                                float param3, float param4,
                                float param5, float param6, float param7) {
    px4_msgs::msg::VehicleCommand msg;
    msg.timestamp = getPX4Timestamp();
    msg.command = command;
    msg.param1 = param1;
    msg.param2 = param2;
    msg.param3 = param3;
    msg.param4 = param4;
    msg.param5 = param5;
    msg.param6 = param6;
    msg.param7 = param7;
    msg.target_system = 1;
    msg.target_component = 1;
    msg.source_system = 1;
    msg.source_component = 1;
    msg.from_external = true;
    
    command_pub_->publish(msg);
}

uint64_t PX4Interface::getPX4Timestamp() const {
    return node_->now().nanoseconds() / 1000;  // PX4 uses microseconds
}

// Callbacks
void PX4Interface::statusCallback(const px4_msgs::msg::VehicleStatus::SharedPtr msg) {
    // Arming state - use the arming_state field value directly
    // PX4 arming states: 0=INIT, 1=STANDBY, 2=ARMED, 3=STANDBY_ERROR, 4=SHUTDOWN, 5=IN_AIR_RESTORE
    switch (msg->arming_state) {
        case 2:  // ARMED
            state_.arming_state = ArmingState::ARMED;
            break;
        case 1:  // STANDBY (disarmed, ready to arm)
        case 0:  // INIT
        case 3:  // STANDBY_ERROR
        case 4:  // SHUTDOWN
        default:
            state_.arming_state = ArmingState::DISARMED;
            break;
    }
    
    // Flight mode / nav_state
    // Common nav_state values:
    // 0=MANUAL, 1=ALTCTL, 2=POSCTL, 3=AUTO_MISSION, 4=AUTO_LOITER, 
    // 5=AUTO_RTL, 6=ACRO, 14=OFFBOARD, 15=STAB, 17=AUTO_TAKEOFF, 18=AUTO_LAND
    switch (msg->nav_state) {
        case 0:  // MANUAL
            state_.flight_mode = FlightMode::MANUAL;
            break;
        case 1:  // ALTCTL
            state_.flight_mode = FlightMode::ALTITUDE;
            break;
        case 2:  // POSCTL
            state_.flight_mode = FlightMode::POSITION;
            break;
        case 14:  // OFFBOARD
            state_.flight_mode = FlightMode::OFFBOARD;
            state_.offboard_enabled = true;
            break;
        case 3:  // AUTO_MISSION
            state_.flight_mode = FlightMode::MISSION;
            break;
        case 5:  // AUTO_RTL
            state_.flight_mode = FlightMode::RETURN_TO_LAUNCH;
            break;
        case 18:  // AUTO_LAND
            state_.flight_mode = FlightMode::LAND;
            break;
        case 17:  // AUTO_TAKEOFF
            state_.flight_mode = FlightMode::TAKEOFF;
            break;
        case 4:  // AUTO_LOITER
            state_.flight_mode = FlightMode::HOLD;
            break;
        default:
            state_.flight_mode = FlightMode::UNKNOWN;
    }
    
    if (msg->nav_state != 14) {  // Not OFFBOARD
        state_.offboard_enabled = false;
    }
}

void PX4Interface::localPositionCallback(const px4_msgs::msg::VehicleLocalPosition::SharedPtr msg) {
    state_.timestamp = node_->now();
    
    // Store NED position
    state_.position_ned = Eigen::Vector3d(msg->x, msg->y, msg->z);
    state_.velocity_ned = Eigen::Vector3d(msg->vx, msg->vy, msg->vz);
    
    // Convert to ENU
    state_.position_enu = nedToEnu(state_.position_ned);
    state_.velocity_enu = nedToEnu(state_.velocity_ned);
    
    state_.position_valid = msg->xy_valid && msg->z_valid;
    state_.velocity_valid = msg->v_xy_valid && msg->v_z_valid;
    
    // Trigger callback
    if (state_callback_) {
        state_callback_(state_);
    }
}

void PX4Interface::attitudeCallback(const px4_msgs::msg::VehicleAttitude::SharedPtr msg) {
    // PX4 quaternion is [w, x, y, z]
    Eigen::Quaterniond q_ned(msg->q[0], msg->q[1], msg->q[2], msg->q[3]);
    state_.orientation = nedToEnuQuat(q_ned);
    state_.attitude_valid = true;
}

void PX4Interface::batteryCallback(const px4_msgs::msg::BatteryStatus::SharedPtr msg) {
    state_.battery_voltage = msg->voltage_v;
    state_.battery_percent = msg->remaining * 100.0f;
}

void PX4Interface::gpsCallback(const px4_msgs::msg::SensorGps::SharedPtr msg) {
    state_.gps_fix = (msg->fix_type >= 3);  // 3D fix or better
    state_.num_satellites = msg->satellites_used;
}

aura_msgs::msg::DroneState PX4Interface::toDroneStateMsg() const {
    aura_msgs::msg::DroneState msg;
    
    msg.timestamp = state_.timestamp;
    msg.drone_id = drone_id_;
    
    msg.position.x = state_.position_enu.x();
    msg.position.y = state_.position_enu.y();
    msg.position.z = state_.position_enu.z();
    
    msg.velocity.x = state_.velocity_enu.x();
    msg.velocity.y = state_.velocity_enu.y();
    msg.velocity.z = state_.velocity_enu.z();
    
    msg.orientation.w = state_.orientation.w();
    msg.orientation.x = state_.orientation.x();
    msg.orientation.y = state_.orientation.y();
    msg.orientation.z = state_.orientation.z();
    
    // Flight mode mapping
    switch (state_.flight_mode) {
        case FlightMode::OFFBOARD:
            msg.flight_mode = aura_msgs::msg::DroneState::FLIGHT_MODE_OPERATIONS;
            break;
        case FlightMode::TAKEOFF:
            msg.flight_mode = aura_msgs::msg::DroneState::FLIGHT_MODE_TAKEOFF;
            break;
        case FlightMode::LAND:
        case FlightMode::RETURN_TO_LAUNCH:
            msg.flight_mode = aura_msgs::msg::DroneState::FLIGHT_MODE_RTL;
            break;
        case FlightMode::HOLD:
            msg.flight_mode = aura_msgs::msg::DroneState::FLIGHT_MODE_FORMATION;
            break;
        default:
            msg.flight_mode = aura_msgs::msg::DroneState::FLIGHT_MODE_IDLE;
    }
    
    msg.battery_percent = state_.battery_percent;
    msg.battery_voltage = state_.battery_voltage;
    msg.gps_fix = state_.gps_fix;
    msg.num_satellites = state_.num_satellites;
    
    return msg;
}

}  // namespace aura