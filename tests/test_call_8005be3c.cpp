// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be3c.hpp"
#include <cstdint>
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_8005be3c(0, word) != 0) return 1;
    if (word != 0) return 2;
    return 0;
}
