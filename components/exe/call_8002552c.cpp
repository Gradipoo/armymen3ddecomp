// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002552c.hpp"

#include "call_8007d12c.hpp"

namespace am3d::exe {

void call_8002552c(std::uint32_t& a0) {
    a0 = 3;
    std::uint32_t word = 1;
    std::uint32_t s0 = 0;
    (void)call_8007d12c(word, s0, 0x8009f510u, 0x80025534u);
}

}
