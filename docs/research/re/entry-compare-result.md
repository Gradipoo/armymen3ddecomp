# Result of the three compares

The BIOS files stay in `build/bios/`. They are not committed. Each file is mapped at `0x1fc00000`, so file offset `0x129` is address `0x1fc00129` and file offset `0x12c` is address `0x1fc0012c`.

The files are `scph5500.bin`, `scph5501.bin`, and `scph5502.bin`. At these two offsets the three files hold the same bytes. This note quotes those bytes. It does not dump the ROM.

The executable strings are in [entry-compare-bytes.md](entry-compare-bytes.md). The first call compares `0x8007f9d8` with `0x1fc00129`. The second compares `0x8007f9e2` with `0x1fc0012c`. The third compares `0x8007f9ec` with `0x1fc0012c`. Those calls are in [entry-after-ram.md](entry-after-ram.md), [entry-after-compare.md](entry-after-compare.md), and [entry-after-second-compare.md](entry-after-second-compare.md).

The byte at `0x1fc00129` is `0x00`. The first executable byte is `0x44`. They differ, so the first compare does not match. The byte at `0x1fc0012c` is `0x43`. The first byte of each later string is `0x44`. They differ, so the second compare does not match and the third compare does not match. [entry-byte-compare.md](entry-byte-compare.md) leaves `v0` as 0 on a mismatch. Each call stops on that first byte. This note does not quote the later BIOS bytes.

[entry-after-compare.md](entry-after-compare.md) copies the first result into `t0`. [entry-after-second-compare.md](entry-after-second-compare.md) ORs the second result into `t0`. [entry-after-third-compare.md](entry-after-third-compare.md) ORs the third result into `t0` and stores that word at `0x8007f9a8`. Each result is 0, so the word at `0x8007f9a8` is 0.

This note does not trace the `beq` at `0x80025424`. It does not close the gap in `components/exe/load.cpp`.
