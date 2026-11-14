// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002553c.hpp"

#include "call_80063668.hpp"

namespace am3d::exe {

void call_8002553c(std::uint32_t& a0, std::uint32_t& s0) {
    s0 = 0x8009f444u;
    a0 = s0;
    std::uint32_t a1 = 1;
    std::uint8_t copied[9];
    call_80063668(copied, a1, a0);
}

}
