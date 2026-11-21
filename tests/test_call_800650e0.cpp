// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800650e0.hpp"

#include <cstdint>

int main() {
    if (am3d::exe::call_800650e0(0u)) {
        return 1;
    }
    if (am3d::exe::call_800650e0(0x10u)) {
        return 2;
    }
    if (!am3d::exe::call_800650e0(0x40u)) {
        return 3;
    }
    if (!am3d::exe::call_800650e0(0xffffu)) {
        return 4;
    }
    return 0;
}
