// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800254f0.hpp"

int main() {
    std::uint32_t a0 = 0;
    am3d::exe::call_800254f0(a0);
    if (a0 != 0x800bfe8cu) return 1;
    return 0;
}
