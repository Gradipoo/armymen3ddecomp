// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80079b24.hpp"

#include "call_80079270.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80079b4c.md.
std::uint32_t call_80079b24(std::uint32_t a0) {
    const std::uint32_t v0 = call_80079270();
    if (v0 == 0) {
        return 0;
    }
    (void)a0;
    return v0;
}

}
