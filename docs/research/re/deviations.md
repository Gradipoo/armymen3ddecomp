# Deviations

These lanes differ from the PlayStation game on purpose. Each one will be a `// gap:` in our code.

## Keyboard

The USA disc has no keyboard control. A later input path will add a keyboard.

Status: not started.

## Server browser

The USA disc has no server browser. A later path will show a server list.

Status: not started.

## Mods

A local `mods/` directory will be searched before the disc.

Status: not started.

## Mission path loop

The traced boot at `0x800237d0` keeps `s4` at 1 and `s1` at 0, so it calls `0x80063b34` again and does not reach the epilogue at `0x80023828`. The word at `0x800e152c` stays 0 on every traced load. Stores of that word exist at `0x80074200`, `0x8007428c`, `0x80074380`, `0x800744ac`, `0x800745f0`, `0x80074d38`, `0x80074e4c`, and `0x800750d0`, and none is on this path. The next block may start at `0x80023828` as the exit address. That start does not mean this boot took the branch.

Status: approved. Sean said go on the investigate-then-deviation step.
