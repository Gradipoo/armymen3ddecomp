// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b3c.hpp"

namespace am3d::exe {

std::uint32_t call_80060b3c(std::uint32_t saved_ra, std::uint32_t& s0, std::uint32_t saved_s0) {
    s0 = saved_s0;
    return saved_ra;
}

}
