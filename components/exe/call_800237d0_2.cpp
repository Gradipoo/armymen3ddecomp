// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800237d0_2.hpp"

namespace am3d::exe {

unsigned call_800237d0_2(int result, int fourth) {
    if (result == 0 && fourth != 0) {
        return 0x800bfdbc;
    }
    return 0;
}

}
