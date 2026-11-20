// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dc8.hpp"

#include <cstdint>

int main() {
    constexpr std::uint32_t kS1 = 0x800e18fau;
    constexpr std::uint8_t kNonzero = 0x01u;
    const am3d::exe::MenuLoopBody64dc8 taken =
        am3d::exe::call_80064dc8(kS1, &kNonzero);
    if (taken.v0 != 1u || taken.s1 != kS1 + 1u || !taken.branch_to_65194 ||
        taken.entered_64dd8) {
        return 1;
    }
    const am3d::exe::MenuLoopBody64dc8 fall =
        am3d::exe::call_80064dc8(kS1, nullptr);
    if (fall.v0 != 0u || fall.s1 != kS1 + 1u || fall.branch_to_65194 ||
        !fall.entered_64dd8) {
        return 2;
    }
    return 0;
}