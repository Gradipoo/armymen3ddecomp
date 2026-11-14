// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008dabc.hpp"
namespace am3d::exe {
void call_8008dabc(std::uint32_t& table, std::uint32_t& number) {
    table = 0xa0u;
    number = 0x44u;
}
}
