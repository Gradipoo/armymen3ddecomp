# Display-clear return at 0x8007641c

This follows [call-80076274-second.md](call-80076274-second.md). The
completed count in `s0` is 2. The display-buffer count is still 2 in the
recorded state. The load at `0x8007641c` replaces the unused return value
from `DrawPrim` with the current count. After the load delay, the unsigned
comparison produces zero. The branch at `0x80076428` is not taken. Its
delay slot is a nop, then control reaches `0x80076430`.

The epilogue restores the saved return address and registers from the
frame opened by the function at `0x800763e0`. `jr ra` at `0x80076440`
returns through `0x80025390`. Its delay slot at `0x80076444` releases the
frame. The caller's restored `s0`, `s1`, and `s2` are `0x8009f510`,
`0x8009f820`, and `0x80080000`. `v0` remains zero after the comparison.
This note covers 11 instructions and ends at the return, below the cap.
There is no call in this continuation. The next boot address is
`0x80025390`; its words are not traced here.

## Our display-clear implementation

`components/exe/display_clear.cpp` implements the function that starts at
`0x800763e0`. Its initial nonzero test is recorded in
[call-800763e0.md](call-800763e0.md). The two call sites and loop back edge
are covered by that note and the later display-loop notes.

An initial zero count makes no buffer advance or fill. Otherwise the
routine advances, fills with the supplied color, and compares the unsigned
completed count against the count read after that fill. It does not cache
the initial count across calls. The native state therefore has a distinct
buffer-count field, not a count inferred from vector size.

The native caller uses our buffer-advance and display-fill implementations.
The fill reads live drawing state after `DrawSync`, so a callback cannot
leave it using a snapshot from before the wait. The existing direct-state
fill interface uses the same packet construction path.

Host checks cover clearing both synthetic pages, zero buffers, call order,
color forwarding, state changes during the wait, shrinking counts, and
unsigned count comparison. The optional renderer test checks both pages
were cleared before drawing. The smoke test now calls this reconstructed
startup routine before presenting its synthetic pattern.

These tests do not execute a retail SDK or complete the game boot. The
104-byte disassembly range was independently rebuilt without changing
its bytes, but our C++ has not been matched to it. Ledger status is
implemented, not verified. The loader and first-scene milestones remain
open. Generated assembly and C remain under `build/`.
