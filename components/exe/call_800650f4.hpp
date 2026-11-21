// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_800650d0.hpp"

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800650f4.md.
// Taken block when bit 0x40 of complemented input is clear.
bool call_800650f4(std::uint8_t*& record, std::uint32_t stack_word_58,
                   MenuInputScanState& scan, std::uint32_t loop_limit);

}
