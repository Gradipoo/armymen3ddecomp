# Ordering-table adapter trial

## Outcome and acceptance

On November 17, 2026, test a bounded fixed 32-bit ordering-table adapter
and one non-neutral modulated, semi-transparent textured quad. Require
safe list traversal, correct command boundaries, and no VRAM changes on
malformed-list rejection. Retain the preceding fill and primitive checks.

The build and runner exited zero. All 42 assertions passed. This is a
local synthetic trial, not backend adoption or game function verification.

## List and command boundary

The original adapter uses byte offsets into synthetic word RAM. Each tag's
upper eight bits count payload words. Its lower 24 bits name the next
offset, with `0xffffff` terminating the walk. This does not implement retail
bus addresses or KSEG aliases. No retail packet data was used.

The adapter checks alignment, bounds, payload ranges, repeated links,
a 4096-node cap, and a 16384-payload-word cap. It flattens the entire list
before decoding complete GP0 commands. This supports empty nodes, multiple
commands in a node, and commands split across nodes. It validates the whole
command stream before writing to the GPU. Unknown and truncated commands
reject. The rejection guarantee excludes allocation failures and other
host exceptions and does not model asynchronous GPU execution.

Supported commands remain deliberately narrow: fill `0x02`, flat triangle
`0x20`, flat quad `0x28`, textured quads `0x2e` and `0x2f`, and CPU-to-VRAM
upload `0xa0`. Upload dimensions must be nonzero and no greater than
1024 by 512. Payload words are not decoded as commands. All GPU writes must
go through this adapter for its parser-state guarantee to apply.

Fill retains the [previous adapter's behavior](gpu-fill-adapter-trial.md).
Other accepted commands run through the candidate's actual GP0 parser.
No dependency source was changed.

## Executed evidence

A synthetic list passed with an empty node, multiple commands in one node,
and a triangle split across nodes. A texture-upload data word with high
byte `0x02` reached VRAM as data. Existing fill and primitive samples passed.

The `0x2e` sample used a green RGB555 texture value of 31 with bit 15 set,
and command color 64 rather than neutral 128. Modulation reduces green to
15. Blend mode zero over red 31 produces red 15 and green 7, or `0x00ef`.
The real parser produced that expected pixel. This is one sampled texture
and blend case, not a general rasterizer verification.

Malformed alignment, out-of-bounds links and counts, cycles, late invalid
links and cycles, unsupported and incomplete tails, invalid upload size,
and both caps were rejected. Every rejection compared all 524288 VRAM
pixels with their prior values. All remained unchanged. A valid list was
accepted after rejection. Both the initial run and the strengthened final
run passed; no failed trial run occurred.

## Provenance and limits

The dependency selection is unchanged from the
[isolated GPU trial](ps1recomp-gpu-trial.md): pinned PS1Recomp
`49c4a5164149a0b0eeaf1299f7cffa56d5ee1df1`, GPL-3.0-or-later, and pinned
fmt `f99d53024782bf928b07839140862163f15ade5b`, MIT. Local notices and the
complete dependency scan remain with that trial. No public source import
or new download was needed. The host was macOS arm64 with Apple clang
21.0.0. Other hosts were not tested.

Original source, exact commands, hashes, and logs remain under
`build/coordination/gpu-list-adapter/`. The repository guard passed.
The existing SDL2 source and interface were unchanged.

This does not establish full menu command coverage, retail replay, visible
output, display pages, controller transitions, performance, or reconstructed
game behavior. In particular, observed `0x80` and unresolved `0x00` starts
remain outside the adapter. Full VRAM copies for fill remain unmeasured.

The next bounded outcome is visible synthetic output through the existing
SDL2 display, without changing its default disc-free behavior. Preserve
16-bit candidate VRAM and distinguish the displayed RGB conversion from
its texture mask bit. A native game screen still requires reconstructed
update code and an observed controller transition.

The [visible synthetic trial](gpu-visible-trial.md) displayed the tested
shapes and passed sampled readback checks, but exposed a shared-edge
double-blending artifact in candidate VRAM. Adoption remains open.
