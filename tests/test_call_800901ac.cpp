// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800901ac.hpp"
#include <cstdint>
int main() {
    std::uint32_t table = 0;
    std::uint32_t number = 0;
    am3d::exe::call_800901ac(table, number);
    if (table != 0xb0u || number != 0xbu) return 1;
    return 0;
}
