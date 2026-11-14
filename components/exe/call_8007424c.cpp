// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007424c.hpp"
#include "call_8005be28.hpp"
#include "call_8005be50.hpp"
#include "call_8005be3c.hpp"
#include "call_8005be9c.hpp"
namespace am3d::exe {
std::uint32_t call_8007424c(std::uint32_t a0, std::uint32_t flag) {
    (void)a0;
    std::uint32_t word = 0;
    call_8005be28(0, word);
    call_8005be50(0, word);
    call_8005be3c(0, word);
    flag &= ~0x19u;
    std::uint32_t slot = 0;
    call_8005be9c(slot);
    return flag;
}
}
