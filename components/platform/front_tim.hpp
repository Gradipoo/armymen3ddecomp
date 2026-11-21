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

// Rectangle fields are VRAM coordinates, word width, and row height. See
// docs/research/re/front-tim.md, offsets 12 and 56.
struct FrontTimUploadRect {
    unsigned x;
    unsigned y;
    unsigned width;
    unsigned height;
};

// Words are valid only during the call. The sink may copy or submit them.
using FrontTimUploadSink = void (*)(void* context, const FrontTimUploadRect& rect,
    const std::uint16_t* words, std::size_t word_count);

// Validates both blocks before calling the sink, then sends the color table
// and packed pixel words in that order. Rectangles that wrap VRAM are rejected.
// Sink exceptions propagate and can leave the first upload already submitted.
bool upload_front_tim(const std::uint8_t* bytes, std::size_t size,
    FrontTimUploadSink sink, void* context);

// Returns false when the bytes are not that layout. A color-table entry of
// zero is left unpainted. Other entries are written as 15-bit colors.
bool paint_front_tim(const std::uint8_t* bytes, std::size_t size,
    unsigned origin_x, unsigned origin_y, FillVram& vram, FrontTim* out);

}
