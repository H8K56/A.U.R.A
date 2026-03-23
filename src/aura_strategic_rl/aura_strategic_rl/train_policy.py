#!/usr/bin/env python3
"""
RL Policy Training Script

Trains strategic positioning policy using PufferLib + Stable-Baselines3.
Uses Gymnasium environment wrapper around A.U.R.A. simulation.
"""

import argparse
import os
from typing import Optional

import numpy as np

# RL libraries
try:
    import torch
    import gymnasium as gym
    from stable_baselines3 import PPO
    from stable_baselines3.common.callbacks import EvalCallback, CheckpointCallback
    from stable_baselines3.common.vec_env import DummyVecEnv, SubprocVecEnv
    RL_AVAILABLE = True
except ImportError:
    RL_AVAILABLE = False
    print("Warning: RL libraries not available. Install with:")
    print("  pip install torch stable-baselines3 gymnasium")


class AURASwarmEnv(gym.Env):
    """
    Gymnasium environment for A.U.R.A. swarm positioning.
    
    Observation:
    - Drone positions (normalized)
    - Coverage map
    - Network metrics
    
    Action:
    - Delta positions for each drone
    
    Reward:
    - Coverage percentage
    - Network quality
    - Energy efficiency
    - Connectivity bonus
    """
    
    def __init__(self, num_drones: int = 5, grid_size: int = 20):
        super().__init__()
        
        self.num_drones = num_drones
        self.grid_size = grid_size
        
        # Observation space
        drone_obs_dim = 7  # x, y, z, vx, vy, vz, battery
        coverage_dim = grid_size * grid_size
        network_dim = num_drones * 4
        
        obs_dim = num_drones * drone_obs_dim + coverage_dim + network_dim
        
        self.observation_space = gym.spaces.Box(
            low=-np.inf, 
            high=np.inf, 
            shape=(obs_dim,),
            dtype=np.float32
        )
        
        # Action space: delta position per drone
        self.action_space = gym.spaces.Box(
            low=-1.0,
            high=1.0,
            shape=(num_drones * 3,),
            dtype=np.float32
        )
        
        # Simulation state
        self.drone_positions = np.zeros((num_drones, 3))
        self.drone_velocities = np.zeros((num_drones, 3))
        self.battery_levels = np.ones(num_drones)
        self.coverage_map = np.zeros((grid_size, grid_size))
        
        self.step_count = 0
        self.max_steps = 1000
        
        # Bounds
        self.pos_bounds = np.array([[-100, 100], [-100, 100], [10, 50]])
    
    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        
        # Random initial positions
        self.drone_positions = np.random.uniform(
            [-50, -50, 20],
            [50, 50, 30],
            (self.num_drones, 3)
        )
        self.drone_velocities = np.zeros((self.num_drones, 3))
        self.battery_levels = np.ones(self.num_drones)
        
        self.step_count = 0
        
        self._update_coverage()
        
        return self._get_observation(), {}
    
    def step(self, action):
        # Apply action (scaled delta positions)
        action = action.reshape(self.num_drones, 3)
        delta = action * 5.0  # Max 5m per step
        
        # Update positions
        self.drone_positions += delta
        
        # Enforce bounds
        for i, (low, high) in enumerate(self.pos_bounds):
            self.drone_positions[:, i] = np.clip(
                self.drone_positions[:, i], low, high
            )
        
        # Update battery
        movement = np.linalg.norm(delta, axis=1)
        self.battery_levels -= movement * 0.001  # Simple drain
        self.battery_levels = np.maximum(self.battery_levels, 0)
        
        # Update coverage
        self._update_coverage()
        
        # Compute reward
        reward = self._compute_reward()
        
        self.step_count += 1
        
        # Termination
        terminated = np.any(self.battery_levels <= 0)
        truncated = self.step_count >= self.max_steps
        
        return self._get_observation(), reward, terminated, truncated, {}
    
    def _get_observation(self):
        obs_parts = []
        
        # Drone states
        drone_obs = np.zeros((self.num_drones, 7))
        drone_obs[:, :3] = self.drone_positions / 100.0
        drone_obs[:, 3:6] = self.drone_velocities / 3.0
        drone_obs[:, 6] = self.battery_levels
        obs_parts.append(drone_obs.flatten())
        
        # Coverage map
        obs_parts.append(self.coverage_map.flatten())
        
        # Network metrics (simplified)
        network_obs = np.zeros((self.num_drones, 4))
        for i in range(self.num_drones):
            # Count neighbors within range
            for j in range(self.num_drones):
                if i != j:
                    dist = np.linalg.norm(self.drone_positions[i] - self.drone_positions[j])
                    if dist < 80:  # Within range
                        network_obs[i, 0] += 1  # Neighbor count
        network_obs[:, 0] /= self.num_drones  # Normalize
        obs_parts.append(network_obs.flatten())
        
        return np.concatenate(obs_parts).astype(np.float32)
    
    def _update_coverage(self):
        """Update coverage map based on drone positions"""
        self.coverage_map = np.zeros((self.grid_size, self.grid_size))
        
        # Simple model: each drone covers area below it
        for pos in self.drone_positions:
            # Map position to grid
            gx = int((pos[0] + 100) / 200 * self.grid_size)
            gy = int((pos[1] + 100) / 200 * self.grid_size)
            
            # Coverage radius based on altitude
            radius = int(pos[2] / 10)  # Higher = larger coverage
            
            for dx in range(-radius, radius + 1):
                for dy in range(-radius, radius + 1):
                    if dx*dx + dy*dy <= radius*radius:
                        x, y = gx + dx, gy + dy
                        if 0 <= x < self.grid_size and 0 <= y < self.grid_size:
                            self.coverage_map[y, x] = 1.0
    
    def _compute_reward(self):
        reward = 0.0
        
        # Coverage reward
        coverage_pct = np.mean(self.coverage_map)
        reward += coverage_pct * 10.0
        
        # Connectivity reward
        connected = True
        for i in range(self.num_drones):
            has_neighbor = False
            for j in range(self.num_drones):
                if i != j:
                    dist = np.linalg.norm(self.drone_positions[i] - self.drone_positions[j])
                    if dist < 80:
                        has_neighbor = True
                        break
            if not has_neighbor:
                connected = False
                reward -= 5.0
        
        if connected:
            reward += 2.0
        
        # Energy penalty
        energy_used = 1.0 - np.mean(self.battery_levels)
        reward -= energy_used * 0.1
        
        return reward


def train(
    total_timesteps: int = 1_000_000,
    num_envs: int = 4,
    save_path: str = "models",
    log_path: str = "logs"
):
    """Train PPO policy"""
    if not RL_AVAILABLE:
        print("RL libraries not available!")
        return
    
    os.makedirs(save_path, exist_ok=True)
    os.makedirs(log_path, exist_ok=True)
    
    # Create environments
    def make_env():
        def _init():
            return AURASwarmEnv()
        return _init
    
    env = SubprocVecEnv([make_env() for _ in range(num_envs)])
    eval_env = DummyVecEnv([make_env()])
    
    # Callbacks
    checkpoint_callback = CheckpointCallback(
        save_freq=10000,
        save_path=save_path,
        name_prefix="aura_policy"
    )
    
    eval_callback = EvalCallback(
        eval_env,
        best_model_save_path=os.path.join(save_path, "best"),
        log_path=log_path,
        eval_freq=5000,
        deterministic=True
    )
    
    # Create model
    model = PPO(
        "MlpPolicy",
        env,
        learning_rate=3e-4,
        n_steps=2048,
        batch_size=64,
        n_epochs=10,
        gamma=0.99,
        gae_lambda=0.95,
        clip_range=0.2,
        ent_coef=0.01,
        verbose=1,
        tensorboard_log=log_path
    )
    
    print(f"Training for {total_timesteps} timesteps...")
    model.learn(
        total_timesteps=total_timesteps,
        callback=[checkpoint_callback, eval_callback],
        progress_bar=True
    )
    
    # Save final model
    model.save(os.path.join(save_path, "aura_policy_final"))
    print(f"Model saved to {save_path}")


def main():
    parser = argparse.ArgumentParser(description="Train A.U.R.A. strategic RL policy")
    parser.add_argument("--timesteps", type=int, default=1_000_000)
    parser.add_argument("--num-envs", type=int, default=4)
    parser.add_argument("--save-path", type=str, default="models")
    parser.add_argument("--log-path", type=str, default="logs")
    
    args = parser.parse_args()
    
    train(
        total_timesteps=args.timesteps,
        num_envs=args.num_envs,
        save_path=args.save_path,
        log_path=args.log_path
    )


if __name__ == '__main__':
    main()
