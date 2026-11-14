// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80073c2c.hpp"
namespace am3d::exe {
std::uint32_t call_80073c2c(std::uint32_t a0, std::uint32_t a1) {
    const std::uint32_t aligned = ((a1 + 3u) & ~3u) + 4u;
    const std::uint32_t product = static_cast<std::uint32_t>(
        static_cast<std::int32_t>(a0) * static_cast<std::int32_t>(aligned));
    return product + 0x14u;
}
}
