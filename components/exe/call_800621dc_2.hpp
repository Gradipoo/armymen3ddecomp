// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800621dc-2.md.
std::uint32_t call_800621dc_2(std::uint32_t& counter, std::uint32_t& slot,
                              std::uint32_t& a0, std::uint32_t& a1,
                              std::uint32_t handler);

}
