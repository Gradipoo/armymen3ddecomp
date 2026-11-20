// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800651c8.hpp"

#include <cstdint>

int main() {
    constexpr std::uint32_t kEntryV0 = 0x800e0000u;
    constexpr std::uint32_t kS1 = kEntryV0 + 0x18fau;
    std::uint32_t sp18 = 0u;
    const am3d::exe::MenuLoopTaken651c8 taken =
        am3d::exe::call_800651c8(kEntryV0, &sp18);
    if (taken.s1 != kS1 || taken.v0 != 1u || !taken.branch_to_64dc8 ||
        taken.entered_651e0 || sp18 != 1u) {
        return 1;
    }
    sp18 = 1u;
    const am3d::exe::MenuLoopTaken651c8 fall =
        am3d::exe::call_800651c8(kEntryV0, &sp18);
    if (fall.s1 != kS1 || fall.v0 != 0u || fall.branch_to_64dc8 ||
        !fall.entered_651e0 || sp18 != 2u) {
        return 2;
    }
    return 0;
}