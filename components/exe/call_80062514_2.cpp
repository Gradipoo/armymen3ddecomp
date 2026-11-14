// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062514_2.hpp"

#include "call_80062548_2.hpp"
#include "call_80075198_7.hpp"

namespace am3d::exe {

unsigned call_80062514_2(int result, unsigned* slot, int* argument) {
    if (result != 0) {
        return 0;
    }
    slot[2] = 0;
    *argument = 5;
    call_80075198_7();
    call_80062548_2(0);
    return 0x80075198;
}

}
