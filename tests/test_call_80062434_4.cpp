// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434_4.hpp"

int main() {
    unsigned char dest[13] = {};
    unsigned char expect[] = {0x5c, 0x6d, 0x69, 0x73, 0x73, 0x69, 0x6f, 0x6e, 0x2e, 0x69, 0x6e, 0x69, 0x00};
    am3d::exe::call_80062434_4(dest);
    for (int i = 0; i < 13; ++i) {
        if (dest[i] != expect[i]) {
            return 1;
        }
    }
    return 0;
}
