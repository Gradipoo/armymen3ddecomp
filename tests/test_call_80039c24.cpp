// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80039c24.hpp"
int main() {
    if (am3d::exe::call_80039c24(1, 2) != 0x102u) return 1;
    return 0;
}
