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

// Frame 0 released and frame 1 up at advancing table_cursor yield distinct tail bytes.
int main() {
    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> record_bytes{};
    std::uint8_t* record = record_bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
    am3d::exe::MenuTableSequencer sequencer{};

    record_bytes.fill(0u);
    scan = {};
    record = record_bytes.data();
    const am3d::exe::MenuInputScanLoopResult frame0 = am3d::exe::run_menu_input_scan_frames(
        1u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        &sequencer);
    constexpr std::size_t kRecordStride = 0x7cu;
    // Frame 0 clear tail writes at the record base; frame 1 up tail follows record advance.
    const std::uint8_t tail_frame0 = record_bytes[0x0bu];
    const std::uint32_t s7_after_frame0 = scan.s7;

    const am3d::exe::MenuInputScanLoopResult frame1 = am3d::exe::run_menu_input_scan_frames(
        1u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        &sequencer);
    const std::uint8_t tail_frame1 = record_bytes[kRecordStride + 0x0bu];

    if (frame0.frames_run != 1u || frame1.frames_run != 1u) {
        return 1;
    }
    if (!frame0.last_step.tail_ran || !frame1.last_step.tail_ran) {
        return 2;
    }
    if (tail_frame0 != 0u || tail_frame1 != 0x80u) {
        return 3;
    }
    if (tail_frame0 == tail_frame1) {
        return 4;
    }
    if (s7_after_frame0 == scan.s7) {
        return 5;
    }
    return 0;
}