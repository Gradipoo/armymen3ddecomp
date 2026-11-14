// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074b4c.hpp"
#include "call_8005be28.hpp"
#include "call_8005be3c.hpp"
#include "call_8005be50.hpp"
namespace am3d::exe {
void call_80074b4c(std::uint32_t& slot_c0, std::uint32_t& slot_c4, std::uint32_t& slot_c8) {
    call_8005be28(0x80074a90u, slot_c0);
    call_8005be3c(0, slot_c4);
    call_8005be50(0, slot_c8);
    // gap: CdControl at 0x80081a68. a0 is 2. a1 is 0x800e1548. a2 is 0. v0 is not stated. bne at 0x80074ba8 is not followed.
}
}
