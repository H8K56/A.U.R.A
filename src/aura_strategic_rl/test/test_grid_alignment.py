#!/usr/bin/env python3
"""The measurement grids, the training objective and the scenario must agree.

Everything in AURA is positioned relative to one of two centres, and for a
long time the wrong one was used in most places:

- the **disaster zone** at (120, -170), which is what the checkpoint was
  trained against (`ActionConfig.world_center_*`, `RewardConfig`), and
- the **origin**, where the drones spawn in Gazebo and transit from.

The ROS coverage grid was a 400 m box on the *origin*. It contained 6 of the
17 disaster structures and excluded the entire eastern cluster, so the
headline ROS coverage figure was measured over mostly empty ground while two
thirds of the disaster sat outside the grid. The gym env's grid was correctly
centred, but its initial drone ring and its weather zones were not — training
began 200 m from the objective, in a state that never occurs at inference
(RL activates only in OPERATIONS, after TRANSIT and FORMATION), and weather
usually fell outside the measured area and attenuated nothing.

These tests are the reason that cannot drift back. They read the shipped YAML
rather than trusting a comment, because the comment is what failed last time.

Runs without ROS.
"""

import math
import pathlib

import pytest
import yaml

from aura_strategic_rl import disaster_scene as scene
from aura_strategic_rl.rewards import RewardConfig
from aura_strategic_rl.spaces import ActionConfig
from aura_strategic_rl.swarm_gym_env import EnvConfig, SwarmGymEnv

REPO = pathlib.Path(__file__).resolve().parents[3]
SIM_PARAMS = REPO / 'src/aura_simulation/config/sim_params.yaml'
NETWORK_PARAMS = REPO / 'src/aura_network_sim/config/network_sim_params.yaml'

#: The trained centre. Changing this invalidates the checkpoint's 250 m clip
#: disk, so it is written out here rather than imported — a test that reads
#: the value it is checking cannot catch the value changing.
TRAINED_CENTER = (120.0, -170.0)


def load_params(path, node):
    """Merged `/**:` globals and node-specific parameters, as ROS resolves them."""
    doc = yaml.safe_load(path.read_text())
    merged = {}
    for key in ('/**', node):
        section = doc.get(key)
        if section:
            merged.update(section.get('ros__parameters', {}))
    return merged


def grid_bounds(params):
    return (params['area_x_min'], params['area_y_min'],
            params['area_x_max'], params['area_y_max'])


def structures():
    """The gym env's hand-maintained list — 17 of the world's 29.

    Kept distinct from `scene.STRUCTURES` on purpose: replacing it changes the
    importance map and therefore the reward, so it is retrain-gated and
    deliberately still the smaller list. See TestGymStructureListIsKnownStale.
    """
    return list(SwarmGymEnv._DISASTER_STRUCTURES)


class TestTrainedGeometryIsUnchanged:
    """These numbers are baked into the published checkpoint."""

    def test_action_config_centre(self):
        cfg = ActionConfig(num_drones=5)
        assert (cfg.world_center_x, cfg.world_center_y) == TRAINED_CENTER

    def test_reward_config_centre_matches_action_config(self):
        action, reward = ActionConfig(num_drones=5), RewardConfig()
        assert (reward.world_center_x, reward.world_center_y) == TRAINED_CENTER
        assert reward.area_bound == action.area_bound

    def test_env_config_centre_matches(self):
        cfg = EnvConfig()
        assert (cfg.world_center_x, cfg.world_center_y) == TRAINED_CENTER

    def test_the_clip_disk_is_sized_to_the_scene(self):
        """The 250 m bound is not arbitrary: the furthest of the 29 structures
        is 251 m from the trained centre, so the disk is the scene's
        circumscribed circle to within a couple of metres. Two boundary
        features (the reactor and the furthest radio tower) sit marginally
        outside it, which costs nothing — the per-drone range is ~158 m, so a
        drone at the bound still covers them."""
        bound = ActionConfig(num_drones=5).area_bound
        distances = [math.hypot(sx - TRAINED_CENTER[0], sy - TRAINED_CENTER[1])
                     for _, sx, sy in scene.STRUCTURES]
        assert max(distances) == pytest.approx(251.0, abs=2.0)
        outside = [d for d in distances if d > bound]
        assert len(outside) <= 2, f'{len(outside)} structures beyond the disk'

    def test_the_gym_list_is_within_the_clip_disk(self):
        bound = ActionConfig(num_drones=5).area_bound
        for sx, sy in structures():
            distance = math.hypot(sx - TRAINED_CENTER[0], sy - TRAINED_CENTER[1])
            assert distance <= bound, f'({sx}, {sy}) is {distance:.0f} m out'


class TestRosGridCoversTheDisaster:
    """The grid is fitted to the scene, not squared off around a centre:
    coverage % is a fraction of cells, so empty area dilutes it directly."""

    CONFIGS = [(SIM_PARAMS, 'network_sim'), (NETWORK_PARAMS, 'network_sim')]

    @pytest.mark.parametrize("path,node", CONFIGS)
    def test_grid_matches_the_generated_bounds(self, path, node):
        """The YAML is a hand-maintained copy of disaster_scene.GRID_BOUNDS.
        If it drifts, the shipped grid stops matching the world."""
        assert grid_bounds(load_params(path, node)) == scene.GRID_BOUNDS

    @pytest.mark.parametrize("path,node", CONFIGS)
    def test_grid_contains_every_disaster_structure(self, path, node):
        """The regression test for the original fault: on the old origin-centred
        bounds this failed for 23 of the 29 structures."""
        x_min, y_min, x_max, y_max = grid_bounds(load_params(path, node))
        outside = [(name, sx, sy) for name, sx, sy in scene.STRUCTURES
                   if not (x_min <= sx <= x_max and y_min <= sy <= y_max)]
        assert not outside, f'{len(outside)} structures outside the grid: {outside}'

    @pytest.mark.parametrize("path,node", CONFIGS)
    def test_grid_leaves_an_importance_margin_around_the_scene(self, path, node):
        """A structure flush against the edge would have its coverage area
        clipped, and the importance radius is 50 m."""
        x_min, y_min, x_max, y_max = grid_bounds(load_params(path, node))
        margin = scene.IMPORTANCE_RADIUS_M
        bx_min, by_min, bx_max, by_max = scene.BBOX
        assert bx_min - x_min >= margin
        assert by_min - y_min >= margin
        assert x_max - bx_max >= margin
        assert y_max - by_max >= margin

    @pytest.mark.parametrize("path,node", CONFIGS)
    def test_grid_is_not_centred_on_the_origin(self, path, node):
        """Stated separately so the failure message says what went wrong."""
        x_min, y_min, x_max, y_max = grid_bounds(load_params(path, node))
        centre = ((x_min + x_max) / 2, (y_min + y_max) / 2)
        assert centre != (0.0, 0.0), 'grid is back on the origin'

    @pytest.mark.parametrize("path,node", CONFIGS)
    def test_grid_is_an_exact_number_of_cells(self, path, node):
        x_min, y_min, x_max, y_max = grid_bounds(load_params(path, node))
        res = scene.GRID_RESOLUTION_M
        assert (x_max - x_min) % res == 0.0
        assert (y_max - y_min) % res == 0.0

    def test_both_config_files_declare_the_same_grid(self):
        """sim_params.yaml wins in the SIL launch path and
        network_sim_params.yaml in the standalone one. If they disagree, which
        coverage number you get depends on how you launched."""
        assert (grid_bounds(load_params(SIM_PARAMS, 'network_sim'))
                == grid_bounds(load_params(NETWORK_PARAMS, 'network_sim')))

    def test_no_single_drone_can_blanket_the_grid(self):
        """The fault the coverage threshold fix was about: if one drone's range
        exceeds the grid's half-diagonal, coverage reads ~100% wherever the
        swarm flies. At -80 dBm the per-drone range is ~158 m."""
        x_min, y_min, x_max, y_max = scene.GRID_BOUNDS
        half_diagonal = math.hypot((x_max - x_min) / 2, (y_max - y_min) / 2)
        assert half_diagonal > 158.0


class TestGymStructureListIsKnownStale:
    """Documenting a gap rather than asserting it away.

    `SwarmGymEnv._DISASTER_STRUCTURES` holds 17 of the world's 29 damaged
    structures. Replacing it changes the importance map, hence the reward,
    hence what training optimizes — so it belongs with a retrain, not here.
    These tests pin the size of the gap so it cannot quietly widen, and will
    need updating (not deleting) when the list is fixed.
    """

    def test_the_gym_list_is_a_subset_of_the_world(self):
        """Whatever else is wrong with it, it must not contain structures the
        world does not have."""
        world = scene.structure_xy()
        for sx, sy in structures():
            assert any(abs(sx - wx) < 2.0 and abs(sy - wy) < 2.0
                       for wx, wy in world), f'({sx}, {sy}) is not in the world'

    def test_the_gap_is_the_known_twelve(self):
        world = scene.structure_xy()
        gym = structures()
        missing = [(wx, wy) for wx, wy in world
                   if not any(abs(wx - gx) < 2.0 and abs(wy - gy) < 2.0
                              for gx, gy in gym)]
        assert len(missing) == 12, (
            f'the gym/world gap changed: {len(missing)} missing, {missing}')

    def test_the_coverage_grid_covers_the_full_scene_regardless(self):
        """Measurement is already honest even though the reward is not: the
        ROS grid covers all 29."""
        x_min, y_min, x_max, y_max = scene.GRID_BOUNDS
        for name, sx, sy in scene.STRUCTURES:
            assert x_min <= sx <= x_max and y_min <= sy <= y_max, name


class TestRlTargetAgreesWithTraining:

    def test_rl_target_is_the_trained_centre(self):
        """strategic_rl_node warns when these disagree, because the policy is
        clipped against the trained disk regardless. At (125, -164) the
        warning fired on every run and so carried no information."""
        params = load_params(SIM_PARAMS, 'strategic_rl')
        assert (params['rl_target_x'], params['rl_target_y']) == TRAINED_CENTER

    def test_offset_is_below_the_nodes_warning_threshold(self):
        params = load_params(SIM_PARAMS, 'strategic_rl')
        offset = math.hypot(params['rl_target_x'] - TRAINED_CENTER[0],
                            params['rl_target_y'] - TRAINED_CENTER[1])
        assert offset <= 1.0, f'strategic_rl_node will warn: {offset:.1f} m'


class TestGymScenarioIsAligned:

    def test_drones_start_around_the_disaster_zone(self):
        env = SwarmGymEnv(config=EnvConfig(), seed=1)
        env.reset(seed=1)
        for drone in env.drones:
            offset = math.hypot(drone.position[0] - TRAINED_CENTER[0],
                                drone.position[1] - TRAINED_CENTER[1])
            assert offset < 2 * EnvConfig().initial_radius, (
                f'drone {drone.drone_id} starts {offset:.0f} m from the zone')

    def test_drones_do_not_start_at_the_origin(self):
        env = SwarmGymEnv(config=EnvConfig(), seed=1)
        env.reset(seed=1)
        for drone in env.drones:
            assert math.hypot(*drone.position[:2]) > 100.0

    def test_the_starting_ring_is_inside_the_coverage_grid(self):
        cfg = EnvConfig()
        env = SwarmGymEnv(config=cfg, seed=1)
        env.reset(seed=1)
        half = cfg.area_size
        for drone in env.drones:
            assert abs(drone.position[0] - cfg.world_center_x) <= half
            assert abs(drone.position[1] - cfg.world_center_y) <= half

    def test_a_non_randomized_reset_also_starts_at_the_zone(self):
        cfg = EnvConfig(randomize_initial_positions=False)
        env = SwarmGymEnv(config=cfg, seed=1)
        env.reset(seed=1)
        for drone in env.drones:
            offset = math.hypot(drone.position[0] - cfg.world_center_x,
                                drone.position[1] - cfg.world_center_y)
            assert offset == pytest.approx(cfg.initial_radius, abs=1e-6)

    def test_reset_does_not_accumulate_drones(self):
        """The ring construction was rewritten; make sure the list is still
        cleared each episode."""
        cfg = EnvConfig()
        env = SwarmGymEnv(config=cfg, seed=1)
        for _ in range(3):
            env.reset(seed=1)
            assert len(env.drones) == cfg.num_drones

    def test_weather_zones_land_inside_the_coverage_grid(self):
        """They were drawn from uniform(-100, 100) on the origin while the grid
        sat on (120, -170), so weather attenuated ground nobody measured."""
        cfg = EnvConfig(randomize_weather=True, weather_probability=1.0)
        half = cfg.area_size
        seen = 0
        for seed in range(25):
            env = SwarmGymEnv(config=cfg, seed=seed)
            env.reset(seed=seed)
            for zone in env.weather_zones:
                seen += 1
                assert abs(zone.center[0] - cfg.world_center_x) <= half
                assert abs(zone.center[1] - cfg.world_center_y) <= half
        assert seen > 0, 'no weather zones were generated to check'

    def test_weather_actually_overlaps_the_importance_map(self):
        """Being inside the grid is not enough — it has to reach cells that
        count. At least some draws must touch a high-importance cell."""
        cfg = EnvConfig(randomize_weather=True, weather_probability=1.0)
        overlapping = 0
        for seed in range(25):
            env = SwarmGymEnv(config=cfg, seed=seed)
            env.reset(seed=seed)
            for zone in env.weather_zones:
                for sx, sy in structures():
                    if math.hypot(sx - zone.center[0],
                                  sy - zone.center[1]) < zone.radius + 50.0:
                        overlapping += 1
                        break
        assert overlapping > 5, (
            f'only {overlapping}/25 weather draws reached a structure')


class TestDeadZonesAreAligned:
    """`aura_simulation` is a separate package; import it lazily so this file
    still runs where only aura_strategic_rl is on the path."""

    @staticmethod
    def _module():
        return pytest.importorskip(
            'aura_simulation.dead_zone_publisher',
            reason='aura_simulation not on the path')

    def test_dead_zone_centre_is_the_scene_centre_not_the_trained_centre(self):
        """These are two different things and both are correct.

        The trained centre (120, -170) is the centre of the policy's 250 m
        clip disk and cannot move without retraining. The scene centre is
        where the damaged structures actually are, and that is what scenario
        content like dead zones should be placed around. They sit about 9 m
        apart, which is immaterial at this scale — but conflating them is how
        a hardcoded constant drifts from the world.
        """
        dz = self._module()
        bx_min, by_min, bx_max, by_max = scene.BBOX
        assert dz.DISASTER_CENTER_X == pytest.approx((bx_min + bx_max) / 2,
                                                     abs=0.1)
        assert dz.DISASTER_CENTER_Y == pytest.approx((by_min + by_max) / 2,
                                                     abs=0.1)
        offset = math.hypot(dz.DISASTER_CENTER_X - TRAINED_CENTER[0],
                            dz.DISASTER_CENTER_Y - TRAINED_CENTER[1])
        assert offset < 20.0, f'scene and trained centres {offset:.0f} m apart'

    def test_preset_zones_sit_on_real_structures(self):
        dz = self._module()
        known = scene.structure_xy()
        for key, zone in dz.PRESET_ZONES.items():
            nearest = min(math.hypot(zone.center_x - sx, zone.center_y - sy)
                          for sx, sy in known)
            assert nearest < 1.0, (
                f'{key} is {nearest:.0f} m from the nearest structure')

    def test_preset_zones_are_inside_the_coverage_grid(self):
        dz = self._module()
        x_min, y_min, x_max, y_max = grid_bounds(
            load_params(SIM_PARAMS, 'network_sim'))
        for key, zone in dz.PRESET_ZONES.items():
            assert x_min <= zone.center_x <= x_max, key
            assert y_min <= zone.center_y <= y_max, key

    def test_the_roam_box_stays_inside_the_coverage_grid(self):
        """A zone may roam to the edge of this box, so the box has to fit."""
        dz = self._module()
        x_min, y_min, x_max, y_max = grid_bounds(
            load_params(SIM_PARAMS, 'network_sim'))
        assert dz.ZONE_ROAM_X_MIN >= x_min
        assert dz.ZONE_ROAM_Y_MIN >= y_min
        assert dz.ZONE_ROAM_X_MAX <= x_max
        assert dz.ZONE_ROAM_Y_MAX <= y_max

    def test_the_spawn_box_fits_inside_the_roam_box(self):
        """Otherwise a freshly spawned zone starts out of bounds — which is
        exactly the state the old 90-degree bounce could not recover from."""
        dz = self._module()
        half = dz.ZONE_SPAWN_HALF_WIDTH_M
        assert dz.DISASTER_CENTER_X - half >= dz.ZONE_ROAM_X_MIN
        assert dz.DISASTER_CENTER_X + half <= dz.ZONE_ROAM_X_MAX
        assert dz.DISASTER_CENTER_Y - half >= dz.ZONE_ROAM_Y_MIN
        assert dz.DISASTER_CENTER_Y + half <= dz.ZONE_ROAM_Y_MAX

    def test_the_centre_is_the_scene_bounding_box_centre(self):
        dz = self._module()
        bx_min, by_min, bx_max, by_max = scene.BBOX
        assert dz.DISASTER_CENTER_X == pytest.approx((bx_min + bx_max) / 2,
                                                     abs=0.1)
        assert dz.DISASTER_CENTER_Y == pytest.approx((by_min + by_max) / 2,
                                                     abs=0.1)
