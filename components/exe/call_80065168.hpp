// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_800650d0.hpp"

#include <cstdint>

namespace am3d::exe {

// Shared tail at 0x80065168 when compare-four masks to zero at 0x80064f7c.
// Behavior reference: docs/research/re/call-80065168.md.
// stack_word_1c is the limit at sp+0x1c (caller supplied, not retail).
// stack_word_28 is the cursor at sp+0x28 in/out; optional when nullptr.
bool call_80065168(std::uint8_t*& record, MenuInputScanState& scan,
                   std::uint32_t stack_word_1c, std::uint32_t* stack_word_28);

}