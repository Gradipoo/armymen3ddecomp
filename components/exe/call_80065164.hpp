// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_800650d0.hpp"

#include <cstdint>

namespace am3d::exe {

// Shared tail at 0x80065164 after the first-byte branch at 0x80065144.
// Advances s1 by seven bytes and s0 by 0x7c before the loop compare at 0x8006518c.
// Behavior reference: docs/research/re/call-80065164.md.
bool call_80065164(std::uint8_t*& record, std::uint32_t& menu_table_index,
                   MenuInputScanState& scan, std::uint32_t stack_word_1c,
                   std::uint32_t* stack_word_28);

}  // namespace am3d::exe