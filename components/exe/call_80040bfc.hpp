// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
void call_80040bfc(std::int32_t x, std::int32_t y, std::uint32_t half, std::uint32_t& index, std::uint32_t& result);
}
