// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074144.hpp"
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_80074144(std::uint32_t a0, std::uint32_t link, std::uint32_t flag) {
    (void)a0;
    std::uint32_t word = 0;
    call_8005be28(0, word);
    if (link != 0) {
        return 0;
    }
    return flag | 2u;
}
}
