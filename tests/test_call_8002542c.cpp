// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002542c.hpp"

int main() {
    std::uint32_t a0 = 0x800d0000u;
    am3d::exe::call_8002542c(a0);
    return a0 == 0x800c8500u ? 0 : 1;
}
