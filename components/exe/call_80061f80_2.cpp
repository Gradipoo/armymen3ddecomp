// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061f80_2.hpp"

#include "call_80061ff0_2.hpp"

namespace am3d::exe {

void call_80061f80_2(unsigned char* dest, int* index) {
    dest[0] = 0x5c;
    dest[1] = 0x6d;
    dest[2] = 0x69;
    dest[3] = 0x73;
    *index = 3;
    call_80061ff0_2(dest, index);
}

}
