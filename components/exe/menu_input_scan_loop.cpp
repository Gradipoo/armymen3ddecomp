// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"

namespace am3d::exe {

MenuInputScanLoopResult run_menu_input_scan_frames(
    std::uint32_t count, std::uint32_t (*pad_get_state)(std::uint32_t port),
    const std::uint8_t* table, MenuInputScanIndices& indices,
    std::uint32_t& sp20, std::uint32_t fp, std::uint32_t compare_word,
    std::uint8_t*& record, MenuInputScanState& scan, std::uint32_t limit) {
    MenuInputScanLoopResult result{};
    while (count > 0u) {
        indices.menu_table_index = scan.table_cursor;
        const std::uint32_t step_fp =
            (result.frames_run == 0u) ? fp : scan.fp;
        result.last_step = menu_input_scan_step(
            indices.stack_word_18, scan.s7, pad_get_state, table,
            indices.menu_table_index, indices.menu_table_bytes, sp20, step_fp,
            compare_word, record, indices.stack_word_58, scan, limit);
        result.frames_run += 1u;
        count -= 1u;
        if (!result.last_step.loop_again) {
            break;
        }
    }
    return result;
}

}