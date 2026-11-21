// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800645a8.hpp"

#include <cstring>

namespace am3d::exe {

void call_800645a8(std::uint32_t slot_index, std::uint8_t* slots_base,
                   std::size_t slot_stride) {
    if (slots_base == nullptr || slot_stride < 0x15u) {
        return;
    }
    std::uint8_t* const slot = slots_base + slot_index * slot_stride;
    std::memset(slot, 0, 0x15u);
}

}  // namespace am3d::exe