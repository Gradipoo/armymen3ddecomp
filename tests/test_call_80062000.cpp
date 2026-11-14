// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062000.hpp"

int main() {
    unsigned first = 1;
    unsigned second = 1;
    unsigned third = 0;
    unsigned result = am3d::exe::call_80062000(&first, &second, &third);
    if (result != 0 || first != 0 || second != 0 || third != 0x800bfdbc) {
        return 1;
    }
    return 0;
}
