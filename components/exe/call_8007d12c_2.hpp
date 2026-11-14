// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007d12c-2.md.
std::uint32_t call_8007d12c_2(std::uint32_t& word, std::uint32_t& s0,
                              std::uint32_t saved_s0, std::uint32_t saved_ra);

}
