// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025470.hpp"

#include "call_80060aac.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025470.md.
// The arriving a0 is 0x800d0000. The callee replaces it.
void call_80025470(std::uint32_t& a0, std::uint32_t& cleared_word, std::uint16_t first[9],
    std::uint16_t& second_4, std::uint16_t& second_a, std::uint16_t& second_10) {
    call_80060aac(a0, cleared_word, first, second_4, second_a, second_10);
}

}
