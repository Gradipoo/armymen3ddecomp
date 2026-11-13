# Second display fill at 0x80076274

This follows [call-80076414-second.md](call-80076414-second.md). The color
argument is zero. The saved return address is `0x8007641c`. The caller's
completed-count register is 2. The first-pass note
[call-80076274.md](call-80076274.md) remains unchanged.

The same straight path executes 38 instructions including delay slots.
It has no unnamed calls. This pass reads the origin from the first drawing
node, after the second advance wrapped the list. Origin values remain
symbolic here; no data words or instruction listing are copied into this
note. The known rectangle is left/top zero, width 512, and height 240.

The call at `0x80076284` is the named `DrawSync`, with argument zero and
return address `0x8007628c`. Its body is not entered and its return value
is discarded. Drawing state is loaded after this wait.

The packet has three GPU command words. Its command is a fill, its color
is black, and its rectangle uses the current drawing node's origin plus
the stored left/top. Width and height are right minus left and bottom
minus top, retaining the low 16 bits. The low tag bytes remain unspecified.

The call at `0x800762f4` is the named `DrawPrim`. `a0` points to that stack
packet. Its delay slot completes the vertical coordinate. The return
address is `0x800762fc`. Its body is not entered and its return value is
not used. No additional interface arguments are inferred from volatile
registers.

The function restores its saved registers. `jr ra` at `0x80076304` returns
through `0x8007641c`; its delay slot releases the frame. The caller's `s0`
is restored as 2. The next note is
[call-8007641c-second.md](call-8007641c-second.md).
