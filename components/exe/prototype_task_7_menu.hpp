// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>

namespace am3d::exe {

// Shared Down transition for PROTOTYPE row 7.
// selection_index_after_a is 0 (NEW GAME) and selection_index_after_b is 1
// (OPTIONS after Down). Those indices follow the story in
// docs/research/re/first-screen-observation.md. They are an observation-aligned
// stand-in, not a read of retail RAM.
struct PrototypeTask7MenuResult {
    std::uint32_t frames_run = 0;
    std::uint32_t s7_after_a = 0;
    std::uint8_t tail_0b = 0;
    std::uint8_t tail_87 = 0;
    bool phase_a_tail_ran = false;
    std::uint32_t frames_run_b = 0;
    bool destination_stated = false;
    std::uint32_t destination = 0;
    std::uint32_t word_address = 0;
    bool phase_b_tail_ran = false;
    std::uint32_t s7_after_b = 0;
    std::uint32_t marker_x_a = 0;
    std::uint32_t marker_x_b = 0;
    std::uint32_t selection_index_after_a = 0;
    std::uint32_t selection_index_after_b = 1;
    bool has_front = false;
};

// Pad used by the shared runner. Returns 2 until s7 reaches 8, then 3.
// Valid only while run_prototype_task_7_menu_transition is on the stack.
std::uint32_t prototype_task_7_pad_get_state(std::uint32_t port);

// Phase A is four sequencer frames. Phase B resumes and takes one Down step
// with PadStateDispatchInject entry 3 at the provisional destination
// 0x80064f14. front_bytes is optional and only sets has_front.
PrototypeTask7MenuResult run_prototype_task_7_menu_transition(
    std::uint32_t (*pad_get_state)(std::uint32_t port), const std::uint8_t* front_bytes,
    std::size_t front_size);

}  // namespace am3d::exe
