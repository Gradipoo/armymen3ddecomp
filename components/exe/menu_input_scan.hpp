// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_80064e40.hpp"
#include "call_80064e68.hpp"
#include "call_800650d0.hpp"
#include "call_80064dc8.hpp"
#include "call_80064dd8.hpp"
#include "call_80064dfc.hpp"
#include "call_80064dec.hpp"
#include "call_80065194.hpp"
#include "call_800651c8.hpp"

#include <cstdint>

namespace am3d::exe {

struct MenuInputScanStep {
    MenuLoopHead head;
    PadStateDispatch dispatch;
    bool tail_ran;
    bool loop_again;
    MenuLoopFallthrough loop_exit;
    bool loop_exit_recorded;
    MenuLoopTaken651c8 loop_taken_651c8;
    bool loop_taken_651c8_recorded;
    MenuLoopBody64dc8 loop_body_64dc8;
    bool loop_body_64dc8_recorded;
    MenuLoopBody64dd8 loop_body_64dd8;
    bool loop_body_64dd8_recorded;
    MenuLoopBody64dfc loop_body_64dfc;
    bool loop_body_64dfc_recorded;
    MenuLoopBody64dec loop_body_64dec;
    bool loop_body_64dec_recorded;
    bool compare_four_ran;
    bool compare_four_to_65168;
    std::uint32_t compare_four_v0;
};

// Integration of the reconstructed menu scan pieces.
// Behavior notes: docs/research/re/menu-input-scan.md.
// pad_get_state is PadGetState. Table bytes drive mask and bit paths.
MenuInputScanStep menu_input_scan_step(
    std::uint32_t& stack_word_18, std::uint32_t loop_s7,
    std::uint32_t (*pad_get_state)(std::uint32_t port),
    const std::uint8_t* menu_table, std::uint32_t& menu_table_index,
    std::uint32_t menu_table_bytes, std::uint32_t& stack_word_20,
    std::uint32_t fp, std::uint32_t compare_word_dd730, std::uint8_t*& record,
    std::uint32_t stack_word_58, MenuInputScanState& scan,
    std::uint32_t& stack_word_1c,
    const std::uint32_t* test_inject_s6 = nullptr,
    std::uint32_t* stack_word_28 = nullptr,
    const PadStateDispatchInject* test_inject_pad_dispatch = nullptr,
    const std::uint8_t* test_inject_s1_lbu = nullptr);

}
