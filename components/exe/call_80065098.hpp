// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuS6TakenPath {
    std::uint32_t stored_word;
    bool complemented_bit_0x80;
    bool branch_to_650b4;
};

// Behavior reference: docs/research/re/call-80065098.md.
MenuS6TakenPath call_80065098(std::uint8_t* record, std::uint32_t complemented_a0,
                                std::uint32_t v0, std::uint32_t& table_cursor_s1);

}