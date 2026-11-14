// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "fill_vram.hpp"
#include <cstddef>
#include <cstdint>

namespace am3d::platform {

// One 4-bit picture with a color table. The field order is the measured
// layout of DATA/FRONT.TIM. See docs/research/re/front-tim.md.
struct FrontTim {
    unsigned width = 0;
    unsigned height = 0;
};

// Returns false when the bytes are not that layout. A color-table entry of
// zero is left unpainted. Other entries are written as 15-bit colors.
bool paint_front_tim(const std::uint8_t* bytes, std::size_t size,
    unsigned origin_x, unsigned origin_y, FillVram& vram, FrontTim* out);

}
