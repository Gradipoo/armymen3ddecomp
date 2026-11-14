# GPU word after the display-area command

The three-word fill is the packet in [call-80076274.md](call-80076274.md). Tag length 3 and command byte 2. `DrawPrim` sends it. The return is `0x8007641c`.

[display-environment-layout.md](display-environment-layout.md) records the display environment that `PutDispEnv` submits before the next fill. Mode on this boot is 2. The interlace byte and the RGB24 byte are both zero.

[gpu-display-area-after-fill.md](gpu-display-area-after-fill.md) records the first GPU store in that submit. `lui` at `0x80086e48` writes `0x05000000`. The display x and y halfwords are not quoted, so that note does not state the full word. The next instruction is `jal 0x80086230` at `0x80086ef0`. The instruction word is `0x0c02188c`.

[call-80086ef8.md](call-80086ef8.md) continues after that call returns. `s0` becomes `0x08000002`. `jalr` at `0x80086fcc` calls `gpu_store`. The delay slot copies `s0` into `a0`. The stored word is `0x08000002`. The port is `0x1f801814`. The return address is `0x80086fd4`. The return value is `0x8`. This note does not enter `gpu_store` again.

`components/platform/fill_vram.cpp` cites that word as `next_gpu_word`. The sink still paints only the three-word fill. This word is not a fill packet. This note does not state a VRAM write from it.
