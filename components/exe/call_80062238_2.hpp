// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80062238-2.md.
std::uint32_t call_80062238_2(std::uint32_t& v0, std::uint32_t& s0, std::uint32_t& s1,
                              std::uint32_t& s2, std::uint32_t saved_s0,
                              std::uint32_t saved_s1, std::uint32_t saved_s2,
                              std::uint32_t saved_ra);

}
