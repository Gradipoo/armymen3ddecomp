// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064758.hpp"

int main() {
    if (am3d::exe::call_80064758(0u, 1u) != 0u) {
        return 1;
    }
    if (am3d::exe::call_80064758(1u, 1u) != 1u) {
        return 2;
    }
    if (am3d::exe::call_80064758(0x100u, 1u) != 0u) {
        return 3;
    }
    if (am3d::exe::call_80064758(0xffffu, 1u) != 1u) {
        return 4;
    }
    return 0;
}
