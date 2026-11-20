// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuInputScanState {
    std::uint32_t s4;
    std::uint32_t index;
    std::uint32_t fp;
    std::uint32_t s7;
    std::uint32_t table_cursor;
};

// Behavior reference: docs/research/re/call-800650d0.md.
bool call_800650d0(std::uint8_t*& record, std::uint32_t complemented_input,
                   std::uint32_t stack_word_58, MenuInputScanState& scan,
                   std::uint32_t loop_limit);

}