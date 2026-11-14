// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007571c.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_8007571c(std::uint32_t& flag, std::uint32_t& slot) {
    call_8005be28(0, slot);
    flag &= ~8u;
    flag |= 0x10u;
    return flag;
}
}
