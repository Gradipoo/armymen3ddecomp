// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002fb9c.hpp"

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

// Behavior reference: docs/research/re/call-8002fb9c.md.
void call_8002fb9c(std::uint8_t* object, std::uint32_t second,
                   const std::uint8_t* table) {
    (void)second;
    object[0x35] = 0xff;
    object[0x34] = 0x1;
    store_le(object, 0);
    store_le(object + 0x24, 0);
    for (std::size_t i = 0; i < kCall8002fb9cCopyWords; ++i) {
        const std::size_t offset = i * 4;
        store_le(object + kCall8002fb9cCopyOffset + offset,
                 load_le(table + offset));
    }
    object[0x36] = 0;
    object[0x37] = 0;
    // gap: jal 0x8007f920. a0 is the object plus 0x28. a1 is 0. a2 is 0xc. The return address is 0x8002fc1c.
}

}
