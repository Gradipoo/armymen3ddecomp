// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be9c.hpp"
#include <cstdint>
int main() {
    std::uint32_t slot = 0;
    if (am3d::exe::call_8005be9c(slot) != 2) return 1;
    if (slot != 2) return 2;
    return 0;
}
