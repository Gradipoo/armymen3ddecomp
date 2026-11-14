// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064500.hpp"
namespace am3d::exe {
std::uint32_t call_80064500(std::uint32_t a0, std::uint32_t& word) {
    word = a0;
    return 0x800e0000u;
}
}
