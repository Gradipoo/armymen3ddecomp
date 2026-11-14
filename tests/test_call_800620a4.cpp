// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800620a4.hpp"

int main() {
    unsigned first = 1;
    unsigned second = 1;
    unsigned third = 0;
    unsigned slot[15];
    for (int i = 0; i < 15; ++i) {
        slot[i] = 1;
    }
    unsigned result = am3d::exe::call_800620a4(&first, &second, &third, slot);
    if (result != 0 || first != 0 || second != 0 || third != 0x8009f444) {
        return 1;
    }
    if (slot[0] != 0 || slot[4] != 0 || slot[2] != 1) {
        return 1;
    }
    return 0;
}
