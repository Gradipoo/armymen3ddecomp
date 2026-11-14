// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434.hpp"

namespace am3d::exe {

void call_80062434(std::uint8_t* dest, std::uint32_t& a0, std::uint32_t source) {
    // strcpy at 0x800800dc. Destination is 0x800dd668 on this entry.
    // Source is 0x8009f444. The return address is 0x80062460.
    dest[0] = 0x6c;
    dest[1] = 0x65;
    dest[2] = 0x67;
    dest[3] = 0x61;
    dest[4] = 0x6c;
    dest[5] = 0x2e;
    dest[6] = 0x62;
    dest[7] = 0x67;
    dest[8] = 0;
    a0 = source;
    // gap: unnamed call at 0x80061f80. a0 is the source address.
    // The return address is 0x80062474.
}

}
