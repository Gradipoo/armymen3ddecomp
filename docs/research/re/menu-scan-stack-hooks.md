# Menu scan stack hooks (sp+0x18, sp+0x1c, sp+0x28)

Integration note. Does not invent `0x800dd764` or claim retail loop counts.

## sp+0x18 (`stack_word_18`)

[call-80064e40.md](call-80064e40.md) loads this word into the `PadGetState` port
argument as `(stack_word_18 << 4) | s7`. [call-80064e58.md](call-80064e58.md)
measured entries used `a0=0`, so host smoke and headless ctests keep
`MenuInputScanIndices::stack_word_18` at zero.

## sp+0x1c (`stack_word_1c`)

[call-80065168.md](call-80065168.md) compares `s7` to the limit at `sp+0x1c`
for the `bne` back to `0x80064e40`. Live retail value is unstated. The loop
API passes the caller limit as `stack_word_1c` into `menu_input_scan_step` and
`menu_scan_should_loop`. Synthetic tests use small limits (often four or eight).

## sp+0x28 (`stack_word_28`)

The shared tail at `0x80065168` loads `sp+0x28`, adds four, and stores it in
the delay slot on both branch sides. An optional `std::uint32_t*` on
`run_menu_input_scan_frames` and `menu_input_scan_step` models that word when
the compare-word-four path enters `call_80065168`. When the pointer is null,
`table_cursor` still advances four and the live stack word stays unhooked.

Headless smoke passes `&indices.stack_word_28` with `compare_word` four and
asserts the word becomes four after one compare-four frame.

## Gap

Retail words at `sp+0x1c` and `sp+0x28`, and the dword at `0x800dd764`, stay
unstated outside synthetic limits. Task 7 transition replay is still open.