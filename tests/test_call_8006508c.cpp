// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006508c.hpp"

int main() {
    const auto zero = am3d::exe::call_8006508c(0u);
    if (zero.v0 != 5u || zero.s6_nonzero) {
        return 1;
    }
    const auto set = am3d::exe::call_8006508c(1u);
    if (set.v0 != 5u || !set.s6_nonzero) {
        return 2;
    }
    return 0;
}
