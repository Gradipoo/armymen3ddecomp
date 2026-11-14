// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800302a4.hpp"

#include "call_8002fe4c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800302a4.md.
void call_800302a4(std::uint8_t* object, std::uint32_t second) {
    const auto byte = static_cast<std::int8_t>(object[kCall800302a4ByteOffset]);
    if (byte < 0) {
        return;
    }
    if (byte != 0) {
        // gap: fall-through at 0x800302dc. The byte is positive and not zero.
        return;
    }
    (void)call_8002fe4c(object, second);
}

}
