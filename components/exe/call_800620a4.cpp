// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800620a4.hpp"

#include "call_80062474.hpp"

namespace am3d::exe {

unsigned call_800620a4(unsigned* first, unsigned* second, unsigned* third, unsigned* slot) {
    *first = 0;
    *second = 0;
    *third = 0x8009f444;
    call_80062474(slot);
    return 0;
}

}
