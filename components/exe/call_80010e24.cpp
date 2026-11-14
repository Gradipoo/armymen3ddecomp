// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010e24.hpp"
namespace am3d::exe {
std::uint32_t call_80010e24(std::uint32_t v0) {
    // gap: jr at 0x80010e2c. The saved ra is the ra that entered 0x80010e00. It is not stated.
    return v0;
}
}
