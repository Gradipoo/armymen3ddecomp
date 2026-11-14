// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800254fc.hpp"

namespace am3d::exe {

void call_800254fc(std::uint32_t& a0, std::uint32_t& s2, std::uint32_t& cleared) {
    a0 = 0x8005b3d4u;
    s2 = 0x8009f820u;
    cleared = 0;
    // gap: unnamed call at 0x800621dc. a0 is 0x8005b3d4. The return address
    // is 0x80025514. call-800621dc.md is the first entry.
}

}
