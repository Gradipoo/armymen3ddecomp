// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800957e4.hpp"

int main() {
    std::uint32_t base = 9;
    std::uint32_t next = 9;
    std::uint32_t flag = 0;
    std::uint32_t s0 = 0x800e3ab8u;
    std::uint32_t ra = am3d::exe::call_800957e4(base, next, flag, s0, 0x8009f510u,
                                                0x80094f64u);
    if (base != 0 || next != 0 || flag != 1) return 1;
    if (s0 != 0x8009f510u || ra != 0x80094f64u) return 1;
    return 0;
}
