// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008f9dc.hpp"
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8008f9dc(word) != 0xffffffffu) return 1;
    return 0;
}
