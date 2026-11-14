// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b2c.hpp"

namespace am3d::exe {

void call_80060b2c(std::uint32_t& a0, std::uint32_t& word_14, std::uint32_t& word_18) {
    a0 = 0x1000u;
    word_14 = 0;
    word_18 = 0;
    // gap: unnamed call at 0x80060b4c. a0 is 0x1000. The return address is 0x80060b3c.
}

}
