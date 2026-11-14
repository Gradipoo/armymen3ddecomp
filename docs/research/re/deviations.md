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

The `sp` from that start is untrusted. `0x80063b34` opens with `addiu sp, sp, -0x88`. The returns in `call-80063b78.md` and `call-80063b78-2.md` pop that frame with `addiu sp, sp, 0x88` at `0x80063ed4` and resume `0x800237d0`. `call-80063b34-3.md` opens a third frame of `0x88`. No note pops it. `call-80062434-4.md` is still inside that frame, and `call-80062434.md` opened its own frame by `0x40`. `call-80023828.md` reads `0x24(sp)` as the saved `ra` of `0x80023794`. That slot is the `0x80023794` slot only after the `0x88` pop. `0x80060aac` is a separate frame of `0x18`. `call-80060b3c.md` pops it and returns to `0x80025478`. It is not the `0x88` frame, and it does not return through `0x80063b34`.

Status: the exit address stays. Sean reopened the stack. [stack-ledger.md](stack-ledger.md) states `sp` at `0x8002390c` as `0x80010bfc` after the inner pops. The third `0x88` frame has not reached that pop.
