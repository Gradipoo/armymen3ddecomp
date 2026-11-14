// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063668.hpp"

namespace am3d::exe {

void call_80063668(std::uint32_t& a1, std::uint32_t a0) {
    a1 = a0;
    // gap: unnamed call at 0x80062434. a1 is the arriving pointer.
    // a0 is the stack address at 0x10(sp). The return address is 0x80063684.
}

}
