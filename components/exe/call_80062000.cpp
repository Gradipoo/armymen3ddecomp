// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062000.hpp"

#include "call_80062474_2.hpp"

namespace am3d::exe {

unsigned call_80062000(unsigned* first, unsigned* second, unsigned* third) {
    *first = 0;
    *second = 0;
    *third = 0x800bfdbc;
    unsigned slot[15];
    for (int i = 0; i < 15; ++i) {
        slot[i] = 1;
    }
    call_80062474_2(slot);
    return 0;
}

}
