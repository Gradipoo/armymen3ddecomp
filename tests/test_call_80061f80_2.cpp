// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061f80_2.hpp"

int main() {
    unsigned char dest[4] = {};
    int index = 0;
    am3d::exe::call_80061f80_2(dest, &index);
    if (dest[0] != 0x5c || dest[1] != 0x6d || dest[2] != 0x69 || dest[3] != 0x73 || index != 3) {
        return 1;
    }
    return 0;
}
