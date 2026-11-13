// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b4c.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t stored = 0;
    call_80060b4c(0x1000u, stored);
    if (stored != 0x1000u) return 1;
    return 0;
}
