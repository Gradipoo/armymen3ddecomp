// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074360.hpp"
#include "call_80074144.hpp"
#include "call_8007424c.hpp"
namespace am3d::exe {
std::uint32_t call_80074360() {
    const std::uint32_t result = call_80074144(5);
    call_8007424c(5);
    return result;
}
}
