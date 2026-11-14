// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800372cc.hpp"
#include <cstdint>
int main() {
    std::uint32_t a = 0, b = 0, c = 0;
    am3d::exe::call_800372cc(a, b, c);
    if (a != 0xe00u || b != 0xa00u || c != 0x200u) return 1;
    return 0;
}
