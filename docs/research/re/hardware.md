# Hardware

Ports the research notes already use. Names come from the public [psx-spx memory map](http://problemkaputt.de/psxspx-memory-map.htm). Quote addresses only.

Scratchpad is `0x1f800000` through `0x1f8003ff`. [entry-loop.md](entry-loop.md) writes that range.

BIOS ROM starts at `0x1fc00000`. It is not in this tree. [entry-bios-call.md](entry-bios-call.md) compares bytes from that ROM.

Main RAM top is `0x80200000`. Stores past the text image stay below that address.

`0x1f801814` is the GPU control port. [call-8008824c.md](call-8008824c.md) stores `0x03000001` there.

This note does not close the gap in `components/exe/load.cpp`.
