// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800621dc.hpp"

#include "call_80075198.hpp"

namespace am3d::exe {

std::uint32_t call_800621dc(std::uint32_t& counter, std::uint32_t& slot,
                            std::uint32_t& a0, std::uint32_t& a1,
                            std::uint32_t handler) {
    slot = handler;
    a0 = 0;
    a1 = 0;
    counter += 1;
    (void)call_80075198();
    return handler;
}

}
