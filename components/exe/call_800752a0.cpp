// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800752a0.hpp"
#include "call_8005c014.hpp"
namespace am3d::exe {
void call_800752a0() {
    const std::uint32_t v0 = call_8005c014(0);
    (void)v0;
    // gap: beq at 0x800752a8. v0 is 0, so that branch would be taken. No traced entry has a0 2.
}
}
