// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "menu_input_scan.hpp"

#include <cstdint>

namespace am3d::exe {

struct MenuTableSequencer;

struct MenuInputScanIndices {
    std::uint32_t stack_word_18;
    std::uint32_t menu_table_index;
    std::uint32_t menu_table_bytes;
    std::uint32_t stack_word_58;
};

struct MenuInputScanLoopResult {
    std::uint32_t frames_run;
    MenuInputScanStep last_step;
};

// Multi-frame integration over menu_input_scan_step.
// Behavior notes: docs/research/re/menu-input-scan-loop.md.
// Stops when count reaches zero or the last step sets loop_again false.
// Before each step, menu_table_index follows scan.table_cursor and fp follows
// scan.fp so loop re-entry matches the cited tail updates.
MenuInputScanLoopResult run_menu_input_scan_frames(
    std::uint32_t count, std::uint32_t (*pad_get_state)(std::uint32_t port),
    std::uint8_t* table, MenuInputScanIndices& indices, std::uint32_t& sp20,
    std::uint32_t fp, std::uint32_t compare_word, std::uint8_t*& record,
    MenuInputScanState& scan, std::uint32_t limit,
    MenuTableSequencer* table_sequencer = nullptr);

}