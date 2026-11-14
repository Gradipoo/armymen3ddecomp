// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002542c.hpp"

namespace am3d::exe {

// The other side of beq at 0x80025424. This boot does not reach it.
void call_8002542c(std::uint32_t& a0) {
    a0 = a0 - 0x7b00u;
    // gap: unnamed jal 0x8007d52c. a0 is 0x800c8500. The return address is 0x80025434.
}

}
