// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be9c.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_8005be9c(std::uint32_t& slot) {
    std::uint32_t saved = 0;
    call_8005be28(0x8005be64u, saved);
    slot |= 2u;
    // gap: CdControl at 0x80081a68. a0 is 9. a1 is 0. a2 is 0. The return address is 0x8005bed8. v0 is not stated.
    return slot;
}
}
