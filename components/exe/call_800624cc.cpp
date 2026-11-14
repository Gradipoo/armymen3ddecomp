// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc.hpp"

#include "call_80075198_3.hpp"

namespace am3d::exe {

unsigned call_800624cc(int result, int* argument) {
    if (result == 0) {
        *argument = 5;
        call_80075198_3();
        return 0x80075198;
    }
    return 0;
}

}
