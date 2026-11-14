// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025488.hpp"

#include <cstdint>

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 0x80022c1cu;
    call_80025488(a0);
    if (a0 != 3) return 1;
    return 0;
}
