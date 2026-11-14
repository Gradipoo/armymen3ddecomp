// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002554c.hpp"

#include "call_8001d590.hpp"

namespace am3d::exe {

void call_8002554c(unsigned* a0, int* a2) {
    *a0 = 0x8009f444;
    *a2 = 0;
    call_8001d590(*a2);
}

}
