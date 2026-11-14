// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007fc1c.hpp"
namespace am3d::exe {
std::uint32_t call_8007fc1c(std::uint32_t status) {
    return status & 0xfffffbfeu;
}
}
