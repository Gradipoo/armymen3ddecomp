// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_task_7_menu.hpp"

#include "menu_input_scan_loop.hpp"
#include "menu_scan_pad_dispatch_inject.hpp"
#include "menu_table_sequence.hpp"

#include <array>

namespace am3d::exe {
namespace {

constexpr std::size_t kSlots = 8u;

MenuInputScanState* g_scan_for_pad = nullptr;

}  // namespace

std::uint32_t prototype_task_7_pad_get_state(std::uint32_t port) {
    (void)port;
    if (g_scan_for_pad != nullptr && g_scan_for_pad->s7 >= 8u) {
        return 3u;
    }
    return 2u;
}

PrototypeTask7MenuResult run_prototype_task_7_menu_transition(
    std::uint32_t (*pad_get_state)(std::uint32_t port), const std::uint8_t* front_bytes,
    std::size_t front_size) {
    PrototypeTask7MenuResult result{};
    result.has_front = front_bytes != nullptr && front_size != 0u;
    result.selection_index_after_a = 0u;
    result.selection_index_after_b = 1u;
    if (pad_get_state == nullptr) {
        return result;
    }

    std::array<std::uint8_t, kSlots * kMenuInputScanSlotBytes> table{};
    menu_table_fill_released_slots(table.data(), kSlots);

    std::array<std::uint8_t, 0x400u> bytes{};
    std::uint8_t* record = bytes.data();
    MenuInputScanState scan{};
    MenuInputScanIndices indices{};
    indices.stack_word_18 = 0u;
    indices.menu_table_bytes = static_cast<std::uint32_t>(table.size());
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
    MenuTableSequencer sequencer{};

    g_scan_for_pad = &scan;
    const MenuInputScanLoopResult phase_a = run_menu_input_scan_frames(
        4u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        &sequencer, nullptr);
    result.frames_run = phase_a.frames_run;
    result.s7_after_a = scan.s7;
    result.tail_0b = bytes[0x0bu];
    result.tail_87 = bytes[0x87u];
    result.phase_a_tail_ran = phase_a.last_step.tail_ran;
    result.marker_x_a = 200u + scan.s7 * 12u;

    PadStateDispatchInject pad_inject{};
    const std::uint32_t down_dest = kMenuScanProvisionalDownDispatchDest;
    pad_inject.entry[3] = &down_dest;

    menu_input_scan_host_resume(scan, indices, stack_word_1c, scan.s7 + 1u);
    const MenuInputScanLoopResult transition = run_menu_input_scan_frames(
        1u, pad_get_state, table.data(), indices, sp20, 0u, 0u, record, scan, stack_word_1c,
        nullptr, nullptr, &pad_inject);
    g_scan_for_pad = nullptr;

    result.frames_run_b = transition.frames_run;
    result.destination_stated = transition.last_step.dispatch.destination_stated;
    result.destination = transition.last_step.dispatch.destination;
    result.word_address = transition.last_step.dispatch.word_address;
    result.phase_b_tail_ran = transition.last_step.tail_ran;
    result.s7_after_b = scan.s7;
    result.marker_x_b = 200u + scan.s7 * 12u;
    return result;
}

}  // namespace am3d::exe
