// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
void call_80059f88(std::uint32_t selector, std::uint32_t& slot, std::uint32_t& stored);
}
