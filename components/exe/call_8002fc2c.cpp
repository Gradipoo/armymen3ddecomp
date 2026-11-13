// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002fc2c.hpp"

namespace am3d::exe {
namespace {

void store_le(std::uint8_t* dest, std::uint32_t value) {
    dest[0] = static_cast<std::uint8_t>(value);
    dest[1] = static_cast<std::uint8_t>(value >> 8);
    dest[2] = static_cast<std::uint8_t>(value >> 16);
    dest[3] = static_cast<std::uint8_t>(value >> 24);
}

}

// Behavior reference: docs/research/re/call-8002fc2c.md.
void call_8002fc2c(std::uint8_t* object, std::uint32_t second) {
    (void)second;
    store_le(object + kCall8002fc2cStoreOffset, kCall8002fc2cStored);
    // gap: jal 0x800302a4. a0 is the object. a1 is the second argument. The return address is 0x8002fc54.
}

}
