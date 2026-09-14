# CLAUDE.md — AURA project context for Claude Code

> Context, conventions, invariants and backlog for AURA. Pair it with
> `AURA_Roadmap_and_Gaps.md` (the full roadmap).

## What this is
**AURA (Autonomous Urban Reconnaissance Array)** — a post-earthquake UAV relay swarm that restores an emergency WiFi mesh over a disaster zone. Five drones (hub + leaf pattern). **ROS 2 Humble** orchestrates **Gazebo Classic 11 + PX4 SITL**, a **custom log-distance path-loss network simulator** with **BFS mesh connectivity**, a **PPO reinforcement-learning positioning policy** with a **Hungarian-assignment baseline**, and a **web dashboard**. Basis of IEEE CAMAD 2026 (Session-05, paper ID 1571300267).

## Workspace / package layout
colcon workspace — repo root mounts at `/home/aura/ws` in the container, packages under `src/`:
- **aura_msgs** — message definitions (`NetworkMetrics`, `CoverageMap`, `SwarmState`, ...)
- **aura_trajectory** (C++) — MINCO trajectory / formation control
- **aura_px4_interface** (C++) — PX4 uORB <-> ROS 2 DDS bridge
- **aura_network_sim** (Python) — log-distance path loss, BFS connectivity, coverage grid
- **aura_strategic_rl** (Python) — RL: `spaces.py`, `rewards.py`, `policy.py`, `swarm_gym_env.py`, `train_policy.py`, `baseline_hho.py`, `strategic_rl_node.py`
- **aura_mission_control** (Python) — mission state machine and orchestration

## Build & run
```bash
# Start the container (single shared clone; ssh-agent forwarded, no key inside)
cd docker && docker compose up -d && docker compose exec aura-dev bash

# Build (build aura_msgs first whenever a .msg changes)
cd /home/aura/ws && colcon build --packages-select aura_msgs && source install/setup.bash
colcon build && source install/setup.bash

# Tests
colcon test --ctest-args -LE linter && colcon test-result --all

# Train the RL policy (always pass an explicit --seed for anything reportable)
python3 -m aura_strategic_rl.train_policy --seed 42
```
- Ports: PX4 lockstep TCP **4561-4565**; Micro-XRCE-DDS agent **localhost:8888**; ROS Bridge WebSocket **9090**.
- A non-interactive `docker exec` does **not** source `~/.bashrc` (it returns early for non-interactive shells), so `px4_msgs` is missing and `aura_px4_interface` will not configure. Source `/opt/ros/humble/setup.bash` **and** `/opt/px4_ros/install/setup.bash` explicitly in scripts.

## Environment — pinned, do not drift
`docker/versions.env` holds the exact revisions; `docker/requirements.txt` the Python pins; `docker/requirements.lock.txt` the full forensic freeze. `docker/check_pins.py` fails CI if the Dockerfile's ARG defaults and `versions.env` disagree.

**The published baseline is tagged `camad-2026-baseline`** (commit `e371402`). Freeze before upgrading; re-run the tests and eval after every bump.

## Invariants — DO NOT BREAK
- **Coordinate frames:** PX4 = NED, ROS 2 = ENU. The conversion (`x_enu=y_ned, y_enu=x_ned, z_enu=-z_ned`) is isolated to **exactly two lines** — keep it there; never scatter transforms across the code.
- **RL activates only during the OPERATIONS mission phase** (safety boundary). RL must never drive TAKEOFF, FORMATION exit, RTL, or landing.
- **Message contracts:** downstream nodes read specific fields (`NetworkMetrics.mesh_connected`, `CoverageMap.header`, ...). Change a `.msg` -> rebuild `aura_msgs` -> verify every reader/writer.
- **Gazebo Classic duplicate `Load()` race** is fixed via a static `std::set<std::string>` model-name registry + `SO_REUSEADDR` + no-op aborts. Do not reintroduce it.
- **Spaces:** Observation = **184-D**, Action = **15-D** (`dx,dy,dz` x 5 drones, tanh-squashed, 250 m clip radius, altitude 15-80 m). Reward is multi-objective (coverage; mesh connectivity weight alpha_m=3.0; signal; zone proximity; penalties for collision/boundary/altitude).
- **Training and inference must share `spaces.py`.** `strategic_rl_node` converts actions with the same `ActionProcessor` training uses. Never re-derive movement or altitude limits in the node — a second copy is how the deployed z-step silently became 2.5x the trained one.

## Stack — actual versions (CHECK COMPATIBILITY BEFORE UPGRADING)
| Component | Pinned to | Note |
|---|---|---|
| Ubuntu | 22.04.5 LTS | |
| ROS 2 | Humble | -> Jazzy needs Ubuntu 24.04 (roadmap 0.3) |
| Gazebo | Classic 11.10.2 | **EOL Jan 2025** — Harmonic is the forward path (roadmap 0.4) |
| PX4-Autopilot | `7b72335` (main, 2026-02-06) | **v1.16.0-rc line, NOT v1.14** |
| torch | 2.6.0+cu124 | kernels sm_50-sm_90 only |

> **PX4 is not v1.14.** Earlier docs said it was. The Dockerfile cloned the default branch unpinned, so the image carries PX4 main on the v1.16.0-rc line — and that is what produced the published results. Verified against the running container on 2026-09-14.

> **GPU training does not work on Blackwell.** The RTX 5050 is sm_120; the pinned cu124 torch has no kernels for it, so `torch.cuda.is_available()` returns True and kernels then fail to launch. `train_policy.resolve_device()` detects this and falls back to CPU. The fix is a cu128 build on the modernization branch — not on the frozen baseline.

**Compatibility rules before any upgrade:**
- The **PX4 <-> Gazebo <-> ROS 2 version matrix must align** — mismatches break SITL lockstep, the Micro-XRCE-DDS bridge, and message APIs. Check each project's supported-versions table first.
- Gazebo Classic -> Harmonic **changes the model-spawn architecture**: the `Load()`-race workaround likely no longer applies (good), but launch/spawn code needs rework.
- **Do it on a branch, keep `camad-2026-baseline` intact**, re-run the tests + eval script, and confirm results still match before merging.

## Known-fragile / gotchas
- **End-to-end wiring is still unverified** — packages compile and unit tests pass, but there is no integration smoke test (roadmap A.1). This is the largest open gap.
- **Battery model** (~0.5%/min) is optimistic vs real 15-25 min flight.
- **Propagation** omits shadowing/fading/interference, so coverage is optimistic (add a log-normal shadowing term).
- `src/aura_localization` is an empty directory — no package, nothing references it.
- `etc` and `test_data` are tracked symlinks to absolute `/home/aura/PX4-Autopilot/...` paths; they resolve only inside the container.

## Guardrails for Claude Code
- **NEVER commit** `build/`, `install/`, `log/`, `node_modules/` — they are in `.gitignore`.
- Keep runs **reproducible**: always pass `--seed`; `run_config.json` is written next to every checkpoint and records seed, device, git revision, library versions and the full env/reward configs.
- Maintain **unit tests** for reward calc, coverage grid, BFS connectivity, action clipping; run them before committing.
- Editing messages -> rebuild `aura_msgs` first, then re-verify downstream nodes.
- Prefer **small, verifiable changes**; run the tests after each.
- Don't overclaim in docs/comments: respect the roadmap's credibility tags (some "gaps" are already solved).
- **No `Co-Authored-By` trailers** in commit messages.

## Task backlog — first sprint (see AURA_Roadmap_and_Gaps.md)
0. **FOUNDATION FIRST.** (a) Freeze & tag the CAMAD baseline + pin the environment — **done**: tag `camad-2026-baseline`, `docker/versions.env`, `docker/requirements*.txt`. (b) On a branch: Gazebo Classic->Harmonic, ROS 2 Humble->Jazzy, PX4 align, RL stack refresh. Re-run eval before merging.
1. **Repo hygiene** — **done**.
2. **Reproducibility pass** — **done** — + **standardized eval script** (coverage, SINR, throughput, connectivity, energy, fault-recovery time -> plots).
3. **Log-normal shadowing add-on** to the propagation model.
4. **alpha_m coverage<->connectivity Pareto sweep.**
5. **Resilient multi-hop routing** — redundant/disjoint paths + k-connectivity; fold path-redundancy into the reward.
6. **Energy-efficiency term** in the reward — coverage-per-joule.
7. **Package AURA as a benchmark.**
8. **Flagship:** **MAPPO / decentralized policy.**

## Definition of done (per task)
`colcon build` clean · unit tests pass · eval script runs and emits plots · no new committed artifacts · README/config updated · invariants above respected.
