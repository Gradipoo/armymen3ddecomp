// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007424c.hpp"
#include "call_8005be28.hpp"
#include "call_8005be50.hpp"
#include "call_8005be3c.hpp"
namespace am3d::exe {
std::uint32_t call_8007424c(std::uint32_t a0) {
    (void)a0;
    std::uint32_t word = 0;
    call_8005be28(0, word);
    call_8005be50(0, word);
    call_8005be3c(0, word);
    // gap: resume at 0x80074278. v0 is 0. The flag word on this side is 2.
    return 0;
}
}
