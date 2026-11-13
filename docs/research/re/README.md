# Research notes

Notes in this folder describe the PlayStation USA executable, serial SLUS-00491. Quote one address. Raw decompiled C stays under `build/ghidra/`. It is never committed.

| File | Contents |
| --- | --- |
| [todo.md](todo.md) | Open research work |
| [unverified.md](unverified.md) | Claims waiting for a second check on a disc you own |
| [deviations.md](deviations.md) | Keyboard, server browser, and mods. Not started. |
| [exe-header.md](exe-header.md) | PS-X EXE header at `0x8007f9f8`. |
| [entry.md](entry.md) | First block at `0x8007f9f8`. The rest of the body is not traced. |
| [entry-call.md](entry-call.md) | First block at `0x8007faf8`. The fall-through is in [entry-loop.md](entry-loop.md). |
| [entry-loop.md](entry-loop.md) | Loop at `0x8007fb04`. It returns at `0x8007fb14`. The return continues in [entry-return.md](entry-return.md). |
| [entry-return.md](entry-return.md) | Block at `0x8007fa2c` after the scratchpad fill. It calls `0x8007faf8`. The return continues in [entry-after-fill.md](entry-after-fill.md). |
| [entry-after-fill.md](entry-after-fill.md) | Block at `0x8007fa4c` after the second fill. It calls `0x8007faf8`. The return continues in [entry-after-zero.md](entry-after-zero.md). |
| [entry-after-zero.md](entry-after-zero.md) | Block at `0x8007fa68` after the zero fill. It calls `0x8007faf8`. The return continues in [entry-after-ram.md](entry-after-ram.md). |
| [entry-after-ram.md](entry-after-ram.md) | Block at `0x8007fa84` after the RAM fill. It calls `0x8007fb1c`. The callee is in [entry-bios-call.md](entry-bios-call.md). |
| [entry-bios-call.md](entry-bios-call.md) | Block at `0x8007fb1c`. It loads bytes from `a0` and `a1`, then branches to `0x8007fb3c`. The two paths are in [entry-byte-compare.md](entry-byte-compare.md). |
| [entry-byte-compare.md](entry-byte-compare.md) | Compare at `0x8007fb2c` and return at `0x8007fb3c`. Equal values loop to `0x8007fb1c`. The return continues in [entry-after-compare.md](entry-after-compare.md). |
| [entry-after-compare.md](entry-after-compare.md) | Block at `0x8007fa9c` after the byte compare. It copies `v0` to `t0` and calls `0x8007fb1c`. The return continues in [entry-after-second-compare.md](entry-after-second-compare.md). |
| [entry-after-second-compare.md](entry-after-second-compare.md) | Block at `0x8007fab8` after the second byte compare. It ORs `v0` into `t0` and calls `0x8007fb1c`. The return continues in [entry-after-third-compare.md](entry-after-third-compare.md). |
| [entry-after-third-compare.md](entry-after-third-compare.md) | Block at `0x8007fad4` after the third byte compare. It ORs `v0` into `t0`, stores that word, and calls `0x800251f8`. The callee is in [call-800251f8.md](call-800251f8.md). The return at `0x8007faec` is not traced. |
| [call-800251f8.md](call-800251f8.md) | First block at `0x800251f8`. It saves `ra`, `fp`, and `s0` through `s7`, then calls `0x8007faf0`. The callee is in [call-8007faf0.md](call-8007faf0.md). The return continues in [call-80025228.md](call-80025228.md). |
| [call-8007faf0.md](call-8007faf0.md) | Block at `0x8007faf0`. `jr ra` returns through `ra`. The delay slot at `0x8007faf4` is `nop`. Control does not fall into the fill at `0x8007faf8`. The return continues in [call-80025228.md](call-80025228.md). |
| [call-80025228.md](call-80025228.md) | Block at `0x80025228`. It loads the word at `0x8007f9a8` into `v0` and branches to `0x8002524c` when that word is 0. The delay slot writes `0x8007f9a8` into `v1`. The fall-through is `0x8002523c`. Both paths are in [call-8002523c.md](call-8002523c.md). |
| [call-8002523c.md](call-8002523c.md) | Paths at `0x8002523c` and `0x8002524c`. The non-zero path adds `0x1400` to the word at `0x8007f9d0` and falls into `0x8002524c`. Both paths call `0x8007f920` with `a0` `0x8009f820`, `a1` 0, and `a2` `0x9a4`. `ra` becomes `0x80025264`. Which path this boot takes is unknown. The callee's first block is in [call-8007f920.md](call-8007f920.md). |
| [call-8007f920.md](call-8007f920.md) | First block at `0x8007f920`. It branches to `0x8007f9a0` when `a0` is 0. This call's `a0` is `0x8009f820`, so the branch is not taken. The delay slot copies `a0` into `v0`. Control continues at `0x8007f928`. That body is not traced. |
| game-functions.tsv | Function facts from the Ghidra export: address, size, name |

The TSV appears here after Ghidra export. `python tools/gaps.py` compares `// gap:` comments and that TSV with these notes.

A normal gap change may add a note here. It leaves [docs/PLAN.md](../../PLAN.md) alone.
