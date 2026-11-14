// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005b3d4.hpp"

int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8005b3d4(word, 1) != 0 || word != 1) return 1;
    return 0;
}
