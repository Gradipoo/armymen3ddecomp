# SDK

Hits from `python3 tools/sdk_match.py` on the local PS-X EXE.

`0x8007faf8` is `word_fill`.
`0x8007fb1c` is `byte_compare`.
`0x8008824c` is `gpu_store`.

`tools/sdk_names.txt` has 383 named rows, with 375 distinct labels. They come from the union of signature hits for Psy-Q versions 260, 300, 330, 340, 350, 370, 400, 410, 420, 430, 440, 450, 460, and 470. An address was accepted when that union had one non-internal name. The public source is [psx_psyq_signatures](https://github.com/lab313ru/psx_psyq_signatures/tree/e9e46e7e133ef275a79bfce650924f98edb086bc). That checkout stays under `build/`. The signature bytes are not in this tree.

`loc_` and `text_` labels were dropped. They are internal offsets, not public function names. The reviewed union has 203 addresses with more than one remaining name. They stay unnamed. A label can appear at more than one address. Accepted rows have hits in between one and fourteen versions. Only 39 rows have hits in all fourteen. Repeated versions are not independent confirmations and do not identify the game's SDK version.

Correction, November 13, 2026: the [reviewed R03 audit](../../workers/results/sdk-provenance.md) reproduced all 383 table rows without changing names. The coordinator reran the unchanged scanner for all fourteen versions and independently reproduced the table and coverage counts. The earlier claim that every version agreed at every accepted address was unsupported. The earlier ambiguous-address count was 206; this audit found 203. No cause for that difference was established. No external name confirmations were performed.

These functions are named. A later note that calls one of them records the name, the arguments, and the return address. It does not disassemble the body again.

Unmatched bytes stay untraced.
