// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075758.hpp"
int main() {
    std::uint32_t flag = 0;
    std::uint32_t slot = 0;
    if (am3d::exe::call_80075758(0, flag, slot) != 0u) return 1;
    if (slot != 0u) return 2;
    return 0;
}
