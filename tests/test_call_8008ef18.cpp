// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008ef18.hpp"
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8008ef18(6, word) != 0u) return 1;
    if (word != 6u) return 2;
    return 0;
}
