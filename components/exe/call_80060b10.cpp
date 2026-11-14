// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b10.hpp"

namespace am3d::exe {

void call_80060b10(std::uint32_t& a0, std::uint32_t& a1, std::uint32_t& a2, std::uint32_t& a3,
    std::uint32_t& s0) {
    s0 = 0x800dd2d8u;
    a0 = s0;
    a1 = 0x1000u;
    a2 = 0xa00u;
    a3 = a1;
    // gap: unnamed call at 0x8007abf8. a0 is 0x800dd2d8. a1 is 0x1000. a2 is 0xa00.
    // a3 is 0x1000. The return address is 0x80060b2c.
}

}
