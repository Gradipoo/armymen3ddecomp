// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007fbbc.hpp"

using namespace am3d::exe;

int main() {
    std::uint32_t control_29 = 0;
    std::uint32_t control_30 = 0;
    call_8007fbbc(0x55u, 0x40u, control_29, control_30);
    if (control_29 != 0x55u) return 1;
    if (control_30 != 0x40u) return 2;
    return 0;
}
