# PCSX-Redux capture

PCSX-Redux is a local debugger for retail PlayStation capture. It fills the
same role as DuckStation's GDB server for parked branches: stop at one PC,
read a few RAM words, and record registers. The emulator is not in this
repo. Install it on the machine that owns the disc.

Docs: [PCSX-Redux](https://pcsx-redux.consoledev.net/). Command line flags
are listed at [cli_flags](https://pcsx-redux.consoledev.net/cli_flags/).
Lua breakpoints are listed at
[breakpoints](https://pcsx-redux.consoledev.net/Lua/breakpoints/).

## Install

macOS ARM builds are on the dev channel:

https://distrib.app/pub/org/pcsx-redux/project/dev-macos-arm

Open the DMG and copy `PCSX-Redux.app` to `/Applications`. The binary is
`/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux`.

The published macOS app is not signed with a Developer ID certificate. If
Gatekeeper blocks it, clear the quarantine attribute and try again:

```
xattr -dr com.apple.quarantine /Applications/PCSX-Redux.app
```

If macOS still refuses the app, open System Settings, Privacy & Security,
and allow PCSX-Redux. Check the install with:

```
/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux -version
```

The copy checked on 2026-11-14 reported version `7637751d`, changeset
`7637751dc246876ee658e94825d9c91129fef820`, timestamp 2026-11-11 17:00:35.
That build is dev-channel build 443. A later download can differ.

## Portable config

Pass a directory that lives under `build/` so settings, memory cards, and
save states stay out of the home directory and out of git:

```
-portable build/research/pcsx/config
```

`-safe` resets that config to defaults for the run. `-portable` and
`-debugger` can still write into the portable directory. That directory is
under `build/`. Do not commit it.

## Scripts

`capture_at_pc.lua` sets an execution breakpoint. On each hit it reads the
PC and `ra`, `v0`, `v1`, and `a0`, plus the RAM words in its table, and
appends one JSON line. `gpu_beq_800883c4.lua` is the preset for PC
`0x800883c4` and the words at `0x800b76f0` and `0x800b76f4`.

The table at the top of `capture_at_pc.lua` is the default. These
environment variables replace fields when they are set:

| Variable | Meaning |
| --- | --- |
| `PCSX_PC` | Execution address (`0x` hex or decimal). |
| `PCSX_HITS` | Stop the emulator after this many hits. |
| `PCSX_RAM` | Comma-separated RAM addresses to read as little-endian words. |
| `PCSX_OUT` | Host path for the JSON lines. |

PCSX-Redux does not pass script arguments. `-exec` runs a Lua string.
`-dofile` loads a file. Use `-exec` with `dofile`, as in the example
below. Run from the repository root. The preset writes
`build/research/behavior/gpu-beq-800883c4.jsonl`. The generic script writes
`build/research/behavior/pcsx-capture.jsonl` unless `PCSX_OUT` is set.

Breakpoints fire only with `-debugger` and `-interpreter`. The preset
stops after one hit. `side` is `taken` when `v0` equals `v1`, and
`fall-through` otherwise. At this PC, `v0` is the low 6 bits of the first
word plus 1, and `v1` is the second word. When both words are 0, `v0` is 1
and `v1` is 0, so the expected side is fall-through. That matches the
DuckStation fast boot of the USA disc.

## Example

```
/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux \
  -portable build/research/pcsx/config \
  -safe -interpreter -debugger -fastboot -run -cli \
  -iso "$AM3D_DISC" \
  -exec "dofile('tools/pcsx/gpu_beq_800883c4.lua')"
```

Replace `$AM3D_DISC` with the cue path on the machine that owns the disc.
Output stays in `build/research/behavior/`. Do not commit game files, a
BIOS, or anything under `build/`.

## ALP1 movement observation

Row 8 retail compare procedure:
`docs/research/re/prototype-alp1-movement-observation.md`.

### Runbook script

From the repository root, with `AM3D_DISC` set to the USA cue path (or pass
the cue as the first argument):

```sh
export AM3D_DISC="/path/to/Army Men 3D (USA).cue"
sh tools/pcsx/run_alp1_observation.sh
```

The script creates `build/coordination/alp1-movement-observation/<run-id>/`
(UTC timestamp id), `session.txt`, `checklist.tsv` via
`tools/alp1_observation_checklist.py init`, portable config under
`<run-id>/pcsx-config`, and `frames/` for captures. It exports
`PCSX_ALP1_OUT=<run-id>/frames` and starts PCSX-Redux with `-interpreter
-debugger -run -iso`, portable config, and
`-exec "dofile('tools/pcsx/alp1_movement_observation.lua')"`. Fast boot stays
off. Nothing under `build/` is committed.

Checklist helpers (stdlib only):

```sh
python3 tools/alp1_observation_checklist.py validate \
  build/coordination/alp1-movement-observation/<run-id>
```

### Frame helper

`alp1_movement_observation.lua` listens for `GPU::Vsync` and writes
`frame-NNNNNN.ppm` every N blanks (default 60). Set `PCSX_ALP1_OUT` for the
directory and `PCSX_ALP1_EVERY` for N. The runbook sets `PCSX_ALP1_OUT`
automatically. The script does not press buttons or claim a movement match.
