// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061ff0_2.hpp"

namespace am3d::exe {

void call_80061ff0_2(unsigned char* dest, int* index) {
    dest[4] = 0x73;
    dest[5] = 0x69;
    dest[6] = 0x6f;
    dest[7] = 0x6e;
    dest[8] = 0x2e;
    *index = 9;
}

}
