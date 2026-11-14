// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80023794_2.hpp"

#include "call_80063b34.hpp"

namespace am3d::exe {

void call_80023794_2(unsigned* a0, int* a1) {
    *a0 = 0x800bfdbc;
    *a1 = 0;
    call_80063b34();
}

}
