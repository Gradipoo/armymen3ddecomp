// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e1c8.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x100u;
    std::uint32_t a1 = 0x8000u;
    std::uint32_t stored = 0;
    call_8007e1c8(a0, a1, stored);
    if (a0 != 0x55u) return 1;
    if (a1 != 0x40u) return 2;
    if (stored != 0x100u) return 3;
    return 0;
}
