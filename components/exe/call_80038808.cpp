// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80038808.hpp"
namespace am3d::exe {
void call_80038808(std::uint32_t pointer) {
    // gap: bne compares 0x800abb98 with an unstated a0.
    (void)pointer;
}
}
