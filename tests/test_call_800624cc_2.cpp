// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc_2.hpp"

int main() {
    int argument = 0;
    if (am3d::exe::call_800624cc_2(0, &argument) != 0x80075198 || argument != 5) {
        return 1;
    }
    return 0;
}
