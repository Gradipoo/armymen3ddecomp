// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010d38.hpp"

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

// Behavior reference: docs/research/re/call-80010d38.md,
// docs/research/re/call-80010d6c.md, and docs/research/re/call-80010d74.md.
void call_80010d38(std::uint8_t* object, std::uint32_t second, Call80010d38Fn callee,
                   Call80010d74Fn nonzero) {
    if (second != 0) {
        // gap: unnamed callee at 0x8001d434. a0 is the second argument. The return address is 0x80010d7c.
        nonzero(second);
        // gap: continuation at 0x80010d7c is not traced.
        return;
    }
    const std::uint32_t field = load_le(object + kCall80010d38WordOffset);
    if (field != 0) {
        // gap: 0x8001b298 calls __builtin_delete at 0x8001b214. a0 is the word at offset 0x74.
        callee(field);
    }
    store_le(object + kCall80010d38WordOffset, 0);
}

}
