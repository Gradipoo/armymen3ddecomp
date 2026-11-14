// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800624cc.hpp"

int main() {
    int argument = 0;
    unsigned handler = am3d::exe::call_800624cc(0, &argument);
    if (handler != 0x80075198 || argument != 5) {
        return 1;
    }
    return 0;
}
