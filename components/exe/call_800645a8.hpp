// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

constexpr std::size_t kCall800645a8SlotStride = 124u;

// Unnamed body at 0x800645a8. Clears one menu record slot when slots_base is set.
// Behavior reference: docs/research/re/call-800645a8.md.
void call_800645a8(std::uint32_t slot_index, std::uint8_t* slots_base = nullptr,
                   std::size_t slot_stride = kCall800645a8SlotStride);

}  // namespace am3d::exe