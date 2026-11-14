// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010fbc.hpp"

#include "call_8002fb9c.hpp"
#include "table_8009f0b4.hpp"

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
    // The delay slot does not write a1. call_8002fb9c does not read it.
    call_8002fb9c(object, 0, kTable8009f0b4.data());
}

}
