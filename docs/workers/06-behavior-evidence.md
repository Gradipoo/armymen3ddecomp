# R06: Trustworthy behavior evidence

Status: Discovery and protocol proposal reviewed November 13, 2026.
Capture prerequisites remain open. No synthetic or retail capture ran.
See the [result](results/behavior-evidence.md).

## Question and scope

Can an existing local debugger capture a small repeatable input/output
observation with enough state to explain its limits? Evaluate the local
[PCSX-Redux debugging tools](https://pcsx-redux.consoledev.net/). Retail PC capture scripts for that emulator are in [tools/pcsx/](../../tools/pcsx/README.md). Do not
write a replacement emulator. This task prepares the method. A later
one-gap assignment must choose the game function and claim.

Permitted public file: `docs/workers/results/behavior-evidence.md`.
Permitted local directory: `build/research/behavior/`.
No game source, research block notes, platform code or ledger changes.
Read `docs/WORKERS.md`.

## Inputs and commands

```
python3 tools/progress.py
python3 tools/pr_guard.py
```

Discover an existing local debugger first. Pin its actual source revision
or installed build identity and verify its license. Save `--help`, supported
local debugger commands, and the actual capture command lists in the
manifest. If it is absent, report Blocked for the capture phase. Do not
install a whole emulator or BIOS under this task without coordinating scope.
No browser emulator or external upload is part of this trial.

## Acceptance and evidence

Draft an evidence schema covering EXE hash and load map, debugger revision,
BIOS identity, initialization, deterministic input sequence, entry/exit
conditions, arguments, memory ranges, output observations, call count,
interrupt/timing assumptions, and expected limits. Keep hashes and raw
capture data local. Explain how pointer values and uninitialized memory
affect repeatability.

Use an original synthetic executable for the capture check if the installed
debugger supports it. Run twice from a fresh initialization. The recorded
observations must agree; deliberately alter one input and detect the
expected change. A checksum alone cannot locate an unexplained difference.

Specify a later retail protocol with at least a normal input, boundary
case and failure or zero-work case where they exist. It must state the
claimed scope and observable behavior. Do not inspect a named SDK body.
Do not report the SDL synthetic display as a retail capture or a running
game scene. Do not call a function verified from host tests alone.

## Known failure modes

Save states can omit host or device state. GPU output can depend on prior
VRAM contents. Intercepting a call can change timing. An emulator can share
a mistaken assumption with our implementation. Report these limits and
retain enough local state to repeat the observation.
