// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_buffers.hpp"
#include <stdexcept>

using namespace am3d::exe;

class Capture final : public DisplayEnvironmentGpu {
public:
    int calls = 0;
    bool valid = true;
    DisplayEnvironment display{};
    DrawEnvironment draw{};
    DisplayBufferState* mutate = nullptr;
    void apply_display(const DisplayEnvironment& value) override {
        valid = valid && calls++ == 0;
        display = value;
        if (mutate) mutate->left = 9;
    }
    void apply_draw(const DrawEnvironment& value) override {
        valid = valid && calls++ == 1;
        draw = value;
    }
};

int main() {
    DisplayBufferState state;
    state.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
    state.width = 512;
    state.height = 240;
    state.mode = 3;
    state.right = 512;
    state.bottom = 240;
    Capture first;
    advance_display_buffers(state, first);
    if (!first.valid || first.calls != 2 || state.displaying != 0 || state.drawing != 1 ||
        first.display.y != 0 || first.display.interlaced || !first.display.rgb24 || first.display.width != 512 ||
        first.draw.y != 256 || first.draw.height != 240) return 1;

    state.mode = 2;
    Capture second;
    second.mutate = &state;
    advance_display_buffers(state, second);
    if (!second.valid || state.displaying != 1 || state.drawing != 0 ||
        second.display.y != 256 || second.display.interlaced || second.display.rgb24 || second.draw.x != 9 ||
        second.draw.width != 503) return 2;

    state.buffers[0] = {std::nullopt, 0xffffffffu, 65535};
    state.left = 2;
    state.top = 3;
    state.right = 1;
    state.bottom = 1;
    Capture wrapping;
    advance_display_buffers(state, wrapping);
    if (wrapping.draw.x != 1 || wrapping.draw.y != 2 || wrapping.draw.width != 65535 ||
        wrapping.draw.height != 65534 || !wrapping.valid) return 3;
    const auto fill = drawing_fill_state(state);
    if (fill.origin_x != 65535 || fill.origin_y != 65535 || fill.left != 2) return 4;

    const auto previous_display = state.displaying;
    state.buffers[0].next = 99;
    Capture invalid;
    try {
        advance_display_buffers(state, invalid);
        return 5;
    } catch (const std::out_of_range&) {}
    if (invalid.calls != 0 || state.displaying != previous_display || state.drawing != 0) return 6;
    return 0;
}
