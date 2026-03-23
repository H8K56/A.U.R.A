#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>

#include "aura_px4_interface/px4_interface.hpp"
#include "aura_px4_interface/offboard_controller.hpp"

#include "aura_msgs/msg/drone_state.hpp"
#include "aura_msgs/msg/swarm_state.hpp"
#include "aura_msgs/srv/emergency_stop.hpp"

#include <vector>
#include <memory>

namespace aura {

/**
 * @brief Multi-drone PX4 swarm manager
 * 
 * Manages multiple PX4 interfaces for swarm operations.
 * Provides synchronized arming, takeoff, and emergency stop.
 */
class SwarmPX4ManagerNode : public rclcpp::Node {
public:
    SwarmPX4ManagerNode() : Node("swarm_px4_manager") {
        // Parameters
        this->declare_parameter("num_drones", 5);
        this->declare_parameter("takeoff_altitude", 2.0);
        this->declare_parameter("takeoff_spacing", 2.0);  // meters between drones
        this->declare_parameter("stagger_delay_ms", 500);  // delay between drone takeoffs
        
        num_drones_ = this->get_parameter("num_drones").as_int();
        takeoff_altitude_ = this->get_parameter("takeoff_altitude").as_double();
        takeoff_spacing_ = this->get_parameter("takeoff_spacing").as_double();
        stagger_delay_ms_ = this->get_parameter("stagger_delay_ms").as_int();
        
        // Initialize interfaces for each drone
        OffboardConfig config;
        config.takeoff_altitude = takeoff_altitude_;
        
        for (int i = 0; i < num_drones_; ++i) {
            auto px4 = std::make_unique<PX4Interface>(this, i);
            auto controller = std::make_unique<OffboardController>(px4.get(), config);
            
            px4_interfaces_.push_back(std::move(px4));
            controllers_.push_back(std::move(controller));
        }
        
        // Publishers
        swarm_state_pub_ = this->create_publisher<aura_msgs::msg::SwarmState>(
            "/swarm/state", 10);
        
        // Subscribe to individual drone states
        for (int i = 0; i < num_drones_; ++i) {
            std::string topic = "/drone_" + std::to_string(i) + "/drone_state";
            auto sub = this->create_subscription<aura_msgs::msg::DroneState>(
                topic, 10,
                [this, i](const aura_msgs::msg::DroneState::SharedPtr msg) {
                    if (i < static_cast<int>(drone_states_.size())) {
                        drone_states_[i] = *msg;
                    }
                });
            state_subs_.push_back(sub);
            drone_states_.emplace_back();
        }
        
        // Swarm-level services
        arm_all_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "/swarm/arm_all",
            std::bind(&SwarmPX4ManagerNode::armAllCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        disarm_all_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "/swarm/disarm_all",
            std::bind(&SwarmPX4ManagerNode::disarmAllCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        takeoff_all_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "/swarm/takeoff_all",
            std::bind(&SwarmPX4ManagerNode::takeoffAllCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        land_all_srv_ = this->create_service<std_srvs::srv::Trigger>(
            "/swarm/land_all",
            std::bind(&SwarmPX4ManagerNode::landAllCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        emergency_stop_all_srv_ = this->create_service<aura_msgs::srv::EmergencyStop>(
            "/swarm/emergency_stop",
            std::bind(&SwarmPX4ManagerNode::emergencyStopAllCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        // Control timer
        control_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(20),
            std::bind(&SwarmPX4ManagerNode::controlLoop, this));
        
        // State publish timer
        state_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&SwarmPX4ManagerNode::publishSwarmState, this));
        
        RCLCPP_INFO(this->get_logger(), "Swarm PX4 manager started for %d drones", num_drones_);
    }

private:
    int num_drones_;
    double takeoff_altitude_;
    double takeoff_spacing_;
    int stagger_delay_ms_;
    
    std::vector<std::unique_ptr<PX4Interface>> px4_interfaces_;
    std::vector<std::unique_ptr<OffboardController>> controllers_;
    std::vector<aura_msgs::msg::DroneState> drone_states_;
    
    // Staggered operation state
    int stagger_index_ = 0;
    rclcpp::Time last_stagger_time_;
    bool staggered_op_active_ = false;
    enum class StaggerOp { NONE, ARM, TAKEOFF, LAND, DISARM } stagger_op_ = StaggerOp::NONE;
    
    // ROS interfaces
    rclcpp::Publisher<aura_msgs::msg::SwarmState>::SharedPtr swarm_state_pub_;
    std::vector<rclcpp::Subscription<aura_msgs::msg::DroneState>::SharedPtr> state_subs_;
    
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr arm_all_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr disarm_all_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr takeoff_all_srv_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr land_all_srv_;
    rclcpp::Service<aura_msgs::srv::EmergencyStop>::SharedPtr emergency_stop_all_srv_;
    
    rclcpp::TimerBase::SharedPtr control_timer_;
    rclcpp::TimerBase::SharedPtr state_timer_;
    
    void controlLoop() {
        // Update all controllers
        for (auto& controller : controllers_) {
            controller->update();
        }
        
        // Handle staggered operations
        if (staggered_op_active_) {
            auto now = this->now();
            double elapsed_ms = (now - last_stagger_time_).seconds() * 1000.0;
            
            if (elapsed_ms >= stagger_delay_ms_ && stagger_index_ < num_drones_) {
                executeStaggeredOp(stagger_index_);
                stagger_index_++;
                last_stagger_time_ = now;
                
                if (stagger_index_ >= num_drones_) {
                    staggered_op_active_ = false;
                    stagger_op_ = StaggerOp::NONE;
                    RCLCPP_INFO(this->get_logger(), "Staggered operation complete");
                }
            }
        }
    }
    
    void executeStaggeredOp(int drone_id) {
        switch (stagger_op_) {
            case StaggerOp::ARM:
                controllers_[drone_id]->requestArm();
                RCLCPP_INFO(this->get_logger(), "Arming drone %d", drone_id);
                break;
            case StaggerOp::TAKEOFF:
                controllers_[drone_id]->requestTakeoff(takeoff_altitude_);
                RCLCPP_INFO(this->get_logger(), "Takeoff drone %d", drone_id);
                break;
            case StaggerOp::LAND:
                controllers_[drone_id]->requestLand();
                RCLCPP_INFO(this->get_logger(), "Landing drone %d", drone_id);
                break;
            case StaggerOp::DISARM:
                controllers_[drone_id]->requestDisarm();
                RCLCPP_INFO(this->get_logger(), "Disarming drone %d", drone_id);
                break;
            default:
                break;
        }
    }
    
    void startStaggeredOp(StaggerOp op) {
        stagger_op_ = op;
        stagger_index_ = 0;
        staggered_op_active_ = true;
        last_stagger_time_ = this->now();
        
        // Execute first one immediately
        executeStaggeredOp(0);
        stagger_index_ = 1;
    }
    
    void publishSwarmState() {
        aura_msgs::msg::SwarmState msg;
        msg.timestamp = this->now();
        msg.num_drones_total = num_drones_;
        
        int active = 0;
        int hubs = 0;
        int leaves = 0;
        
        for (const auto& state : drone_states_) {
            if (state.flight_mode != aura_msgs::msg::DroneState::FLIGHT_MODE_IDLE) {
                active++;
            }
            if (state.role == aura_msgs::msg::DroneState::ROLE_HUB) {
                hubs++;
            } else {
                leaves++;
            }
            msg.drones.push_back(state);
        }
        
        msg.num_drones_active = active;
        msg.num_hubs = hubs;
        msg.num_leaves = leaves;
        
        swarm_state_pub_->publish(msg);
    }
    
    void armAllCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                        std_srvs::srv::Trigger::Response::SharedPtr response) {
        RCLCPP_INFO(this->get_logger(), "Arming all drones (staggered)");
        startStaggeredOp(StaggerOp::ARM);
        response->success = true;
        response->message = "Arm all command initiated";
    }
    
    void disarmAllCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                           std_srvs::srv::Trigger::Response::SharedPtr response) {
        RCLCPP_INFO(this->get_logger(), "Disarming all drones");
        // Disarm is immediate, no stagger needed for safety
        for (auto& controller : controllers_) {
            controller->requestDisarm();
        }
        response->success = true;
        response->message = "Disarm all command sent";
    }
    
    void takeoffAllCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                            std_srvs::srv::Trigger::Response::SharedPtr response) {
        RCLCPP_INFO(this->get_logger(), "Takeoff all drones (staggered)");
        startStaggeredOp(StaggerOp::TAKEOFF);
        response->success = true;
        response->message = "Takeoff all command initiated";
    }
    
    void landAllCallback(const std_srvs::srv::Trigger::Request::SharedPtr,
                         std_srvs::srv::Trigger::Response::SharedPtr response) {
        RCLCPP_INFO(this->get_logger(), "Landing all drones (staggered)");
        startStaggeredOp(StaggerOp::LAND);
        response->success = true;
        response->message = "Land all command initiated";
    }
    
    void emergencyStopAllCallback(
        const aura_msgs::srv::EmergencyStop::Request::SharedPtr request,
        aura_msgs::srv::EmergencyStop::Response::SharedPtr response)
    {
        RCLCPP_ERROR(this->get_logger(), "EMERGENCY STOP ALL: %s", request->reason.c_str());
        
        // Emergency stop is immediate, no stagger
        for (auto& controller : controllers_) {
            controller->requestEmergencyStop();
        }
        
        // Cancel any staggered operation
        staggered_op_active_ = false;
        stagger_op_ = StaggerOp::NONE;
        
        response->success = true;
        response->message = "Emergency stop activated for all drones";
        response->drones_affected = num_drones_;
    }
};

}  // namespace aura

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<aura::SwarmPX4ManagerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
