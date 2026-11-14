// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062514.hpp"

namespace am3d::exe {

unsigned call_80062514(int result, unsigned* slot, int* argument) {
    if (result != 0) {
        return 0;
    }
    slot[2] = 0;
    *argument = 5;
    return 0x80075198;
}

}
