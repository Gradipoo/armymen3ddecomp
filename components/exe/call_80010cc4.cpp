// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010cc4.hpp"

#include "call_8002fc2c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80010cc4.md.
// jal at 0x80010cc8. The return address is 0x80010cd0. The saved ra there is not known.
void call_80010cc4(std::uint8_t* object, std::uint32_t second) {
    call_8002fc2c(object, second);
}

}
