// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b2c.hpp"

#include "call_80060b4c.hpp"

namespace am3d::exe {

void call_80060b2c(std::uint32_t& a0, std::uint32_t& word_14, std::uint32_t& word_18,
    std::uint32_t& stored) {
    a0 = 0x1000u;
    word_14 = 0;
    word_18 = 0;
    call_80060b4c(a0, stored);
}

}
