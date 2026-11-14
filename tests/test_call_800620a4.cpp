// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800620a4.hpp"

int main() {
    unsigned first = 1;
    unsigned second = 1;
    unsigned third = 0;
    unsigned result = am3d::exe::call_800620a4(&first, &second, &third);
    if (result != 0 || first != 0 || second != 0 || third != 0x8009f444) {
        return 1;
    }
    return 0;
}
