// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012a3c.hpp"
namespace am3d::exe {
std::uint32_t call_80012a3c(std::uint32_t& link, std::uint32_t* dest) {
    static constexpr std::uint32_t words[] = {0, 0xc, 0xc, 0, 0, 0, 0, 0, 0, 0, 0};
    link = 0x800c5564u;
    for (unsigned i = 0; i < 11; ++i) dest[i] = words[i];
    return 0x800c5538u;
}
}
