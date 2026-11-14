// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060c24.hpp"
int main() {
    if (am3d::exe::call_80060c24() != 0x800dd2d8u) return 1;
    return 0;
}
