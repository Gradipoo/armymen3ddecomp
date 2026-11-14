// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008918c.hpp"
int main() {
    std::uint32_t word = 1;
    if (am3d::exe::call_8008918c(4, word) != 0u) return 1;
    if (word != 4u) return 2;
    return 0;
}
