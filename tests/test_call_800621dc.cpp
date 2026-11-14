// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc.hpp"

int main() {
    std::uint32_t counter = 0;
    std::uint32_t slot = 0;
    std::uint32_t a0 = 0x80075198u;
    std::uint32_t a1 = 0x1000u;
    std::uint32_t target = am3d::exe::call_800621dc(counter, slot, a0, a1, a0);
    if (counter != 1 || slot != 0x80075198u) return 1;
    if (a0 != 0 || a1 != 0 || target != 0x80075198u) return 1;
    return 0;
}
