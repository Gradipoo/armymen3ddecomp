// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074144.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_80074144(std::uint32_t a0) {
    (void)a0;
    std::uint32_t word = 0;
    call_8005be28(0, word);
    // gap: resume at 0x80074174. v0 is 0. The word at 0x800e154c is 0.
    return 0;
}
}
