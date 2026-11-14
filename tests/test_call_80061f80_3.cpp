// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061f80_3.hpp"

int main() {
    unsigned char dest[4] = {};
    int index = 0;
    am3d::exe::call_80061f80_3(dest, &index);
    return dest[0] == 0x5c && dest[3] == 0x73 && index == 3 ? 0 : 1;
}
