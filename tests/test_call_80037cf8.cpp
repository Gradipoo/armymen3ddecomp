// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80037cf8.hpp"
int main() {
    std::uint32_t word = 0x186a0u;
    if (am3d::exe::call_80037cf8(word) != 0x186a0u) return 1;
    if (word != 0x186a1u) return 2;
    return 0;
}
