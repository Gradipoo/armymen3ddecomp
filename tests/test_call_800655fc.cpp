// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800655fc.hpp"
int main() {
    std::uint32_t record[4] = {0, 0, 0, 6};
    am3d::exe::Call800655fcBlock block{};
    const std::uint32_t got = am3d::exe::call_800655fc(record, block);
    if (got != 0x800dd708u) return 1;
    if (block.at_28 != 4u || block.at_30 != 6u || block.at_34 || block.at_38) return 2;
    if (block.at_2c != static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(record))) return 3;
    return 0;
}
