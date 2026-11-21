// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800650e0.md.
// Returns true when bit 0x40 of complemented_input is set (fallthrough
// at 0x800650ec, see call_800650ec). Returns false when that bit is clear
// (branch to 0x800650f4, see call_800650f4).
bool call_800650e0(std::uint32_t complemented_input);

}
