// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8004b68c.hpp"
int main() {
    if (am3d::exe::call_8004b68c(3, 3) != 1u) return 1;
    if (am3d::exe::call_8004b68c(3, 4) != 0u) return 2;
    return 0;
}
