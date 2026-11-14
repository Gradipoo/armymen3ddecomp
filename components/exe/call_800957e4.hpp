// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800957e4.md.
std::uint32_t call_800957e4(std::uint32_t& base, std::uint32_t& next,
                            std::uint32_t& flag, std::uint32_t& s0,
                            std::uint32_t saved_s0, std::uint32_t saved_ra);

}
