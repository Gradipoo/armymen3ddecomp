// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn_fixture.hpp"
#include "prototype_task_8_mission.hpp"

#include <cstdint>

// PROTOTYPE.md row 8 synthetic acceptance (disc-free ALP1 movement slice).
int main() {
    const am3d::exe::PrototypeTask8MissionResult result =
        am3d::exe::run_prototype_task_8_mission_slice();
    if (result.mission_path_gpr != 0x800bfdbcu) {
        return 10;
    }
    if (result.spawn_from_pad) {
        return 6;
    }
    if (result.spawn_x != am3d::exe::kAlp1PadSpawnDiscFreeGoldenX ||
        result.spawn_z != am3d::exe::kAlp1PadSpawnDiscFreeGoldenZ ||
        result.spawn_heading != am3d::exe::kAlp1PadSpawnDiscFreeGoldenHeading) {
        return 5;
    }
    if (result.frames_run != 8u) {
        return 1;
    }
    if (result.final_state.x != result.spawn_x ||
        result.final_state.heading != result.spawn_heading) {
        return 2;
    }
    // Four Cross frames step z by 16.
    if (result.final_state.z != result.spawn_z + 64) {
        return 3;
    }
    return 0;
}
