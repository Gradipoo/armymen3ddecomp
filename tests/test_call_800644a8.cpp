// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800644a8.hpp"

#include <cstdint>

int main() {
    std::uint32_t a = 1;
    std::uint32_t b = 1;
    if (am3d::exe::call_800644a8(&a, &b) != 0x800dd6f8u || a != 0 || b != 0) {
        return 1;
    }
    return 0;
}
