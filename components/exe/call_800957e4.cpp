// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800957e4.hpp"

namespace am3d::exe {

std::uint32_t call_800957e4(std::uint32_t& base, std::uint32_t& next,
                            std::uint32_t& flag, std::uint32_t& s0,
                            std::uint32_t saved_s0, std::uint32_t saved_ra) {
    next = 0;
    base = 0;
    flag = 1;
    s0 = saved_s0;
    return saved_ra;
}

}
