// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065098.hpp"
#include "call_800650a8.hpp"
#include "call_800650b4.hpp"

#include <array>
#include <cstdint>
#include <cstring>

namespace {

std::uint32_t load_le32(const std::uint8_t* bytes) {
    std::uint32_t value = 0u;
    std::memcpy(&value, bytes, sizeof(value));
    return value;
}

} // namespace

int main() {
    std::array<std::uint8_t, 16u> bytes{};
    std::uint32_t cursor = 0x10u;
    const auto clear = am3d::exe::call_80065098(bytes.data(), 0u, 5u, cursor);
    if (load_le32(bytes.data()) != 5u || clear.stored_word != 5u ||
        clear.complemented_bit_0x80 || !clear.branch_to_650b4 ||
        cursor != 0x14u) {
        return 1;
    }

    cursor = 8u;
    const auto bit_set =
        am3d::exe::call_80065098(bytes.data(), 0x80u, 5u, cursor);
    if (!bit_set.complemented_bit_0x80 || bit_set.branch_to_650b4 ||
        cursor != 0xcu) {
        return 2;
    }

    cursor = 0u;
    const auto masked =
        am3d::exe::call_80065098(bytes.data(), 0x0180u, 5u, cursor);
    if (!masked.complemented_bit_0x80 || masked.branch_to_650b4 ||
        cursor != 4u) {
        return 3;
    }

    cursor = 1u;
    if (am3d::exe::call_80065098(nullptr, 0u, 5u, cursor).stored_word != 0u ||
        cursor != 1u) {
        return 4;
    }

    bytes.fill(0u);
    const auto a8 = am3d::exe::call_800650a8(bytes.data());
    if (a8.stored_at_0xa != 0x80u || bytes[0x0au] != 0x80u) {
        return 5;
    }
    if (am3d::exe::call_800650a8(nullptr).stored_at_0xa != 0u) {
        return 6;
    }

    bytes.fill(0xeeu);
    const auto b4_taken = am3d::exe::call_800650b4(bytes.data(), 0u);
    if (!b4_taken.branch_to_650c8 || b4_taken.complemented_bit_0x20 ||
        b4_taken.stored_at_0xa != 0u || bytes[0x0au] != 0u) {
        return 7;
    }

    bytes.fill(0u);
    const auto b4_fall = am3d::exe::call_800650b4(bytes.data(), 0x20u);
    if (!b4_fall.complemented_bit_0x20 || b4_fall.branch_to_650c8 ||
        b4_fall.stored_at_0xa != 0x7fu || bytes[0x0au] != 0x7fu) {
        return 8;
    }

    const auto chain_clear =
        am3d::exe::call_80065098(bytes.data(), 0u, 5u, cursor);
    (void)am3d::exe::call_800650b4(bytes.data(), 0u);
    if (!chain_clear.branch_to_650b4 || bytes[0x0au] != 0u) {
        return 9;
    }

    (void)am3d::exe::call_80065098(bytes.data(), 0x80u, 5u, cursor);
    (void)am3d::exe::call_800650a8(bytes.data());
    if (bytes[0x0au] != 0x80u) {
        return 10;
    }

    return 0;
}