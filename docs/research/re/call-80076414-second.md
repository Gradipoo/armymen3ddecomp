# Second fill call at 0x80076414

This follows [call-80076164-second.md](call-80076164-second.md). The caller
has `s0` 2, `s1` `0x800e0000`, and `s2` zero. The selected drawing node has
wrapped to the first node. The display node is the second node.

The call at `0x80076414` targets `0x80076274` and writes return address
`0x8007641c`. The delay slot copies `s2` to `a0`, so the color argument is
zero. This target is not named by the SDK matcher. This note stops at the
call and its delay slot. The next note is
[call-80076274-second.md](call-80076274-second.md).

The caller has not yet reloaded the buffer count. This call does not read
the volatile return value from the buffer-advance routine. The saved
parent return remains `0x80025390` on the caller's open frame.
