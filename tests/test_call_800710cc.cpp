// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800710cc.hpp"
int main() {
    std::uint32_t word = 0;
    am3d::exe::call_800710cc(7, word);
    if (word != 7u) return 1;
    return 0;
}
