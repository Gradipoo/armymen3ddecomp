// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "prototype_playable_pipeline.hpp"

#include <filesystem>
#include <string>

namespace am3d::exe {

// Default smoke path. One space-separated line, trailing newline.
// Columns:
//   menu_s7_after_menu_budget
//   menu_s7
//   mission_z
//   frames.menu frames.down frames.mission
//   mission_path_gpr (0x + lowercase hex)
//   movement_start.x movement_start.z movement_start.heading
//   spawn_from_pad (1 when ALP1.PAD pad index 1 filled the start, else 0)
inline constexpr const char kPrototypePlayableCheckpointPath[] =
    "build/platform/task9-checkpoint.txt";

struct PrototypePlayableCheckpointLine {
    std::uint32_t menu_s7_after_menu_budget = 0u;
    std::uint32_t menu_s7 = 0u;
    std::int32_t mission_z = 0;
    PrototypePlayablePipelineStageFrames frames{};
    std::uint32_t mission_path_gpr = 0u;
    MissionMovementStartState movement_start{};
    bool spawn_from_pad = false;
};

PrototypePlayableCheckpointLine make_prototype_playable_checkpoint_line(
    const PrototypePlayablePipelineResult& result,
    const MissionMovementStartState& movement_start, bool spawn_from_pad);

std::string format_prototype_playable_checkpoint_line(
    const PrototypePlayableCheckpointLine& line);

void write_prototype_playable_checkpoint_file(const std::filesystem::path& path,
                                              const PrototypePlayableCheckpointLine& line);

}  // namespace am3d::exe
