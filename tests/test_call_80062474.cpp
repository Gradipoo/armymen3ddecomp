// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062474.hpp"

int main() {
    unsigned slot[15];
    for (int i = 0; i < 15; ++i) {
        slot[i] = 1;
    }
    unsigned handler = am3d::exe::call_80062474(slot);
    if (handler != 0x80075198) {
        return 1;
    }
    int cleared[] = {0, 1, 4, 5, 6, 9, 10, 13, 14};
    for (int index : cleared) {
        if (slot[index] != 0) {
            return 1;
        }
    }
    if (slot[2] != 1) {
        return 1;
    }
    return 0;
}
