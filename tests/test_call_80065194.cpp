// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065194.hpp"

#include <cstdint>

int main() {
    const am3d::exe::MenuLoopFallthrough zero =
        am3d::exe::call_80065194(0u);
    if (!zero.entered_6519c || zero.branch_to_651c8 ||
        zero.v0 != 0x800e0000u) {
        return 1;
    }
    const am3d::exe::MenuLoopFallthrough nonzero =
        am3d::exe::call_80065194(1u);
    if (!nonzero.branch_to_651c8 || nonzero.entered_6519c ||
        nonzero.v0 != 0x800e0000u) {
        return 2;
    }
    return 0;
}