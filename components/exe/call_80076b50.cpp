// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80076b50.hpp"

#include "call_80076938.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80076b50.md.
void call_80076b50(std::uint32_t a0, std::uint32_t a1) {
    call_80076938(a0, a1, 0, 0);
}

}
