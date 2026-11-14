// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007569c.hpp"
#include "call_8005be28.hpp"
#include "call_8005be50.hpp"
#include "call_8005be9c.hpp"
namespace am3d::exe {
void call_8007569c(std::uint32_t a0, std::uint32_t& flag, std::uint32_t& link, std::uint32_t& slot_c0, std::uint32_t& slot_c8, std::uint32_t& cd_slot) {
    (void)a0;
    const std::uint32_t saved = link;
    call_8005be28(0, slot_c0);
    link = 0;
    call_8005be50(0, slot_c8);
    flag &= ~4u;
    call_8005be9c(cd_slot);
    if (saved == 0) {
        // gap: v0 from call_8005be9c is not stated. The arriving ra is not stated.
        return;
    }
}
}
