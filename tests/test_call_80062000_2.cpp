// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062000_2.hpp"

int main() {
    unsigned first = 1;
    unsigned second = 1;
    unsigned third = 0;
    return am3d::exe::call_80062000_2(&first, &second, &third) == 0 && third == 0x800bfdbc ? 0 : 1;
}
