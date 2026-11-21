// SPDX-License-Identifier: GPL-3.0-or-later
#include "disc_front_tim_load.hpp"
#include "menu_submit_frame.hpp"
#include "menu_task7_checkpoint.hpp"
#include "prototype_task_7_menu.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace {

constexpr int kSkipNoDisc = 77;

std::filesystem::path resolve_disc_root() {
    if (std::filesystem::is_directory("build/disc")) {
        return "build/disc";
    }
    if (std::filesystem::is_directory("disc")) {
        return "disc";
    }
    return {};
}

bool front_stand_in_has_visible_pixel(const am3d::platform::FillVram& vram,
                                      std::uint16_t origin_x, std::uint16_t origin_y) {
    // Stop above the selection bars at quad_y+80 so the stand-in does not count as FRONT.
    const unsigned left = origin_x + 234u;
    const unsigned top = origin_y + 56u;
    for (unsigned y = top; y < top + 64u; ++y) {
        for (unsigned x = left; x < left + 44u; ++x) {
            if (vram.pixel(x, y) != 0u) {
                return true;
            }
        }
    }
    return false;
}

int submit_menu_frame(am3d::platform::FillVram& vram, const std::vector<std::uint8_t>& front_bytes,
                      std::uint32_t marker_x, std::uint32_t highlight_index,
                      std::uint32_t phase_code) {
    am3d::platform::MenuSubmitFrameRequest request{};
    request.origin_x = 0u;
    request.origin_y = 0u;
    request.marker_x = marker_x;
    request.marker_y = 112u;
    request.marker_color = 0x00ff00u;
    request.selection_highlight_index = highlight_index;
    if (!front_bytes.empty()) {
        request.front_bytes = front_bytes.data();
        request.front_size = front_bytes.size();
    }
    const auto trace = am3d::platform::menu_submit_frame(request, vram);
    if (trace.submit_return != 1u) {
        return phase_code + 0;
    }
    if ((vram.argb(marker_x, 112u) & 0xffffffu) != 0x00ff00u) {
        return phase_code + 1;
    }
    if (!front_stand_in_has_visible_pixel(vram, request.origin_x, request.origin_y)) {
        return phase_code + 2;
    }
    const unsigned row0 = request.origin_y + request.quad_y + 80u;
    const unsigned row1 = request.origin_y + request.quad_y + 100u;
    const unsigned bar_x = request.origin_x + request.quad_x;
    // fill_display stores 5-bit channels. 0x404040 comes back as 0x424242.
    const std::uint32_t bright = 0xffffffu;
    const std::uint32_t dim = 0x424242u;
    const std::uint32_t row0_color = highlight_index == 0u ? bright : dim;
    const std::uint32_t row1_color = highlight_index == 0u ? dim : bright;
    if ((vram.argb(bar_x, row0) & 0xffffffu) != row0_color) {
        return phase_code + 3;
    }
    if ((vram.argb(bar_x, row1) & 0xffffffu) != row1_color) {
        return phase_code + 4;
    }
    return 0;
}

}  // namespace

// PROTOTYPE.md row 7 disc-backed acceptance when build/disc/DATA/FRONT.TIM exists.
int main() {
    const std::vector<std::uint8_t> front_bytes =
        am3d::platform::load_front_tim_disc_bytes(resolve_disc_root());
    if (front_bytes.empty()) {
        return kSkipNoDisc;
    }

    const am3d::exe::PrototypeTask7MenuResult menu = am3d::exe::run_prototype_task_7_menu_transition(
        am3d::exe::prototype_task_7_pad_get_state, front_bytes.data(), front_bytes.size());
    if (menu.frames_run != 4u || !menu.phase_a_tail_ran) {
        return 1;
    }
    if (menu.s7_after_a != 8u) {
        return 2;
    }
    if (menu.tail_0b != 0u || menu.tail_87 != 0x80u) {
        return 3;
    }
    if (menu.selection_index_after_a != 0u) {
        return 4;
    }

    am3d::platform::FillVram vram_a;
    const int submit_a = submit_menu_frame(vram_a, front_bytes, menu.marker_x_a, 0u, 20);
    if (submit_a != 0) {
        return submit_a;
    }

    if (menu.frames_run_b != 1u) {
        return 30;
    }
    if (!menu.destination_stated || menu.destination != 0x80064f14u ||
        menu.word_address != 0x800c3ea4u) {
        return 31;
    }
    if (!menu.phase_b_tail_ran) {
        return 32;
    }
    if (menu.s7_after_b != 9u) {
        return 33;
    }
    if (menu.selection_index_after_b != 1u || !menu.has_front) {
        return 34;
    }

    am3d::platform::FillVram vram_b;
    const int submit_b = submit_menu_frame(vram_b, front_bytes, menu.marker_x_b, 1u, 40);
    if (submit_b != 0) {
        return submit_b;
    }

    const std::string line = am3d::exe::format_menu_task7_checkpoint(menu);
    if (line != "8 9 0 128 296 308 1 1\n") {
        return 50;
    }
    return 0;
}
