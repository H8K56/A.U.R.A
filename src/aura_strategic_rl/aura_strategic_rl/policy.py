"""
Policy Networks for A.U.R.A. Strategic RL

Provides neural network architectures for the swarm positioning policy:
- MLP policy with layer normalization
- Actor-critic architecture
- Checkpointing and loading utilities
"""

import numpy as np
from typing import Tuple, Optional, List
from pathlib import Path

try:
    import torch
    import torch.nn as nn
    import torch.nn.functional as F
    from torch.distributions import Normal
    TORCH_AVAILABLE = True
except ImportError:
    TORCH_AVAILABLE = False
    torch = None
    nn = None


class MLPPolicy(nn.Module if TORCH_AVAILABLE else object):
    """
    MLP Actor-Critic Policy Network.

    Architecture:
    - Shared feature extractor (2-3 hidden layers with LayerNorm)
    - Separate actor (mean) and critic (value) heads
    - Tanh-squashed Gaussian for bounded actions
    """

    def __init__(self,
                 obs_dim: int,
                 action_dim: int,
                 hidden_sizes: List[int] = None,
                 activation: str = 'relu',
                 log_std_init: float = -0.5):
        if not TORCH_AVAILABLE:
            raise RuntimeError("PyTorch not available. Install with: pip install torch")

        super().__init__()

        if hidden_sizes is None:
            hidden_sizes = [256, 256]

        self.obs_dim = obs_dim
        self.action_dim = action_dim

        # Activation function
        act_map = {
            'relu': nn.ReLU(),
            'tanh': nn.Tanh(),
            'elu': nn.ELU(),
        }
        self.activation = act_map.get(activation, nn.ReLU())

        # Build shared feature extractor with LayerNorm
        layers = []
        prev_size = obs_dim

        for hidden_size in hidden_sizes:
            layers.append(nn.Linear(prev_size, hidden_size))
            layers.append(nn.LayerNorm(hidden_size))
            layers.append(self.activation)
            prev_size = hidden_size

        self.features = nn.Sequential(*layers)

        # Actor head (outputs action mean)
        self.actor_mean = nn.Linear(prev_size, action_dim)

        # Learnable log standard deviation
        self.actor_log_std = nn.Parameter(
            torch.ones(action_dim) * log_std_init
        )

        # Critic head (outputs state value)
        self.critic = nn.Linear(prev_size, 1)

        # Initialize weights
        self._init_weights()

    def _init_weights(self):
        """Initialize network weights with orthogonal init"""
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.orthogonal_(module.weight, gain=np.sqrt(2))
                nn.init.zeros_(module.bias)

        # Smaller init for output layers (reduces initial entropy)
        nn.init.orthogonal_(self.actor_mean.weight, gain=0.01)
        nn.init.orthogonal_(self.critic.weight, gain=1.0)

    def forward(self, obs: 'torch.Tensor') -> Tuple:
        """
        Forward pass.

        Args:
            obs: Observation tensor [batch, obs_dim]

        Returns:
            action_mean: Mean of action distribution [batch, action_dim]
            action_log_std: Log std of action distribution [action_dim]
            value: State value estimate [batch, 1]
        """
        features = self.features(obs)

        action_mean = self.actor_mean(features)
        action_log_std = self.actor_log_std.expand_as(action_mean)
        value = self.critic(features)

        return action_mean, action_log_std, value

    def get_action(self, obs: 'torch.Tensor',
                   deterministic: bool = False) -> Tuple:
        """
        Get action from policy.

        Args:
            obs: Observation tensor
            deterministic: If True, return mean action (no sampling)

        Returns:
            action: Sampled or deterministic action (tanh-squashed)
            log_prob: Log probability of action
            value: State value estimate
        """
        action_mean, action_log_std, value = self.forward(obs)

        if deterministic:
            action = torch.tanh(action_mean)
            log_prob = torch.zeros(obs.shape[0], device=obs.device)
        else:
            std = torch.exp(action_log_std)
            dist = Normal(action_mean, std)

            # Reparameterized sample + tanh squashing
            raw_action = dist.rsample()
            action = torch.tanh(raw_action)

            # Log probability with tanh correction (Appendix C of SAC paper)
            log_prob = dist.log_prob(raw_action).sum(dim=-1)
            log_prob -= torch.log(1 - action.pow(2) + 1e-6).sum(dim=-1)

        return action, log_prob, value.squeeze(-1)

    def evaluate_actions(self, obs: 'torch.Tensor',
                         actions: 'torch.Tensor') -> Tuple:
        """
        Evaluate log probability of actions (for PPO updates).

        Args:
            obs: Observations [batch, obs_dim]
            actions: Actions [batch, action_dim] (already tanh-squashed)

        Returns:
            log_prob: Log probability of actions
            entropy: Entropy of policy
            value: State value estimates
        """
        action_mean, action_log_std, value = self.forward(obs)
        std = torch.exp(action_log_std)

        # Inverse tanh to get raw actions
        raw_actions = torch.atanh(actions.clamp(-0.999, 0.999))

        dist = Normal(action_mean, std)
        log_prob = dist.log_prob(raw_actions).sum(dim=-1)
        log_prob -= torch.log(1 - actions.pow(2) + 1e-6).sum(dim=-1)

        entropy = dist.entropy().sum(dim=-1)

        return log_prob, entropy, value.squeeze(-1)

    def get_value(self, obs: 'torch.Tensor') -> 'torch.Tensor':
        """Get state value estimate"""
        features = self.features(obs)
        return self.critic(features).squeeze(-1)


class PolicyCheckpoint:
    """Utilities for saving and loading policy checkpoints"""

    @staticmethod
    def save(policy: MLPPolicy, path: str, metadata: dict = None):
        """Save policy checkpoint"""
        if not TORCH_AVAILABLE:
            raise RuntimeError("PyTorch not available")

        checkpoint = {
            'state_dict': policy.state_dict(),
            'obs_dim': policy.obs_dim,
            'action_dim': policy.action_dim,
            'metadata': metadata or {},
        }

        Path(path).parent.mkdir(parents=True, exist_ok=True)
        torch.save(checkpoint, path)

    @staticmethod
    def load(path: str, device: str = 'cpu') -> Tuple[MLPPolicy, dict]:
        """Load policy from checkpoint"""
        if not TORCH_AVAILABLE:
            raise RuntimeError("PyTorch not available")

        checkpoint = torch.load(path, map_location=device, weights_only=False)

        policy = MLPPolicy(
            obs_dim=checkpoint['obs_dim'],
            action_dim=checkpoint['action_dim'],
        )
        policy.load_state_dict(checkpoint['state_dict'])
        policy.to(device)
        policy.eval()

        return policy, checkpoint.get('metadata', {})


class BaselinePolicy:
    """
    Non-learned baseline policy for comparison.

    Implements simple heuristics:
    - Grid formation
    - Spread to maximize coverage
    - Move toward uncovered areas
    """

    def __init__(self, num_drones: int = 5, action_dim: int = 15):
        self.num_drones = num_drones
        self.action_dim = action_dim
        self.step_count = 0

    def get_action(self, obs: np.ndarray,
                   deterministic: bool = True) -> Tuple[np.ndarray, float, float]:
        """
        Get baseline action (spread formation).

        Returns:
            action, log_prob (0), value (0)
        """
        self.step_count += 1
        action = np.zeros(self.action_dim)

        # Simple spread heuristic: move outward from centroid
        for i in range(self.num_drones):
            angle = 2 * np.pi * i / self.num_drones
            # Gentle outward push
            action[i * 3] = 0.3 * np.cos(angle)
            action[i * 3 + 1] = 0.3 * np.sin(angle)
            action[i * 3 + 2] = 0.0  # maintain altitude

        return action, 0.0, 0.0
