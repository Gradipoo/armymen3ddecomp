// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "display_buffers.hpp"

namespace am3d::exe {

void clear_display_buffers(std::uint32_t color, DisplayBufferState& state,
                           DisplayEnvironmentGpu& environments, DisplayFillGpu& primitives);

}
