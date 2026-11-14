// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8004a49c.hpp"
#include <cstdint>
int main() {
    if (am3d::exe::call_8004a49c(0) != 0x5a2a0801u) return 1;
    return 0;
}
