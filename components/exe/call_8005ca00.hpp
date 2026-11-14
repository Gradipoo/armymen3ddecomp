// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
std::uint32_t toupper(std::uint32_t byte);
const std::uint8_t* call_8005ca00(const std::uint8_t* text);
}
