// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006518c.hpp"

#include <cstdint>

int main() {
    // Limits below are synthetic. The retail word at sp+0x1c is unstated.
    if (!am3d::exe::menu_scan_should_loop(1u, 4u)) {
        return 1;
    }
    if (am3d::exe::menu_scan_should_loop(4u, 4u)) {
        return 2;
    }
    if (am3d::exe::menu_scan_should_loop(5u, 4u)) {
        return 3;
    }
    if (!am3d::exe::menu_scan_should_loop(0xffffffffu, 0u)) {
        return 4;
    }
    if (am3d::exe::menu_scan_should_loop(1u, 0xffffffffu)) {
        return 5;
    }
    return 0;
}
