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

# End-to-end integration smoke test (roadmap A.1) — no Gazebo/PX4 needed
python3 scripts/integration_smoke_test.py

# Standardized evaluation + plots (roadmap §12)
python3 scripts/evaluate.py --policies rl,baseline --episodes 10
python3 scripts/evaluate.py --policies rl --fault-step 100 --fault-drone 2

# With log-normal shadowing (roadmap §8). Off by default — the published
# checkpoint was trained on the deterministic median channel.
python3 scripts/evaluate.py --policies rl,baseline --episodes 10 --shadowing

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
- **"Coverage" means two different things.** The ROS pipeline
  (`coverage_calculator.py`) reports the *unweighted* fraction of grid cells
  above `rx_sensitivity_dbm`; the gym env reports *importance-weighted*
  coverage (disaster structures count 3x) against `coverage_threshold_dbm`.
  They also measure different areas: the ROS grid is a fixed 400 m box around
  the origin, the gym grid is centred on the disaster zone. For the same swarm
  the ROS path reports ~95% and the gym env ~20%. Always say which one a
  number came from — they are not comparable. With shadowing on there is a
  third distinction on top of those two: *mean* coverage (expected fraction of
  locations) and *reliable* coverage (fraction covered in >=90% of
  realizations) move in **opposite** directions. See the shadowing entry below.
- **Coverage threshold is now explicit, and it matters.**
  `coverage_threshold_dbm` (-80 dBm in `sim_params.yaml`) is passed through to
  the radio model; leave it unset (NaN) to fall back to the physically derived
  `noise_floor_dbm + min_snr_db`. The difference is large: -90 dBm gives a
  ~340 m per-drone range, which exceeds the 283 m half-diagonal of the 400 m
  simulated box — one drone blanketed the whole area and coverage read ~100%
  regardless of where the swarm flew. At -80 dBm the range is ~158 m and
  coverage is geometry-dependent. Changing this parameter changes every
  reported coverage figure, so say which threshold a number was measured at.
- **`SwarmState`'s network fields are not authoritative.** `coverage_percent`,
  `mesh_connected` and `backhaul_connected` are published as a hardcoded
  `0.0`/`False` by `sim_swarm_driver` and `px4_dds_bridge`, and nothing fills
  them in. Read `/network/metrics` instead. `mission_control` used to fall back
  to them when `/network/metrics` was missing, which made a dropped topic look
  like "coverage 0%, mesh down" and **aborted the mission at formation
  timeout**. Staleness is now explicit:
  `SwarmReadiness.network_data_valid` is False until fresh `NetworkMetrics`
  arrives (budget: `network_timeout_sec`, default 3 s), the FORMATION gate
  requires a *confirmed* mesh rather than an unknown one, and the abort reason
  names telemetry loss instead of blaming the mesh.
- **Battery model** (~0.5%/min) is optimistic vs real 15-25 min flight.
- **Shadowing is on, and it does not do what you would guess.** The
  propagation model has spatially correlated log-normal shadowing
  (`ShadowingField`, Gudmundson exponential correlation; `CorrelatedShadowing`
  adds the shared component). It still omits multipath/fading and
  interference, so SNR is not SINR.
  - It *raises* mean coverage — about +4 pp in the gym env, +13 pp on the ROS
    path. That is not a bug: a ground user attaches to the best drone, and the
    maximum over partly-independent fades is biased upward. It is a real
    macro-diversity gain.
  - What it lowers is **reliable** coverage. At sigma=5 dB the ROS path reports
    78% mean but only **44% covered in 90% of realizations** (65.6% on the
    deterministic channel), and 82% of the area becomes
    sometimes-covered-sometimes-not. Use
    `CoverageCalculator.compute_coverage_reliability()` and quote the
    reliability target; mean coverage alone flatters the system.
  - `shadow_inter_link_correlation` decides the sign. At rho=1 shadowing
    belongs to the ground point, there is no diversity to gain, and the effect
    on mean coverage is ~0 pp. At rho=0 it is +22 pp. The default 0.5 is the
    3GPP inter-site value.
  - `compute_max_range()` is the **median** range. At sigma=5 dB the D2G range
    is 158 m median but **97 m at 10% outage** — pass
    `compute_max_range(0.1)` rather than quoting the median as "the range".
  - **Shadowing is off by default in the gym env**
    (`EnvConfig.shadowing_enabled`) because the published checkpoint was
    trained on the deterministic median channel. It is **on** in
    `sim_params.yaml` and `network_sim_params.yaml` (sigma=4 dB, +1 dB for
    D2G). Say which one a number was measured at.
  - Enabling it multiplies episode-to-episode coverage spread by about 12x
    (±0.2 pp to ±2.5 pp over 6 episodes). It does **not** change the
    RL-vs-baseline ordering on coverage or connectivity, which is the useful
    robustness result.
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
2. **Reproducibility pass** — **done**. **Standardized eval script** — **done**: `scripts/evaluate.py` reports coverage, SNR (not SINR — no interference term yet), throughput, connectivity, energy and fault recovery, with plots. **Integration smoke test (A.1)** — **done**: `scripts/integration_smoke_test.py`.
3. **Log-normal shadowing add-on** — **done**: spatially correlated field with
   a configurable inter-link correlation, plus reliability-aware coverage.
   Interference/SINR is still open, so §8 is only partly closed.
4. **alpha_m coverage<->connectivity Pareto sweep.**
5. **Resilient multi-hop routing** — redundant/disjoint paths + k-connectivity; fold path-redundancy into the reward.
6. **Energy-efficiency term** in the reward — coverage-per-joule.
7. **Package AURA as a benchmark.**
8. **Flagship:** **MAPPO / decentralized policy.**

## Definition of done (per task)
`colcon build` clean · unit tests pass · eval script runs and emits plots · no new committed artifacts · README/config updated · invariants above respected.
