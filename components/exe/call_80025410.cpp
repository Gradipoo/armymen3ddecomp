// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025410.hpp"

#include "call_8007e118.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025410.md.
// The lui and the delay slot supply a0. The callee stores that word.
void call_80025410(std::uint32_t& a0, std::uint32_t& stored) {
    a0 = 0x800d1598u;
    call_8007e118(a0, stored);
}

}
