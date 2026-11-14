# Words at 0x8007fbbc

[call-8007fbbc.md](call-8007fbbc.md) quotes the two words and does not name them. This note reads those quoted words. It does not restate the rest of that block.

`0x48c4e800` has top 6 bits `0x12`. That is the coprocessor 2 opcode. The next 5 bits are 6. The next 5 bits are 4, which is `a0`. The next 5 bits are 29. The low 11 bits are 0.

`0x48c5f000` has the same opcode and the same 5-bit field 6. The next 5 bits are 5, which is `a1`. The next 5 bits are 30. The low 11 bits are 0.

On this boot `a0` is `0x55` and `a1` is `0x40`. These words do not write those general registers. `a0` stays `0x55`. `a1` stays `0x40`. There is no SDK name for control field 29 or 30 in this tree, so the code does not name them.

## Our code

`components/exe/call_8007fbbc.cpp` copies `a0` into the first reference and `a1` into the second. It then calls `call_8007e1f8`.

## Gap

The return is `0x8007e1f8`. That site resumes at `0x80025410`.
