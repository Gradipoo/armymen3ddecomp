// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061f80.hpp"

namespace am3d::exe {

void call_80061f80(unsigned char* dest, int* index) {
    dest[0] = 0x6c;
    dest[1] = 0x65;
    dest[2] = 0x67;
    dest[3] = 0x61;
    *index = 3;
}

}
