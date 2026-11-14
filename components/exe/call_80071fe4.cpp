// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80071fe4.hpp"
namespace am3d::exe {
void call_80071fe4(std::uint32_t a0, std::uint32_t a1, std::uint32_t& low, std::uint32_t& high) {
    high = a1;
    low = a0;
}
}
