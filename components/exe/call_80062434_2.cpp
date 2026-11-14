// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434_2.hpp"

#include "call_80061f80_2.hpp"

namespace am3d::exe {

void call_80062434_2(unsigned char* dest) {
    dest[0] = 0x5c;
    dest[1] = 0x6d;
    dest[2] = 0x69;
    dest[3] = 0x73;
    dest[4] = 0x73;
    dest[5] = 0x69;
    dest[6] = 0x6f;
    dest[7] = 0x6e;
    dest[8] = 0x2e;
    dest[9] = 0x69;
    dest[10] = 0x6e;
    dest[11] = 0x69;
    dest[12] = 0x00;
    unsigned char parsed[4];
    int index = 0;
    call_80061f80_2(parsed, &index);
}

}
