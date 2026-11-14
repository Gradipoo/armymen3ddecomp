// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062238.hpp"

namespace am3d::exe {

std::uint32_t call_80062238(std::uint32_t& v0, std::uint32_t& s0, std::uint32_t& s1,
                            std::uint32_t& s2, std::uint32_t saved_s0,
                            std::uint32_t saved_s1, std::uint32_t saved_s2,
                            std::uint32_t saved_ra) {
    v0 = 0;
    s2 = saved_s2;
    s1 = saved_s1;
    s0 = saved_s0;
    return saved_ra;
}

}
