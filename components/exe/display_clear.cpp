// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_clear.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007641c-second.md.
void clear_display_buffers(std::uint32_t color, DisplayBufferState& state,
                           DisplayEnvironmentGpu& environments, DisplayFillGpu& primitives) {
    if (state.buffer_count == 0) return;
    std::uint32_t completed = 0;
    do {
        ++completed;
        advance_display_buffers(state, environments);
        fill_display(color, [&state] { return drawing_fill_state(state); }, primitives);
    } while (completed < state.buffer_count);
}

}
