// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <array>
#include <cstdint>
#include <functional>

namespace am3d::exe {

struct DisplayFillState {
    std::uint16_t origin_x;
    std::uint16_t origin_y;
    std::uint16_t left;
    std::uint16_t top;
    std::uint16_t right;
    std::uint16_t bottom;
};

using FillPacket = std::array<std::uint32_t, 4>;

class DisplayFillGpu {
public:
    virtual ~DisplayFillGpu() = default;
    virtual void draw_sync(int mode) = 0;
    virtual void draw_prim(const FillPacket& packet) = 0;
};

// The caller supplies the current state rather than a host pointer to PS1 RAM.
void fill_display(std::uint32_t color, const DisplayFillState& state, DisplayFillGpu& gpu);
// Read live drawing state after DrawSync, including any callback effects.
void fill_display(std::uint32_t color, const std::function<DisplayFillState()>& read_state,
                  DisplayFillGpu& gpu);

}
