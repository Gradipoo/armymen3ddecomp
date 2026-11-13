// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010cc4.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80010cc4.md.
void call_80010cc4(const std::uint8_t* object, std::uint32_t second) {
    (void)object;
    (void)second;
    // gap: jal 0x8002fc2c. a0 is the object. a1 is the second argument. The return address is 0x80010cd0.
}

}
