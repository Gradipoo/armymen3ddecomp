# Second buffer advance at 0x80076164

This follows [call-8007641c.md](call-8007641c.md). The function entry is
`0x80076164`. Its saved return address is `0x80076414`. The caller's loop
counter is now 2. The function does not use an incoming argument register.

The current drawing-node pointer is at offset `0x0c` of `0x800e15b0`.
The first pass left it pointing to the second node. That node's next
pointer is zero in the established state. This note keeps its origin
coordinates symbolic. It does not quote the data words from the image.

The function copies the drawing-node pointer into the display-node slot
at offset `0x08`. It reads that node's next pointer and writes it into
the drawing-node slot. The branch at `0x80076190` is not taken when that
pointer is zero. The function then reads the first-node pointer at offset
`0x04` and uses it as the next drawing node. This is the list wrap.

## Named calls

All four targets are named by `python tools/sdk_match.py`. Their bodies
were not entered. The return values are not used.

| Call site | Target | Arguments | Return address |
| --- | --- | --- | --- |
| `0x800761bc` | `SetDefDispEnv` | `a0` is the environment at state offset `0x2c`; `a1` and `a2` are the displayed node's origin words; `a3` is display width; stack argument is display height. | `0x800761c4` |
| `0x800761d4` | `PutDispEnv` | `a0` is that display environment. Other volatile argument registers are not additional interface arguments. | `0x800761dc` |
| `0x80076210` | `SetDefDrawEnv` | `a0` is the environment at state offset `0x40`; `a1` and `a2` are the next drawing node's origin plus left and top; `a3` is right minus left; stack argument is bottom minus top. | `0x80076218` |
| `0x80076218` | `PutDrawEnv` | `a0` is that drawing environment. Other volatile argument registers are unknown after the preceding call. | `0x80076220` |

Display width and height come from state offsets `0x10` and `0x14`.
Between the first two calls, the function sets the display environment's
interlace byte to whether the mode word at offset `0x18` equals 3. The
recorded mode is 2, so that byte is zero on this boot.

The drawing rectangle uses word-sized state fields at offsets `0x1c`,
`0x20`, `0x24`, and `0x28` for left, right, top, and bottom. Origins come
from node offsets 4 and 8. These call arguments are word arithmetic;
the SDK environment fields retain their low 16 bits. The drawing state
is read after the display environment has been submitted.

The function restores the saved registers. `jr ra` at `0x8007622c`
returns through the saved `0x80076414`. Its delay slot at `0x80076230`
releases the frame. This path executes 52 instructions including delay
slots, below the 64-instruction cap. It contains no unnamed calls.
The next boot instruction is `0x80076414`, which calls the fill again.
The saved parent return address remains `0x80025390`.

## Our implementation and checks

`components/exe/display_buffers.cpp` implements the state transition with
native buffer indices. It preserves the distinction between the displayed
node and the next drawing node. The environment interface represents the
named SDK initialization/submission pairs. It passes their core rectangle
fields and the interlace flag; a backend owns the rest of the SDK defaults.

Native invalid indices throw before the transition is published. This is
a host validation rule, not a claim about malformed retail pointers.
The implementation does not cast PS1 addresses into host pointers.

Host checks cover linked advancement, wrapping to the head, display/draw
ordering, mode flags, arithmetic truncation, and state reads after display
submission. The optional SDL test renders different synthetic colors in
two VRAM pages and checks that successive advances select the right page.
It records the draw environment but has no polygon or texture pipeline.
Interlaced presentation is explicitly unsupported in this backend.

The 208-byte code range was disassembled with the pinned local tools and
rebuilt exactly. That validates the disassembly exporter on this range.
It is not a compiler match of our C++ or a retail behavior verification.
Generated C, assembly, objects, and metadata stay under `build/analysis/`.
The function is recorded as implemented, not verified. The first running
scene and executable-load gap remain open.
