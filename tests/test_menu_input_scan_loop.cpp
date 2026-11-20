// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t g_pad_state = 2u;

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return g_pad_state;
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
    std::uint32_t stack_word_1c = 4u;
    const am3d::exe::MenuInputScanLoopResult result =
        am3d::exe::run_menu_input_scan_frames(
            16u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record,
            scan, stack_word_1c);
    if (result.frames_run < 3u) {
        return 1;
    }
    if (result.frames_run != 4u || scan.s7 != 4u) {
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
    constexpr std::uint32_t kS1After651c8 = 0x800e0000u + 0x18fau;
    if (!result.last_step.loop_body_64dc8_recorded ||
        result.last_step.loop_body_64dc8.branch_to_65194 ||
        !result.last_step.loop_body_64dc8.entered_64dd8 ||
        result.last_step.loop_body_64dc8.v0 != 0u ||
        result.last_step.loop_body_64dc8.s1 != kS1After651c8 + 1u) {
        return 8;
    }
    if (!result.last_step.loop_body_64dd8_recorded ||
        !result.last_step.loop_body_64dd8.branch_to_64dfc ||
        result.last_step.loop_body_64dd8.entered_64dec ||
        result.last_step.loop_body_64dd8.v0 != 0u ||
        result.last_step.loop_body_64dd8.t1 != 1u) {
        return 9;
    }
    if (!result.last_step.loop_body_64dfc_recorded ||
        result.last_step.loop_body_64dfc.branch_to_65194 ||
        !result.last_step.loop_body_64dfc.entered_64e14 ||
        result.last_step.loop_body_64dfc.s1 != kS1After651c8 ||
        result.last_step.loop_body_64dfc.s7 != 0u ||
        stack_word_1c != 1u) {
        return 10;
    }

    g_pad_state = 3u;
    scan = {};
    indices = {};
    stack_word_1c = 4u;
    indices.menu_table_bytes =
        static_cast<std::uint32_t>(table.size());
    record = bytes.data();
    constexpr std::uint32_t kProvisionalDownDest = 0x80064f14u;
    am3d::exe::PadStateDispatchInject pad_inject{};
    pad_inject.entry[3] = &kProvisionalDownDest;
    const am3d::exe::MenuInputScanLoopResult down =
        am3d::exe::run_menu_input_scan_frames(
            1u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record,
            scan, stack_word_1c, nullptr, nullptr, &pad_inject);
    if (down.frames_run != 1u || !down.last_step.dispatch.destination_stated ||
        down.last_step.dispatch.destination != kProvisionalDownDest ||
        down.last_step.dispatch.word_address != 0x800c3ea4u ||
        !down.last_step.tail_ran) {
        return 7;
    }

    return 0;
}