// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800254f0.hpp"

#include "call_800636b8.hpp"

namespace am3d::exe {

void call_800254f0(std::uint32_t& a0) {
    a0 = 0x800bfe8cu;
    std::uint8_t dest[6] = {};
    std::uint32_t length = 0;
    call_800636b8(dest, length);
}

}
