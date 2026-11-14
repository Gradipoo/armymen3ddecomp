// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc_3.hpp"

namespace am3d::exe {

unsigned call_800624cc_3(int result, int* argument) {
    if (result == 0) {
        *argument = 5;
        return 0x80075198;
    }
    return 0;
}

}
