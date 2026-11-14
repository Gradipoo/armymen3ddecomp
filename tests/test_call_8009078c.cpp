// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8009078c.hpp"
#include <cstdint>
int main() {
    std::uint32_t table = 0;
    std::uint32_t number = 0;
    am3d::exe::call_8009078c(table, number);
    if (table != 0xb0u || number != 0x4bu) return 1;
    return 0;
}
