// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062514.hpp"

int main() {
    unsigned slot[3] = {1, 1, 1};
    int argument = 0;
    unsigned handler = am3d::exe::call_80062514(0, slot, &argument);
    if (handler != 0x80075198 || argument != 5 || slot[2] != 0) {
        return 1;
    }
    return 0;
}
