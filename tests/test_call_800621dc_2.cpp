// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc_2.hpp"

int main() {
    std::uint32_t counter = 1;
    std::uint32_t slot = 0;
    std::uint32_t a0 = 0x8005b3d4u;
    std::uint32_t a1 = 0;
    std::uint32_t target = am3d::exe::call_800621dc_2(counter, slot, a0, a1, a0);
    if (counter != 2 || slot != 0x8005b3d4u) return 1;
    if (a0 != 0 || a1 != 1 || target != 0x8005b3d4u) return 1;
    return 0;
}
