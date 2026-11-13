// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80060b58.hpp"

namespace am3d::exe {

void call_80060b58(std::uint32_t a0, std::uint16_t& slot0, std::uint16_t& slot6,
    std::uint16_t& slot12, std::uint16_t& slot2, std::uint16_t& slot8, std::uint16_t& slot14) {
    const auto half = static_cast<std::uint16_t>(a0);
    slot0 = half;
    slot6 = half;
    slot12 = half;
    slot2 = half;
    slot8 = half;
    slot14 = half;
}

}
