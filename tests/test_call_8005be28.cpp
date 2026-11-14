// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be28.hpp"
#include <cstdint>
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8005be28(0, word) != 0) return 1;
    if (word != 0) return 2;
    word = 4;
    if (am3d::exe::call_8005be28(0x8005be64u, word) != 4) return 3;
    if (word != 0x8005be64u) return 4;
    return 0;
}
