# Plan

Agents read this roadmap. Edit it when the user asks for a roadmap change.
A normal gap change leaves it alone. Live function status belongs in the
progress ledger. Boot handoffs belong in AGENTS.md and the research notes.

## Goal

A public decomp of Army Men 3D, PlayStation USA release, serial SLUS-00491,
on Linux, macOS, and Windows. The goal is a portable program that reads a
disc the user owns and reproduces the supported retail behavior.

The repo ships our code and research facts. The user supplies the disc.
Game files, extracted assets, the executable, the Ghidra project, generated
assembly, and raw decompiled C stay local. This project is not affiliated
with 3DO. Follow [LEGAL.md](../LEGAL.md) and [AGENTS.md](../AGENTS.md).

## Current position

Updated November 13, 2026. The scaffold, disc tools, first function
inventory, progress ledger, and local compile-and-compare loop exist.
The loop passes a synthetic test. A display-fill function has our own
implementation and host tests. It is not connected to a GPU backend.
The launcher checks the disc and executable. It does not run the game.

The current export has 1,869 candidate functions. The ledger records one
implemented function and no verified functions. These are a dated snapshot,
not a completion percentage. Automatic function boundaries need review.
Use `python tools/progress.py` for current counts and evidence.
See [PROGRESS.md](PROGRESS.md).

The first retail compiler experiment did not match. Its candidate was
168 bytes against a 152-byte reference range. The game's compiler, flags,
and assembler remain unconfirmed. See the
[display-fill research note](research/re/call-80076274.md).

## Milestones

| Milestone | Status | Completion criteria |
| --- | --- | --- |
| Scaffold and local checks | Complete locally | Disc checks, Python tests, guard, CMake build, and host behavior tests pass. CI covers the three host systems. |
| First inventory and progress tracking | Complete as a baseline | Address/size/name export exists. A separate evidence ledger distinguishes research, implementation, and verification. Missing evidence does not advance status. |
| Local comparison loop | Complete for a synthetic case | Explicit local tools compile our fixture. Its expected bytes match. Commands, flags, and hashes are recorded locally. |
| Retail compiler calibration | In progress | Reviewed functions provide reproducible evidence for a useful compiler configuration. Mismatches and limits are documented. |
| PS1 platform layer | Not started | A selected backend supplies the display, input, disc, and timing interfaces needed by the first scene. |
| First running scene | Not started | A clean build reads the owner's disc, reaches the main loop, and displays one identified scene with documented retail comparisons. |
| First playable slice | Not started | One defined play sequence supports movement and its required game behavior, with reproducible checks. |

A configured CI matrix is not evidence of a successful remote run. Record
results when they are available. The optional research toolchain currently
has a tested macOS ARM64 setup. Other host toolchains need their own checks.

## 1. Calibrate against retail code

Keep the current synthetic test as a basic toolchain check. It does not
identify the retail toolchain. Continue with our own C for researched game
functions, following the boot path and note limits in AGENTS.md.

For each experiment:

1. Confirm the function's boundaries and contiguous comparison range.
2. Check types, structure offsets, and named SDK calls before changing flags.
3. Record compiler and adapter versions, assembler, flags, symbol placement,
   input hashes, and results.
4. Compare full intended ranges. Do not trim bytes, mask differences, or
   copy the reference into a candidate to produce a match.
5. Test cases with branches, memory access, and calls before making a claim
   about the original toolchain. One small match is insufficient.

The existing tools are described in [TOOLCHAIN.md](TOOLCHAIN.md) and
[COMPARE.md](COMPARE.md). The current compiler settings are experimental.
Stop after three failed attempts at the same problem. Report what changed,
what was learned, and what remains uncertain.

Matching is a research check. Portable code can differ in machine code.
A behavior verification record must state its method, scope, and limits.
A host unit test alone does not establish agreement with the retail game.

## 2. Reuse shared PS1 infrastructure

The runtime currently has no third-party libraries. Our Python tools use
the standard library. Optional local research tools are separate: Ghidra,
old GCC, maspsx, and an assembler are not shipped as runtime dependencies.
They are not required by the disc-free CI tests. Keep local downloads,
compiler output, and comparison reports under ignored build directories.

Evaluate shared tools and platform code before writing replacements:

| Reference | Work to evaluate |
| --- | --- |
| [SOTN decomp](https://github.com/Xeeynamo/sotn-decomp) | Function selection, shared type context, duplicate detection, and comparison workflow. |
| [Spyro 1 decomp](https://github.com/TheMobyCollective/spyro-1) | PS1 build layout and overlay organization where our disc evidence supports it. |
| [splat](https://github.com/ethteck/splat) | Local code/data splitting and symbol maps. |
| [PsyCross](https://github.com/OpenDriver2/PsyCross) | A possible PS1 platform backend. Test the required interfaces and its dependencies first. |
| [ghidra_psx_ldr](https://github.com/lab313ru/ghidra_psx_ldr) | PS1 and GTE analysis support. |
| [PCSX-Redux](https://github.com/pcsx-redux/pcsx-redux) | Local retail debugging and behavior observations. |

These are evaluation leads, not adopted dependencies. Select only what
removes demonstrated work. Record the selected revision, files, license,
attribution, dependencies, and supported interfaces before importing code.
Keep our GPL-3.0-or-later terms and upstream notices explicit. Do not import
another game's reconstructed logic as Army Men behavior. Keep SDK signature
leads separate from confirmed names and implementations.

Choose the platform backend in a separate focused change. Document any
runtime dependencies and update the build instructions with that choice.
First prove a small display and input example on the supported host systems.
Check sound and movie needs against the actual disc before expanding scope.

## 3. Reach the first scene

Follow the actual boot path. Reuse the named-call rule instead of tracing
SDK bodies again. Grow shared types and prototypes from cited evidence.
Look for duplicates before implementing another function. Consider a local
one-command task preparation tool only when it removes repeated setup.

Connect the required startup state, display packet submission, disc reads,
timing, and controller interfaces. Choose one identified scene as the
milestone. Its assets must come from the owner's disc. Do not assume its
file formats or overlay layout from another game.

The milestone is complete when a fresh local build can load that scene,
reach the main loop, and produce a documented display result. Include a
repeatable input sequence and comparisons with the retail game. Keep local
captures and traces out of the public tree when they contain game data.

## 4. Build one playable slice

After the first scene works, choose one bounded play sequence. Implement
its required movement, camera, collision, and game rules one gap at a time.
Define the sequence before broadening it. Record retail comparisons for
observable behavior and tests for the reconstructed calculations.

Keyboard play, a server browser, and mods stay later milestones. They are
intentional differences from the PlayStation game. They do not block the
first scene or the first controller-driven play sequence. See
[deviations.md](research/re/deviations.md).

## How a gap is closed

1. Run `python tools/gaps.py` and `python tools/progress.py`.
2. Pick one code gap or an uncited function from the exported inventory.
   Follow AGENTS.md for the current boot path and note boundaries.
3. Read the local executable. Generated C stays under `build/ghidra/`.
4. Write our code and a research note that cites the address.
5. Add suitable checks. Update the ledger with the evidence for its actual
   status. A citation is not an implementation. A partial block note does
   not establish a whole function.
6. Run the relevant checks and `python tools/pr_guard.py`.

Preserve existing block notes. For a named SDK or BIOS call, record the
name, arguments, and return address without entering its body. For an
unnamed call, the next note follows the callee. The exact rules stay in
AGENTS.md. Ask before any GitHub issue, pull request, or push.

## Checks

The public checks need no disc, Ghidra, or original-era compiler:

```
python -m unittest discover -s tests
python tools/progress.py
python tools/pr_guard.py
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Use synthetic inputs in public tests. Do not weaken the guard. Local disc,
Ghidra, compiler, and retail behavior checks supplement these checks.
They do not run against uploaded game files or game data in CI.
