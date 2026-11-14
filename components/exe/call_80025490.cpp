// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025490.hpp"

namespace am3d::exe {

void call_80025490(std::uint32_t& a0) {
    a0 = 0x80075198u;
    // gap: unnamed call at 0x800621dc. a0 is 0x80075198. The return address
    // is 0x800254f0.
}

}
