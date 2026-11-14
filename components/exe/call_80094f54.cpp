// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80094f54.hpp"

#include "call_80094f64.hpp"
#include "call_80095744.hpp"

namespace am3d::exe {

std::uint32_t call_80094f54(std::uint32_t& a0) {
    std::uint32_t cleared = 1;
    std::uint32_t status = 1;
    std::uint32_t mask = 0;
    call_80095744(cleared, status, mask);
    (void)a0;
    return call_80094f64(0x80064598u);
}

}
