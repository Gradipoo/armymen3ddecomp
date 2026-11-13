// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80060b58.md.
// The six halfwords are the ones this block stores.
void call_80060b58(std::uint32_t a0, std::uint16_t& slot0, std::uint16_t& slot6,
    std::uint16_t& slot12, std::uint16_t& slot2, std::uint16_t& slot8, std::uint16_t& slot14);

}
