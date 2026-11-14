// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8004a49c.hpp"
namespace am3d::exe {
std::uint32_t call_8004a49c(std::uint32_t second) {
    const std::uint32_t field = ((second + 1u) & 7u) << 21;
    return 0x5a0a0801u | field;
}
}
