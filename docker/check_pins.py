#!/usr/bin/env python3
"""Verify the Dockerfile's ARG defaults match versions.env.

The Dockerfile carries defaults so a plain `docker build` still produces the
pinned stack, while versions.env is the documented place to read or override
them. Two copies of a version is exactly the drift this pinning exists to stop,
so CI fails if they disagree.

Usage:  python3 docker/check_pins.py
"""

import pathlib
import re
import sys

HERE = pathlib.Path(__file__).resolve().parent

# versions.env keys that are not Dockerfile ARGs (documentation only).
NOT_ARGS = {'UBUNTU_VERSION', 'ROS_DISTRO', 'GAZEBO_VERSION'}


def read_versions_env(path):
    pins = {}
    for line in path.read_text().splitlines():
        line = line.split('#', 1)[0].strip()
        if not line or '=' not in line:
            continue
        key, value = line.split('=', 1)
        pins[key.strip()] = value.strip()
    return pins


def read_dockerfile_args(path):
    args = {}
    for match in re.finditer(r'^ARG\s+([A-Z0-9_]+)=(\S+)\s*$',
                             path.read_text(), re.MULTILINE):
        args[match.group(1)] = match.group(2)
    return args


def main():
    versions = read_versions_env(HERE / 'versions.env')
    args = read_dockerfile_args(HERE / 'Dockerfile')

    problems = []
    for key, value in sorted(versions.items()):
        if key in NOT_ARGS:
            continue
        if key not in args:
            problems.append(f"{key}: in versions.env but not an ARG in Dockerfile")
        elif args[key] != value:
            problems.append(
                f"{key}: versions.env has {value!r}, Dockerfile ARG has {args[key]!r}")

    for key in sorted(args):
        if key in ('USER_ID', 'GROUP_ID'):
            continue
        if key not in versions:
            problems.append(f"{key}: Dockerfile ARG has no entry in versions.env")

    if problems:
        print("Pinned versions disagree:", file=sys.stderr)
        for p in problems:
            print(f"  - {p}", file=sys.stderr)
        return 1

    checked = len([k for k in versions if k not in NOT_ARGS])
    print(f"OK — {checked} pinned versions agree between "
          f"versions.env and Dockerfile.")
    return 0


if __name__ == '__main__':
    sys.exit(main())
