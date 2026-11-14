// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008c29c.hpp"
namespace am3d::exe {
std::uint32_t* call_8008c29c(std::uint32_t* dest, const std::uint32_t* src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}
}
