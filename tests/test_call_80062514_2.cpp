// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062514_2.hpp"

int main() {
    unsigned slot[3] = {1, 1, 1};
    int argument = 0;
    if (am3d::exe::call_80062514_2(0, slot, &argument) != 0x80075198 || argument != 5 || slot[2] != 0) {
        return 1;
    }
    return 0;
}
