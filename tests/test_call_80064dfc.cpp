// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dfc.hpp"

#include <cstdint>

int main() {
    constexpr std::uint32_t kS1 = 0x800e18fbu;
    constexpr std::uint32_t kT1 = 1u;
    std::uint32_t stack_word = 0xffu;
    const am3d::exe::MenuLoopBody64dfc fall =
        am3d::exe::call_80064dfc(kS1, kT1, &stack_word);
    if (fall.s1 != kS1 - 1u || fall.s7 != 0u || fall.branch_to_65194 ||
        !fall.entered_64e14 || stack_word != kT1) {
        return 1;
    }
    const am3d::exe::MenuLoopBody64dfc taken =
        am3d::exe::call_80064dfc(kS1, kT1, nullptr);
    if (taken.s1 != kS1 - 1u || taken.s7 != 0u || !taken.branch_to_65194 ||
        taken.entered_64e14) {
        return 2;
    }
    return 0;
}