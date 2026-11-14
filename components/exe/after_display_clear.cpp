// SPDX-License-Identifier: GPL-3.0-or-later
#include "after_display_clear.hpp"

#include "call_80076234.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025390.md.
// The display-clear compare left this result in v0. This site does not write it.
std::uint32_t call_after_display_clear(std::uint32_t compare_result) {
    (void)call_80076234();
    return compare_result;
}

}
