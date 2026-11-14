// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063b08.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80063b08.md.
// The jal to 0x8007f920 is not entered here.
std::uint32_t call_80063b08_a0() {
    return 0x800dd6e8u;
}

}
