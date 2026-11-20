// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"
#include "menu_scan_pad_dispatch_inject.hpp"
#include "menu_table_sequence.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return 2u;
}

constexpr std::size_t kSlots = 8u;

constexpr std::array<std::uint8_t, 4u> kCompareFourSlot{0u, 0x41u, 0xffu, 0xffu};

int run_sequencer_smoke() {
    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
    am3d::exe::MenuTableSequencer sequencer{};

    const am3d::exe::MenuInputScanLoopResult result = am3d::exe::run_menu_input_scan_frames(
        2u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan,
        stack_word_1c, &sequencer, nullptr);
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

int run_stack_word_28_compare_four() {
    std::array<std::uint8_t, kCompareFourSlot.size()> table = kCompareFourSlot;
    std::array<std::uint8_t, 0x100u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.stack_word_28 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    constexpr std::uint32_t kCompareWordFour = 4u;
    std::uint32_t stack_word_1c = 8u;

    const am3d::exe::MenuInputScanLoopResult result = am3d::exe::run_menu_input_scan_frames(
        1u, pad_get_state, table.data(), indices, sp20, 0u, kCompareWordFour, record,
        scan, stack_word_1c, nullptr, &indices.stack_word_28);
    if (result.frames_run != 1u) {
        return 10;
    }
    if (!result.last_step.compare_four_to_65168 || !result.last_step.tail_ran ||
        !result.last_step.loop_again) {
        return 11;
    }
    if (indices.stack_word_28 != 4u) {
        return 12;
    }
    // call_80065168: add four at sp+0x28 per call-80065168.md.
    if (scan.table_cursor != 4u || record != bytes.data() + 0x7cu) {
        return 13;
    }
    return 0;
}

int run_down_dispatch_inject() {
    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;

    const am3d::exe::PadStateDispatchInject& inject =
        am3d::exe::menu_scan_down_dispatch_inject();
    const am3d::exe::MenuInputScanLoopResult result = am3d::exe::run_menu_input_scan_frames(
        1u, [](std::uint32_t port) {
            (void)port;
            return 3u;
        },
        table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c, nullptr, nullptr,
        &inject);
    if (result.frames_run != 1u) {
        return 20;
    }
    if (!result.last_step.dispatch.destination_stated ||
        result.last_step.dispatch.destination != am3d::exe::kMenuScanProvisionalDownDispatchDest ||
        result.last_step.dispatch.word_address != 0x800c3ea4u || !result.last_step.tail_ran) {
        return 21;
    }
    return 0;
}

}  // namespace

// Disc-free check for the menu scan smoke integration path (no SDL).
int main() {
    const int sequencer = run_sequencer_smoke();
    if (sequencer != 0) {
        return sequencer;
    }
    const int compare_four = run_stack_word_28_compare_four();
    if (compare_four != 0) {
        return compare_four;
    }
    if constexpr (am3d::exe::kMenuScanHeadlessInjectDown != 0) {
        return run_down_dispatch_inject();
    }
    return 0;
}