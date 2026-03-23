#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <std_srvs/srv/trigger.hpp>

#include "aura_px4_interface/px4_interface.hpp"
#include "aura_px4_interface/offboard_controller.hpp"
#include "aura_px4_interface/vehicle_state.hpp"

#include "aura_msgs/msg/drone_state.hpp"
#include "aura_msgs/srv/emergency_stop.hpp"

namespace aura {

/**
 * @brief ROS 2 node wrapping PX4 interface for a single drone
 * 
 * Provides:
 * - DroneState publishing
 * - Trajectory setpoint subscription
 * - Arm/disarm/takeoff/land services
 * - Integration with trajectory planner
 */
class PX4InterfaceNode : public rclcpp::Node {
public:
    PX4InterfaceNode() : Node("px4_interface") {
        // Parameters
        this->declare_parameter("drone_id", 0);
        this->declare_parameter("state_publish_rate_hz", 50.0);
        this->declare_parameter("takeoff_altitude", 2.0);
        this->declare_parameter("max_velocity", 3.0);
        
        drone_id_ = this->get_parameter("drone_id").as_int();
        double state_rate = this->get_parameter("state_publish_rate_hz").as_double();
        
        // Initialize PX4 interface
        px4_ = std::make_unique<PX4Interface>(this, drone_id_);
        
        // Configure offboard controller
        OffboardConfig config;
        config.takeoff_altitude = this->get_parameter("takeoff_altitude").as_double();
        config.max_velocity = this->get_parameter("max_velocity").as_double();
        controller_ = std::make_unique<OffboardController>(px4_.get(), config);
        
        // State estimator
        state_estimator_ = std::make_unique<VehicleStateEstimator>();
        
        // Set callback for state updates
        px4_->setStateCallback([this](const VehicleState& state) {
            state_estimator_->update(state);
        });
        
        // Publishers
        drone_state_pub_ = this->create_publisher<aura_msgs::msg::DroneState>(
            "drone_state", 10);
        
        // Subscribers
        setpoint_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "trajectory_setpoint", 10,
            std::bind(&PX4InterfaceNode::setpointCallback, this, std::placeholders::_1));
        
        // Services
        arm_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "arm",
            std::bind(&PX4InterfaceNode::armCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        disarm_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "disarm",
            std::bind(&PX4InterfaceNode::disarmCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        takeoff_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "takeoff",
            std::bind(&PX4InterfaceNode::takeoffCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        land_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "land",
            std::bind(&PX4InterfaceNode::landCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        emergency_stop_srv_ = this->create_service<aura_msgs::srv::EmergencyStop>(
            "emergency_stop",
            std::bind(&PX4InterfaceNode::emergencyStopCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        // Timers
        state_pub_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(static_cast<int>(1000.0 / state_rate)),
            std::bind(&PX4InterfaceNode::publishState, this));
        
        control_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(20),  // 50Hz control loop
            std::bind(&PX4InterfaceNode::controlLoop, this));
        
        RCLCPP_INFO(this->get_logger(), "PX4 interface node started for drone %d", drone_id_);
    }

private:
    int drone_id_;
    
    std::unique_ptr<PX4Interface> px4_;
    std::unique_ptr<OffboardController> controller_;
    std::unique_ptr<VehicleStateEstimator> state_estimator_;
    
    // Latest setpoint from trajectory planner
    geometry_msgs::msg::PoseStamped latest_setpoint_;
    bool setpoint_received_ = false;
    
    // ROS interfaces
    rclcpp::Publisher<aura_msgs::msg::DroneState>::SharedPtr drone_state_pub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr setpoint_sub_;
    
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr arm_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr disarm_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr takeoff_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr land_srv_;
    rclcpp::Service<aura_msgs::srv::EmergencyStop>::SharedPtr emergency_stop_srv_;
    
    rclcpp::TimerBase::SharedPtr state_pub_timer_;
    rclcpp::TimerBase::SharedPtr control_timer_;
    
    void setpointCallback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
        latest_setpoint_ = *msg;
        setpoint_received_ = true;
        
        // Forward to controller if ready
        if (controller_->isReady()) {
            Eigen::Vector3d pos(msg->pose.position.x,
                               msg->pose.position.y,
                               msg->pose.position.z);
            
            // Extract yaw from quaternion
            double yaw = 0.0;  // TODO: extract from quaternion
            
            controller_->setPositionTarget(pos, yaw);
        }
    }
    
    void publishState() {
        auto msg = px4_->toDroneStateMsg();
        drone_state_pub_->publish(msg);
    }
    
    void controlLoop() {
        controller_->update();
    }
    
    void armCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                     std_srvs::srv::Trigger::Response::SharedPtr response) {
        controller_->requestArm();
        response->success = true;
        response->message = "Arm command sent";
    }
    
    void disarmCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                        std_srvs::srv::Trigger::Response::SharedPtr response) {
        controller_->requestDisarm();
        response->success = true;
        response->message = "Disarm command sent";
    }
    
    void takeoffCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                         std_srvs::srv::Trigger::Response::SharedPtr response) {
        controller_->requestTakeoff();
        response->success = true;
        response->message = "Takeoff command sent";
    }
    
    void landCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                      std_srvs::srv::Trigger::Response::SharedPtr response) {
        controller_->requestLand();
        response->success = true;
        response->message = "Land command sent";
    }
    
    void emergencyStopCallback(
        const aura_msgs::srv::EmergencyStop::Request::SharedPtr request,
        aura_msgs::srv::EmergencyStop::Response::SharedPtr response) 
    {
        if (request->drone_id != drone_id_ && 
            request->drone_id != aura_msgs::srv::EmergencyStop::Request::ALL_DRONES) {
            response->success = false;
            response->message = "Wrong drone ID";
            response->drones_affected = 0;
            return;
        }
        
        controller_->requestEmergencyStop();
        
        response->success = true;
        response->message = "Emergency stop activated";
        response->drones_affected = 1;
        
        RCLCPP_ERROR(this->get_logger(), "EMERGENCY STOP ACTIVATED: %s", request->reason.c_str());
    }
};

}  // namespace aura

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<aura::PX4InterfaceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
