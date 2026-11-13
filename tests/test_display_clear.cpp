// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_clear.hpp"
#include <string>
#include <vector>

using namespace am3d::exe;

class Capture final : public DisplayEnvironmentGpu, public DisplayFillGpu {
public:
    explicit Capture(DisplayBufferState& value) : state(value) {}
    DisplayBufferState& state;
    std::string calls;
    std::vector<FillPacket> packets;
    int mutate = 0;
    void apply_display(const DisplayEnvironment&) override { calls += 'D'; }
    void apply_draw(const DrawEnvironment&) override { calls += 'E'; }
    void draw_sync(int mode) override {
        calls += mode == 0 ? 'S' : '!';
        if (mutate == 1) {
            state.buffer_count = 1;
            state.left = 9;
            state.buffers[state.drawing].y = 300;
        }
    }
    void draw_prim(const FillPacket& packet) override {
        calls += 'P';
        packets.push_back(packet);
        if (mutate == 2) state.buffer_count = packets.size() == 1 ? 0x80000000u : 0;
    }
};

DisplayBufferState make_state() {
    DisplayBufferState state;
    state.buffer_count = 2;
    state.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
    state.width = state.right = 512;
    state.height = state.bottom = 240;
    state.mode = 2;
    return state;
}

int main() {
    auto state = make_state();
    Capture two(state);
    clear_display_buffers(0xfe123456u, state, two, two);
    if (two.calls != "DESPDESP" || two.packets.size() != 2 || state.drawing != 0 ||
        state.displaying != 1 || two.packets[0][1] != 0x02123456u ||
        two.packets[0][2] != 0x01000000u || two.packets[1][2] != 0 ||
        two.packets[1][3] != 0x00f00200u) return 1;

    state = DisplayBufferState{};
    Capture empty(state);
    clear_display_buffers(0, state, empty, empty);
    if (!empty.calls.empty() || state.displaying) return 2;

    state = make_state();
    Capture shrinking(state);
    shrinking.mutate = 1;
    clear_display_buffers(0, state, shrinking, shrinking);
    if (shrinking.calls != "DESP" || shrinking.packets.size() != 1 ||
        shrinking.packets[0][2] != 0x012c0009u ||
        shrinking.packets[0][3] != 0x00f001f7u) return 3;

    state = make_state();
    state.buffer_count = 1;
    Capture unsigned_count(state);
    unsigned_count.mutate = 2;
    clear_display_buffers(0, state, unsigned_count, unsigned_count);
    if (unsigned_count.calls != "DESPDESP" || unsigned_count.packets.size() != 2) return 4;
    return 0;
}
