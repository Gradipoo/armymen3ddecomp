# Projects to reuse

Use established tools where they remove demonstrated work. This list is
research, not a claim that every candidate has been integrated. Pin and
check each tool before adoption. Our own Python wrappers remain standard
library only. Optional analysis tools can use an isolated local environment.
Keep generated C, assembly, target objects, and tool caches under `build/`.

## Analysis tools and next trials

Current local pins and installation provenance are in
[ANALYSIS.md](ANALYSIS.md) and [analysis-tools.json](analysis-tools.json).
spimdisasm, splat and m2c are installed in an isolated local environment.
Installation alone does not complete the adoption checks below.

| Priority | Project | What it adds here | Adoption check |
| --- | --- | --- | --- |
| 1 | [spimdisasm](https://github.com/Decompollaborate/spimdisasm) with [splat](https://github.com/ethteck/splat) | MIPS I and PS1 GTE disassembly, symbol pairing, section analysis, and local assembly suitable for other tools. | One reviewed 104-byte range rebuilt exactly with spimdisasm 1.42.4. This checks exporter fidelity. splat 0.50.1 has no established full-game segment map here. Keep code/data boundaries provisional. |
| 2 | [m2c](https://github.com/matt-kempster/m2c) | A second C draft with shared type context. It can help identify where a Ghidra draft lacks useful types. | Local preparation runs the pinned revision. [R01](workers/results/shared-context.md) resolved two synthetic fields with correct context. Wrong context exited without a warning. No speed gain was measured. Keep drafts local and write our code separately. Its little-endian GCC mode is an analysis choice, not a retail compiler finding. |
| 3 | [asm-differ](https://github.com/simonlindholm/asm-differ) or [objdiff](https://github.com/encounter/objdiff) | An instruction-level view of differences. | [R04](workers/results/mismatch-viewer.md) passed six synthetic object views with native objdiff 3.8.3. asm-differ's raw and ELF paths failed with this host's LLVM objdump arguments. Scheduling and review speed remain unmeasured. Preserve our full-range exact check. A 100% object score can still contain unresolved relocations. |
| 4 | [psy-q-decomp](https://github.com/sozud/psy-q-decomp) | SDK research and API/type information. | Its documented current target is Psy-Q 3.5. Confirm the relevant version and function before applying a conclusion. Do not fetch or redistribute SDK archives. |
| Later | [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) | Search among equivalent source forms when a candidate is understood and the compiler setup is useful. | Do not use it to bypass the three-attempt stop or an unknown toolchain. Do not use its distributed mode with retail data. |

The reviewed repository license declarations are MIT for spimdisasm and
splat, GPL-3.0-only for m2c, Unlicense for asm-differ, MIT or Apache-2.0 for
objdiff, and MIT for psy-q-decomp. Review selected
files and dependencies before importing code. A repository declaration
does not authorize copying proprietary SDK archives or game assets.

Use these as local tools first. We do not need another game's gameplay,
AI, collision, or structures unless Army Men evidence supports the same
behavior or layout.

## Game projects worth studying

[SOTN](https://github.com/Xeeynamo/sotn-decomp) provides a useful function
selection and comparison workflow. Check duplicates before starting a
function and grow shared context from confirmed types.
Its [local preparation helper](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/decompile.py)
combines context and m2c. Its source-injection and upload actions do not
fit this repo's local-draft workflow. Its
[duplicate finder](https://github.com/Xeeynamo/sotn-decomp/blob/b2350ec342ea498d0b838fdd19b6ed2dddc2595a/tools/dups/src/main.rs)
uses opcode-derived similarity leads. Those leads still need boundary
and behavior checks. No code was imported from these helpers.

[Spyro 1](https://github.com/TheMobyCollective/spyro-1) is a useful reference
for build layout, linker organization, and overlays. Army Men's layout
must still come from its own executable and disc.

[Breath of Fire III](https://github.com/loopyd/bof3-decompilation)
prepares one function with a local brief and names Psy-Q calls before
anyone writes C. `tools/boot_slice.py` takes that shape for the boot note.

[BattleTanx: Global Assault (PlayStation)](https://github.com/TheGh0stShip/BattleTanx-Global-Assault-PS1)
is a matching decomp of another 3DO PS1 game (SLUS-01044). Its speed is
a segment map plus a compiler that already matches. Our compiler is still
unconfirmed. Do not import its game code.

[3dokit](https://github.com/vs-sr-dev/3dokit) and the
[Road Rash 3DO decomp](https://github.com/trapexit/3do-decomp-road-rash)
target the 3DO's ARM60 and Portfolio OS.
[Army Men (1998) source](https://github.com/OnyeNacho/ArmyMen) is a
different game. [army-men-3do](https://github.com/tminard/army-men-3do)
notes 3DO disc files. None of that code belongs in this tree.

[REDRIVER2](https://github.com/OpenDriver2/REDRIVER2) shows a PS1 platform
boundary in a native port. Its README also describes the use of debug
symbols. Look for symbols in our owned disc and supported builds before
assuming that all names and types must be recovered manually. Shared
platform practice is the useful part; Driver's game logic is not Army Men.

## Current reuse

Old GCC and maspsx are pinned local tools. See [TOOLCHAIN.md](TOOLCHAIN.md).
The optional host display/input implementation uses the SDL2 API. See
[PLATFORM.md](PLATFORM.md). No other game's reconstructed logic has been
imported for these steps.

PsyCross was evaluated at a pinned revision. Three local build attempts
failed, and its parser did not implement our needed fill primitive. It has
not been adopted as the runtime. Its evaluation and limits are recorded
in [PLATFORM.md](PLATFORM.md).

The concrete experiment queue and adoption decisions are in
[RESEARCH.md](RESEARCH.md) and [WORKERS.md](WORKERS.md). A Pending worker
task is not an executed trial. Tooling checks do not close a game gap.
