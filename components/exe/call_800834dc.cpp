// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800834dc.hpp"
namespace am3d::exe {
void call_800834dc(std::uint8_t& port, std::uint8_t& index, std::uint32_t& first, std::uint32_t& second) {
    port = 0;
    index = 0x80;
    first = 0x20943u;
    second = 0x1323u;
}
}
