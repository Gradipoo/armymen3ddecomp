// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_playable_pipeline.hpp"

#include <cstdint>

namespace {

std::uint32_t pad_get_state_idle(std::uint32_t port) {
    (void)port;
    return 2u;
}

}  // namespace

// Post–task-8 integration: menu multi-frame scan, optional Down, ALP1 movement.
int main() {
    am3d::exe::PrototypePlayablePipelineConfig config{};
    const am3d::exe::PrototypePlayablePipelineResult result =
        am3d::exe::run_prototype_playable_pipeline(config, pad_get_state_idle);

    if (result.frames.menu != 4u || result.frames.down != 1u || result.frames.mission != 8u) {
        return 1;
    }
  // s7==8 after four menu frames; Down dispatch then bumps s7 before mission handoff.
    if (result.menu_s7_after_menu_budget != 8u) {
        return 2;
    }
    if (result.menu_s7 != 9u) {
        return 3;
    }
    if (!result.dispatch_destination_stated || !result.dispatch_tail_ran ||
        result.dispatch_destination != 0x80064f14u || result.dispatch_word_address != 0x800c3ea4u) {
        return 4;
    }
    if (result.mission_path_gpr != 0x800bfdbcu) {
        return 5;
    }
    if (result.movement_final_state.x != config.movement_start.x ||
        result.movement_final_state.heading != config.movement_start.heading) {
        return 6;
    }
    if (result.movement_final_state.z <= config.movement_start.z) {
        return 7;
    }
    return 0;
}