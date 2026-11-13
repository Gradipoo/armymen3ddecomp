// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b10.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x1000u;
    std::uint32_t a1 = 0;
    std::uint32_t a2 = 0;
    std::uint32_t a3 = 0;
    std::uint32_t s0 = 0x8009f510u;
    call_80060b10(a0, a1, a2, a3, s0);
    if (s0 != 0x800dd2d8u || a0 != 0x800dd2d8u || a1 != 0x1000u || a2 != 0xa00u ||
        a3 != 0x1000u) {
        return 1;
    }
    return 0;
}
