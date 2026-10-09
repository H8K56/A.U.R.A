"""Value target normalization for PPO.

`MLPPolicy` shares a feature trunk between the actor and the critic, PPO
normalizes advantages but not value targets, and the gradient norm is clipped
globally. Put together, those three mean the critic's gradient scale decides
how much of each update the actor gets: when returns are large, the value term
dominates the shared trunk and the policy's features are destroyed. Measured on
this project, at the default `vf_coef=0.5` the policy collapsed on the second
update and never recovered, while `vf_coef=0.005` merely delayed it.

Lowering `vf_coef` is a workaround with a hidden dependency on the reward
scale, which is exactly how this went unnoticed: it only started biting when a
scenario fix roughly doubled per-step reward, because value loss grows with the
*square* of returns.

The fix is to keep the critic's targets O(1) regardless of reward scale, so
`vf_coef` means what it says.

Scale only, no mean subtraction
-------------------------------
This divides by a running estimate of the return standard deviation and leaves
the mean alone. Subtracting a running mean would shift the critic's target
every time the estimate moved, so the critic would be chasing a target that
drifts for reasons unrelated to the policy; PopArt handles that with an
explicit output correction, which is more machinery than the problem needs.
Dividing by a running scale is what Stable-Baselines3 does for reward
normalization and it addresses the actual failure, which is scale.

Rewards and advantages stay in their original units. Only the critic's
input/output scale changes, so `ep_reward_mean` remains comparable to runs made
before this existed.
"""

from __future__ import annotations

from typing import Dict, Optional

import numpy as np


class RunningMeanStd:
    """Running mean and variance over a stream of batches.

    Chan's parallel variance update, so a batch is folded in at once without
    keeping the samples and without the catastrophic cancellation that
    accumulating sums of squares would bring.
    """

    def __init__(self, epsilon: float = 1e-4):
        self.mean = 0.0
        self.var = 1.0
        # Pseudo-count, so the first update does not divide by zero and the
        # initial variance of 1.0 carries a little weight rather than being
        # overwritten outright.
        self.count = epsilon

    def update(self, x) -> None:
        x = np.asarray(x, dtype=np.float64).ravel()
        if x.size == 0:
            return
        self.update_from_moments(float(x.mean()), float(x.var()), x.size)

    def update_from_moments(self, batch_mean: float, batch_var: float,
                            batch_count: int) -> None:
        delta = batch_mean - self.mean
        total = self.count + batch_count

        new_mean = self.mean + delta * batch_count / total
        m_a = self.var * self.count
        m_b = batch_var * batch_count
        m_2 = m_a + m_b + delta * delta * self.count * batch_count / total

        self.mean = new_mean
        self.var = max(m_2 / total, 0.0)
        self.count = total

    @property
    def std(self) -> float:
        return float(np.sqrt(self.var))

    def state_dict(self) -> Dict[str, float]:
        return {'mean': float(self.mean), 'var': float(self.var),
                'count': float(self.count)}

    def load_state_dict(self, state: Dict[str, float]) -> None:
        self.mean = float(state['mean'])
        self.var = float(state['var'])
        self.count = float(state['count'])


class ValueNormalizer:
    """Keeps the critic's targets O(1) whatever the reward scale.

    The critic predicts *normalized* values, so two conversions are needed and
    they must not be mixed up:

    - `denormalize` turns a critic prediction back into reward units. Needed
      wherever a value is used as a value: GAE, and bootstrapping the last
      step of a truncated rollout.
    - `normalize` turns computed returns into the critic's target units. Needed
      only for the value loss.

    `enabled=False` makes both the identity, so a run can be compared against
    one made without this.
    """

    def __init__(self, enabled: bool = True, epsilon: float = 1e-8,
                 min_std: float = 1e-2):
        self.enabled = enabled
        self.epsilon = epsilon
        # Floor the scale: early on, or for a reward that barely varies, the
        # estimated std can approach zero and dividing by it would hand the
        # critic enormous targets — the very failure this exists to prevent.
        self.min_std = min_std
        self.rms = RunningMeanStd()

    @property
    def scale(self) -> float:
        """The divisor currently applied to returns."""
        if not self.enabled:
            return 1.0
        return max(self.rms.std, self.min_std) + self.epsilon

    def update(self, returns) -> None:
        """Fold this rollout's returns into the running scale estimate."""
        if self.enabled:
            self.rms.update(returns)

    def normalize(self, returns):
        """Returns -> critic target units."""
        if not self.enabled:
            return returns
        return returns / self.scale

    def denormalize(self, values):
        """Critic prediction -> reward units."""
        if not self.enabled:
            return values
        return values * self.scale

    def state_dict(self) -> Dict[str, object]:
        return {
            'enabled': bool(self.enabled),
            'min_std': float(self.min_std),
            'epsilon': float(self.epsilon),
            'rms': self.rms.state_dict(),
        }

    def load_state_dict(self, state: Optional[Dict[str, object]]) -> None:
        """Restore from a checkpoint.

        A checkpoint written before this existed has no normalizer state. Its
        critic was trained on raw returns, which is scale 1.0 — so the absence
        of state means "disabled", not "defaults".
        """
        if not state:
            self.enabled = False
            self.rms = RunningMeanStd()
            return
        self.enabled = bool(state.get('enabled', True))
        self.min_std = float(state.get('min_std', self.min_std))
        self.epsilon = float(state.get('epsilon', self.epsilon))
        rms_state = state.get('rms')
        if rms_state:
            self.rms.load_state_dict(rms_state)

    def __repr__(self) -> str:
        if not self.enabled:
            return 'ValueNormalizer(disabled)'
        return (f'ValueNormalizer(scale={self.scale:.3f}, '
                f'count={self.rms.count:.0f})')
