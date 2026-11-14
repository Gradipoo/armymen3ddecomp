# Return at 0x8005bfe8, cited v0

Traced fact from the USA PS-X EXE, plus one PCSX-Redux capture. Re-check the instructions with `python3 tools/entry_disasm.py build/disc/SLUS_004.91 --start 0x8005bfe8`. The executable and the capture stay in `build/`.

The start address is `0x8005bfe8`. [call-8005bfe8.md](call-8005bfe8.md) stops here because `CdDiskReady`'s `v0` was not stated. `s0` is `0x800d89b8`. The saved `ra` is `0x8007a6bc`. The saved `s0` is `0x80010054`. The caller `s1` is 23. The frame at `0x800251f8` stays open. Its saved `ra` stays `0x8007faec`.

PCSX-Redux, interpreter, fast boot, the USA cue, and BIOS file `build/bios/scph5501.bin`. The emulator reports that file as hash `8d8cb7e4`, labeled SCPH-7003 (US). The first hit at `0x8005bfe8` is in `build/research/behavior/cddiskready-8005bfe8-5501.jsonl`. `v0` is 2. `v1` is 2. `a0` is 1. `ra` is `0x8005bfe8`. `bne` at `0x8005bfec` compares `v0` with `v1`. They are equal, so the branch is not taken. The capture's `side` field means `v0` equals `v1`. For this `bne`, that is the fall-through.

The first hit at `0x8005bff4` is in `build/research/behavior/cddiskready-8005bff4-5501.jsonl`. The word at `0x800d89bc` is 0. `lw` loads that word into `v0`. `ori` at `0x8005bffc` sets `v0` to 1. `sw` at `0x8005c000` stores 1 at `0x800d89bc`.

`lw` at `0x8005c004` loads `ra` from `sp+0x14`. `lw` at `0x8005c008` loads `s0` from `sp+0x10`, so `s0` becomes `0x80010054`. `jr` at `0x8005c00c` returns through `ra`. The delay slot adds `0x18` to `sp`. `ra` leaves as `0x8007a6bc`. `v0` leaves as 1. Control goes to `0x8007a6bc`. That arrival is not traced. The caller return at `0x8007faec` is not traced.
