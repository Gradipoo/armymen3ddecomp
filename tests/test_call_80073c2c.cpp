// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80073c2c.hpp"
int main() {
    if (am3d::exe::call_80073c2c(0, 0) != 0x14u) return 1;
    if (am3d::exe::call_80073c2c(1, 1) != 0x1cu) return 2;
    return 0;
}
