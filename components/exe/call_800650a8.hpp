// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Menu650a8Result {
    std::uint8_t stored_at_0xa;
};

// Behavior reference: docs/research/re/call-800650a8.md.
// Fallthrough of beq at 0x800650a0; joins 0x800650cc.
Menu650a8Result call_800650a8(std::uint8_t* record);

} // namespace am3d::exe