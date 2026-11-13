// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010f00.hpp"

namespace am3d::exe {
namespace {

void store_le(std::uint8_t* dest, std::uint32_t value) {
    dest[0] = static_cast<std::uint8_t>(value);
    dest[1] = static_cast<std::uint8_t>(value >> 8);
    dest[2] = static_cast<std::uint8_t>(value >> 16);
    dest[3] = static_cast<std::uint8_t>(value >> 24);
}

}

// Behavior reference: docs/research/re/call-80010f00.md
// and docs/research/re/call-80010f28.md.
std::uint32_t call_80010f00(Call80010f00Fn callee, std::uint8_t* first,
                            std::uint32_t second, std::uint32_t third,
                            std::uint32_t fourth, std::uint32_t fifth) {
    // gap: unnamed jal 0x80010e34. a0 is the second argument. a1 is the third. a2 is the fourth. a3 is the fifth. The return address is 0x80010f28.
    const std::uint32_t packed = callee(second, third, fourth, fifth);
    store_le(first + kCall80010f00StoreOffset, packed);
    return packed;
}

}
