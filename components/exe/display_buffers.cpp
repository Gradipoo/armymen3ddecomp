// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_buffers.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80076164-second.md.
// Field correction: docs/research/re/display-environment-layout.md.
void advance_display_buffers(DisplayBufferState& state, DisplayEnvironmentGpu& gpu) {
    const auto displaying = state.drawing;
    const auto old_buffer = state.buffers.at(displaying);
    const auto drawing = old_buffer.next.value_or(state.first);
    (void)state.buffers.at(drawing); // Check the native index before publishing state.
    state.displaying = displaying;
    state.drawing = drawing;

    gpu.apply_display({static_cast<std::uint16_t>(old_buffer.x),
        static_cast<std::uint16_t>(old_buffer.y), static_cast<std::uint16_t>(state.width),
        static_cast<std::uint16_t>(state.height), false, state.mode == 3});

    // The retail function reads the drawing state after publishing the display.
    const auto& buffer = state.buffers.at(state.drawing);
    gpu.apply_draw({static_cast<std::uint16_t>(buffer.x + state.left),
        static_cast<std::uint16_t>(buffer.y + state.top),
        static_cast<std::uint16_t>(state.right - state.left),
        static_cast<std::uint16_t>(state.bottom - state.top)});
}

DisplayFillState drawing_fill_state(const DisplayBufferState& state) {
    const auto& buffer = state.buffers.at(state.drawing);
    return {static_cast<std::uint16_t>(buffer.x), static_cast<std::uint16_t>(buffer.y),
        static_cast<std::uint16_t>(state.left), static_cast<std::uint16_t>(state.top),
        static_cast<std::uint16_t>(state.right), static_cast<std::uint16_t>(state.bottom)};
}

}
