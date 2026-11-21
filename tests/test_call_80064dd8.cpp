// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064dd8.hpp"

#include <cstdint>

int main() {
    constexpr std::uint32_t kS1 = 0x800e18fbu;
    const am3d::exe::MenuLoopBody64dd8 zero =
        am3d::exe::call_80064dd8(kS1, nullptr);
    if (zero.v0 != 0u || zero.v1 != 0x80u || zero.t1 != 1u ||
        !zero.branch_to_64dfc || zero.entered_64dec) {
        return 1;
    }
    constexpr std::uint8_t kHighNibble80 = 0x85u;
    const am3d::exe::MenuLoopBody64dd8 match =
        am3d::exe::call_80064dd8(kS1, &kHighNibble80);
    if (match.v0 != 0x80u || !match.entered_64dec || match.branch_to_64dfc) {
        return 2;
    }
    constexpr std::uint8_t kHighNibble70 = 0x7fu;
    const am3d::exe::MenuLoopBody64dd8 branch =
        am3d::exe::call_80064dd8(kS1, &kHighNibble70);
    if (branch.v0 != 0x70u || !branch.branch_to_64dfc || branch.entered_64dec) {
        return 3;
    }
    return 0;
}