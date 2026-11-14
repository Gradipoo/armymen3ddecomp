// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc_2.hpp"

#include "call_80062514_2.hpp"
#include "call_80075198_6.hpp"

namespace am3d::exe {

unsigned call_800624cc_2(int result, int* argument) {
    if (result == 0) {
        *argument = 5;
        call_80075198_6();
        unsigned slot[3] = {1, 1, 1};
        int next = 0;
        call_80062514_2(0, slot, &next);
        return 0x80075198;
    }
    return 0;
}

}
