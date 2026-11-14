// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80077fdc.hpp"

namespace am3d::exe {

std::uint32_t call_80077fdc(std::uint32_t& word, std::uint32_t a0, std::uint32_t saved_ra) {
    word = a0;
    return saved_ra;
}

}
