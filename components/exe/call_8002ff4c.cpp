// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002ff4c.hpp"

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

std::int32_t sra13(std::int32_t value) {
    const auto bits = static_cast<std::uint32_t>(value);
    const auto shifted = bits >> 13;
    if ((bits & 0x80000000u) == 0) {
        return static_cast<std::int32_t>(shifted);
    }
    return static_cast<std::int32_t>(shifted | 0xfff80000u);
}

std::int32_t floor_shift(std::int32_t value) {
    if (value < 0) {
        return 0;
    }
    return value >> 13;
}

std::int32_t clamp_shift(std::int32_t value) {
    constexpr auto kLimit = static_cast<std::int32_t>(0x3ffff);
    if (value > kLimit) {
        return sra13(kLimit);
    }
    return sra13(value);
}

}

// Behavior reference: docs/research/re/call-8002ff4c.md.
Call8002ff4cBlock call_8002ff4c(const std::uint8_t* object) {
    Call8002ff4cBlock result;
    const auto at_38 = load_s32(object + 0x38);
    const auto at_3c = load_s32(object + 0x3c);
    const auto at_44 = load_s32(object + 0x44);
    const auto at_48 = load_s32(object + 0x48);
    const auto at_50 = load_s32(object + 0x50);
    const auto at_54 = load_s32(object + 0x54);
    const auto at_5c = load_s32(object + 0x5c);
    const auto at_60 = load_s32(object + 0x60);
    if (!(at_54 < at_60)) {
        // gap: word at 0x54 is not smaller, so this block is not entered.
        return result;
    }
    result.entered = true;
    result.y_low = smaller(smaller(at_48, at_3c), at_54);
    result.y_high = larger(at_60, larger(at_48, at_3c));
    const auto x_low = smaller(smaller(at_5c, at_50), smaller(at_44, at_38));
    const auto x_high = larger(larger(at_5c, at_50), larger(at_44, at_38));
    result.x_low_shift = floor_shift(x_low);
    result.x_high_shift = clamp_shift(x_high);
    result.y_low_shift = floor_shift(result.y_low);
    result.y_high_shift = clamp_shift(result.y_high);
    if (result.x_high_shift < result.x_low_shift) {
        result.x_skipped = true;
        // gap: bne to 0x80030050 is not traced.
        return result;
    }
    if (result.y_high_shift < result.y_low_shift) {
        result.y_skipped = true;
        // gap: bne to 0x80030040 is not traced.
        return result;
    }
    constexpr auto kBase = static_cast<std::uint32_t>(0x800a03a8u);
    const auto y_term = static_cast<std::uint32_t>(result.y_low_shift) << 5;
    const auto x_term = static_cast<std::uint32_t>(result.x_low_shift) << 10;
    result.called = true;
    result.call_a0 = kBase + y_term + x_term;
    result.call_a1 = object;
    result.call_ra = 0x80030030u;
    // gap: unnamed jal at 0x80079b24. The return address is 0x80030030.
    return result;
}

}
