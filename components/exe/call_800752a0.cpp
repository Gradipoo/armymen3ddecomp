// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800752a0.hpp"
#include "call_8005c014.hpp"
namespace am3d::exe {
void call_800752a0() {
    if (call_8005c014(0) == 0) {
        // gap: jr at 0x80075438. The saved ra is not stated. No traced entry has a0 2.
        return;
    }
}
}
