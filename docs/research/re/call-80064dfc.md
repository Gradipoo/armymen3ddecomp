# Taken path at 0x80064dfc

[call-80064dd8.md](call-80064dd8.md) records the taken `bne` at `0x80064de4`
when the masked byte at `s1` is not `0x80`. The delay slot at `0x80064de8`
sets `t1` to one. That path lands here. Live `s1` matches the value passed
into the `0x80064dd8` `lbu`. This note does not resume the parked static boot.

`python3 tools/boot_slice.py build/disc/SLUS_004.91 --start 0x80064dfc --max 64`
reports six instructions and stops at the unknown `beq` at `0x80064e0c`. The
report stays in `build/`.

| Address | Instruction |
| --- | --- |
| `0x80064dfc` | `sw t1, 0x1c(sp)` |
| `0x80064e00` | `addiu s1, s1, -0x1` |
| `0x80064e04` | `lw t0, 0x1c(sp)` |
| `0x80064e08` | `nop` |
| `0x80064e0c` | `beq t0, zero, 0x80065194` |
| `0x80064e10` | `addu s7, zero, zero` |

The delay slot at `0x80064e10` clears `s7` on either `beq` side. The taken
target is `0x80065194`. The fallthrough is `0x80064e14`. Live `t1` on entry
is one from the `0x80064de8` delay slot. The slice contains no `jal`.

## Our code

`components/exe/call_80064dfc.cpp` stores `t1` through optional
`stack_word_1c` (sp+0x1c), decrements `s1`, reloads the stack word into `t0`,
applies the delay-slot `s7` clear, and records `branch_to_65194` or
`entered_64e14`.

`menu_input_scan_step` calls this block after [call-80064dd8](call-80064dd8.md)
when `loop_body_64dd8.branch_to_64dfc` is true. Glue passes `s1` from the
64dc8 delay-slot bump, `t1` from the 64dd8 delay slot, and the caller
`stack_word_1c` reference for the store and load. When `entered_64e14` is
true, glue calls [call-80064e14](call-80064e14.md). When `branch_to_65194` is
true, glue calls `record_65194_reentry_from_64e0c` in
[menu-input-scan.md](menu-input-scan.md). That sets `reentered_65194` and,
when `scan.index` is not zero, records a second
[call_80065194](call-80065194.md) result without re-entering `0x800651c8`.

## Gap

Live retail words at `sp+0x1c` on this path are not stated.