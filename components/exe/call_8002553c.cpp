// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002553c.hpp"

namespace am3d::exe {

void call_8002553c(std::uint32_t& a0, std::uint32_t& s0) {
    s0 = 0x8009f444u;
    a0 = s0;
    // gap: unnamed call at 0x80063668. a0 is 0x8009f444. The return address
    // is 0x8002554c.
}

}
