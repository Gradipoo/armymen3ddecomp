// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80075ba8.hpp"
#include "call_8007571c.hpp"
namespace am3d::exe {
std::uint32_t call_80075ba8(std::uint32_t a0, std::uint32_t& flag, std::uint32_t& slot) {
    (void)a0;
    return call_8007571c(flag, slot);
}
}
