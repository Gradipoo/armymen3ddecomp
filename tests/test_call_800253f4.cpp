// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253f4.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0;
    call_800253f4(a0);
    if (a0 != 0x55u) return 1;
    return 0;
}
