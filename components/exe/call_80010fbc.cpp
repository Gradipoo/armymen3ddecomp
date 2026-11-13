// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010fbc.hpp"

namespace am3d::exe {
namespace {

void store_le(std::uint8_t* dest, std::uint32_t value) {
    dest[0] = static_cast<std::uint8_t>(value);
    dest[1] = static_cast<std::uint8_t>(value >> 8);
    dest[2] = static_cast<std::uint8_t>(value >> 16);
    dest[3] = static_cast<std::uint8_t>(value >> 24);
}

}

// Behavior reference: docs/research/re/call-80010fbc.md.
void call_80010fbc(std::uint8_t* object) {
    store_le(object + kCall80010fbcStoreOffset, kCall80010fbcStored);
    // gap: jal 0x8002fb9c. a0 is the object. The return address is 0x80010fdc.
}

}
