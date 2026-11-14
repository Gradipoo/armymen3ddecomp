// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434.hpp"

#include "call_80061f80.hpp"

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
    unsigned char parsed[9];
    int index = 0;
    unsigned first = 1;
    unsigned second = 1;
    unsigned third = 0;
    unsigned slot[15];
    for (int i = 0; i < 15; ++i) {
        slot[i] = 1;
    }
    call_80061f80(parsed, &index, &first, &second, &third, slot);
}

}
