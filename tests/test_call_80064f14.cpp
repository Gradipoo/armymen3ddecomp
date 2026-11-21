// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064f14.hpp"

#include <array>
#include <cstdint>

int main() {
    constexpr std::array<std::uint8_t, 4u> measured{0u, 0x41u, 0u, 0u};
    std::uint32_t index = 0u;
    const auto ok = am3d::exe::call_80064f14(measured.data(), index, measured.size());
    if (!ok.compare_0x41 || ok.first_byte_branch || ok.masked_a2 != 0x41u || index != 2u) {
        return 1;
    }
    index = 0u;
    constexpr std::array<std::uint8_t, 2u> branch{1u, 0x41u};
    const auto taken = am3d::exe::call_80064f14(branch.data(), index, branch.size());
    if (!taken.first_byte_branch || taken.compare_0x41 || index != 0u) {
        return 2;
    }
    index = 0u;
    constexpr std::array<std::uint8_t, 2u> mismatch{0u, 0x42u};
    const auto fail = am3d::exe::call_80064f14(mismatch.data(), index, mismatch.size());
    if (fail.compare_0x41 || fail.first_byte_branch || index != 2u) {
        return 3;
    }
    return 0;
}