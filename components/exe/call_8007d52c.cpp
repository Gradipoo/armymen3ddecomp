// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d52c.hpp"

#include "call_8007d234.hpp"

namespace am3d::exe {

void call_8007d52c(std::uint32_t address, std::uint32_t& cleared) {
    (void)address;
    cleared = 0;
    (void)call_8007d234();
    (void)call_8007d234();
    // gap: halfwords at offsets 4 and 6. call-8007d234.md states a0 2 only.
}

}
