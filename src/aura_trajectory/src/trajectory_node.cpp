#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include "aura_trajectory/minco_trajectory.hpp"
#include "aura_trajectory/trajectory_optimizer.hpp"
#include "aura_trajectory/safety_checker.hpp"

#include "aura_msgs/msg/drone_state.hpp"
#include "aura_msgs/msg/coverage_goal.hpp"
#include "aura_msgs/msg/trajectory_broadcast.hpp"
#include "aura_msgs/srv/request_trajectory.hpp"
#include "aura_msgs/srv/emergency_stop.hpp"

#include <mutex>
#include <map>

namespace aura {

class TrajectoryNode : public rclcpp::Node {
public:
    TrajectoryNode() : Node("trajectory_planner") {
        // Declare parameters
        this->declare_parameter("drone_id", 0);
        this->declare_parameter("replan_rate_hz", 10.0);
        this->declare_parameter("max_velocity", 3.0);
        this->declare_parameter("max_acceleration", 5.0);
        this->declare_parameter("obstacle_clearance", 0.5);
        this->declare_parameter("swarm_clearance", 0.8);
        
        drone_id_ = this->get_parameter("drone_id").as_int();
        double replan_rate = this->get_parameter("replan_rate_hz").as_double();
        
        // Configure optimizer
        OptimizationConfig config;
        config.max_velocity = this->get_parameter("max_velocity").as_double();
        config.max_acceleration = this->get_parameter("max_acceleration").as_double();
        config.obstacle_clearance = this->get_parameter("obstacle_clearance").as_double();
        config.swarm_clearance = this->get_parameter("swarm_clearance").as_double();
        
        optimizer_ = std::make_unique<TrajectoryOptimizer>(config);
        safety_checker_ = std::make_unique<SafetyChecker>();
        
        // Subscribers
        goal_sub_ = this->create_subscription<aura_msgs::msg::CoverageGoal>(
            "coverage_goal", 10,
            std::bind(&TrajectoryNode::goalCallback, this, std::placeholders::_1));
        
        state_sub_ = this->create_subscription<aura_msgs::msg::DroneState>(
            "drone_state", 10,
            std::bind(&TrajectoryNode::stateCallback, this, std::placeholders::_1));
        
        // Subscribe to all drones' trajectory broadcasts
        swarm_traj_sub_ = this->create_subscription<aura_msgs::msg::TrajectoryBroadcast>(
            "/swarm/trajectories", 10,
            std::bind(&TrajectoryNode::swarmTrajectoryCallback, this, std::placeholders::_1));
        
        // Publishers
        traj_pub_ = this->create_publisher<aura_msgs::msg::TrajectoryBroadcast>(
            "/swarm/trajectories", 10);
        
        setpoint_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(
            "trajectory_setpoint", 10);
        
        // Services
        request_traj_srv_ = this->create_service<aura_msgs::srv::RequestTrajectory>(
            "request_trajectory",
            std::bind(&TrajectoryNode::requestTrajectoryCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        emergency_stop_srv_ = this->create_service<aura_msgs::srv::EmergencyStop>(
            "emergency_stop",
            std::bind(&TrajectoryNode::emergencyStopCallback, this,
                      std::placeholders::_1, std::placeholders::_2));
        
        // Replan timer
        replan_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(static_cast<int>(1000.0 / replan_rate)),
            std::bind(&TrajectoryNode::replanCallback, this));
        
        // Safety check timer (higher frequency)
        safety_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(20),  // 50 Hz
            std::bind(&TrajectoryNode::safetyCheckCallback, this));
        
        // Setpoint publishing timer (high frequency for smooth tracking)
        setpoint_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),  // 100 Hz
            std::bind(&TrajectoryNode::publishSetpointCallback, this));
        
        RCLCPP_INFO(this->get_logger(), "Trajectory planner node started for drone %d", drone_id_);
    }

private:
    // Parameters
    int drone_id_;
    
    // Core components
    std::unique_ptr<TrajectoryOptimizer> optimizer_;
    std::unique_ptr<SafetyChecker> safety_checker_;
    
    // Current state
    std::mutex state_mutex_;
    Eigen::Vector3d current_pos_ = Eigen::Vector3d::Zero();
    Eigen::Vector3d current_vel_ = Eigen::Vector3d::Zero();
    Eigen::Vector3d current_acc_ = Eigen::Vector3d::Zero();
    bool state_valid_ = false;
    
    // Current goal
    std::mutex goal_mutex_;
    Eigen::Vector3d goal_pos_ = Eigen::Vector3d::Zero();
    bool goal_valid_ = false;
    
    // Current trajectory
    std::mutex traj_mutex_;
    MincoTrajectory current_trajectory_;
    rclcpp::Time trajectory_start_time_;
    bool trajectory_valid_ = false;
    bool emergency_stop_active_ = false;
    
    // Other drones' trajectories
    std::mutex swarm_mutex_;
    std::map<int, MincoTrajectory> other_trajectories_;
    
    // Obstacles (would come from perception in real system)
    std::vector<Obstacle> obstacles_;
    
    // ROS interfaces
    rclcpp::Subscription<aura_msgs::msg::CoverageGoal>::SharedPtr goal_sub_;
    rclcpp::Subscription<aura_msgs::msg::DroneState>::SharedPtr state_sub_;
    rclcpp::Subscription<aura_msgs::msg::TrajectoryBroadcast>::SharedPtr swarm_traj_sub_;
    
    rclcpp::Publisher<aura_msgs::msg::TrajectoryBroadcast>::SharedPtr traj_pub_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr setpoint_pub_;
    
    rclcpp::Service<aura_msgs::srv::RequestTrajectory>::SharedPtr request_traj_srv_;
    rclcpp::Service<aura_msgs::srv::EmergencyStop>::SharedPtr emergency_stop_srv_;
    
    rclcpp::TimerBase::SharedPtr replan_timer_;
    rclcpp::TimerBase::SharedPtr safety_timer_;
    rclcpp::TimerBase::SharedPtr setpoint_timer_;
    
    // Callbacks
    void goalCallback(const aura_msgs::msg::CoverageGoal::SharedPtr msg) {
        if (msg->drone_id != drone_id_) return;
        
        std::lock_guard<std::mutex> lock(goal_mutex_);
        goal_pos_ << msg->position.x, msg->position.y, msg->position.z;
        goal_valid_ = true;
        
        RCLCPP_INFO(this->get_logger(), "Received new goal: [%.2f, %.2f, %.2f]",
                    goal_pos_.x(), goal_pos_.y(), goal_pos_.z());
    }
    
    void stateCallback(const aura_msgs::msg::DroneState::SharedPtr msg) {
        if (msg->drone_id != drone_id_) return;
        
        std::lock_guard<std::mutex> lock(state_mutex_);
        current_pos_ << msg->position.x, msg->position.y, msg->position.z;
        current_vel_ << msg->velocity.x, msg->velocity.y, msg->velocity.z;
        state_valid_ = true;
    }
    
    void swarmTrajectoryCallback(const aura_msgs::msg::TrajectoryBroadcast::SharedPtr msg) {
        if (msg->drone_id == drone_id_) return;  // Ignore our own
        
        // Convert ROS message to MincoTrajectory
        int M = msg->num_pieces;
        if (M < 1 || msg->waypoints.size() != static_cast<size_t>(M - 1)) {
            return;
        }
        
        MincoTrajectory::Waypoints q(3, M - 1);
        for (size_t i = 0; i < msg->waypoints.size(); ++i) {
            q(0, i) = msg->waypoints[i].x;
            q(1, i) = msg->waypoints[i].y;
            q(2, i) = msg->waypoints[i].z;
        }
        
        MincoTrajectory::TimeAlloc T(M);
        for (int i = 0; i < M; ++i) {
            T(i) = msg->time_allocation[i];
        }
        
        // Get start position - use first waypoint or goal if no waypoints
        Eigen::Vector3d start_pos;
        if (msg->waypoints.empty()) {
            start_pos << msg->goal_position.x, msg->goal_position.y, msg->goal_position.z;
        } else {
            start_pos << msg->waypoints[0].x, msg->waypoints[0].y, msg->waypoints[0].z;
        }
        
        Eigen::Vector3d goal_pos;
        goal_pos << msg->goal_position.x, msg->goal_position.y, msg->goal_position.z;
        
        MincoTrajectory traj(q, T, start_pos, Eigen::Vector3d::Zero(),
                            goal_pos, Eigen::Vector3d::Zero());
        
        if (traj.isValid()) {
            std::lock_guard<std::mutex> lock(swarm_mutex_);
            other_trajectories_[msg->drone_id] = traj;
        }
    }
    
    void replanCallback() {
        if (emergency_stop_active_) return;
        
        std::lock_guard<std::mutex> goal_lock(goal_mutex_);
        std::lock_guard<std::mutex> state_lock(state_mutex_);
        
        if (!goal_valid_ || !state_valid_) return;
        
        // Check if we're close enough to goal
        double dist_to_goal = (current_pos_ - goal_pos_).norm();
        if (dist_to_goal < 0.5) {
            // Close enough, no need to replan
            return;
        }
        
        // Collect other trajectories
        std::vector<MincoTrajectory> others;
        {
            std::lock_guard<std::mutex> lock(swarm_mutex_);
            for (const auto& [id, traj] : other_trajectories_) {
                others.push_back(traj);
            }
        }
        
        // Optimize trajectory
        auto result = optimizer_->optimize(
            current_pos_, current_vel_, goal_pos_,
            obstacles_, others
        );
        
        if (result.feasible) {
            std::lock_guard<std::mutex> lock(traj_mutex_);
            current_trajectory_ = result.trajectory;
            trajectory_start_time_ = this->now();
            trajectory_valid_ = true;
            
            // Broadcast trajectory
            broadcastTrajectory();
            
            RCLCPP_DEBUG(this->get_logger(), "Replanned trajectory, cost: %.3f", result.total_cost);
        } else {
            RCLCPP_WARN(this->get_logger(), "Failed to plan trajectory: %s", result.message.c_str());
        }
    }
    
    void safetyCheckCallback() {
        std::lock_guard<std::mutex> lock(traj_mutex_);
        
        if (!trajectory_valid_) return;
        
        double elapsed = (this->now() - trajectory_start_time_).seconds();
        
        std::vector<MincoTrajectory> others;
        {
            std::lock_guard<std::mutex> swarm_lock(swarm_mutex_);
            for (const auto& [id, traj] : other_trajectories_) {
                others.push_back(traj);
            }
        }
        
        auto check = safety_checker_->checkAtTime(
            current_trajectory_, elapsed, obstacles_, others
        );
        
        switch (check.status) {
            case SafetyChecker::SafetyStatus::SAFE:
                break;
                
            case SafetyChecker::SafetyStatus::REPLANNING_NEEDED:
                RCLCPP_WARN(this->get_logger(), "Safety check: replanning needed - %s",
                            check.violation_type.c_str());
                // Trigger immediate replan
                trajectory_valid_ = false;
                break;
                
            case SafetyChecker::SafetyStatus::EMERGENCY_STOP_REQUIRED:
                RCLCPP_ERROR(this->get_logger(), "EMERGENCY STOP - %s, collision in %.2fs",
                            check.violation_type.c_str(), check.time_to_collision);
                triggerEmergencyStop();
                break;
        }
    }
    
    void publishSetpointCallback() {
        std::lock_guard<std::mutex> lock(traj_mutex_);
        
        if (!trajectory_valid_) return;
        
        double elapsed = (this->now() - trajectory_start_time_).seconds();
        
        // Clamp to trajectory duration
        double duration = current_trajectory_.getTotalDuration();
        elapsed = std::min(elapsed, duration);
        
        Eigen::Vector3d pos = current_trajectory_.getPosition(elapsed);
        
        // Publish setpoint
        geometry_msgs::msg::PoseStamped setpoint;
        setpoint.header.stamp = this->now();
        setpoint.header.frame_id = "world";
        setpoint.pose.position.x = pos.x();
        setpoint.pose.position.y = pos.y();
        setpoint.pose.position.z = pos.z();
        setpoint.pose.orientation.w = 1.0;
        
        setpoint_pub_->publish(setpoint);
    }
    
    void broadcastTrajectory() {
        aura_msgs::msg::TrajectoryBroadcast msg;
        msg.timestamp = this->now();
        msg.drone_id = drone_id_;
        msg.start_time = trajectory_start_time_;
        
        const auto& waypoints = current_trajectory_.getWaypoints();
        const auto& times = current_trajectory_.getTimeAllocation();
        
        msg.num_pieces = current_trajectory_.getNumPieces();
        
        for (int i = 0; i < waypoints.cols(); ++i) {
            geometry_msgs::msg::Point pt;
            pt.x = waypoints(0, i);
            pt.y = waypoints(1, i);
            pt.z = waypoints(2, i);
            msg.waypoints.push_back(pt);
        }
        
        for (int i = 0; i < times.size(); ++i) {
            msg.time_allocation.push_back(times(i));
        }
        
        msg.total_duration = current_trajectory_.getTotalDuration();
        msg.is_valid = trajectory_valid_ && !emergency_stop_active_;
        msg.max_velocity = optimizer_->getConfig().max_velocity;
        msg.clearance = optimizer_->getConfig().swarm_clearance;
        
        // Goal position
        Eigen::Vector3d goal = current_trajectory_.getPosition(msg.total_duration);
        msg.goal_position.x = goal.x();
        msg.goal_position.y = goal.y();
        msg.goal_position.z = goal.z();
        msg.goal_reached = false;
        
        traj_pub_->publish(msg);
    }
    
    void triggerEmergencyStop() {
        std::lock_guard<std::mutex> state_lock(state_mutex_);
        
        emergency_stop_active_ = true;
        
        // Generate emergency stop trajectory
        current_trajectory_ = safety_checker_->generateEmergencyStop(
            current_pos_, current_vel_, current_acc_
        );
        trajectory_start_time_ = this->now();
        trajectory_valid_ = current_trajectory_.isValid();
        
        RCLCPP_ERROR(this->get_logger(), "Emergency stop trajectory generated");
    }
    
    void requestTrajectoryCallback(
        const aura_msgs::srv::RequestTrajectory::Request::SharedPtr request,
        aura_msgs::srv::RequestTrajectory::Response::SharedPtr response)
    {
        if (request->drone_id != drone_id_) {
            response->success = false;
            response->message = "Wrong drone ID";
            return;
        }
        
        Eigen::Vector3d goal;
        goal << request->goal_position.x, request->goal_position.y, request->goal_position.z;
        
        std::lock_guard<std::mutex> state_lock(state_mutex_);
        
        std::vector<MincoTrajectory> others;
        {
            std::lock_guard<std::mutex> lock(swarm_mutex_);
            for (const auto& [id, traj] : other_trajectories_) {
                others.push_back(traj);
            }
        }
        
        auto result = optimizer_->optimize(
            current_pos_, current_vel_, goal,
            obstacles_, others
        );
        
        response->success = result.feasible;
        response->message = result.message;
        response->estimated_time = result.trajectory.getTotalDuration();
        
        if (result.feasible) {
            std::lock_guard<std::mutex> lock(traj_mutex_);
            current_trajectory_ = result.trajectory;
            trajectory_start_time_ = this->now();
            trajectory_valid_ = true;
            emergency_stop_active_ = false;
            
            // Set new goal
            {
                std::lock_guard<std::mutex> goal_lock(goal_mutex_);
                goal_pos_ = goal;
                goal_valid_ = true;
            }
            
            broadcastTrajectory();
        }
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
        
        triggerEmergencyStop();
        
        response->success = true;
        response->message = "Emergency stop activated";
        response->drones_affected = 1;
    }
};

}  // namespace aura

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<aura::TrajectoryNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}