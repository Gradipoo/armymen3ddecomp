// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061ff0.hpp"

#include "call_800620a4.hpp"

namespace am3d::exe {

void call_80061ff0(unsigned char* dest, int* index, unsigned* first, unsigned* second, unsigned* third) {
    dest[4] = 0x6c;
    dest[5] = 0x2e;
    dest[6] = 0x62;
    dest[7] = 0x67;
    dest[8] = 0x00;
    *index = 8;
    call_800620a4(first, second, third);
}

}
