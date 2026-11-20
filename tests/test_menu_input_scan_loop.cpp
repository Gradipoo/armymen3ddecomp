// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return 2u;
}

constexpr std::array<std::uint8_t, 4u> kReleased{0u, 0x41u, 0xffu, 0xffu};

void fill_released_slots(std::uint8_t* bytes, std::size_t slot_count) {
    for (std::size_t slot = 0u; slot < slot_count; ++slot) {
        const std::size_t base = slot * kReleased.size();
        for (std::size_t i = 0u; i < kReleased.size(); ++i) {
            bytes[base + i] = kReleased[i];
        }
    }
}

}

int main() {
    constexpr std::size_t kSlots = 8u;
    std::array<std::uint8_t, kSlots * kReleased.size()> table{};
    fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    indices.menu_table_bytes =
        static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    constexpr std::uint32_t kLimit = 4u;
    const am3d::exe::MenuInputScanLoopResult result =
        am3d::exe::run_menu_input_scan_frames(
            16u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record,
            scan, kLimit);
    if (result.frames_run < 3u) {
        return 1;
    }
    if (result.frames_run != 4u || scan.s7 != kLimit) {
        return 2;
    }
    if (result.last_step.loop_again) {
        return 3;
    }
    if (!result.last_step.tail_ran) {
        return 4;
    }
    if (!result.last_step.loop_exit_recorded ||
        !result.last_step.loop_exit.branch_to_651c8 ||
        result.last_step.loop_exit.entered_6519c ||
        result.last_step.loop_exit.v0 != 0x800e0000u) {
        return 5;
    }
    if (!result.last_step.loop_taken_651c8_recorded ||
        !result.last_step.loop_taken_651c8.branch_to_64dc8 ||
        result.last_step.loop_taken_651c8.entered_651e0 ||
        indices.stack_word_18 != 1u) {
        return 6;
    }
    return 0;
}