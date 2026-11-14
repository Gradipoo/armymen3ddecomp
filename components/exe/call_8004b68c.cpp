// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8004b68c.hpp"
namespace am3d::exe {
std::uint32_t call_8004b68c(std::int8_t byte, std::uint32_t a1) {
    const std::uint32_t diff = static_cast<std::uint32_t>(byte) ^ a1;
    return diff < 1u ? 1u : 0u;
}
}
