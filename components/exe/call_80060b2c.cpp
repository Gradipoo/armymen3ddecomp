// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b2c.hpp"

#include "call_80060b3c.hpp"
#include "call_80060b4c.hpp"

namespace am3d::exe {

std::uint32_t call_80060b2c(std::uint32_t& a0, std::uint32_t& word_14, std::uint32_t& word_18,
    std::uint32_t& stored, std::uint32_t& s0) {
    a0 = 0x1000u;
    word_14 = 0;
    word_18 = 0;
    call_80060b4c(a0, stored);
    return call_80060b3c(0x80025478u, s0, 0x8009f510u);
}

}
