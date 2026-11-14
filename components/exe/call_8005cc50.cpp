// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005cc50.hpp"
namespace am3d::exe {
std::uint32_t call_8005cc50(std::uint32_t a0) {
    // gap: unnamed jal 0x8005c9b0. a0 stays the arriving value. The return address is 0x8005cc80.
    return a0;
}
}
