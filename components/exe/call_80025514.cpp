// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025514.hpp"

#include "call_80077fdc.hpp"

namespace am3d::exe {

void call_80025514(std::uint32_t& a0) {
    a0 = 0x800638b8u;
    std::uint32_t word = 0;
    (void)call_80077fdc(word, a0, 0x8002552cu);
}

}
