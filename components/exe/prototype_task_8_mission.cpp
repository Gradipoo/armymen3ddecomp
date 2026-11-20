// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_task_8_mission.hpp"

#include "alp1_pad_spawn.hpp"
#include "alp1_pad_spawn_fixture.hpp"
#include "mission_menu_handoff.hpp"

namespace am3d::exe {

MissionMovementStartState mission_movement_start_disc_free() {
    return mission_start_from_alp1_pad_fixture();
}

MissionPadScript prototype_task_8_default_pad_script() {
    MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = MissionPadScript::kPadCrossS2;
    }
    return script;
}

PrototypeTask8MissionResult run_prototype_task_8_mission_slice(
    const std::filesystem::path& disc_root) {
    PrototypeTask8MissionResult result{};
    const MissionLoadIntent intent = record_mission_load_intent();
    result.mission_path_gpr = intent.mission_path_gpr;

    MissionMovementStartState start = mission_movement_start_disc_free();
    if (!disc_root.empty()) {
        const Alp1PadSpawnParseResult spawn = load_alp1_pad_spawn_from_disc_root(disc_root, 1u);
        if (spawn.ok) {
            start.x = spawn.x;
            start.z = spawn.z;
            start.heading = spawn.heading;
            result.spawn_from_pad = true;
        }
    }

    result.spawn_x = start.x;
    result.spawn_z = start.z;
    result.spawn_heading = start.heading;

    MissionMovementStartState state{};
    const MissionMovementRunResult run =
        run_mission_movement_frames(prototype_task_8_default_pad_script(), start, state);
    result.frames_run = run.frames_run;
    result.final_state = run.final_state;
    return result;
}

}  // namespace am3d::exe
