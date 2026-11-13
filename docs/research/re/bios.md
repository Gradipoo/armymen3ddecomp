# BIOS

Function numbers from the public [psx-spx BIOS function summary](http://problemkaputt.de/psxspx-bios-function-summary.htm). Quote addresses only.

Call an A function at `0xa0` with the number in `t1`. Call a B function at `0xb0`. Call a C function at `0xc0`. A call through those tables is the public name plus the number.

This boot trace has not called through those tables.

[entry-bios-call.md](entry-bios-call.md) compares a byte at `0x1fc00129`. [call-80025228.md](call-80025228.md) branches on the word at `0x8007f9a8`. The function summary does not name offset `0x129`, so that branch stays unknown.

This note does not close the gap in `components/exe/load.cpp`.
