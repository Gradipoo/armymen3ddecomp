// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80095730.hpp"
int main() {
    std::uint32_t word = 0;
    if (am3d::exe::call_80095730(word) != 0u) return 1;
    return 0;
}
