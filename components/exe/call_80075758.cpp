// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075758.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_80075758(std::uint32_t word, std::uint32_t& flag, std::uint32_t& slot) {
    call_8005be28(word, slot);
    flag &= ~0x20u;
    return flag;
}
}
