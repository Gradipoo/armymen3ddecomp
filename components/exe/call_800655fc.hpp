// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
struct Call800655fcBlock {
    std::uint32_t at_28;
    std::uint32_t at_2c;
    std::uint32_t at_30;
    std::uint32_t at_34;
    std::uint32_t at_38;
};
std::uint32_t call_800655fc(const std::uint32_t* record, Call800655fcBlock& block);
}
