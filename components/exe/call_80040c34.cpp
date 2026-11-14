// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80040c34.hpp"
namespace am3d::exe {
std::uint32_t call_80040c34(std::uint32_t half) {
    return 0x800a0210u + ((half >> 6) & 0x1cu);
}
}
