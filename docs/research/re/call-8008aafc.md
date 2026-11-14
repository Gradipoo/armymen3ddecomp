# Block at 0x8008aafc

Traced fact from the USA PS-X EXE. Re-check on a disc you own with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8008aafc`. The executable and the listing stay in `build/`.

The start address is `0x8008aafc`. `python3 tools/sdk_match.py` names it `SetDefDrawEnv`. The `jal` in [call-800761dc.md](call-800761dc.md) calls here and sets `ra` to `0x80076218`. On arrival `a0` is `0x800e15f0` and `a3` is `0x200`. The word at `0x10(sp)` on the frame opened at `0x80076164` is `0xf0`. `a1` is the word at `0x8009f520`. `a2` is the word at `0x8009f524`. Both addresses are inside the text image, `0x80010000` through `0x800c57ff`. This note reads those two words. They are 0 and `0xf0`. No note in this boot stores either address. `s0` is `0x800e15f0`. `s1` is `0x800e15b0`. `s2` is 0. The noted call below returns `v0` as 0, so the `beq` is taken. The tool followed 27 instructions and stopped because it did not keep that return value. This note follows the taken side through `jr ra`. The hard cap is 64 instructions. This block ended before the cap.

`addiu` at `0x8008aafc` opens a frame of `0x28`. The saves store the arriving `s0`, `s1`, and `s2`, and `ra`. `lw` at `0x8008ab04` reads `0x38(sp)`. That is the caller's `0x10(sp)` after this frame opens, so `s2` becomes `0xf0`. `s1` becomes `a0` (`0x800e15f0`). `s3` becomes `a1` (0). `s4` becomes `a2` (`0xf0`).

`jal` at `0x8008ab28` calls `0x80086230` and sets `ra` to `0x8008ab30`. The delay slot copies `a3` into `s0`, so `s0` is `0x200`. [call-80086230.md](call-80086230.md) already traces that body. It returns 0 in `v0`. `a0` stays `0x800e15f0`.

The stores through `s1` write the draw environment at `0x800e15f0`. The halfword at `0x800e15f0` becomes 0. The halfword at `0x800e15f2` becomes `0xf0`. The halfword at `0x800e15f4` becomes `0x200`. The halfwords at `0x800e15fc`, `0x800e15fe`, `0x800e1600`, and `0x800e1602` become 0. The bytes at `0x800e1609`, `0x800e160a`, and `0x800e160b` become 0. The byte at `0x800e1606` becomes 1.

`beq` at `0x8008ab60` is taken because `v0` is 0. The delay slot stores `s2` (`0xf0`) at `0x800e15f6`. The `j` at `0x8008ab68` does not run. `slti` at `0x8008ab70` compares `s2` (`0xf0`) with `0x101` and leaves `v0` at 1. `sb` stores that 1 at `0x800e1607`. `v0` is then set to `s1` (`0x800e15f0`). `v1` is set to `0xa`. The halfword at `0x800e15f8` becomes 0. The halfword at `0x800e15fa` becomes `0xf0`. The halfword at `0x800e1604` becomes `0xa`. The byte at `0x800e1608` becomes 0.

The epilogue reloads `ra`, `s0`, `s1`, and `s2`. `jr` returns to `0x80076218`. The delay slot adds `0x28` to `sp`. `v0` leaves as `0x800e15f0`. `s0` leaves as `0x800e15f0`. `s1` leaves as `0x800e15b0`. `s2` leaves as 0. The display x and y halfwords are still not quoted. This note does not close the gap in `components/exe/load.cpp`.
