// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061ff0_2.hpp"

int main() {
    unsigned char dest[9] = {0x5c, 0x6d, 0x69, 0x73};
    int index = 3;
    am3d::exe::call_80061ff0_2(dest, &index);
    unsigned char expect[] = {0x5c, 0x6d, 0x69, 0x73, 0x73, 0x69, 0x6f, 0x6e, 0x2e};
    for (int i = 0; i < 9; ++i) {
        if (dest[i] != expect[i]) {
            return 1;
        }
    }
    if (index != 9) {
        return 1;
    }
    return 0;
}
