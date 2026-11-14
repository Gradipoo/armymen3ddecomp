// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060aac.md.
// first is nine halfwords. The three later arguments are the other halfwords.
void call_80060aac(std::uint32_t& a0, std::uint32_t& cleared_word, std::uint16_t first[9],
    std::uint16_t& second_4, std::uint16_t& second_a, std::uint16_t& second_10,
    std::uint16_t& slot0, std::uint16_t& slot6, std::uint16_t& slot12, std::uint16_t& slot2,
    std::uint16_t& slot8, std::uint16_t& slot14, std::uint32_t& a1, std::uint32_t& a2,
    std::uint32_t& a3, std::uint32_t& s0);

}
