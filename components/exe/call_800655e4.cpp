// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800655e4.hpp"
namespace am3d::exe {
std::uint32_t call_800655e4(std::uint32_t word) {
    return (word - 1u) < 2u ? 1u : 0u;
}
}
