// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be64.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_8005be64(std::uint32_t& slot, std::uint32_t& flag) {
    call_8005be28(0, slot);
    flag &= ~2u;
    return 0x800d89b8u;
}
}
