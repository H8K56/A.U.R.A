#!/usr/bin/env python3
"""
A.U.R.A. RL Policy Training — Pure PyTorch PPO

Trains the swarm positioning policy using PPO (Proximal Policy Optimization)
with the SwarmGymEnv gymnasium environment and MLPPolicy actor-critic.

No stable-baselines3 dependency — uses your existing MLPPolicy directly.
The saved checkpoint loads directly into strategic_rl_node via PolicyCheckpoint.

Usage:
    # Quick training (smoke test, ~2 min)
    python3 -m aura_strategic_rl.train_policy --timesteps 50000

    # Standard training (~15 min on CPU)
    python3 -m aura_strategic_rl.train_policy --timesteps 500000

    # Full training (~1 hour)
    python3 -m aura_strategic_rl.train_policy --timesteps 2000000 --num-envs 8

    # With weather randomization
    python3 -m aura_strategic_rl.train_policy --timesteps 500000 --weather
"""

import argparse
import os
import time
import json
from typing import Dict, List, Tuple

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim

from .swarm_gym_env import SwarmGymEnv, EnvConfig
from .policy import MLPPolicy, PolicyCheckpoint
from .spaces import ObservationConfig, ActionConfig


class RolloutBuffer:
    """Stores rollout data for PPO updates."""

    def __init__(self, buffer_size: int, obs_dim: int, action_dim: int):
        self.obs = np.zeros((buffer_size, obs_dim), dtype=np.float32)
        self.actions = np.zeros((buffer_size, action_dim), dtype=np.float32)
        self.log_probs = np.zeros(buffer_size, dtype=np.float32)
        self.rewards = np.zeros(buffer_size, dtype=np.float32)
        self.values = np.zeros(buffer_size, dtype=np.float32)
        self.dones = np.zeros(buffer_size, dtype=np.float32)

        self.buffer_size = buffer_size
        self.pos = 0
        self.full = False

    def add(self, obs, action, log_prob, reward, value, done):
        self.obs[self.pos] = obs
        self.actions[self.pos] = action
        self.log_probs[self.pos] = log_prob
        self.rewards[self.pos] = reward
        self.values[self.pos] = value
        self.dones[self.pos] = done
        self.pos += 1
        if self.pos >= self.buffer_size:
            self.full = True

    def compute_returns(self, last_value: float, gamma: float = 0.99,
                        gae_lambda: float = 0.95) -> Tuple[np.ndarray, np.ndarray]:
        """Compute GAE advantages and returns."""
        advantages = np.zeros(self.buffer_size, dtype=np.float32)
        last_gae = 0.0

        for t in reversed(range(self.buffer_size)):
            if t == self.buffer_size - 1:
                next_value = last_value
                next_non_terminal = 1.0 - self.dones[t]
            else:
                next_value = self.values[t + 1]
                next_non_terminal = 1.0 - self.dones[t]

            delta = (self.rewards[t] + gamma * next_value * next_non_terminal
                     - self.values[t])
            last_gae = delta + gamma * gae_lambda * next_non_terminal * last_gae
            advantages[t] = last_gae

        returns = advantages + self.values[:self.buffer_size]
        return advantages, returns

    def reset(self):
        self.pos = 0
        self.full = False


class PPOTrainer:
    """
    PPO trainer for A.U.R.A. swarm positioning.

    Uses your existing MLPPolicy (actor-critic with LayerNorm + tanh-squashed
    Gaussian) and SwarmGymEnv (standalone Gymnasium environment with log-distance
    path loss network simulation).
    """

    def __init__(self,
                 num_drones: int = 5,
                 num_envs: int = 4,
                 n_steps: int = 2048,
                 batch_size: int = 64,
                 n_epochs: int = 10,
                 gamma: float = 0.99,
                 gae_lambda: float = 0.95,
                 clip_range: float = 0.2,
                 lr: float = 3e-4,
                 ent_coef: float = 0.01,
                 vf_coef: float = 0.5,
                 max_grad_norm: float = 0.5,
                 weather: bool = False,
                 device: str = 'cpu'):

        self.num_envs = num_envs
        self.n_steps = n_steps
        self.batch_size = batch_size
        self.n_epochs = n_epochs
        self.gamma = gamma
        self.gae_lambda = gae_lambda
        self.clip_range = clip_range
        self.ent_coef = ent_coef
        self.vf_coef = vf_coef
        self.max_grad_norm = max_grad_norm
        self.device = device

        # Create environments
        env_config = EnvConfig(
            num_drones=num_drones,
            max_steps=500,
            randomize_initial_positions=True,
            randomize_weather=weather,
            weather_probability=0.5 if weather else 0.0,
        )

        self.envs = [SwarmGymEnv(config=env_config) for _ in range(num_envs)]
        self.eval_env = SwarmGymEnv(config=EnvConfig(
            num_drones=num_drones,
            max_steps=500,
            randomize_initial_positions=True,
            randomize_weather=False,
        ))

        # Get dimensions
        obs_config = ObservationConfig(num_drones=num_drones)
        action_config = ActionConfig(num_drones=num_drones)
        self.obs_dim = obs_config.total_obs_dim
        self.action_dim = action_config.action_dim

        # Create policy
        self.policy = MLPPolicy(
            obs_dim=self.obs_dim,
            action_dim=self.action_dim,
            hidden_sizes=[256, 256],
            activation='relu',
            log_std_init=-0.5,
        ).to(device)

        self.optimizer = optim.Adam(self.policy.parameters(), lr=lr, eps=1e-5)

        # Rollout buffers (one per env)
        self.buffers = [
            RolloutBuffer(n_steps, self.obs_dim, self.action_dim)
            for _ in range(num_envs)
        ]

        # Tracking
        self.total_timesteps = 0
        self.episode_rewards: List[float] = []
        self.episode_coverages: List[float] = []
        self.best_eval_reward = float('-inf')

    def collect_rollouts(self) -> Dict[str, float]:
        """Collect n_steps of experience from all environments."""
        self.policy.eval()

        # Reset buffers
        for buf in self.buffers:
            buf.reset()

        # Current observations for each env
        if not hasattr(self, '_current_obs'):
            self._current_obs = []
            self._episode_rewards_acc = []
            self._episode_coverages_acc = []
            for env in self.envs:
                obs, _ = env.reset()
                self._current_obs.append(obs)
                self._episode_rewards_acc.append(0.0)
                self._episode_coverages_acc.append(0.0)

        ep_rewards = []
        ep_coverages = []

        for step in range(self.n_steps):
            for i, env in enumerate(self.envs):
                obs = self._current_obs[i]

                # Get action from policy
                with torch.no_grad():
                    obs_t = torch.FloatTensor(obs).unsqueeze(0).to(self.device)
                    action, log_prob, value = self.policy.get_action(obs_t)
                    action = action.squeeze(0).cpu().numpy()
                    log_prob = log_prob.item()
                    value = value.item()

                # Step environment
                next_obs, reward, terminated, truncated, info = env.step(action)
                done = terminated or truncated

                # Store transition
                self.buffers[i].add(obs, action, log_prob, reward, value, float(done))
                self._episode_rewards_acc[i] += reward
                self._episode_coverages_acc[i] = info.get('coverage_percent', 0.0)

                if done:
                    ep_rewards.append(self._episode_rewards_acc[i])
                    ep_coverages.append(self._episode_coverages_acc[i])
                    self._episode_rewards_acc[i] = 0.0
                    self._episode_coverages_acc[i] = 0.0
                    next_obs, _ = env.reset()

                self._current_obs[i] = next_obs

        self.total_timesteps += self.n_steps * self.num_envs

        # Compute advantages for each buffer
        all_obs = []
        all_actions = []
        all_log_probs = []
        all_advantages = []
        all_returns = []

        for i in range(self.num_envs):
            with torch.no_grad():
                last_obs_t = torch.FloatTensor(
                    self._current_obs[i]).unsqueeze(0).to(self.device)
                last_value = self.policy.get_value(last_obs_t).item()

            advantages, returns = self.buffers[i].compute_returns(
                last_value, self.gamma, self.gae_lambda)

            all_obs.append(self.buffers[i].obs[:self.n_steps])
            all_actions.append(self.buffers[i].actions[:self.n_steps])
            all_log_probs.append(self.buffers[i].log_probs[:self.n_steps])
            all_advantages.append(advantages)
            all_returns.append(returns)

        # Concatenate all envs
        self._rollout_obs = np.concatenate(all_obs)
        self._rollout_actions = np.concatenate(all_actions)
        self._rollout_log_probs = np.concatenate(all_log_probs)
        self._rollout_advantages = np.concatenate(all_advantages)
        self._rollout_returns = np.concatenate(all_returns)

        # Normalize advantages
        self._rollout_advantages = (
            (self._rollout_advantages - self._rollout_advantages.mean()) /
            (self._rollout_advantages.std() + 1e-8)
        )

        self.episode_rewards.extend(ep_rewards)
        self.episode_coverages.extend(ep_coverages)

        stats = {}
        if ep_rewards:
            stats['ep_reward_mean'] = np.mean(ep_rewards)
            stats['ep_reward_std'] = np.std(ep_rewards)
            stats['ep_coverage_mean'] = np.mean(ep_coverages)
        return stats

    def update_policy(self) -> Dict[str, float]:
        """Run PPO update using collected rollouts."""
        self.policy.train()

        total_samples = len(self._rollout_obs)
        indices = np.arange(total_samples)

        total_pg_loss = 0.0
        total_vf_loss = 0.0
        total_entropy = 0.0
        total_clip_frac = 0.0
        n_updates = 0

        for epoch in range(self.n_epochs):
            np.random.shuffle(indices)

            for start in range(0, total_samples, self.batch_size):
                end = start + self.batch_size
                if end > total_samples:
                    continue

                batch_idx = indices[start:end]

                obs_b = torch.FloatTensor(
                    self._rollout_obs[batch_idx]).to(self.device)
                actions_b = torch.FloatTensor(
                    self._rollout_actions[batch_idx]).to(self.device)
                old_log_probs_b = torch.FloatTensor(
                    self._rollout_log_probs[batch_idx]).to(self.device)
                advantages_b = torch.FloatTensor(
                    self._rollout_advantages[batch_idx]).to(self.device)
                returns_b = torch.FloatTensor(
                    self._rollout_returns[batch_idx]).to(self.device)

                # Evaluate actions under current policy
                log_probs, entropy, values = self.policy.evaluate_actions(
                    obs_b, actions_b)

                # Policy loss (clipped surrogate)
                ratio = torch.exp(log_probs - old_log_probs_b)
                surr1 = ratio * advantages_b
                surr2 = torch.clamp(
                    ratio, 1.0 - self.clip_range, 1.0 + self.clip_range
                ) * advantages_b
                pg_loss = -torch.min(surr1, surr2).mean()

                # Value loss
                vf_loss = nn.functional.mse_loss(values, returns_b)

                # Entropy bonus
                entropy_loss = -entropy.mean()

                # Total loss
                loss = (pg_loss +
                        self.vf_coef * vf_loss +
                        self.ent_coef * entropy_loss)

                self.optimizer.zero_grad()
                loss.backward()
                nn.utils.clip_grad_norm_(
                    self.policy.parameters(), self.max_grad_norm)
                self.optimizer.step()

                # Track stats
                with torch.no_grad():
                    clip_frac = ((ratio - 1.0).abs() > self.clip_range).float().mean()

                total_pg_loss += pg_loss.item()
                total_vf_loss += vf_loss.item()
                total_entropy += -entropy_loss.item()
                total_clip_frac += clip_frac.item()
                n_updates += 1

        return {
            'pg_loss': total_pg_loss / max(n_updates, 1),
            'vf_loss': total_vf_loss / max(n_updates, 1),
            'entropy': total_entropy / max(n_updates, 1),
            'clip_frac': total_clip_frac / max(n_updates, 1),
        }

    def evaluate(self, n_episodes: int = 5) -> Dict[str, float]:
        """Evaluate current policy."""
        self.policy.eval()
        rewards = []
        coverages = []
        connectivities = []

        for _ in range(n_episodes):
            obs, info = self.eval_env.reset()
            total_reward = 0.0
            done = False

            while not done:
                with torch.no_grad():
                    obs_t = torch.FloatTensor(obs).unsqueeze(0).to(self.device)
                    action, _, _ = self.policy.get_action(obs_t, deterministic=True)
                    action = action.squeeze(0).cpu().numpy()

                obs, reward, terminated, truncated, info = self.eval_env.step(action)
                total_reward += reward
                done = terminated or truncated

            rewards.append(total_reward)
            coverages.append(info.get('coverage_percent', 0.0))
            connectivities.append(info.get('mesh_connected', False))

        return {
            'eval_reward': np.mean(rewards),
            'eval_coverage': np.mean(coverages),
            'eval_connected': np.mean(connectivities),
        }

    def save(self, path: str, metadata: dict = None):
        """Save policy checkpoint."""
        meta = {
            'total_timesteps': self.total_timesteps,
            'num_drones': self.envs[0].config.num_drones,
            'obs_dim': self.obs_dim,
            'action_dim': self.action_dim,
            **(metadata or {}),
        }
        PolicyCheckpoint.save(self.policy, path, metadata=meta)


def train(args):
    """Main training loop."""
    print("=" * 60)
    print("A.U.R.A. Strategic RL Training — PPO")
    print("=" * 60)
    print(f"  Drones:     {args.num_drones}")
    print(f"  Timesteps:  {args.timesteps:,}")
    print(f"  Envs:       {args.num_envs}")
    print(f"  Batch size: {args.batch_size}")
    print(f"  Weather:    {args.weather}")
    print(f"  Device:     {'CUDA' if torch.cuda.is_available() else 'CPU'}")
    print(f"  Save path:  {args.save_path}")
    print("=" * 60)

    trainer = PPOTrainer(
        num_drones=args.num_drones,
        num_envs=args.num_envs,
        n_steps=args.n_steps,
        batch_size=args.batch_size,
        n_epochs=args.n_epochs,
        gamma=args.gamma,
        lr=args.lr,
        ent_coef=args.ent_coef,
        weather=args.weather,
        device="cuda" if torch.cuda.is_available() else "cpu",
    )

    os.makedirs(args.save_path, exist_ok=True)

    # Training loop
    n_updates = args.timesteps // (args.n_steps * args.num_envs)
    eval_interval = max(1, n_updates // 20)  # Evaluate ~20 times
    save_interval = max(1, n_updates // 10)  # Save ~10 times

    print(f"\nTraining for {n_updates} updates "
          f"({args.n_steps * args.num_envs} steps/update)...\n")

    start_time = time.time()
    training_log = []

    for update in range(1, n_updates + 1):
        # Collect rollouts
        rollout_stats = trainer.collect_rollouts()

        # Update policy
        update_stats = trainer.update_policy()

        # Log
        elapsed = time.time() - start_time
        fps = trainer.total_timesteps / elapsed

        if rollout_stats.get('ep_reward_mean') is not None:
            log_entry = {
                'update': update,
                'timesteps': trainer.total_timesteps,
                'fps': fps,
                **rollout_stats,
                **update_stats,
            }
            training_log.append(log_entry)

            print(f"Update {update:4d}/{n_updates} | "
                  f"Steps: {trainer.total_timesteps:>8,} | "
                  f"FPS: {fps:>6.0f} | "
                  f"Reward: {rollout_stats['ep_reward_mean']:>7.1f} ± "
                  f"{rollout_stats.get('ep_reward_std', 0):.1f} | "
                  f"Coverage: {rollout_stats.get('ep_coverage_mean', 0):>5.1f}% | "
                  f"PG Loss: {update_stats['pg_loss']:.4f} | "
                  f"Entropy: {update_stats['entropy']:.3f}")

        # Evaluate
        if update % eval_interval == 0:
            eval_stats = trainer.evaluate(n_episodes=5)
            print(f"  ► EVAL | Reward: {eval_stats['eval_reward']:.1f} | "
                  f"Coverage: {eval_stats['eval_coverage']:.1f}% | "
                  f"Connected: {eval_stats['eval_connected']:.0%}")

            # Save best
            if eval_stats['eval_reward'] > trainer.best_eval_reward:
                trainer.best_eval_reward = eval_stats['eval_reward']
                best_path = os.path.join(args.save_path, 'best_policy.pt')
                trainer.save(best_path, metadata=eval_stats)
                print(f"  ★ New best! Saved to {best_path}")

        # Periodic save
        if update % save_interval == 0:
            ckpt_path = os.path.join(
                args.save_path, f'policy_step_{trainer.total_timesteps}.pt')
            trainer.save(ckpt_path)

    # Final save
    final_path = os.path.join(args.save_path, 'final_policy.pt')
    trainer.save(final_path)

    # Save training log
    log_path = os.path.join(args.save_path, 'training_log.json')
    with open(log_path, 'w') as f:
        json.dump(training_log, f, indent=2)

    elapsed = time.time() - start_time
    print(f"\n{'=' * 60}")
    print(f"Training complete!")
    print(f"  Total time:   {elapsed / 60:.1f} minutes")
    print(f"  Total steps:  {trainer.total_timesteps:,}")
    print(f"  Best reward:  {trainer.best_eval_reward:.1f}")
    print(f"  Final policy: {final_path}")
    print(f"  Best policy:  {os.path.join(args.save_path, 'best_policy.pt')}")
    print(f"  Training log: {log_path}")
    print(f"{'=' * 60}")
    print(f"\nTo deploy:")
    print(f"  ros2 launch aura_strategic_rl strategic_rl.launch.py "
          f"policy_path:={os.path.abspath(final_path)}")


def main():
    parser = argparse.ArgumentParser(
        description="Train A.U.R.A. strategic RL policy with PPO")

    parser.add_argument("--timesteps", type=int, default=500_000,
                        help="Total training timesteps")
    parser.add_argument("--num-drones", type=int, default=5,
                        help="Number of drones")
    parser.add_argument("--num-envs", type=int, default=4,
                        help="Parallel environments")
    parser.add_argument("--n-steps", type=int, default=2048,
                        help="Steps per rollout per env")
    parser.add_argument("--batch-size", type=int, default=64,
                        help="Minibatch size for PPO updates")
    parser.add_argument("--n-epochs", type=int, default=10,
                        help="PPO epochs per update")
    parser.add_argument("--gamma", type=float, default=0.99,
                        help="Discount factor")
    parser.add_argument("--lr", type=float, default=3e-4,
                        help="Learning rate")
    parser.add_argument("--ent-coef", type=float, default=0.01,
                        help="Entropy coefficient")
    parser.add_argument("--weather", action="store_true",
                        help="Enable weather randomization")
    parser.add_argument("--save-path", type=str,
                        default=os.path.expanduser("~/ws/models/strategic_rl"),
                        help="Save directory")

    args = parser.parse_args()
    train(args)


if __name__ == '__main__':
    main()
