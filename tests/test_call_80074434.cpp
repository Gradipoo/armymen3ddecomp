// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074434.hpp"
int main() {
    if (am3d::exe::call_80074434(0) != 2u) return 1;
    if (am3d::exe::call_80074434(0x102u) != 2u) return 2;
    return 0;
}
