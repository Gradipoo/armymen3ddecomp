# Restricted copy adapter trial

## Outcome and acceptance

On November 19, 2026, add a bounded local `0x80` copy interface to the
[ordering-table adapter](gpu-list-adapter-trial.md), using the
[dimension-fixed candidate](gpu-copy-size-fix-trial.md). Require rejection
of source/destination overlap before execution, working nonoverlapping
copies, and an explicit mask-state contract. Preserve prior checks.

The local build and runner passed all 71 named checks. Copy is now supported by this restricted
local adapter. It is not a public runtime import or backend adoption.
Overlap hardware behavior remains unverified and is rejected.

## Contract

Only exact opcode `0x80`, with exactly four words, is accepted. Source and
destination coordinates and dimensions are normalized before overlap checks.
The adapter intersects the wrapped pixel intervals on each axis. Intersection
on both axes rejects the copy. Identical rectangles and full-VRAM copies
therefore reject. Touching edges without shared pixels are permitted.

The adapter privately owns a reset GPU. Its copy mask state remains zero.
It exposes no GP1 path and rejects `0xe6`; callers cannot enable the local
candidate's copy-only mask behavior. This is not general E6 support.
Existing supported drawing and upload commands remain unchanged.

The full list is flattened and validated before any GPU writes. Copy
geometry, unknown commands, incomplete commands, list bounds, cycles, and
caps are checked before execution. A late overlapping copy or unsupported
mask command cannot execute a valid prefix. As before, this contract excludes
host allocation failures and bypassing the private adapter.

## Executed evidence

The independent overlap oracle enumerated pixel membership on each wrapped
axis for 8448 selected cases. It found no disagreement with the compact
interval predicate. This checks the overlap restriction, not hardware copy
ordering.

Eleven successful copy cases compared the complete VRAM with expected
contents, totaling 5767168 pixel comparisons. Cases include normal copy,
source and destination wrap, zero and maximum width and height, masked
width 1025 and height 513, and touching X and Y edges. Source bit 15 remains
part of the copied value under the fixed zero-mask-state contract.

Full-VRAM rejection checks cover identical rectangles, both directions of
horizontal and vertical overlap, wrapped overlap in both directions, and
zero or explicit maximum full-VRAM rectangles. They also cover a late
`0xe6` after a valid copy. Those rejections leave VRAM unchanged. Separate
checks reject direct `0xe6`, unsupported `0x81`, and a truncated copy.

A successful list includes an empty node, multiple commands, a copy split
across nodes, and an upload data word whose high byte is `0x80`. The latter
remains data. Prior 42 adapter checks still pass. No failed trial run was
recorded. Existing edge and mask regression suites were not repeated because
the GPU source was unchanged.

## Provenance and next outcome

The runner links the unchanged local size-fixed variant of PS1Recomp
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1`, GPL-3.0-or-later, with preceding
local patches. Pinned fmt remains unchanged under MIT. Dependency notices
and source hashes remain in the preceding records. Adapter source, exact
commands, hashes, full logs, and local manifest remain under
`build/coordination/gpu-restricted-copy/`.

The host was macOS arm64 with Apple clang 21.0.0. Other hosts, performance,
retail agreement, and native update behavior remain untested. No retail
data, new dependency, UI session, public source import, or default build
change was needed. The repository guard passed.

The next bounded observation is to compare the retained menu-list command
boundaries and copy geometry with this restricted contract, including the
unresolved `0x00` start. The retail copy's mask state remains unknown. Do
not replay unsupported commands, infer missing state, or claim a running
screen from these synthetic checks.

The later [retained menu-list review](menu-list-contract.md) found an
identical-source copy and four zero words outside this contract. The
captured mask state remains unknown; no replay was attempted.
