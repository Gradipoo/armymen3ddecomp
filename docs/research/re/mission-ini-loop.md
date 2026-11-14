# Mission path loop at 0x800237d0

`python3 tools/boot_slice.py EXE --start 0x800237d0 --max 256` writes `build/boot-slice.txt`. That report is not a note. It follows four instructions and stops at `beq s4, zero, 0x80023828`. The tool does not know `s4`, so it does not take a side. The notes below do know the registers.

`call-80023848-2.md` calls `0x80023794` with `a2` equal to 1. `call-80023794-2.md` copies that into `s4`. Each return from `0x80063b34` restores that saved `s4`, so `s4` stays 1. `call-80063b78.md` returns `v0` as 0 and restores `s4` to 1. `call-800237d0.md` and `call-800237d0-2.md` copy that `v0` into `s1`, so `s1` becomes 0. The same return happens on the later passes. Nothing on this path stores `0x800e152c`, `0x800dd494`, or `0x800dd490`.

`beq s4, zero, 0x80023828` is not taken while `s4` is 1. `beq s1, zero, 0x800237bc` is taken while `s1` is 0. That branch calls `0x80063b34` again with `a0` `0x800bfdbc`, `a1` 0, and `a2` 1. The cited bodies are `call-80063b34.md`, `call-80062434-2.md`, `call-80061f80-3.md`, `call-80061ff0-3.md`, `call-80062000.md`, `call-80062474-2.md`, and `call-80075198-5.md`. `0x800e152c` stays 0, so `0x80075198` returns 0. `0x80062434` then returns 0. `0x80063b34` returns 0. `s1` is 0 again. `s4` is 1 again.

The loop leaves only if `s4` is 0 or `s1` is not 0 at `0x80023818`. `s4` changes only if a later path returns without restoring the saved 1. `s1` changes only if `0x80063b34` returns a value other than 0. That return is 0 while the word at `0x800e152c` stays 0. The epilogue at `0x80023828` is the exit address. This boot does not reach it. No exit note is written.

The frames at `0x80023794`, `0x80023848`, and `0x800251f8` stay open. Their saved `ra` values stay `0x8002390c`, `0x800255d8`, and `0x8007faec`.
