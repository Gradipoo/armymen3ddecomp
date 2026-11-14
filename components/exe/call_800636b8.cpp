// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800636b8.hpp"

namespace am3d::exe {

void call_800636b8(std::uint8_t* dest, std::uint32_t& length) {
    // strcpy at 0x800800dc. Destination is the caller's buffer. Source is
    // 0x800bfe8c. The return address is 0x800636e0.
    dest[0] = 0x64;
    dest[1] = 0x61;
    dest[2] = 0x74;
    dest[3] = 0x61;
    dest[4] = 0x5c;
    dest[5] = 0;
    // strlen at 0x8008012c. a0 is 0x800bfe8c. The return address is 0x800636e8.
    length = 5;
}

}
