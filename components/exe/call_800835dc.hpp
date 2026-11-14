// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
void call_800835dc(std::uint8_t& port, std::uint8_t& index, std::uint32_t& first, std::uint32_t& second);
}
