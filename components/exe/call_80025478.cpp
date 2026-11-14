// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025478.hpp"

#include "call_80025488.hpp"
#include "call_8007d3f8.hpp"

namespace am3d::exe {

std::uint32_t call_80025478(std::uint32_t& a0, std::uint32_t& stored) {
    a0 = 0x80022c1cu;
    stored = 0;
    const std::uint32_t loaded = call_8007d3f8(a0, stored);
    call_80025488(a0);
    return loaded;
}

}
