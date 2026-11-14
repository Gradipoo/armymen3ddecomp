// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800124cc.hpp"
int main() {
    std::uint32_t words[19];
    for (auto& word : words) word = 1;
    if (am3d::exe::call_800124cc(words) != 0x800989a0u) return 1;
    if (words[0] || words[4] || words[18]) return 2;
    if (words[5] != 1u || words[14] != 1u) return 3;
    return 0;
}
