// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002542c.hpp"

#include "call_8007d52c.hpp"

namespace am3d::exe {

// The other side of beq at 0x80025424. This boot does not reach it.
void call_8002542c(std::uint32_t& a0) {
    a0 = a0 - 0x7b00u;
    std::uint32_t cleared = 1;
    call_8007d52c(a0, cleared);
}

}
