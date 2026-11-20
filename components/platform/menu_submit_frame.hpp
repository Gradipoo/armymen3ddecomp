// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "fill_vram.hpp"
#include <cstddef>
#include <cstdint>

namespace am3d::platform {

struct MenuSubmitFrameRequest {
    std::uint16_t origin_x = 0;
    std::uint16_t origin_y = 0;
    unsigned quad_x = 234;
    unsigned quad_y = 56;
    std::uint32_t marker_x = 0;
    std::uint32_t marker_y = 0;
    std::uint32_t marker_color = 0;
    const std::uint8_t* front_bytes = nullptr;
    std::size_t front_size = 0;
    // 0 brightens the first stand-in row. 1 brightens the second. Other values skip it.
    std::uint32_t selection_highlight_index = 0;
};

struct MenuSubmitFrameTrace {
    std::uint32_t draw_otag_address = 0;
    std::uint32_t submit_return = 0;
    bool list_accepted = false;
    std::uint32_t draw_sync_calls = 0;
};

// Submits one presentation slice through call_8007c11c with observed table
// arguments. See docs/research/re/menu-scan-submission.md.
MenuSubmitFrameTrace menu_submit_frame(const MenuSubmitFrameRequest& request, FillVram& vram);

}