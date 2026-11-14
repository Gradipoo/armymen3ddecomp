// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061f80.hpp"

int main() {
    unsigned char dest[4] = {};
    int index = 0;
    am3d::exe::call_80061f80(dest, &index);
    if (dest[0] != 0x6c || dest[1] != 0x65 || dest[2] != 0x67 || dest[3] != 0x61) {
        return 1;
    }
    if (index != 3) {
        return 1;
    }
    return 0;
}
