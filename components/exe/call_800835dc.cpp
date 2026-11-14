// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800835dc.hpp"
namespace am3d::exe {
void call_800835dc(std::uint8_t& port, std::uint8_t& index, std::uint32_t& first, std::uint32_t& second) {
    port = 0;
    index = 0x80;
    first = 0x2102843u;
    second = 0x1325u;
}
}
