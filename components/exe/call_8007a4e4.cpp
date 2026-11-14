// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a4e4.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007a4e4.md.
std::uint32_t call_8007a4e4(std::uint32_t a0) {
    if (a0 == 0x8007c4a4u) {
        return 0x800b5d78u;
    }
    if (a0 == 0x8005bf80u) {
        return 0x800b3b68u;
    }
    if (a0 == 0x8007c2dcu) {
        return 0x800b5d30u;
    }
    if (a0 == 0x8007cb9cu) {
        return 0x800b5da0u;
    }
    return 0;
}

}
