// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007560c.hpp"
#include "call_8005c014.hpp"
namespace am3d::exe {
std::uint32_t call_8007560c() {
    // gap: the arriving ra is not stated.
    return call_8005c014(0);
}
}
