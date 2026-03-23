#include <rclcpp/rclcpp.hpp>
#include "aura_msgs/msg/swarm_state.hpp"
#include "aura_msgs/msg/drone_state.hpp"
#include "aura_msgs/msg/trajectory_broadcast.hpp"
#include "aura_msgs/srv/set_formation.hpp"

#include <map>
#include <mutex>

namespace aura {

/**
 * @brief Swarm coordinator node
 * 
 * Aggregates state from all drones and manages swarm-level coordination.
 * Runs as a single instance (not per-drone).
 */
class SwarmCoordinatorNode : public rclcpp::Node {
public:
    SwarmCoordinatorNode() : Node("swarm_coordinator") {
        this->declare_parameter("num_drones", 5);
        this->declare_parameter("publish_rate_hz", 10.0);
        
        num_drones_ = this->get_parameter("num_drones").as_int();
        double rate = this->get_parameter("publish_rate_hz").as_double();
        
        // Subscribe to individual drone states
        for (int i = 0; i < num_drones_; ++i) {
            std::string topic = "/drone_" + std::to_string(i) + "/drone_state";
            auto sub = this->create_subscription<aura_msgs::msg::DroneState>(
                topic, 10,
                [this, i](const aura_msgs::msg::DroneState::SharedPtr msg) {
                    this->droneStateCallback(i, msg);
                });
            drone_state_subs_.push_back(sub);
        }
        
        // Subscribe to trajectory broadcasts
        traj_sub_ = this->create_subscription<aura_msgs::msg::TrajectoryBroadcast>(
            "/swarm/trajectories", 10,
            std::bind(&SwarmCoordinatorNode::trajectoryCallback, this, std::placeholders::_1));
        
        // Publish aggregated swarm state
        swarm_state_pub_ = this->create_publisher<aura_msgs::msg::SwarmState>(
            "/swarm/state", 10);
        
        // Formation service
        formation_srv_ = this->create_service<aura_msgs::srv::SetFormation>(
            "/swarm/set_formation",
            std::bind(&SwarmCoordinatorNode::setFormationCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        // Timer to publish swarm state
        publish_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(static_cast<int>(1000.0 / rate)),
            std::bind(&SwarmCoordinatorNode::publishSwarmState, this));
        
        RCLCPP_INFO(this->get_logger(), "Swarm coordinator started for %d drones", num_drones_);
    }

private:
    int num_drones_;
    
    std::mutex state_mutex_;
    std::map<int, aura_msgs::msg::DroneState> drone_states_;
    std::map<int, rclcpp::Time> last_state_time_;
    
    std::mutex traj_mutex_;
    std::map<int, aura_msgs::msg::TrajectoryBroadcast> trajectories_;
    
    std::vector<rclcpp::Subscription<aura_msgs::msg::DroneState>::SharedPtr> drone_state_subs_;
    rclcpp::Subscription<aura_msgs::msg::TrajectoryBroadcast>::SharedPtr traj_sub_;
    rclcpp::Publisher<aura_msgs::msg::SwarmState>::SharedPtr swarm_state_pub_;
    rclcpp::Service<aura_msgs::srv::SetFormation>::SharedPtr formation_srv_;
    rclcpp::TimerBase::SharedPtr publish_timer_;
    
    void droneStateCallback(int drone_id, const aura_msgs::msg::DroneState::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(state_mutex_);
        drone_states_[drone_id] = *msg;
        last_state_time_[drone_id] = this->now();
    }
    
    void trajectoryCallback(const aura_msgs::msg::TrajectoryBroadcast::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(traj_mutex_);
        trajectories_[msg->drone_id] = *msg;
    }
    
    void publishSwarmState() {
        aura_msgs::msg::SwarmState swarm_state;
        swarm_state.timestamp = this->now();
        
        std::lock_guard<std::mutex> lock(state_mutex_);
        
        swarm_state.num_drones_total = num_drones_;
        swarm_state.num_drones_active = 0;
        swarm_state.num_hubs = 0;
        swarm_state.num_leaves = 0;
        
        double total_throughput = 0.0;
        double total_latency = 0.0;
        int throughput_count = 0;
        
        rclcpp::Time now = this->now();
        double timeout = 2.0;  // seconds
        
        for (const auto& [id, state] : drone_states_) {
            // Check if state is recent
            if ((now - last_state_time_[id]).seconds() > timeout) {
                continue;
            }
            
            swarm_state.num_drones_active++;
            
            if (state.role == aura_msgs::msg::DroneState::ROLE_HUB) {
                swarm_state.num_hubs++;
            } else {
                swarm_state.num_leaves++;
            }
            
            // Aggregate network metrics
            total_throughput += state.throughput_mbps;
            total_latency += state.latency_ms;
            throughput_count++;
            
            swarm_state.drones.push_back(state);
        }
        
        // Compute averages
        if (throughput_count > 0) {
            swarm_state.avg_throughput_mbps = total_throughput / throughput_count;
            swarm_state.avg_latency_ms = total_latency / throughput_count;
        }
        
        // Determine mission state based on drone states
        swarm_state.mission_state = determineMissionState();
        
        // Check mesh connectivity
        swarm_state.mesh_connected = checkMeshConnectivity();
        swarm_state.backhaul_connected = checkBackhaulConnectivity();
        
        swarm_state_pub_->publish(swarm_state);
    }
    
    uint8_t determineMissionState() {
        // Simple state determination based on drone states
        int idle_count = 0;
        int ops_count = 0;
        
        for (const auto& [id, state] : drone_states_) {
            if (state.flight_mode == aura_msgs::msg::DroneState::FLIGHT_MODE_IDLE) {
                idle_count++;
            } else if (state.flight_mode == aura_msgs::msg::DroneState::FLIGHT_MODE_OPERATIONS) {
                ops_count++;
            }
        }
        
        if (idle_count == static_cast<int>(drone_states_.size())) {
            return aura_msgs::msg::SwarmState::MISSION_IDLE;
        } else if (ops_count > 0) {
            return aura_msgs::msg::SwarmState::MISSION_OPERATIONS;
        } else {
            return aura_msgs::msg::SwarmState::MISSION_TRANSIT;
        }
    }
    
    bool checkMeshConnectivity() {
        // Simple check: all drones have at least one neighbor
        for (const auto& [id, state] : drone_states_) {
            if (state.connected_neighbors == 0) {
                return false;
            }
        }
        return !drone_states_.empty();
    }
    
    bool checkBackhaulConnectivity() {
        // Check if any hub has backhaul connection
        for (const auto& [id, state] : drone_states_) {
            if (state.role == aura_msgs::msg::DroneState::ROLE_HUB) {
                // Simplified: assume hub has backhaul if signal strength is good
                if (state.signal_strength_dbm > -80) {
                    return true;
                }
            }
        }
        return false;
    }
    
    void setFormationCallback(
        const aura_msgs::srv::SetFormation::Request::SharedPtr request,
        aura_msgs::srv::SetFormation::Response::SharedPtr response)
    {
        RCLCPP_INFO(this->get_logger(), "Setting formation type: %d", request->formation_type);
        
        // TODO: Compute formation positions and publish goals to each drone
        // For now, just acknowledge
        
        response->success = true;
        response->message = "Formation command received";
        response->estimated_transition_time = 10.0;  // Estimate
    }
};

}  // namespace aura

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<aura::SwarmCoordinatorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
