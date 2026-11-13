// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800253fc.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0;
    std::uint32_t a1 = 0;
    call_800253fc(a0, a1);
    if (a0 != 1u) return 1;
    if (a1 != 0x8000u) return 2;
    return 0;
}
