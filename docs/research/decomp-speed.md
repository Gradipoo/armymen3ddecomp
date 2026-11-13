# Decomp speed

## Goal

Make one pass of the note loop cheaper. The loop lists gaps, names a jal, and slices the next instructions. Listing uncited functions was the slow step. Matching SDK patterns was the next cost. The 64-instruction slice was already smaller than process startup.

## Cite each address once

This comes from splat (`symbol_addrs.txt` in ethteck/splat). A name is an address lookup. The gap list was searching the whole research text once per function.

Files: `tools/gaps.py`, `tests/test_gaps.py`.

Steps:

1. Read the citation text once.
2. Collect every run of 8 hex digits, including overlaps.
3. Test each function address against that set.
4. Print the same lines in the same order.

We will know it is faster when `python3 tools/gaps.py` on this tree has a lower median time and the same output.

## Match a pattern with a byte search

This comes from Psy-Q signature scans (`lab313ru/psx_psyq_signatures`) and Ghidra FLIRT. Those tools search for a known byte string, then keep the hits on their alignment rule. Our matcher walked every word in Python and compared every pattern.

Files: `tools/sdk_match.py`, `tests/test_sdk_match.py`.

Steps:

1. Search each pattern with the standard byte search.
2. Keep a hit only when it starts on a 4-byte boundary.
3. Emit hits in address order. At one address, keep pattern-table order.

We will know it is faster when `python3 tools/sdk_match.py` on the local PS-X EXE has a lower median time and the same output.

## How we will know

Time each command five times after one warm run. Use the median. Save the output first. After the change, the median must be lower and the output must match. `python3 tools/pr_guard.py` must pass. The gap tests and the SDK match tests must pass.

## What we will not adopt

- decomp.me. It uploads the function. Retail bytes stay on this machine.
- decomp-permuter. The compiler is not known. It does not list gaps or name a jal. Its distributed mode can send retail data.
- splat, spimdisasm, and m2c as new dependencies. They are already optional local tools. Installing them again does not speed this loop. m2c context caching was already measured here and was not faster.
- asm-differ and objdiff. They show a mismatch after a compile. They do not list gaps or name the next jal. An earlier local check found no review speedup.
- Ghidra headless scripts and ghidra_psx_ldr. Ghidra is optional. This change does not run the importer.
- A new package such as pyahocorasick. The standard library search is enough.

## Not done

The 64-instruction slice stays as it is. `tools/entry_disasm.py` already stops at the first branch, and that work is smaller than process startup. Changing the stop rule would be a behavior change, not a measured speedup. A one-address name flag on `sdk_match.py` is also not done. The full pattern command is the one this loop already runs, and the byte search speeds that command.

## Result

Measured November 13, 2026. Five runs after one warm run. The number is the median.

`python3 tools/gaps.py` went from 0.372s to 0.054s. On the tree at the end of the change, the new address set listed the same 1,835 uncited functions as the old per-address search. A saved before and after printout differed where another worker added citations during the run.

`python3 tools/sdk_match.py` on the local PS-X EXE went from 0.067s to 0.031s. The printed lines matched.

`python3 tools/pr_guard.py` passed. `tests.test_gaps`, `tests.test_sdk_match`, and `tests.test_pr_guard` passed (17 tests).

`tools/entry_disasm.py` was not changed. Its median stayed about 0.031s.

## One slice per note

The remaining cost was the note, not the scanners. `entry_disasm.py` stops at the first branch or jump. A boot note is allowed to continue through named calls until an unnamed call, `jr`, or 64 instructions.

This comes from the PS1 projects that prepare one function with one local command. Breath of Fire III (`loopyd/bof3-decompilation`) names Psy-Q calls and writes a one-function brief. SOTN's `tools/decompile.py` prepares one function locally. The upload and source-injection actions in that helper stay unused.

BattleTanx: Global Assault for PlayStation (`TheGh0stShip/BattleTanx-Global-Assault-PS1`, SLUS-01044, another 3DO game) gets its speed from a full segment map, SDK signature proposals, and a compiler that already matches. This repo's compiler is still unconfirmed, so that path is not open. No code was copied from that project.

The 3DO console ports (`vs-sr-dev/3dokit`, `trapexit/3do-decomp-road-rash`) recompile ARM60 or retarget the 3DO devkit. Army Men 3D is MIPS. `OnyeNacho/ArmyMen` is source for the 1998 PC game, a different program. `tminard/army-men-3do` notes 3DO disc files. None of that source was imported.

Files: `tools/boot_slice.py`, `tests/test_boot_slice.py`.

The command is `python3 tools/boot_slice.py EXE --start ADDRESS`. It writes `build/boot-slice.txt`. A target is named from `tools/sdk_names.txt`, a `tools/sdk_patterns.txt` hit, BIOS A/B/C (`0xa0`, `0xb0`, `0xc0`), or an existing `docs/research/re/call-ADDRESS.md`. Named calls keep immediate register values from `lui`, `addiu`, `ori`, and the other ALU forms the tool tracks. An existing call note is not entered again, including when that note stopped early.

Checked November 13, 2026 on the local PS-X EXE. `--start 0x800253b0` reported 17 instructions and the same unnamed call the note already records: `jal` `0x8007e130`, `a0` `0x100`, `a1` `0x78`, return `0x800253f4`.

## Follow a known branch

m2c and the other matching decompilers fold a compare when both sides are known, then keep only that path. Pictochat's duplicate pass (`tangOS-decomps/pictochat-decomp`, `tools/find_duplicates.py`) is the other popular speedup. This repo already has `tools/research_duplicates.py` for that, and a short Ghidra size can fake a duplicate, so that tool stays a lead list.

`tools/boot_slice.py` now follows `beq`, `bne`, `blez`, `bgtz`, `bltz`, and `bgez` when the compared registers are known. A word store of a known value is kept. A later `lw` of that address reuses it and marks the argument `mem`. `word_fill` and `bzero` drop tracked words in their destination range. Any other skipped call leaves the stored words in place, so a loaded argument still needs a check that the callee did not write that address.

An unknown compare still stops. The taken side is not guessed.

## Longer local report

splat reads a static word from the binary. Tried here on the load at `0x800253cc`. The executable still holds the original word. [call-800253b0.md](re/call-800253b0.md) says the earlier fill left 0 at that address. The file word is not the live value, so the walker does not read the executable as memory.

The note cap stays 64. `--max N` raises it for `build/boot-slice.txt` only, up to 4096. The header GP is the starting `gp`. A store through an unknown pointer does not wipe the other tracked words.

Checked November 13, 2026. `--start 0x800252b8 --max 512` reached the unnamed `jal` at `0x800253ec` in 79 instructions. The default cap had stopped at `0x800253bc`.

## Saved return address

The function at `0x8007e130` saves `ra` at `0x10(sp)`, calls `SetGeomOffset`, reloads `ra`, and executes `jr`. `--ra` is that entry value. The walker tracks `sp` as a delta from the start of the slice and returns the saved word. `--start 0x8007e130 --ra 0x800253f4` reports `next 0x800253f4`.

`tests.test_boot_slice` covered the saved `ra`.

## Enter the unnamed call

The notes enter an unnamed call, then continue the caller when that call returns. SOTN and Breath of Fire III keep that walk in one local command. `boot_slice.py` now enters an unnamed target inside the executable, up to 8 calls deep. `jr` to that call's return address resumes the caller. A named target is still not entered. A target outside the executable still stops the slice.

`tests.test_boot_slice` passed (17 tests). `python3 tools/pr_guard.py` passed.
