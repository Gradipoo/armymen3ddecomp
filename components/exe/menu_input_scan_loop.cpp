// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"

#include "menu_table_sequence.hpp"

namespace am3d::exe {

MenuInputScanLoopResult run_menu_input_scan_frames(
    std::uint32_t count, std::uint32_t (*pad_get_state)(std::uint32_t port),
    std::uint8_t* table, MenuInputScanIndices& indices, std::uint32_t& sp20,
    std::uint32_t fp, std::uint32_t compare_word, std::uint8_t*& record,
    MenuInputScanState& scan, std::uint32_t stack_word_1c,
    MenuTableSequencer* table_sequencer, std::uint32_t* stack_word_28) {
    MenuInputScanLoopResult result{};
    while (count > 0u) {
        if (table_sequencer != nullptr) {
            table_sequencer->apply_frame(table, indices.menu_table_bytes, scan.table_cursor);
        }
        indices.menu_table_index = scan.table_cursor;
        const std::uint32_t step_fp =
            (result.frames_run == 0u) ? fp : scan.fp;
        result.last_step = menu_input_scan_step(
            indices.stack_word_18, scan.s7, pad_get_state, table,
            indices.menu_table_index, indices.menu_table_bytes, sp20, step_fp,
            compare_word, record, indices.stack_word_58, scan, stack_word_1c, nullptr,
            stack_word_28);
        result.frames_run += 1u;
        count -= 1u;
        if (!result.last_step.loop_again) {
            break;
        }
    }
    return result;
}

}