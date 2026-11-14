// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800302a4.hpp"

#include "call_8002fe4c.hpp"
#include "call_80079b24.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800302a4.md.
void call_800302a4(std::uint8_t* object, std::uint32_t second) {
    const auto byte = static_cast<std::int8_t>(object[kCall800302a4ByteOffset]);
    if (byte < 0 || byte >= 3) {
        return;
    }
    if (byte != 0) {
        const std::uint32_t a0 = 0x8009f368u + (static_cast<std::uint32_t>(byte) << 5);
        (void)call_80079b24(a0);
        // gap: lw at 0x800302f8 loads offset 0x24. That word is not stated.
        return;
    }
    (void)call_8002fe4c(object, second);
}

}
