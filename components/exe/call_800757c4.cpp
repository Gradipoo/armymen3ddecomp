// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800757c4.hpp"
namespace am3d::exe {
void call_800757c4(std::uint32_t a0, std::uint32_t a1, std::uint32_t flag) {
    (void)a0;
    (void)a1;
    if ((flag & 1u) == 0) {
        // gap: beq a1, zero at 0x800758b8. a1 is not stated.
        return;
    }
}
}
