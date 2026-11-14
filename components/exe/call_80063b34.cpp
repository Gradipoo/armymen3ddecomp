// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063b34.hpp"

#include "call_80062434_2.hpp"

namespace am3d::exe {

unsigned call_80063b34() {
    unsigned char copied[13] = {};
    call_80062434_2(copied);
    return 0x800bfdbc;
}

}
