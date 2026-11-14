// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8008ac3c.hpp"
namespace am3d::exe {
std::uint32_t call_8008ac3c(std::uint32_t a0, std::uint32_t a1) {
    const std::uint32_t shifted = static_cast<std::uint32_t>(static_cast<std::int32_t>(a0) >> 4);
    const std::uint32_t joined = (a1 << 6) | (shifted & 0x3fu);
    return joined & 0xffffu;
}
}
