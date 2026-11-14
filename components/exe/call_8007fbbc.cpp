// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007fbbc.hpp"

#include "call_8007e1f8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007fbbc.md.
// The two words write coprocessor 2 control fields 29 and 30. jr ra returns to 0x8007e1f8.
void call_8007fbbc(std::uint32_t a0, std::uint32_t a1, std::uint32_t& control_29,
    std::uint32_t& control_30) {
    control_29 = a0;
    control_30 = a1;
    call_8007e1f8();
}

}
