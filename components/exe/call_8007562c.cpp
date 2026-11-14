// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007562c.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_8007562c(std::uint32_t a0, std::uint32_t& flag, std::uint32_t& link, std::uint32_t& slot) {
    (void)a0;
    call_8005be28(0, slot);
    link = 0;
    flag |= 2u;
    return flag;
}
}
