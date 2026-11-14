// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025470.hpp"

#include "call_80060aac.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025470.md.
// The arriving a0 is 0x800d0000. The callee replaces it.
void call_80025470(std::uint32_t& a0, std::uint32_t& cleared_word, std::uint16_t first[9],
    std::uint16_t& second_4, std::uint16_t& second_a, std::uint16_t& second_10) {
    std::uint16_t slot0 = 0;
    std::uint16_t slot6 = 0;
    std::uint16_t slot12 = 0;
    std::uint16_t slot2 = 0;
    std::uint16_t slot8 = 0;
    std::uint16_t slot14 = 0;
    std::uint32_t a1 = 0;
    std::uint32_t a2 = 0;
    std::uint32_t a3 = 0;
    std::uint32_t s0 = 0x8009f510u;
    call_80060aac(a0, cleared_word, first, second_4, second_a, second_10, slot0, slot6,
        slot12, slot2, slot8, slot14, a1, a2, a3, s0);
}

}
