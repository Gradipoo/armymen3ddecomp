// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "display_fill.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace am3d::exe {

struct DisplayBuffer {
    std::optional<std::size_t> next;
    std::uint32_t x;
    std::uint32_t y;
};

struct DisplayBufferState {
    std::uint32_t buffer_count = 0;
    std::vector<DisplayBuffer> buffers;
    std::size_t first = 0;
    std::size_t drawing = 0;
    std::optional<std::size_t> displaying;
    std::uint32_t width = 0;
    std::uint32_t height = 0;
    std::uint32_t mode = 0;
    std::uint32_t left = 0;
    std::uint32_t right = 0;
    std::uint32_t top = 0;
    std::uint32_t bottom = 0;
};

struct DisplayEnvironment {
    std::uint16_t x, y, width, height;
    bool interlaced;
    bool rgb24;
};

struct DrawEnvironment {
    std::uint16_t x, y, width, height;
};

class DisplayEnvironmentGpu {
public:
    virtual ~DisplayEnvironmentGpu() = default;
    // Apply SDK default environments with these core fields.
    virtual void apply_display(const DisplayEnvironment& environment) = 0;
    virtual void apply_draw(const DrawEnvironment& environment) = 0;
};

void advance_display_buffers(DisplayBufferState& state, DisplayEnvironmentGpu& gpu);
DisplayFillState drawing_fill_state(const DisplayBufferState& state);

}
