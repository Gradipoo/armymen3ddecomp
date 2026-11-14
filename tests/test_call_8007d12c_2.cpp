// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d12c_2.hpp"

int main() {
    std::uint32_t word = 9;
    std::uint32_t s0 = 2;
    std::uint32_t ra = am3d::exe::call_8007d12c_2(word, s0, 0x8009f510u, 0x8002553cu);
    if (word != 0 || s0 != 0x8009f510u || ra != 0x8002553cu) return 1;
    return 0;
}
