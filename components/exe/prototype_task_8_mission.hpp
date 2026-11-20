// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "mission_movement_slice.hpp"

#include <cstdint>
#include <filesystem>

namespace am3d::exe {

// Shared ALP1 movement slice for PROTOTYPE row 8.
// Disc-free start is mission_movement_start_disc_free (pad index 1 fixture).
// A non-empty disc_root loads pad index 1 from DATA/ALP1.PAD when that parse
// succeeds. spawn_from_pad is true only for that owner file path.
struct PrototypeTask8MissionResult {
    std::int32_t spawn_x = 0;
    std::int32_t spawn_z = 0;
    std::int32_t spawn_heading = 0;
    bool spawn_from_pad = false;
    std::uint32_t frames_run = 0u;
    MissionMovementStartState final_state{};
    std::uint32_t mission_path_gpr = 0u;
};

// Disc-free start decoded from the ALP1.PAD fixture bytes.
MissionMovementStartState mission_movement_start_disc_free();

// Eight frames: idle s2=2 for four frames, then Cross s2=6 for four frames.
MissionPadScript prototype_task_8_default_pad_script();

// Records the mission.ini path GPR, resolves start, and runs the default script.
PrototypeTask8MissionResult run_prototype_task_8_mission_slice(
    const std::filesystem::path& disc_root = {});

}  // namespace am3d::exe
