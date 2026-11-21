// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_submit_frame.hpp"

int main() {
    am3d::platform::FillVram vram;
    am3d::platform::MenuSubmitFrameRequest request{};
    request.marker_x = 200u;
    request.marker_y = 112u;
    request.marker_color = 0x00ff00u;
    const auto trace = am3d::platform::menu_submit_frame(request, vram);
    if (trace.draw_sync_calls != 1u) {
        return 1;
    }
    if (trace.draw_otag_address != 0x800ca914u) {
        return 2;
    }
    if (!trace.list_accepted) {
        return 3;
    }
    if (trace.submit_return != 1u) {
        return 4;
    }
    if ((vram.argb(200u, 112u) & 0xffffffu) != 0x00ff00u) {
        return 5;
    }
    return 0;
}