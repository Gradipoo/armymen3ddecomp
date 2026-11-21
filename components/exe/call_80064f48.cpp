// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064f48.hpp"

#include "call_80064f78.hpp"

namespace am3d::exe {

namespace {

std::uint16_t load_le16(const std::uint8_t* bytes) {
    return static_cast<std::uint16_t>(bytes[0]) |
           (static_cast<std::uint16_t>(bytes[1]) << 8u);
}

void store_le16(std::uint8_t* bytes, std::uint16_t value) {
    bytes[0] = static_cast<std::uint8_t>(value & 0xffu);
    bytes[1] = static_cast<std::uint8_t>((value >> 8u) & 0xffu);
}

}

MenuMaskPathResult call_80064f48(std::uint32_t& stack_word_20, std::uint32_t fp,
                                 const std::uint8_t* table, std::uint32_t& index,
                                 std::uint32_t table_bytes, std::uint32_t compare_word,
                                 std::uint8_t* record) {
    MenuMaskPathResult result{};
    if (table == nullptr || record == nullptr || index + 1u >= table_bytes) {
        return result;
    }
    stack_word_20 |= fp;
    result.raw_halfword = load_le16(table + index);
    index += 2u;
    const std::uint32_t complemented =
        (~static_cast<std::uint32_t>(result.raw_halfword)) & 0xffffu;
    result.complemented = complemented;
    constexpr std::uint32_t kCompareFour = 4u;
    if (compare_word == kCompareFour) {
        const MenuCompareFourResult alt = call_80064f78(complemented);
        result.compare_eq_four = true;
        result.branch_to_65168 = alt.branch_to_65168;
        result.compare_four_v0 = alt.v0;
        return result;
    }
    const std::uint16_t old = load_le16(record + 4u);
    store_le16(record + 4u, static_cast<std::uint16_t>(complemented));
    const std::uint16_t delta = old ^ static_cast<std::uint16_t>(complemented);
    store_le16(record + 6u, static_cast<std::uint16_t>(delta & complemented));
    store_le16(record + 8u, static_cast<std::uint16_t>(delta & result.raw_halfword));
    result.entered = true;
    return result;
}

}