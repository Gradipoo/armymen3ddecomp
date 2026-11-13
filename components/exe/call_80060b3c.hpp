// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060b3c.md.
std::uint32_t call_80060b3c(std::uint32_t saved_ra, std::uint32_t& s0, std::uint32_t saved_s0);

}
