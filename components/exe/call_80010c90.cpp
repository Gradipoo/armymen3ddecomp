// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010c90.hpp"

#include "call_80010cc4.hpp"
#include "call_8001b298.hpp"

namespace am3d::exe {
namespace {

std::uint32_t load_le(const std::uint8_t* src) {
    return static_cast<std::uint32_t>(src[0]) |
           (static_cast<std::uint32_t>(src[1]) << 8) |
           (static_cast<std::uint32_t>(src[2]) << 16) |
           (static_cast<std::uint32_t>(src[3]) << 24);
}

void store_le(std::uint8_t* dest, std::uint32_t value) {
    dest[0] = static_cast<std::uint8_t>(value);
    dest[1] = static_cast<std::uint8_t>(value >> 8);
    dest[2] = static_cast<std::uint8_t>(value >> 16);
    dest[3] = static_cast<std::uint8_t>(value >> 24);
}

}

// Behavior reference: docs/research/re/call-80010c90.md.
void call_80010c90(std::uint8_t* object, std::uint32_t second) {
    (void)second;
    store_le(object + kCall80010c90StoreOffset, kCall80010c90Stored);
    const std::uint32_t field = load_le(object + kCall80010c90WordOffset);
    if (field != 0) {
        call_8001b298(field);
    }
    call_80010cc4(object, second);
}

}
