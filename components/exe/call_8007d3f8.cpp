// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d3f8.hpp"

namespace am3d::exe {

std::uint32_t call_8007d3f8(std::uint32_t a0, std::uint32_t& slot) {
    const std::uint32_t loaded = slot;
    slot = a0;
    return loaded;
}

}
