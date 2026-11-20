// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064f48.hpp"

#include <array>
#include <cstdint>

int main() {
    constexpr std::array<std::uint8_t, 2u> table{0xffu, 0xffu};
    std::uint32_t index = 0u;
    std::array<std::uint8_t, 16u> record{};
    std::uint32_t sp20 = 0x100u;
    const auto zero = am3d::exe::call_80064f48(
        sp20, 0x20u, table.data(), index, table.size(), 0u, record.data());
    if (!zero.entered || zero.raw_halfword != 0xffffu || zero.complemented != 0u ||
        sp20 != 0x120u || index != 2u) {
        return 1;
    }
    constexpr std::array<std::uint8_t, 2u> up_table{0xefu, 0xffu};
    index = 0u;
    const auto up_half = am3d::exe::call_80064f48(
        sp20, 0u, up_table.data(), index, up_table.size(), 0u, record.data());
    if (!up_half.entered || up_half.complemented != 0x10u) {
        return 2;
    }
    index = 0u;
    const auto blocked = am3d::exe::call_80064f48(
        sp20, 0u, table.data(), index, table.size(), 4u, record.data());
    if (blocked.entered) {
        return 3;
    }
    return 0;
}