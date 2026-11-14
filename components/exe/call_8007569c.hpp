// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
void call_8007569c(std::uint32_t a0, std::uint32_t& flag, std::uint32_t& link, std::uint32_t& slot_c0, std::uint32_t& slot_c8, std::uint32_t& cd_slot);
}
