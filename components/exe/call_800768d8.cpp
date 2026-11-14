// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800768d8.hpp"

#include "call_800767d8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800768d8.md.
void call_800768d8(std::uint32_t a0, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    (void)a0;
    (void)a1;
    (void)a2;
    (void)a3;
    call_800767d8(0x800c5424u, 0);
}

}
