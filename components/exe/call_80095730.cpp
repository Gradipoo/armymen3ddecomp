// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80095730.hpp"
namespace am3d::exe {
std::uint32_t call_80095730(std::uint32_t& word) {
    const std::uint32_t old = word;
    word = 0;
    return old;
}
}
