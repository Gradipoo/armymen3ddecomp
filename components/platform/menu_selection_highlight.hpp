// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "fill_vram.hpp"

#include <cstdint>

namespace am3d::platform {

// Stand-in bars over the FRONT quad. Not retail GPU text.
// Row 0 sits at quad_y + 80. Row 1 sits at quad_y + 100. Each bar is 120 by 2.
// Index 0 brightens row 0 (NEW GAME). Index 1 brightens row 1 (OPTIONS).
// Any other index draws nothing.
void draw_menu_selection_highlight(FillVram& vram, std::uint16_t origin_x, std::uint16_t origin_y,
                                   unsigned quad_x, unsigned quad_y,
                                   std::uint32_t selection_highlight_index);

}  // namespace am3d::platform
