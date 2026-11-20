// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_menu_handoff.hpp"
#include "mission_movement_slice.hpp"

#include <cstdint>

namespace {

int run_movement_slice() {
    am3d::exe::MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadCrossS2;
    }

    am3d::exe::MissionMovementStartState start{};
    start.x = 100;
    start.z = 200;
    start.heading = 0;
    am3d::exe::MissionMovementStartState state{};

    const am3d::exe::MissionMovementRunResult result =
        am3d::exe::run_mission_movement_frames(script, start, state);
    if (result.frames_run != 8u) {
        return 1;
    }
    if (state.x != start.x || state.heading != start.heading) {
        return 2;
    }
    if (state.z <= start.z) {
        return 3;
    }
    if (result.final_state.z != state.z) {
        return 4;
    }
    return 0;
}

}  // namespace

// PROTOTYPE.md row 8 synthetic acceptance (disc-free ALP1 movement slice).
int main() {
    const am3d::exe::MissionLoadIntent intent = am3d::exe::record_mission_load_intent();
    if (intent.mission_path_gpr != 0x800bfdbcu) {
        return 10;
    }
    return run_movement_slice();
}