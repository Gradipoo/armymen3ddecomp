// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b10.hpp"

#include "call_80060b2c.hpp"
#include "call_8007abf8.hpp"

namespace am3d::exe {

void call_80060b10(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& a2, std::uint32_t& a3,
    std::uint32_t& s0, std::uint16_t slot[9], std::uint32_t& word_14, std::uint32_t& word_18,
    std::uint32_t& word_1c) {
    s0 = 0x800dd2d8u;
    a0 = s0;
    a1 = 0x1000u;
    a2 = 0xa00u;
    a3 = a1;
    call_8007abf8(a1, a2, a3, slot, word_14, word_18, word_1c);
    call_80060b2c(a0, word_14, word_18);
}

}
