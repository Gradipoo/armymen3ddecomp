// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800436b4.hpp"
int main() {
    std::uint32_t word = 0;
    am3d::exe::call_800436b4(word, 9);
    if (word != 9u) return 1;
    return 0;
}
