// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025408.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t a0 = 1u;
    call_80025408(a0);
    if (a0 != 0x100u) return 1;
    return 0;
}
