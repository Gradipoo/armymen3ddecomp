// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Menu650b4Result {
    bool complemented_bit_0x20;
    bool branch_to_650c8;
    std::uint8_t stored_at_0xa;
};

// Behavior reference: docs/research/re/call-800650b4.md.
// Taken target of beq at 0x800650a0; rejoins 0x800650cc on both sides.
Menu650b4Result call_800650b4(std::uint8_t* record, std::uint32_t complemented_a0);

} // namespace am3d::exe