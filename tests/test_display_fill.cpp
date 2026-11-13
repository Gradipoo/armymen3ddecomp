// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_fill.hpp"

using namespace am3d::exe;

class Capture final : public DisplayFillGpu {
public:
    int calls = 0;
    bool valid = true;
    FillPacket received{};
    DisplayFillState* update = nullptr;

    void draw_sync(int mode) override {
        valid = valid && calls == 0 && mode == 0;
        ++calls;
        if (update) {
            update->left = 9;
        }
    }

    void draw_prim(const FillPacket& packet) override {
        valid = valid && calls == 1;
        ++calls;
        received = packet;
    }
};

int main() {
    DisplayFillState state{100, 200, 3, 7, 515, 247};
    Capture first;
    fill_display(0xfe123456u, state, first);
    if (!first.valid || first.calls != 2 ||
        first.received != FillPacket{0x03000000u, 0x02123456u, 0x00cf0067u, 0x00f00200u}) {
        return 1;
    }

    // Coordinates and dimensions retain the low 16 bits, including underflow.
    state = {65535, 65534, 2, 3, 1, 1};
    Capture wrapping;
    fill_display(0, state, wrapping);
    if (!wrapping.valid || wrapping.received !=
        FillPacket{0x03000000u, 0x02000000u, 0x00010001u, 0xfffeffffu}) {
        return 2;
    }

    // State is read after DrawSync, matching the retail call order.
    state = {0, 0, 0, 0, 16, 16};
    Capture updating;
    updating.update = &state;
    fill_display(0, state, updating);
    if (!updating.valid || updating.received[2] != 9 || updating.received[3] != 0x00100007u) {
        return 3;
    }
    return 0;
}
