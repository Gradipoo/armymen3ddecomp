// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80040bfc.hpp"
#include <cstdint>
int main() {
    std::uint32_t index = 0;
    std::uint32_t result = 9;
    am3d::exe::call_80040bfc(0, 0, 0x1000u, index, result);
    if (index != 256u || result != 1u) return 1;
    am3d::exe::call_80040bfc(0, 0, 0xfffu, index, result);
    if (result != 0u) return 1;
    return 0;
}
