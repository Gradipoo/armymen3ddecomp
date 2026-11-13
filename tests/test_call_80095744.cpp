// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80095744.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t cleared = 1;
    std::uint32_t status = 1;
    std::uint32_t mask = 0x10u;
    call_80095744(cleared, status, mask);
    if (cleared != 0 || status != 0xfffffffeu || mask != 0x11u) return 1;
    return 0;
}
