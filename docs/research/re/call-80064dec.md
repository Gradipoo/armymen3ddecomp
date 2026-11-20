# Fallthrough at 0x80064dec

[call-80064dd8.md](call-80064dd8.md) records the not-taken `bne` at `0x80064de4`
when the masked byte at `s1` is `0x80`. The delay slot at `0x80064de8`
sets `t1` to one. That path lands here. Live `s1` matches the value passed
into the `0x80064dd8` `lbu`. This note does not resume the parked static boot.

`python3 tools/boot_slice.py build/disc/SLUS_004.91 --start 0x80064dec --max 64`
reports 29 instructions and stops at branches after `PadGetState`. The
report stays in `build/`.

| Address | Instruction |
| --- | --- |
| `0x80064dec` | `addiu t0, zero, 0x4` |
| `0x80064df0` | `sw t0, 0x1c(sp)` |
| `0x80064df4` | `j 0x80064e04` |
| `0x80064df8` | `addiu s1, s1, 0x1` |
| `0x80064e04` | `lw t0, 0x1c(sp)` |
| `0x80064e08` | `nop` |
| `0x80064e0c` | `beq t0, zero, 0x80065194` |
| `0x80064e10` | `addu s7, zero, zero` |

The delay slot at `0x80064df8` increments `s1`. The jump target is
`0x80064e04`, shared with the `0x80064dfc` path. The delay slot at
`0x80064e10` clears `s7` on either `beq` side. The taken target is
`0x80065194`. The fallthrough is `0x80064e14`. On this path `t0` is four
after the store. The slice contains no `jal` through `0x80064e10`.

## Our code

`components/exe/call_80064dec.cpp` stores four through optional
`stack_word_1c` (sp+0x1c), applies the delay-slot `s1` bump, reloads the
stack word into `t0`, applies the delay-slot `s7` clear, and records
`branch_to_65194` or `entered_64e14`.

`menu_input_scan_step` calls this block after [call-80064dd8](call-80064dd8.md)
when `loop_body_64dd8.entered_64dec` is true. Glue passes `s1` from the
64dc8 delay-slot bump and the caller `stack_word_1c` reference for the
store and load. When `entered_64e14` is true, glue calls
[call-80064e14](call-80064e14.md).

## Gap

Re-entry at `0x80065194` on the taken `beq` is not modeled. Live retail words
at `sp+0x1c` on this path are not stated.