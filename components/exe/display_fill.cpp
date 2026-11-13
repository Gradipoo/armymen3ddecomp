// SPDX-License-Identifier: GPL-3.0-or-later
#include "display_fill.hpp"

namespace am3d::exe {
namespace {

std::uint32_t pair(std::uint16_t low, std::uint16_t high) {
    return std::uint32_t{low} | (std::uint32_t{high} << 16);
}

}

// Behavior reference: docs/research/re/call-80076274.md.
void fill_display(std::uint32_t color, const DisplayFillState& state, DisplayFillGpu& gpu) {
    fill_display(color, [&state] { return state; }, gpu);
}

void fill_display(std::uint32_t color, const std::function<DisplayFillState()>& read_state,
                  DisplayFillGpu& gpu) {
    gpu.draw_sync(0);
    const auto state = read_state();
    const auto x = static_cast<std::uint16_t>(state.origin_x + state.left);
    const auto y = static_cast<std::uint16_t>(state.origin_y + state.top);
    const auto width = static_cast<std::uint16_t>(state.right - state.left);
    const auto height = static_cast<std::uint16_t>(state.bottom - state.top);
    const FillPacket packet{
        3u << 24,
        (2u << 24) | (color & 0x00ffffffu),
        pair(x, y),
        pair(width, height),
    };
    gpu.draw_prim(packet);
}

}
