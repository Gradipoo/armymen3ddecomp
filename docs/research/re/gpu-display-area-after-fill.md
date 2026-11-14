# Display-area command after the three-word fill

The fill in [call-80076274.md](call-80076274.md) builds one packet on the stack. The store at `0x80076290` is `sb v0, 0x13(sp)`. The instruction word is `0xa3a20013`. It writes tag length 3. The store at `0x80076298` is `sb v0, 0x17(sp)`. The instruction word is `0xa3a20017`. The byte it writes is 2, from `addiu` at `0x80076294` (`0x24020002`). That is the fill command. `DrawPrim` at `0x800762f4` sends the packet. `jr ra` at `0x80076304` returns to `0x8007641c`.

[call-8007641c.md](call-8007641c.md) takes the loop back edge and calls `0x80076164` again. [call-80076164-second.md](call-80076164-second.md) submits the display environment with `PutDispEnv` before the next fill. [display-environment-layout.md](display-environment-layout.md) says that environment begins with the display rectangle. The mode on this boot is 2, so the interlace byte and the RGB24 byte are both zero. Those flag bytes are not this command.

The first GPU store in that submit is built at `0x80086e48`. The instruction is `lui v0, 0x500`. The instruction word is `0x3c020500`. It writes `0x05000000`. The top byte is `0x05`. [call-80086e48.md](call-80086e48.md) joins the low 10 bits of the display x and y halfwords into that word. This note does not quote those halfwords, so it does not state the full GPU word. `gpu_store` writes the joined word to `0x1f801814`. That body is already traced. This note does not enter it.

No note quotes the display x and y halfwords. This note still does not state the full display-area word.

[call-80086e7c.md](call-80086e7c.md) takes the branch to `0x80086ef0` after that store. The instruction there is `jal 0x80086230`. The instruction word is `0x0c02188c`. The delay slot at `0x80086ef4` is `nop`, word `0x00000000`. `python3 tools/sdk_match.py` does not name `0x80086230`. This note stops at that call. It does not state a GPU command after the `0x05` byte.

This command is not a `DrawPrim` packet. The next cited GPU word after it is in [gpu-word-after-display-area.md](gpu-word-after-display-area.md).
