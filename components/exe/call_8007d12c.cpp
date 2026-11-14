// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d12c.hpp"

namespace am3d::exe {

std::uint32_t call_8007d12c(std::uint32_t& word, std::uint32_t& s0,
                            std::uint32_t saved_s0, std::uint32_t saved_ra) {
    word = 0;
    s0 = saved_s0;
    return saved_ra;
}

}
