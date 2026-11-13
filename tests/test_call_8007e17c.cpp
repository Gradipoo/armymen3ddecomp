// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e17c.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 1u;
    std::uint32_t a1 = 0x8000u;
    std::uint32_t stored_a0 = 0;
    std::uint32_t stored_a1 = 0;
    call_8007e17c(a0, a1, stored_a0, stored_a1);
    if (a0 != 1u) return 1;
    if (a1 != 0x8000u) return 2;
    if (stored_a0 != 1u) return 3;
    if (stored_a1 != 0x8000u) return 4;
    return 0;
}
