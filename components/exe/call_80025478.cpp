// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025478.hpp"

namespace am3d::exe {

void call_80025478(std::uint32_t& a0, std::uint32_t& stored) {
    a0 = 0x80022c1cu;
    stored = 0;
    // gap: unnamed call at 0x8007d3f8. a0 is 0x80022c1c. The return address is 0x80025488.
}

}
