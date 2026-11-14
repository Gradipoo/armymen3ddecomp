// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80040c34.hpp"
#include <cstdint>
int main() {
    if (am3d::exe::call_80040c34(0) != 0x800a0210u) return 1;
    if (am3d::exe::call_80040c34(0x700u) != 0x800a022cu) return 1;
    return 0;
}
