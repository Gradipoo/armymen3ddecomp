// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800710dc.hpp"
int main() {
    std::uint32_t word = 0;
    am3d::exe::call_800710dc(7, word);
    if (word != 7u) return 1;
    return 0;
}
