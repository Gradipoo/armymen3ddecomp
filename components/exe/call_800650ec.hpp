// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_800650d0.hpp"

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800650ec.md.
// Fallthrough at 0x800650ec when bit 0x40 of complemented input is set.
// Delay slot of prior beq stored 0x7f at record+0x0b before j to 0x800650f8.
bool call_800650ec(std::uint8_t*& record, std::uint32_t stack_word_58,
                   MenuInputScanState& scan, std::uint32_t loop_limit);

}