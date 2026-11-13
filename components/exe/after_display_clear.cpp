// SPDX-License-Identifier: GPL-3.0-or-later
#include "after_display_clear.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025390.md.
// The display-clear compare left this result in v0. This site does not write it.
std::uint32_t call_after_display_clear(std::uint32_t compare_result) {
    // gap: unnamed call at 0x80076234. The delay slot is nop.
    // This site does not set a0, a1, a2, or a3.
    return compare_result;
}

}
