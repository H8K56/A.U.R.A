# LBFGS-Lite (vendored)

Header-only L-BFGS optimizer used by `src/trajectory_optimizer.cpp` for MINCO
trajectory optimization.

| | |
|---|---|
| Upstream | https://github.com/ZJU-FAST-Lab/LBFGS-Lite |
| Revision | `a96c50e3fdf8b5278577522a2c5e75766c8670bb` (2022-11-24) |
| License | MIT — see `LICENSE` |
| Source checksum | `dd7c69ab8d34f43deab02f9192012878` (md5 of upstream `include/lbfgs.hpp`) |

## Why this is vendored

`CMakeLists.txt` previously did `include_directories(/opt/LBFGS-Lite/include)`,
an absolute path that only existed inside the dev container. The package built
nowhere else — GitHub Actions failed with
`fatal error: lbfgs.hpp: No such file or directory`, and the first fix was to
make CI clone the library to that exact path, which is a workaround rather than
a fix.

The library is a single 32 KB header with no build step and no upstream releases
to pin against, so vendoring removes the external dependency outright instead of
making the path configurable.

## Local modifications

Only one: the MIT notice above was prepended to `include/lbfgs.hpp`. Upstream
ships the license in a separate `LICENSE` file and the header carries no banner,
but MIT requires the notice to travel with copies. The code is otherwise
byte-identical to the upstream revision named above.

## Updating

Replace `include/lbfgs.hpp` with the new upstream copy, re-apply the license
banner, and update the revision and checksum in this file.
