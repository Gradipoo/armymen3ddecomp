// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025514.hpp"

namespace am3d::exe {

void call_80025514(std::uint32_t& a0) {
    a0 = 0x800638b8u;
    // gap: unnamed call at 0x80077fdc. a0 is 0x800638b8. The byte there is 0.
    // The return address is 0x8002552c.
}

}
