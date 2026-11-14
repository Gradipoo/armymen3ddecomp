// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f930_2.hpp"

namespace am3d::exe {

unsigned call_8007f930_2(unsigned a0, unsigned a2) {
    if (7 < a2) {
        return a0 & 3;
    }
    return 1;
}

}
