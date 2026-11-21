// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_task8_checkpoint.hpp"
#include "prototype_task_8_mission.hpp"

#include <string>

// Disc-free row 8 checkpoint. No ALP1 file and no SDL.
int main() {
    const am3d::exe::PrototypeTask8MissionResult mission =
        am3d::exe::run_prototype_task_8_mission_slice();
    if (mission.spawn_x != 50 || mission.spawn_z != 1252 || mission.spawn_heading != 50) {
        return 1;
    }
    if (mission.spawn_from_pad || mission.frames_run != 8u) {
        return 2;
    }
    if (mission.final_state.x != 50 || mission.final_state.z != 1316 ||
        mission.final_state.heading != 50) {
        return 3;
    }
    if (mission.mission_path_gpr != 0x800bfdbcu) {
        return 4;
    }
    const std::string line = am3d::exe::format_mission_task8_checkpoint(mission);
    if (line != "Alp1 50 1252 50 50 1316 50 8 0 0x800bfdbc\n") {
        return 5;
    }
    return 0;
}
