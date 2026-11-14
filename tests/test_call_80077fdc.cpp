// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80077fdc.hpp"

int main() {
    std::uint32_t word = 0;
    std::uint32_t ra = am3d::exe::call_80077fdc(word, 0x800638b8u, 0x8002552cu);
    if (word != 0x800638b8u || ra != 0x8002552cu) return 1;
    return 0;
}
