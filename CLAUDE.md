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
  They also still measure different *areas*, though both are now on the
  disaster zone rather than one being on the origin. The ROS grid is fitted to
  the scene (`x[-170, 390] y[-350, 20]`, all 29 structures); the gym grid is
  a square 400 m box on the trained centre (`x[-80, 320] y[-370, 30]`, 26 of
  29 — it clips the reactor and two radio towers). The gym grid cannot simply
  be refitted: its 10x10 downsample feeds the 184-D observation, so changing
  its shape changes what each observation cell means. That is retrain-gated.
  So a ROS number and a gym number differ in weighting *and* in region — never
  compare them directly. With shadowing on there is a further
  distinction: *mean* coverage (expected fraction of locations) and *reliable*
  coverage (fraction covered in >=90% of realizations) move in **opposite**
  directions. See the shadowing entry below.
- **Everything is positioned relative to the disaster zone at (120, -170),
  not the origin.** That is `ActionConfig.world_center_*`, the centre of the
  checkpoint's 250 m clip disk, and it cannot move without retraining. The
  drones *spawn* at the origin in Gazebo and transit from there, which is why
  so much had drifted onto it:
  - The ROS coverage grid was a 400 m box on the origin. It contained **6 of
    the 29 disaster structures** and excluded the entire eastern cluster, so
    the headline ROS coverage figure was measured over mostly empty ground.
    It is now **fitted to the scene**: `x[-170, 390] y[-350, 20]`, 56x37
    cells, being the bounding box of all 29 structures plus a 50 m importance
    margin. Not square, because the scene isn't — coverage % is a fraction of
    cells, so empty area dilutes it directly.
  - The gym env's *grid* was centred correctly, but its initial drone ring was
    not — training started the swarm ~200 m from its objective, an initial
    condition that never occurs at inference, because RL activates only in
    OPERATIONS after TRANSIT and FORMATION have already brought the swarm in.
    Fixing it tripled reported gym coverage (RL 17.0% -> 50.7%) and **flipped
    the final-coverage ordering in RL's favour** (see below).
  - Gym weather zones were drawn from `uniform(-100, 100)` on the origin, so
    they usually fell outside the measured area and attenuated nothing.
  - Dead zones roamed inside a box on the origin, and the preset zones sat in
    a +/-80 m box there. `dead_zone_publisher` now holds the centre in
    `DISASTER_CENTER_X/Y` with the spawn and roam boxes derived from it.
  - `rl_target` was (125, -164), 7.8 m off, so `strategic_rl_node`'s
    "rl_target is N m from the trained world centre" warning fired on every
    run and therefore carried no information.
  `test_grid_alignment.py` reads the shipped YAML and asserts it still matches
  `disaster_scene.GRID_BOUNDS` and contains all 29 structures — the comments
  are what failed last time.
- **The scene is generated from the world, not hand-written.**
  `worlds/earthquake_city.world` is the single source of truth;
  `scripts/generate_disaster_scene.py` derives
  `aura_strategic_rl/disaster_scene.py` (structures, bbox, grid bounds) from
  it. Regenerate and commit after editing the world —
  `test_disaster_scene.py` re-derives and fails if the committed module has
  drifted, and `--check` is the CI form.
  **`SwarmGymEnv._DISASTER_STRUCTURES` still holds only 17 of the 29.** It
  omits the reactor, both water towers, all three radio towers, five
  collapsed industrials and a police station. Fixing it changes the
  importance map, hence the reward, hence what training optimizes — so it is
  **retrain-gated** and deliberately still stale.
  `TestGymStructureListIsKnownStale` pins the gap at 12 so it cannot widen.
  Measurement is already honest (the ROS grid covers all 29); the reward is
  not.
- **The 250 m clip radius is the scene's circumscribed circle.** The furthest
  of the 29 structures is 251 m from (120, -170), so `area_bound = 250` was
  evidently sized to the scene. Two boundary features (the reactor and the
  furthest radio tower) sit ~1 m outside, which costs nothing: the per-drone
  range is ~158 m, so a drone at the bound still covers them.
- **The coverage grid is vectorized, and was the node's bottleneck.**
  `compute_coverage` was three nested Python loops (cells x cells x drones),
  ~194 ms per update against `update_rate_hz: 10.0` — so `/network/metrics`
  had been publishing at about half its configured rate, and a larger grid
  made it worse. One numpy pass is ~1 ms, a 165x speedup, and the smoke test
  now sees 320 metrics messages where it saw 165. The arithmetic is
  unchanged: `test_coverage_vectorization.py` keeps an independent scalar
  reference and asserts they agree cell for cell.
- **Measured honestly over the whole disaster, the baseline beats the RL
  policy on coverage.** 90 s of OPERATIONS in the SIL stack, shipped config
  (fitted grid, -80 dBm, shadowing on), 905 samples each:

  | OPERATIONS | RL | Hungarian baseline |
  |---|---|---|
  | coverage, first -> last | 40.7% -> 40.4% | 40.7% -> **70.1%** |
  | coverage, 2nd-half mean | 40.6% | **69.6%** |
  | throughput | **114.7** Mbps | 97.6 Mbps |
  | mesh links | **10.0** | 8.9 |
  | mesh connected | 100% | 100% |

  The baseline spreads into a circular formation over the zone and picks up
  the eastern cluster; the RL policy holds a tight cluster near where it
  starts and never reaches it. RL still wins on throughput and link count,
  which is the connectivity half of the objective.

  This reverses the earlier headline, and the reversal is the point: the old
  figures were measured on a grid that excluded two thirds of the disaster,
  against an importance map holding 17 of 29 structures, from a policy trained
  with its start ring on the origin. Each of those flattered RL. Do not quote
  pre-realignment coverage comparisons.
- **Mean coverage over an episode is the wrong statistic for these policies.**
  The baseline is non-stationary: it peaks around 70% by step 100 and then
  collapses to 33% by step 300, ending below where it started. RL rises
  monotonically (43% -> 54.6%) and ends higher. So the *mean* favours the
  baseline (60.8% vs 50.7%) while the *final* value favours RL (54.6% vs
  33.2%). Training's `eval_coverage` is final-step, which is the right choice
  and the one that agrees with the SIL mission (baseline 89.5% -> 42.7%, RL
  88.7% -> 88.9%). Before the realignment the gym eval disagreed with the
  mission in *sign*; it no longer does.
- **Coverage grid regeneration.** After editing the world:
  `python3 scripts/generate_disaster_scene.py`, then copy
  `GRID_BOUNDS` into `area_x_min`/`area_y_min`/`area_x_max`/`area_y_max` in
  both `sim_params.yaml` and `network_sim_params.yaml`. The tests will tell
  you if you miss one.
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
  - It *raises* mean coverage — about +6 pp in the gym env, +14 pp on the ROS
    path. That is not a bug: a ground user attaches to the best drone, and the
    maximum over partly-independent fades is biased upward. It is a real
    macro-diversity gain.
  - What it lowers is **reliable** coverage. On the shipped config (grid on
    the disaster zone, -80 dBm, sigma=5 dB D2G, rho=0.5) one SIL swarm reads
    53.9% deterministic, **68.2% mean**, but only **39.4% covered in 90% of
    realizations** and 23.4% at 99%; 83.9% of the area becomes
    sometimes-covered-sometimes-not. Use
    `CoverageCalculator.compute_coverage_reliability()` and quote the
    reliability target; mean coverage alone flatters the system.
  - `shadow_inter_link_correlation` decides the sign. At rho=1 shadowing
    belongs to the ground point, there is no diversity to gain, and the effect
    on mean coverage is +1.4 pp. At rho=0 it is +22.6 pp. The default 0.5 is
    the 3GPP inter-site value.
  - `compute_max_range()` is the **median** range. At sigma=5 dB the D2G range
    is 158 m median but **97 m at 10% outage** — pass
    `compute_max_range(0.1)` rather than quoting the median as "the range".
  - **Shadowing is off by default in the gym env**
    (`EnvConfig.shadowing_enabled`) because the published checkpoint was
    trained on the deterministic median channel. It is **on** in
    `sim_params.yaml` and `network_sim_params.yaml` (sigma=4 dB, +1 dB for
    D2G). Say which one a number was measured at.
  - Enabling it multiplies episode-to-episode coverage spread by about 4x
    (±0.5 pp to ±1.8 pp over 6 episodes). It does **not** change the
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
