#include "aura_trajectory/trajectory_optimizer.hpp"
#include "aura_trajectory/minco_trajectory.hpp"
#include "aura_trajectory/penalty_functions.hpp"
#include "lbfgs.hpp"
#include <iostream>
#include <cmath>
using namespace lbfgs;

namespace aura {
    struct LBFGSContext {
        aura::TrajectoryOptimizer* optimizer;
        Eigen::Vector3d start_pos;
        Eigen::Vector3d start_vel;
        Eigen::Vector3d goal_pos;
        int M;
        int num_waypoints;
    };
    namespace {
        inline MincoTrajectory buildTrajectory(
            const Eigen::VectorXd& x,
            int M,
            int num_waypoints,
            const Eigen::Vector3d& start_pos,
            const Eigen::Vector3d& start_vel,
            const Eigen::Vector3d& goal_pos)
        {
            MincoTrajectory::Waypoints q(3, num_waypoints);
            MincoTrajectory::TimeAlloc T(M);
    
            for (int i = 0; i < num_waypoints; ++i)
                q.col(i) = x.segment<3>(3 * i);
    
            for (int i = 0; i < M; ++i)
                T(i) = std::max(0.01, x(3 * num_waypoints + i));
    
            return MincoTrajectory(q, T, start_pos, start_vel,
                                goal_pos, Eigen::Vector3d::Zero());
        }
    }
    // ==============================
    // LBFGS CALLBACK
    // ==============================
    double evaluate(void* instance,const Eigen::VectorXd& x,Eigen::VectorXd& grad)
    {
        LBFGSContext* ctx = reinterpret_cast<LBFGSContext*>(instance);

        auto* opt = ctx->optimizer;

        // === CACHE CHECK ===
        if (opt->grad_valid_ && (x - opt->last_x_).norm() < 1e-4) {
            grad = opt->last_grad_;
            return opt->last_cost_;
        }

        MincoTrajectory traj = buildTrajectory(
            x, ctx->M, ctx->num_waypoints,
            ctx->start_pos, ctx->start_vel, ctx->goal_pos
        );

        double cost = traj.isValid() ? opt->computeTotalCost(traj) : 1e10;

        // === GRADIENT ===
        double eps = 1e-4;
        grad.resize(x.size());

        for (int i = 0; i < grad.size(); ++i) {

            if (i >= 3 * ctx->num_waypoints) {
                grad(i) = 0.0;
                continue;
            }

            Eigen::VectorXd x_plus = x;
            x_plus(i) += eps;

            Eigen::VectorXd x_minus = x;
            x_minus(i) -= eps;

            auto traj_p = buildTrajectory(x_plus, ctx->M, ctx->num_waypoints,
                                        ctx->start_pos, ctx->start_vel, ctx->goal_pos);
            double cost_p = traj_p.isValid() ? opt->computeTotalCost(traj_p) : 1e10;

            auto traj_m = buildTrajectory(x_minus, ctx->M, ctx->num_waypoints,
                                        ctx->start_pos, ctx->start_vel, ctx->goal_pos);
            double cost_m = traj_m.isValid() ? opt->computeTotalCost(traj_m) : 1e10;

            grad(i) = (cost_p - cost_m) / (2.0 * eps);
        }

        // === CACHE STORE ===
        opt->last_x_ = x;
        opt->last_grad_ = grad;
        opt->last_cost_ = cost;
        opt->grad_valid_ = true;

        return cost;
    }

TrajectoryOptimizer::TrajectoryOptimizer(const OptimizationConfig& config)
    : config_(config) {}

OptimizationResult TrajectoryOptimizer::optimize(
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& start_vel,
    const Eigen::Vector3d& goal_pos,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    current_obstacles_ = obstacles;
    current_other_trajectories_ = other_trajectories;

    OptimizationResult result;

    int M = config_.num_pieces;
    int num_waypoints = M - 1;

    // ==============================
    // 1. INITIALIZATION
    // ==============================
    grad_valid_ = false;
    Eigen::Vector3d direction = goal_pos - start_pos;
    double distance = direction.norm();

    if (distance < 1e-6) {
        result.feasible = true;
        result.message = "Already at goal";
        result.trajectory = MincoTrajectory();
        return result;
    }

    double total_time = distance / config_.max_velocity * 1.5;

    // parameter vector: [q(3*(M-1)), T(M)]
    int dim = 3 * num_waypoints + M;
    Eigen::VectorXd x(dim);

    // init waypoints
    for (int i = 0; i < num_waypoints; ++i) {
        double alpha = static_cast<double>(i + 1) / M;
        Eigen::Vector3d pt = start_pos + alpha * direction;
        x.segment<3>(3 * i) = pt;
    }

    // init time
    for (int i = 0; i < M; ++i) {
        x(3 * num_waypoints + i) = total_time / M;
    }

    // ==============================
    // 2. COST FUNCTION
    // ==============================

//    auto costFunction = [&](const Eigen::VectorXd& x_vec,
//                         Eigen::VectorXd& grad) -> double
//     {
//         // ==============================
//         // CACHE CHECK
//         // ==============================
//         if (grad_valid_ && (x_vec - last_x_).norm() < 1e-4) {
//             grad = last_grad_;
//             return last_cost_;
//         }

//         // ==============================
//         // BUILD TRAJECTORY
//         // ==============================
//         MincoTrajectory traj = buildTrajectory(
//             x_vec, M, num_waypoints,
//             start_pos, start_vel, goal_pos
//         );

//         double cost = traj.isValid() ? computeTotalCost(traj) : 1e10;

//         // ==============================
//         // GRADIENT
//         // ==============================
//         double eps = 1e-4;
//         grad.resize(x_vec.size());

//         for (int i = 0; i < grad.size(); ++i) {

//             if (i >= 3 * num_waypoints) {
//                 grad(i) = 0.0;
//                 continue;
//             }

//             Eigen::VectorXd x_plus = x_vec;
//             x_plus(i) += eps;

//             Eigen::VectorXd x_minus = x_vec;
//             x_minus(i) -= eps;

//             auto traj_p = buildTrajectory(x_plus, M, num_waypoints,
//                                         start_pos, start_vel, goal_pos);
//             double cost_p = traj_p.isValid() ? computeTotalCost(traj_p) : 1e10;

//             auto traj_m = buildTrajectory(x_minus, M, num_waypoints,
//                                         start_pos, start_vel, goal_pos);
//             double cost_m = traj_m.isValid() ? computeTotalCost(traj_m) : 1e10;

//             grad(i) = (cost_p - cost_m) / (2.0 * eps);
//         }

//         // ==============================
//         // STORE CACHE
//         // ==============================
//         last_x_ = x_vec;
//         last_grad_ = grad;
//         last_cost_ = cost;
//         grad_valid_ = true;

//         // ==============================
//         // EARLY STOP
//         // ==============================
//         if (grad.norm() < 1e-3) {
//             return cost;
//         }

//         return cost;
//     };

    // ==============================
    // 3. LBFGS SOLVE
    // ==============================

    lbfgs_parameter_t param;
    param.mem_size = 10;
    param.max_iterations = config_.max_iterations;
    param.g_epsilon = config_.convergence_tolerance;

    double final_cost;
    LBFGSContext ctx;
    ctx.optimizer = this;
    ctx.start_pos = start_pos;
    ctx.start_vel = start_vel;
    ctx.goal_pos = goal_pos;
    ctx.M = M;
    ctx.num_waypoints = num_waypoints;

    int ret = lbfgs_optimize(
        x,
        final_cost,
        evaluate,
        nullptr,
        nullptr,
        &ctx,
        param
    );

    // ==============================
    // 4. BUILD FINAL TRAJECTORY
    // ==============================

    MincoTrajectory::Waypoints q(3, num_waypoints);
    MincoTrajectory::TimeAlloc T(M);

    for (int i = 0; i < num_waypoints; ++i)
        q.col(i) = x.segment<3>(3 * i);

    for (int i = 0; i < M; ++i)
        T(i) = std::max(0.01, x(3 * num_waypoints + i));

    MincoTrajectory traj(q, T, start_pos, start_vel,
                         goal_pos, Eigen::Vector3d::Zero());

    result.trajectory = traj;
    result.total_cost = final_cost;
    result.feasible = traj.isValid();
    result.message = (ret == LBFGS_CONVERGENCE) ? "LBFGS converged" : "LBFGS failed";

    return result;
}

OptimizationResult TrajectoryOptimizer::reoptimize(
    const MincoTrajectory& initial_guess,
    const std::vector<Obstacle>& obstacles,
    const std::vector<MincoTrajectory>& other_trajectories)
{
    if (!initial_guess.isValid()) {
        OptimizationResult result;
        result.feasible = false;
        result.message = "Invalid initial guess";
        return result;
    }
    
    // Extract boundary conditions from initial guess
    Eigen::Vector3d start_pos = initial_guess.getPosition(0);
    Eigen::Vector3d start_vel = initial_guess.getVelocity(0);
    double total_time = initial_guess.getTotalDuration();
    Eigen::Vector3d goal_pos = initial_guess.getPosition(total_time);
    
    return optimize(start_pos, start_vel, goal_pos, obstacles, other_trajectories);
}

double TrajectoryOptimizer::computeTotalCost(const MincoTrajectory& traj) {
    double cost = 0.0;
    
    cost += config_.weight_smoothness * computeSmoothnessPenalty(traj);
    cost += config_.weight_time * computeTimePenalty(traj);
    cost += config_.weight_obstacle * computeObstaclePenalty(traj);
    cost += config_.weight_swarm * computeSwarmPenalty(traj);
    cost += config_.weight_dynamics * computeDynamicsPenalty(traj);
    
    if (formation_target_.has_value()) {
        cost += config_.weight_formation * computeFormationPenalty(traj);
    }
    
    return cost;
}

double TrajectoryOptimizer::computeSmoothnessPenalty(const MincoTrajectory& traj) {
    return penalties::smoothness_penalty(traj);
}

double TrajectoryOptimizer::computeTimePenalty(const MincoTrajectory& traj) {
    return penalties::time_penalty(traj);
}

double TrajectoryOptimizer::computeObstaclePenalty(const MincoTrajectory& traj) {
    double total = 0.0;
    for (const auto& obs : current_obstacles_) {
        total += penalties::obstacle_penalty(traj, obs.point, obs.normal,
                                             config_.obstacle_clearance,
                                             config_.num_constraint_samples);
    }
    return total;
}

double TrajectoryOptimizer::computeSwarmPenalty(const MincoTrajectory& traj) {
    double total = 0.0;
    for (const auto& other : current_other_trajectories_) {
        total += penalties::swarm_penalty(traj, other, trajectory_start_time_,
                                          config_.swarm_clearance,
                                          config_.num_constraint_samples);
    }
    return total;
}

double TrajectoryOptimizer::computeDynamicsPenalty(const MincoTrajectory& traj) {
    double cost = 0.0;
    cost += penalties::velocity_penalty(traj, config_.max_velocity, 
                                        config_.num_constraint_samples);
    cost += penalties::acceleration_penalty(traj, config_.max_acceleration,
                                            config_.num_constraint_samples);
    cost += penalties::jerk_penalty(traj, config_.max_jerk,
                                    config_.num_constraint_samples);
    return cost;
}

double TrajectoryOptimizer::computeFormationPenalty(const MincoTrajectory& traj) {
    if (!formation_target_.has_value()) return 0.0;
    return penalties::formation_penalty(traj, formation_target_.value());
}

}  // namespace aura