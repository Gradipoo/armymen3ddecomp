// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061ff0.hpp"

int main() {
    unsigned char dest[9] = {0x6c, 0x65, 0x67, 0x61};
    int index = 3;
    am3d::exe::call_80061ff0(dest, &index);
    unsigned char expect[9] = {0x6c, 0x65, 0x67, 0x61, 0x6c, 0x2e, 0x62, 0x67, 0x00};
    for (int i = 0; i < 9; ++i) {
        if (dest[i] != expect[i]) {
            return 1;
        }
    }
    if (index != 8) {
        return 1;
    }
    return 0;
}
