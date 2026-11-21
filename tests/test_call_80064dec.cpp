// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dec.hpp"

#include <cstdint>

int main() {
    constexpr std::uint32_t kS1 = 0x800e18fbu;
    std::uint32_t stack_word = 0xffu;
    const am3d::exe::MenuLoopBody64dec fall =
        am3d::exe::call_80064dec(kS1, &stack_word);
    if (fall.s1 != kS1 + 1u || fall.s7 != 0u || fall.branch_to_65194 ||
        !fall.entered_64e14 || stack_word != 4u) {
        return 1;
    }
    const am3d::exe::MenuLoopBody64dec taken =
        am3d::exe::call_80064dec(kS1, nullptr);
    if (taken.s1 != kS1 + 1u || taken.s7 != 0u || !taken.branch_to_65194 ||
        taken.entered_64e14) {
        return 2;
    }
    return 0;
}