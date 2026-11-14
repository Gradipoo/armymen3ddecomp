// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074360.hpp"
#include "call_80074144.hpp"
namespace am3d::exe {
std::uint32_t call_80074360() {
    const std::uint32_t result = call_80074144(5);
    // gap: resume at 0x800743a0. v0 is 2. The word at 0x800e152c would be 2 on this side.
    return result;
}
}
