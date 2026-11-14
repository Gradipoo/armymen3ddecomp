// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800655fc.hpp"
namespace am3d::exe {
std::uint32_t call_800655fc(const std::uint32_t* record, Call800655fcBlock& block) {
    block.at_2c = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(record));
    const std::uint32_t field = record[3];
    block.at_34 = 0;
    block.at_38 = 0;
    block.at_28 = 4;
    block.at_30 = field;
    return 0x800dd708u;
}
}
