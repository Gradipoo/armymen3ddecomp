// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008f9cc.hpp"
namespace am3d::exe {
void call_8008f9cc(std::uint32_t& table, std::uint32_t& number) {
    table = 0xb0u;
    number = 0x42u;
}
}
