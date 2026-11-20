# Menu input scan integration

This is an integration note. It is not a boot note and it does not resume
the parked lane at `0x80061fe4`.

`menu_input_scan_step` calls [call_80064e40](call-80064e40.md),
[call_80064e68](call-80064e68.md), [call_80064f14](call-80064f14.md),
[call_80064f48](call-80064f48.md), [call_8006508c](call-8006508c.md), [call_80065098](call-80065098.md),
[call_800650a8](call-800650a8.md), [call_800650b4](call-800650b4.md),
[call_800650d0](call-800650d0.md), [call_800650e0](call-800650e0.md),
[call_800650ec](call-800650ec.md), and [call_800650f4](call_800650f4.md), and [call_80065194](call-80065194.md)
when the loop compare stops the tail.
The table supplies the measured `0x41` byte and the following halfword.
After the mask stores, glue enters `0x8006508c` with `s6` from the loop
head. Measured samples had `s6` zero, so execution continues to the
complemented bit tails. Complemented bits for [call_800650d0](call-800650d0.md)
and [call_800650e0](call-800650e0.md) come from that halfword, not a
separate synthetic word.

## Gap

When `s6` is nonzero, glue runs [call-80065098](call-80065098.md), then
[call-800650a8](call-800650a8.md) or [call-800650b4](call-800650b4.md) from
the `0x80` test, then the same complemented bit tails as the `s6` zero path.
Measured samples still had `s6` zero at the loop head. Optional
`test_inject_s6` overrides `s6` in ctests only.