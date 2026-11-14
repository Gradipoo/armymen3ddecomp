// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80040bfc.hpp"
namespace am3d::exe {
void call_80040bfc(std::int32_t x, std::int32_t y, std::uint32_t half, std::uint32_t& index, std::uint32_t& result) {
    index = static_cast<std::uint32_t>(((y >> 10) + 1) << 8) + static_cast<std::uint32_t>(x >> 10);
    result = (half >> 12) != 0 ? 1u : 0u;
}
}
