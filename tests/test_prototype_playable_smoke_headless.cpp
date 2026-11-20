// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_playable_checkpoint.hpp"
#include "prototype_playable_pipeline.hpp"

#include <cstdint>
#include <string>

namespace {

std::uint32_t pad_get_state_idle(std::uint32_t port) {
    (void)port;
    return 2u;
}

}  // namespace

// Disc-free checkpoint line for the playable pipeline (same tokens as --checkpoint).
int main() {
    am3d::exe::PrototypePlayablePipelineConfig config{};
    const am3d::exe::PrototypePlayablePipelineResult result =
        am3d::exe::run_prototype_playable_pipeline(config, pad_get_state_idle);

    const am3d::exe::PrototypePlayableCheckpointLine line =
        am3d::exe::make_prototype_playable_checkpoint_line(result, config.movement_start, false);
    const std::string text = am3d::exe::format_prototype_playable_checkpoint_line(line);

    if (result.menu_s7_after_menu_budget != 8u || result.menu_s7 != 9u) {
        return 1;
    }
    if (result.mission_path_gpr != 0x800bfdbcu) {
        return 2;
    }
    if (result.movement_final_state.z <= config.movement_start.z) {
        return 3;
    }
    if (result.frames.menu != 4u || result.frames.down != 1u || result.frames.mission != 8u) {
        return 4;
    }
    if (line.spawn_from_pad) {
        return 5;
    }
    // Four Cross frames of the default script step z by 16 from fixture z 1252.
    const std::string expected = "8 9 1316 4 1 8 0x800bfdbc 50 1252 50 0\n";
    if (text != expected) {
        return 6;
    }
    return 0;
}
