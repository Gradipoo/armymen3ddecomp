// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008dabc.hpp"
#include <cstdint>
int main() {
    std::uint32_t table = 0;
    std::uint32_t number = 0;
    am3d::exe::call_8008dabc(table, number);
    if (table != 0xa0u || number != 0x44u) return 1;
    return 0;
}
