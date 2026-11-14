// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002554c.hpp"

int main() {
    unsigned a0 = 0;
    int a2 = 1;
    am3d::exe::call_8002554c(&a0, &a2);
    if (a0 != 0x8009f444 || a2 != 0) {
        return 1;
    }
    return 0;
}
