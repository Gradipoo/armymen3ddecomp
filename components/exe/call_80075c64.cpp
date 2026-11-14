// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075c64.hpp"
#include "call_8005be28.hpp"
#include "call_80075758.hpp"
namespace am3d::exe {
std::uint32_t call_80075c64(std::uint32_t a0, std::uint32_t word, std::uint32_t& flag, std::uint32_t& slot) {
    (void)a0;
    call_80075758(word, flag, slot);
    return call_8005be28(0x800759c8u, slot);
}
}
