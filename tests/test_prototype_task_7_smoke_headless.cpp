// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_scan_pad_dispatch_inject.hpp"
#include "menu_task7_checkpoint.hpp"
#include "prototype_task_7_menu.hpp"

#include <string>

// Disc-free row 7 checkpoint. No FRONT file and no SDL.
int main() {
    const am3d::exe::PrototypeTask7MenuResult menu = am3d::exe::run_prototype_task_7_menu_transition(
        am3d::exe::prototype_task_7_pad_get_state, nullptr, 0u);
    if (menu.frames_run != 4u || menu.s7_after_a != 8u || !menu.phase_a_tail_ran) {
        return 1;
    }
    if (menu.tail_0b != 0u || menu.tail_87 != 0x80u) {
        return 2;
    }
    if (menu.frames_run_b != 1u || menu.s7_after_b != 9u || !menu.phase_b_tail_ran) {
        return 3;
    }
    if (!menu.destination_stated ||
        menu.destination != am3d::exe::kMenuScanProvisionalDownDispatchDest ||
        menu.word_address != 0x800c3ea4u) {
        return 4;
    }
    if (menu.selection_index_after_a != 0u || menu.selection_index_after_b != 1u ||
        menu.has_front) {
        return 5;
    }
    if (menu.marker_x_a != 296u || menu.marker_x_b != 308u) {
        return 6;
    }
    const std::string line = am3d::exe::format_menu_task7_checkpoint(menu);
    if (line != "8 9 0 128 296 308 1 0\n") {
        return 7;
    }
    return 0;
}
