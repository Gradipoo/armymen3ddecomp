# R06 result: Capture blocked, evidence protocol drafted

Date: November 13, 2026. Outcome: Blocked for emulator capture. The evidence
schema and proposed protocol are drafted. Reviewed by the research
coordinator on the same date.
Host: macOS 27.2.1 ARM64, Python 3.15.2. No capture ran.

## Local discovery

No PCSX-Redux executable was found on PATH or in the checked application,
Homebrew, and project build locations. The search inspected relevant
directory names one level deep. It did not scan unrelated personal files.

DuckStation is installed. Its bundle reports `0.1-11894-gc66b2694d`.
That version identifies upstream commit
[`c66b2694da65cece8886ed3d4a069098831f8358`](https://github.com/stenzek/duckstation/commit/c66b2694da65cece8886ed3d4a069098831f8358).
The executable hash was recorded locally. A reproducible build from that
commit was not verified.

The pinned [command parser](https://github.com/stenzek/duckstation/blob/c66b2694da65cece8886ed3d4a069098831f8358/src/duckstation-qt/qthost.cpp)
documents `-help` and `-version`. Both initially aborted with signal 6
under restricted execution. Their logs report unavailable macOS pasteboard
and HIServices connections. Root identified the same environment issue in
an earlier display test and authorized a desktop-access retry of these
information commands only. Both then printed their complete output.
The runtime identity is `0.1-11894-gc66b2694d (dev)`. This build returns
exit 1 after printing help or version, as its source parser specifies.
No boot filename, resume option or save state was supplied.

The bundled Qt platform directory contains only the Cocoa plugin. It has
no minimal or offscreen plugin. Qt documents those as separate platform
plugins, so an offscreen retry without that dependency was not attempted.
See the [Qt platform description](https://doc.qt.io/qt-6/qguiapplication.html#platformName-prop).
Desktop access resolved the information-command startup issue. The first
failures do not establish an emulator capability or accuracy problem.

| Problem | Attempts | Actual result |
| --- | --- | --- |
| Discover PCSX-Redux in relevant local locations | 1 | Not found |
| Run DuckStation information commands under restricted execution | 2 | Both aborted before help output |
| Repeat those commands with desktop access | 2 | Complete help and version output |
| Discover bundled headless Qt platform support | 1 | No minimal or offscreen plugin |
| Capture a synthetic executable | 0 | Blocked |

PCSX-Redux is absent. DuckStation's information path works, but an isolated
capture configuration, an explicit firmware identity and a tested guest
debugger connection have not been established for it. Its installed help
does not expose a separate user-directory or GDB-enable option. The pinned
[debug settings source](https://github.com/stenzek/duckstation/blob/c66b2694da65cece8886ed3d4a069098831f8358/src/duckstation-qt/debuggingsettingswidget.cpp)
instead uses `Debug.EnableGDBServer` and a configured port. Its
[server source](https://github.com/stenzek/duckstation/blob/c66b2694da65cece8886ed3d4a069098831f8358/src/core/gdb_server.cpp)
binds to loopback. Neither the setting nor a connection was tested here.

The pinned [README](https://github.com/stenzek/duckstation/blob/c66b2694da65cece8886ed3d4a069098831f8358/README.md)
requires a BIOS and describes portable configuration next to the executable.
BIOS availability remains unknown because personal emulator data was not
searched. No task-local firmware or portable configuration was selected.
Those are the precise missing capture prerequisites. No emulator, platform
plugin, BIOS or other package was installed. No guest executable, firmware,
game, save state or memory card was loaded. The next capture batch must
coordinate isolation without changing the installed app or personal settings.

## Source and license checks

The checked PCSX-Redux source snapshot is
[`1fdcd0625278590e5e09753aee85b23de3e16f3c`](https://github.com/pcsx-redux/pcsx-redux/tree/1fdcd0625278590e5e09753aee85b23de3e16f3c).
Its root [license contains GPL version 2](https://github.com/pcsx-redux/pcsx-redux/blob/1fdcd0625278590e5e09753aee85b23de3e16f3c/LICENSE).
Selected component notices still need review before code import.
The installed DuckStation revision's
[license is CC BY-NC-ND 4.0](https://github.com/stenzek/duckstation/blob/c66b2694da65cece8886ed3d4a069098831f8358/LICENSE).
Neither source nor binary was copied into the runtime or redistributed.
Both remain external tool candidates.

The PCSX-Redux [CLI documentation](https://pcsx-redux.consoledev.net/cli_flags/)
offers portable configuration, interpreter mode, debugger activation, local
Lua scripts and test mode. Several flags change saved settings. A future
trial must use its own portable directory and explicit configuration.
No documented PCSX-Redux command was executed here.

Its [breakpoint API](https://pcsx-redux.consoledev.net/Lua/breakpoints/)
requires active debugging and interpreter execution. Breakpoint objects
must remain referenced. The proposed capture should record callback errors
and exact hit counts rather than accepting missing output as a pass.
Its [memory API](https://pcsx-redux.consoledev.net/Lua/memory-and-registers/)
can read registers and bounded memory through `getMemoryAsFile()`. Register
writes can alter pending load or branch state. Prefer observation of a
natural entry over injecting registers during execution.
Its [binary loader](https://pcsx-redux.consoledev.net/Lua/binary/)
can obtain entry, GP and SP metadata from supported executable formats.
These are documented leads, not tested integration results.

## Proposed evidence record

The local draft schema and proposal cover:

| Record | Required evidence |
| --- | --- |
| Claim and scope | One bounded observable claim; synthetic or retail; explicit coverage limits |
| Tool | Installed identity, source revision, executable hash, CPU mode, renderer and host |
| Configuration | Exact command argument lists, configuration hash and capture-script hash |
| Image and load map | EXE hash, actual loaded ranges, entry, GP, SP and any overlays |
| Firmware | Owned BIOS or OpenBIOS identity and hash, plus boot method |
| Initialization | Fresh process, reset method, RAM/register initialization and device state |
| Inputs | Exact event order with guest instruction, cycle or frame coordinates |
| Entry and exit | PCs or predicates, hit counts, return handling and delay-slot convention |
| Budgets | Instruction and wall-time limits, exceptions and missing-event failures |
| Observations | Registers, bounded memory bytes, device state, outputs and call counts |
| Artifacts | Local file names and hashes for the actual observations |
| Repeat comparison | Fresh-run pair, deliberately changed input, expected change and first difference |
| Limits | Unknown state, timing assumptions, field exclusions with evidence and emulator limits |
| Attempts | Per-problem counts, exact commands, exits and retained logs |

The proposal is explicitly marked `proposal`, with unknown identities and
empty observation fields. It cannot serve as a capture record. JSON parsing
and required-field coverage checks passed. Formal JSON Schema validation
and runtime capture validation were not run. No baseline or candidate
capture timings, speed gain, or retail quality improvement was measured.

## Proposed synthetic protocol

1. Select an installed local debugger build and an explicit firmware
   identity. Create a fresh task-local configuration. Keep memory cards,
   saves and network services isolated or disabled. Record all settings.
2. Write an original small synthetic program. It initializes its working
   registers, inputs, output buffer and surrounding canaries, performs a
   bounded calculation, then reaches a dedicated completion sentinel.
   Record the complete load map and independent expected arithmetic.
3. Cold-start a new emulator process. Observe the program's entry and
   completion sentinel. Retain exact registers, bounded memory and event
   counts. Treat timeouts, exceptions and missing hits as failures.
4. Repeat from another fresh initialization with identical inputs. Compare
   the actual recorded values and bytes. Locate the first difference if
   they disagree; a checksum alone cannot explain it.
5. Change one defined input and cold-start again. Require the independently
   predicted output change, stable canaries and the expected call counts.
   A repeated constant output is not sufficient evidence of working capture.

No synthetic executable or capture script was built or run in this task.
The local command proposal contains unresolved placeholders and is marked
not run. It must not be executed before real dependencies replace them.

## Later retail protocol

A separate one-gap assignment must choose the researched function and its
claim. Follow natural boot and a recorded input sequence. Define a normal
case, a supported boundary case, and a failure or zero-work case where the
behavior actually supplies one. Mark an inapplicable case explicitly.
Do not invent reachability or alter arguments to manufacture a retail case.

Preserve raw guest pointer values and their load-map bindings. A portable
implementation may need an explicit guest-address mapping for comparison.
Do not silently strip pointer bits or normalize unexplained differences.
Capture every relevant pre-state byte. Unknown or uninitialized state can
invalidate repeatability and must remain a stated limit.

Record pending interrupts, DMA, timers and device state. Graphics checks
need the relevant prior VRAM and packet state. Observe named SDK calls
from caller sites and return sites without inspecting their bodies. State
whether breakpoints or interception changed timing. Reusing a save state
requires evidence that it includes all state the claim depends on.

The later result must state tested inputs and observable agreement. A host
unit test, SDL synthetic image or exporter round trip cannot replace that
record. An emulator may share an incorrect assumption with our code, so
emulator agreement alone has limits. No game status was advanced here.

## Retained evidence and checks

All artifacts stay under `build/research/behavior/`: `discovery.json`, the
two failed and two successful information-command logs, command records, platform
plugin names, `source-review.json`, `evidence-schema.json`,
`protocol-proposal.json`, `schema-check.json`, and `manifest.json`.
They retain local identities, hashes, commands, elapsed times and limits.
The source review separates documented candidate commands from executed
commands. No raw retail bytes or trace were collected.

`tools/progress.py` and the guard passed. The guard was run again after
this report. The safe repeat commands perform discovery and proposal
checks only; the discovery helper no longer launches the failed probes:

```
python3 build/research/behavior/discover_tools.py
python3 build/research/behavior/prepare_protocol.py
python3 tools/progress.py
python3 tools/pr_guard.py
```

The next batch can evaluate the installed DuckStation debugger after its
isolated configuration, firmware and guest connection are selected. PCSX-Redux
remains an uninstalled alternative. Recheck the actual capture API against
the chosen installed build before using the proposed protocol. Keep the
capture phase Blocked until a run produces the required observations.

The coordinator checked all retained artifact hashes, the information-only
command flags, the successful desktop-access output and expected exit codes,
and the proposal marker and required-field coverage. The records confirm
zero captures. No formal schema validation or runtime information-command
repeat was added by this review. The local `review/` folder retains the
review. Missing capture prerequisites remain distinct from an emulator
capability or accuracy finding.
