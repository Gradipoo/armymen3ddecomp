// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800302a4.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800302a4.md.
void call_800302a4(std::uint8_t* object, std::uint32_t second) {
    (void)second;
    const auto byte = static_cast<std::int8_t>(object[kCall800302a4ByteOffset]);
    if (byte != 0) {
        // gap: the branch to 0x800302d4 is not traced.
        return;
    }
    // gap: jal 0x8002fe4c. a0 is the object. a1 is the second argument. The return address is 0x800302cc.
}

}
