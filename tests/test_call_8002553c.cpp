// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002553c.hpp"

int main() {
    std::uint32_t a0 = 2;
    std::uint32_t s0 = 0x8009f510u;
    am3d::exe::call_8002553c(a0, s0);
    if (a0 != 0x8009f444u || s0 != 0x8009f444u) return 1;
    return 0;
}
