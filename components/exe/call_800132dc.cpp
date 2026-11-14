// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800132dc.hpp"
#include "call_80013318.hpp"
namespace am3d::exe {
void call_800132dc(const std::uint8_t* object, std::uint32_t second) {
    // gap: 0x8003035c is named and stops on an unknown blez.
    call_80013318(object, second);
}
}
