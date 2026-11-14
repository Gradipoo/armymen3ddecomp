// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80023848_2.hpp"

int main() {
    int second = 1;
    int third = 0;
    unsigned path = am3d::exe::call_80023848_2(&second, &third);
    if (path != 0x800bfdbc || second != 0 || third != 1) {
        return 1;
    }
    return 0;
}
