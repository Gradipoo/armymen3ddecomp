// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80061ff0_3.hpp"

int main() {
    unsigned char dest[9] = {0x5c, 0x6d, 0x69, 0x73};
    int index = 3;
    am3d::exe::call_80061ff0_3(dest, &index);
    return dest[8] == 0x2e && index == 9 ? 0 : 1;
}
