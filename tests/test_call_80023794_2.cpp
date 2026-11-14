// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80023794_2.hpp"

int main() {
    unsigned a0 = 0;
    int a1 = 1;
    am3d::exe::call_80023794_2(&a0, &a1);
    if (a0 != 0x800bfdbc || a1 != 0) {
        return 1;
    }
    return 0;
}
