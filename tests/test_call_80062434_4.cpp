// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062434_4.hpp"

int main() {
    unsigned char dest[13] = {};
    dest[12] = 1;
    am3d::exe::call_80062434_4(dest);
    return dest[0] == 0x5c && dest[12] == 0 ? 0 : 1;
}
