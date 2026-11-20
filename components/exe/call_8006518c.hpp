// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8006518c.md.
// True when slt at 0x80065188 is 1, so bne at 0x8006518c loops to
// 0x80064e40. False falls through to 0x80065194. Neither target is entered.
// limit is the word at sp+0x1c. Its retail value is not stated here.
bool menu_scan_should_loop(std::uint32_t s7, std::uint32_t limit);

}
