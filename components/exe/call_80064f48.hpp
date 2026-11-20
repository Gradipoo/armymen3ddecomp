// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuMaskPathResult {
    std::uint16_t raw_halfword;
    std::uint32_t complemented;
    bool entered;
    bool compare_eq_four;
    bool branch_to_65168;
    std::uint32_t compare_four_v0;
};

// Behavior reference: docs/research/re/call-80064f48.md.
MenuMaskPathResult call_80064f48(std::uint32_t& stack_word_20, std::uint32_t fp,
                                 const std::uint8_t* table, std::uint32_t& index,
                                 std::uint32_t table_bytes, std::uint32_t compare_word,
                                 std::uint8_t* record);

}