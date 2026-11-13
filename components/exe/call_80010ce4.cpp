// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010ce4.hpp"

namespace am3d::exe {
namespace {

std::uint32_t load_le(const std::uint8_t* src) {
    return static_cast<std::uint32_t>(src[0]) |
           (static_cast<std::uint32_t>(src[1]) << 8) |
           (static_cast<std::uint32_t>(src[2]) << 16) |
           (static_cast<std::uint32_t>(src[3]) << 24);
}

std::int32_t load_le_half(const std::uint8_t* src) {
    const std::uint16_t bits = static_cast<std::uint16_t>(
        src[0] | (static_cast<std::uint16_t>(src[1]) << 8));
    return static_cast<std::int16_t>(bits);
}

}

// Behavior reference: docs/research/re/call-80010ce4.md.
void call_80010ce4(const std::uint8_t* object, Call80010ce4Args& args) {
    args.invoke = false;
    const std::uint32_t field = load_le(object + kCall80010ce4WordOffset);
    if (field == 0) {
        // gap: the branch target 0x80010d18 is not traced.
        return;
    }
    args.invoke = true;
    args.a0 = 3;
    args.a1 = load_le_half(object + kCall80010ce4HalfOffset);
    args.a2 = load_le(object + kCall80010ce4FieldOffset);
    args.a3 = 0;
    args.stack_arg = 0;
    // gap: call 0x8003852c. a0 is 3. a1 is the halfword at offset 0x70. a2 is the word at offset 0x6c. a3 is 0. The fifth argument is 0. The return address is 0x80010d18.
}

}
