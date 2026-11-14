// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025534.hpp"

#include "call_8007d12c_2.hpp"

namespace am3d::exe {

void call_80025534(std::uint32_t& a0) {
    a0 = 2;
    std::uint32_t word = 1;
    std::uint32_t s0 = 0;
    (void)call_8007d12c_2(word, s0, 0x8009f510u, 0x8002553cu);
}

}
