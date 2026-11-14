// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062474.hpp"

#include "call_80075198_2.hpp"

namespace am3d::exe {

unsigned call_80062474(unsigned* slot) {
    slot[0] = 0;
    slot[1] = 0;
    slot[4] = 0;
    slot[5] = 0;
    slot[6] = 0;
    slot[9] = 0;
    slot[10] = 0;
    slot[13] = 0;
    slot[14] = 0;
    call_80075198_2();
    return 0x80075198;
}

}
