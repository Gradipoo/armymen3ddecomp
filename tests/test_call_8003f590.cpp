// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003f590.hpp"
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8003f590(word) != 0x1b58u) return 1;
    return 0;
}
