// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064588.hpp"

#include "call_80064598.hpp"
#include "call_80094f54.hpp"

namespace am3d::exe {

std::uint32_t call_80064588(std::uint32_t& a0) {
    (void)call_80094f54(a0);
    return call_80064598(0x80025490u);
}

}
