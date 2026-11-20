// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"
#include "menu_table_sequence.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return 2u;
}

constexpr std::size_t kSlots = 8u;

}  // namespace

// Disc-free check for the menu scan smoke integration path (no SDL).
int main() {
    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    constexpr std::uint32_t kLimit = 4u;
    am3d::exe::MenuTableSequencer sequencer{};

    const am3d::exe::MenuInputScanLoopResult result = am3d::exe::run_menu_input_scan_frames(
        2u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan, kLimit,
        &sequencer);
    if (result.frames_run != 2u) {
        return 1;
    }
    if (!result.last_step.loop_again) {
        return 2;
    }
    if (!result.last_step.tail_ran) {
        return 3;
    }
    // Frame 0 clear tail at 0x0b; frame 1 up tail at 0x7c+0x0b after record stride.
    if (bytes[0x0bu] != 0u || bytes[0x87u] != 0x80u) {
        return 4;
    }
    return 0;
}