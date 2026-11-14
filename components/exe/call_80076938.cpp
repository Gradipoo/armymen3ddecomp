// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80076938.hpp"

#include "call_800768d8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80076938.md.
void call_80076938(std::uint32_t a0, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    if (a0 != 0xffffffffu) {
        // The branch target 0x80076990 is not this entry.
        return;
    }
    call_800768d8(a0, a1, a2, a3);
}

}
