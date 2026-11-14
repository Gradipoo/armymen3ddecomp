// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007fbbc.hpp"

#include "call_8007e1f8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007fbbc.md.
// The two words are not decoded. jr ra returns to 0x8007e1f8.
void call_8007fbbc(std::uint32_t a0, std::uint32_t a1) {
    // gap: undecoded words at 0x8007fbbc and 0x8007fbc0. a0 is 0x55. a1 is 0x40. The return address is 0x8007e1f8.
    (void)a0;
    (void)a1;
    call_8007e1f8();
}

}
