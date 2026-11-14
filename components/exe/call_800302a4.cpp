// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800302a4.hpp"

#include "call_8002fe4c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800302a4.md.
void call_800302a4(std::uint8_t* object, std::uint32_t second) {
    const auto byte = static_cast<std::int8_t>(object[kCall800302a4ByteOffset]);
    if (byte < 0 || byte >= 3) {
        return;
    }
    if (byte != 0) {
        // gap: jal 0x80079b24. a0 is 0x8009f368 plus the byte shifted left by 5.
        // a1 is the object. The return address is 0x800302f8.
        return;
    }
    (void)call_8002fe4c(object, second);
}

}
