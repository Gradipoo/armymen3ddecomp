// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan_loop.hpp"
#include "menu_table_sequence.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t g_pad_state = 2u;

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return g_pad_state;
}

constexpr std::size_t kSlots = 8u;

int run_phase_a() {
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
        4u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan,
        stack_word_1c, &sequencer, nullptr);
    if (result.frames_run != 4u) {
        return 1;
    }
    if (scan.s7 != 8u) {
        return 2;
    }
    if (bytes[0x0bu] != 0u || bytes[0x87u] != 0x80u) {
        return 3;
    }
    if (!result.last_step.tail_ran) {
        return 4;
    }
    return 0;
}

int run_phase_b() {
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

    constexpr std::uint32_t kProvisionalDownDest = 0x80064f14u;
    am3d::exe::PadStateDispatchInject pad_inject{};
    pad_inject.entry[3] = &kProvisionalDownDest;

    g_pad_state = 3u;
    const am3d::exe::MenuInputScanLoopResult down = am3d::exe::run_menu_input_scan_frames(
        1u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan,
        stack_word_1c, nullptr, nullptr, &pad_inject);
    if (down.frames_run != 1u) {
        return 10;
    }
    if (!down.last_step.dispatch.destination_stated ||
        down.last_step.dispatch.destination != kProvisionalDownDest ||
        down.last_step.dispatch.word_address != 0x800c3ea4u ||
        !down.last_step.tail_ran) {
        return 11;
    }
    return 0;
}

}  // namespace

// PROTOTYPE.md row 7 synthetic acceptance (disc-free multi-frame + Down dispatch).
int main() {
    const int phase_a = run_phase_a();
    if (phase_a != 0) {
        return phase_a;
    }
    return run_phase_b();
}