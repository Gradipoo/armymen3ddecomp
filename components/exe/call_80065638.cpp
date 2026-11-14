// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065638.hpp"
namespace am3d::exe {
std::uint32_t call_80065638(std::uint32_t word) {
    return (word - 4u) < 2u ? 1u : 0u;
}
}
