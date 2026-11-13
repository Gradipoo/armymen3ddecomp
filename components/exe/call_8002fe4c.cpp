// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002fe4c.hpp"

namespace am3d::exe {
namespace {

std::int32_t load_s32(const std::uint8_t* src) {
    const auto word = static_cast<std::uint32_t>(src[0]) |
                      (static_cast<std::uint32_t>(src[1]) << 8) |
                      (static_cast<std::uint32_t>(src[2]) << 16) |
                      (static_cast<std::uint32_t>(src[3]) << 24);
    return static_cast<std::int32_t>(word);
}

std::int32_t smaller(std::int32_t left, std::int32_t right) {
    return left < right ? left : right;
}

std::int32_t larger(std::int32_t left, std::int32_t right) {
    return left < right ? right : left;
}

}

// Behavior reference: docs/research/re/call-8002fe4c.md.
Call8002fe4cPrefix call_8002fe4c(const std::uint8_t* object, std::uint32_t second) {
    (void)second;
    Call8002fe4cPrefix result;
    const auto byte = static_cast<std::int8_t>(object[0x35]);
    if (byte == -1) {
        result.negative_byte = true;
        // gap: beq to 0x80030274 is not taken on this call. That target is not traced.
        return result;
    }
    const auto at_38 = load_s32(object + 0x38);
    const auto at_3c = load_s32(object + 0x3c);
    const auto at_44 = load_s32(object + 0x44);
    const auto at_48 = load_s32(object + 0x48);
    const auto at_50 = load_s32(object + 0x50);
    const auto at_54 = load_s32(object + 0x54);
    const auto at_5c = load_s32(object + 0x5c);
    const auto at_60 = load_s32(object + 0x60);
    result.low = smaller(smaller(at_5c, at_50), smaller(at_44, at_38));
    result.high = larger(larger(at_5c, at_50), larger(at_44, at_38));
    result.pair_low = smaller(at_48, at_3c);
    result.delay_less = result.pair_low < at_60;
    if (!(at_54 < at_60)) {
        result.bound = at_60;
        // gap: beq to 0x8002ff50 is past this prefix.
        return result;
    }
    result.bound = at_54;
    result.bound_replaced = true;
    // gap: the next instruction at 0x8002ff4c is not traced.
    return result;
}

}
