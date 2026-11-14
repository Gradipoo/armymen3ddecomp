// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008ac3c.hpp"
int main() {
    if (am3d::exe::call_8008ac3c(0x10u, 1u) != 0x41u) return 1;
    return 0;
}
