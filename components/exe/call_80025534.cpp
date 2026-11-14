// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025534.hpp"

namespace am3d::exe {

void call_80025534(std::uint32_t& a0) {
    a0 = 2;
    // gap: second entry of the call at 0x8007d12c. a0 is 2.
    // The return address is 0x8002553c.
}

}
