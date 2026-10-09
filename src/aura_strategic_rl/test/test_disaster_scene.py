#!/usr/bin/env python3
"""The committed disaster scene must still match the Gazebo world.

`disaster_scene.py` is generated from `worlds/earthquake_city.world` by
`scripts/generate_disaster_scene.py`. Generated code that nobody re-derives is
just hand-maintained code with a misleading header, so this re-runs the
derivation and compares.

It exists because the scene previously lived in three places that disagreed:
the world (29 damaged structures), `SwarmGymEnv._DISASTER_STRUCTURES` (17, by
hand) and the coverage grid bounds in two YAML files. The importance map — and
therefore the reward — was built from a reactor-free subset of the disaster
for as long as nobody checked.

Runs without ROS.
"""

import importlib.util
import math
import pathlib

import pytest

from aura_strategic_rl import disaster_scene as scene

REPO = pathlib.Path(__file__).resolve().parents[3]
GENERATOR = REPO / 'scripts/generate_disaster_scene.py'


@pytest.fixture(scope='module')
def generator():
    """Load the generator script directly; scripts/ is not an importable package."""
    if not GENERATOR.exists():
        pytest.skip(f'{GENERATOR} not present')
    spec = importlib.util.spec_from_file_location('gen_disaster_scene',
                                                  GENERATOR)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


@pytest.fixture(scope='module')
def derived(generator):
    path = generator.world_path(scene.WORLD)
    if not path.exists():
        pytest.skip(f'{path} not present (world files are repo-root, not installed)')
    return generator.parse_structures(path)


class TestTheCommittedModuleIsCurrent:

    def test_structure_list_matches_the_world(self, derived):
        assert scene.STRUCTURES == derived

    def test_structure_count_matches(self, derived):
        assert len(scene.STRUCTURES) == len(derived)

    def test_bbox_matches_the_world(self, generator, derived):
        assert scene.BBOX == generator.bbox(derived)

    def test_grid_bounds_match_the_world(self, generator, derived):
        assert scene.GRID_BOUNDS == generator.grid_bounds(derived)

    def test_the_rendered_file_is_byte_identical(self, generator, derived):
        """The strongest form: regenerating must be a no-op. Catches drift the
        field-by-field checks above would miss, like a changed comment."""
        rendered = generator.render(scene.WORLD, derived)
        committed = (REPO / 'src/aura_strategic_rl/aura_strategic_rl'
                     / 'disaster_scene.py').read_text()
        assert committed == rendered, (
            'disaster_scene.py is stale — run '
            'python3 scripts/generate_disaster_scene.py')

    def test_check_mode_reports_up_to_date(self, generator):
        """The same check the generator offers for CI."""
        assert generator.main(['--check']) == 0


class TestTheSceneIsWellFormed:

    def test_there_are_structures(self):
        assert len(scene.STRUCTURES) > 0

    def test_names_are_unique(self):
        names = [name for name, _, _ in scene.STRUCTURES]
        assert len(names) == len(set(names))

    def test_no_scenery_leaked_in(self):
        """The terrain heightmap and the launch pad are not damaged structures;
        including them would drag the grid and the importance map toward the
        origin, which is the fault this whole exercise was about."""
        names = {name for name, _, _ in scene.STRUCTURES}
        assert not names & {'simple_baylands', 'ground_plane', 'sun',
                            'launch_pad', 'h_marker'}

    def test_bbox_actually_bounds_the_structures(self):
        x_min, y_min, x_max, y_max = scene.BBOX
        for name, sx, sy in scene.STRUCTURES:
            assert x_min <= sx <= x_max, name
            assert y_min <= sy <= y_max, name

    def test_grid_bounds_contain_the_bbox_with_margin(self):
        gx_min, gy_min, gx_max, gy_max = scene.GRID_BOUNDS
        bx_min, by_min, bx_max, by_max = scene.BBOX
        margin = scene.IMPORTANCE_RADIUS_M
        assert bx_min - gx_min >= margin
        assert by_min - gy_min >= margin
        assert gx_max - bx_max >= margin
        assert gy_max - by_max >= margin

    def test_grid_bounds_are_whole_cells(self):
        gx_min, gy_min, gx_max, gy_max = scene.GRID_BOUNDS
        res = scene.GRID_RESOLUTION_M
        assert (gx_max - gx_min) % res == 0.0
        assert (gy_max - gy_min) % res == 0.0

    def test_structure_xy_drops_only_the_names(self):
        assert scene.structure_xy() == [(x, y) for _, x, y in scene.STRUCTURES]

    def test_the_scene_is_not_square(self):
        """Worth asserting, because a square grid was the obvious wrong answer:
        the scene is markedly wider than it is tall, and coverage % is a
        fraction of cells, so squaring it off dilutes every figure."""
        x_min, y_min, x_max, y_max = scene.BBOX
        width, height = x_max - x_min, y_max - y_min
        assert width > 1.5 * height


class TestTheSceneIsTheDisasterWeDocument:
    """README's "Disaster World" section describes this scene; these keep the
    prose and the world from drifting apart."""

    def test_extent_matches_the_documented_450_by_260_m(self):
        x_min, y_min, x_max, y_max = scene.BBOX
        assert (x_max - x_min) == pytest.approx(450.0, abs=5.0)
        assert (y_max - y_min) == pytest.approx(260.0, abs=5.0)

    def test_the_documented_structure_families_are_present(self):
        names = [name for name, _, _ in scene.STRUCTURES]

        def count(prefix):
            return sum(1 for n in names
                       if n == prefix or n.startswith(prefix + '_'))

        assert count('collapsed_house') == 12
        assert count('collapsed_industrial') == 7
        assert count('collapsed_police_station') == 2
        assert count('radio_tower') == 3
        assert count('water_tower') == 2
        assert count('school') == 1
        assert count('reactor') == 1
        assert count('playground') == 1

    def test_every_structure_is_south_of_the_launch_pad(self):
        """The pad is at the origin and the city is laid out south of it, which
        is why an origin-centred grid wasted half its area on empty ground."""
        assert all(sy < 0.0 for _, _, sy in scene.STRUCTURES)

    def test_the_scene_sits_east_and_south_of_the_origin(self):
        centre_x = (scene.BBOX[0] + scene.BBOX[2]) / 2
        centre_y = (scene.BBOX[1] + scene.BBOX[3]) / 2
        assert math.hypot(centre_x, centre_y) > 150.0
