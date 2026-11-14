// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800901cc.hpp"
#include <cstdint>
int main() {
    std::uint32_t table = 0;
    std::uint32_t number = 0;
    am3d::exe::call_800901cc(table, number);
    if (table != 0xa0u || number != 0xacu) return 1;
    return 0;
}
