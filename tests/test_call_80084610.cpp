// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80084610.hpp"
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_80084610(5, word) != 0u) return 1;
    if (word != 5u) return 2;
    return 0;
}
