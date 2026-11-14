// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062474_3.hpp"

int main() {
    unsigned slot[15];
    for (int i = 0; i < 15; ++i) {
        slot[i] = 1;
    }
    return am3d::exe::call_80062474_3(slot) == 0x80075198 && slot[0] == 0 && slot[9] == 0 ? 0 : 1;
}
