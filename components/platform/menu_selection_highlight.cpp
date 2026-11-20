// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_selection_highlight.hpp"

#include "display_fill.hpp"

namespace am3d::platform {
namespace {

constexpr unsigned kBarWidth = 120u;
constexpr unsigned kBarHeight = 2u;
constexpr unsigned kRow0Dy = 80u;
constexpr unsigned kRow1Dy = 100u;
constexpr std::uint32_t kBright = 0xffffffu;
constexpr std::uint32_t kDim = 0x404040u;

void draw_bar(FillVram& vram, std::uint16_t origin_x, std::uint16_t origin_y, unsigned x,
              unsigned y, std::uint32_t color) {
    const exe::DisplayFillState state{
        origin_x,
        origin_y,
        static_cast<std::uint16_t>(x),
        static_cast<std::uint16_t>(y),
        static_cast<std::uint16_t>(x + kBarWidth),
        static_cast<std::uint16_t>(y + kBarHeight),
    };
    exe::fill_display(color, state, vram);
}

}  // namespace

void draw_menu_selection_highlight(FillVram& vram, std::uint16_t origin_x, std::uint16_t origin_y,
                                   unsigned quad_x, unsigned quad_y,
                                   std::uint32_t selection_highlight_index) {
    if (selection_highlight_index > 1u) {
        return;
    }
    const unsigned x = quad_x;
    const unsigned y0 = quad_y + kRow0Dy;
    const unsigned y1 = quad_y + kRow1Dy;
    const bool first = selection_highlight_index == 0u;
    draw_bar(vram, origin_x, origin_y, x, y0, first ? kBright : kDim);
    draw_bar(vram, origin_x, origin_y, x, y1, first ? kDim : kBright);
}

}  // namespace am3d::platform
