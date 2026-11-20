# Retained menu-list contract review

## Outcome and acceptance

On November 19, 2026, inspect the retained frame-4974 menu-exit list without
replaying it. Establish complete command boundaries, compare its copy with
the [restricted adapter](gpu-restricted-copy-trial.md), and investigate the
unresolved zero command start. Do not infer missing GPU state.

The offline review identifies two contract restrictions: an identical-source
copy that the adapter rejects, and four zero words that it does not support.
The list fits the size caps. It is not accepted for execution or replay.

## Boundaries and mapping

The retained list has 2798 nodes, including 2304 empty nodes, and 2455 payload
words. Its terminator, links, word counts, alignment, and RAM bounds were
checked again by the bounded parser. Head `0x800ccd14` maps to RAM offset
`0x0ccd14`. Retained links are direct RAM offsets or the terminator.
The synthetic adapter expects a RAM vector and mapped starting offset;
it cannot receive that KSEG pointer unchanged.

Flattening the list yields 469 five-word `0x28` quads, 21 four-word `0x20`
triangles, two nine-word `0x2e` textured quads, and one four-word `0x80`
copy before the final node. None of these commands crosses a node boundary.
This is offline interpretation, not proof that submission produced a
particular visible feature.

## Copy restriction

The copy at stream word 2447, node RAM offset `0x0b7688`, normalizes to
source `(0,0)`, destination `(0,0)`, width 2, height 1. Source and destination
therefore overlap on both axes. The current adapter rejects it before any
GPU writes. This identifies the restriction; it does not establish how to
relax it under unobserved mask state.

No E6 event trace accompanies this capture. The list itself does not provide
an initial mask state. Do not assume the adapter's reset mask state matches
the retail GPU at this boundary, or silently treat the copy as a no-op.

## Zero-word restriction

The final node at RAM offset `0x0b7674` contains exactly four payload words,
all zero. They are after the complete copy command, not its parameters.
The [GPU reference](https://psx-spx.consoledev.net/graphicsprocessingunitgpu/)
lists GP0 `0x00` as a one-word command with an uncertain NOP label.
Under that command-length interpretation, this node holds four `0x00`
commands and all 2455 payload words are consumed. No command crosses nodes.

The zero words are known; their hardware effect is not established by this
capture. The adapter rejects `0x00`. This review neither adds support nor
skips those words. It does not claim that a speculative interpretation
proves whole-list coverage.

## Evidence and next outcome

Original parser, input hashes, summary, commands, and logs remain under
`build/coordination/menu-list-contract/`. Raw retained packets remain under
`build/coordination/retail-screen/run11/`. No raw asset data was imported
into public source. No emulator, GPU execution, new retail read, or replay
was used. The adapter and candidate sources were unchanged, so their
synthetic suites were not repeated. The repository guard passed.

The retained picture is a menu-exit transition, not a stable-menu capture.
No native update loop or retail agreement is established. The next bounded
observation is GPU mask state at the relevant submission boundary, with
separate evidence for the zero-command effect. Keep exact self-copy and
unsupported commands distinct when deciding the smallest adapter change.

The [mask-capture method review](gpu-mask-capture-method.md) rejected the
proposed Lua hardware-memory read: version-matched source shows shadow
bytes rather than live GPUSTAT. No new retail capture was made.
