// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8001b17c.hpp"

#include "call_80076b50.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8001b17c.md.
void call_8001b17c(std::uint32_t a0) {
    call_80076b50(0xffffffffu, a0);
}

}
