// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80023848_2.hpp"

#include "call_80023794_2.hpp"

namespace am3d::exe {

unsigned call_80023848_2(int* second, int* third) {
    *second = 0;
    *third = 1;
    unsigned path = 0x800bfdbc;
    int cleared = 1;
    call_80023794_2(&path, &cleared);
    return 0x800bfdbc;
}

}
