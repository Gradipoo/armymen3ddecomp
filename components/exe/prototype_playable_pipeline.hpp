// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "mission_movement_slice.hpp"

#include <cstdint>

namespace am3d::exe {

// Frame budgets match prototype_task_7 / prototype_task_8 synthetic defaults.
struct PrototypePlayablePipelineConfig {
    std::uint32_t menu_frame_budget = 4u;
    std::uint32_t down_frame_budget = 1u;
    std::uint32_t mission_frame_budget = 8u;
    // Disc-free default is the ALP1.PAD index 1 fixture (50/1252/50).
    MissionMovementStartState movement_start{};
    PrototypePlayablePipelineConfig();
};

struct PrototypePlayablePipelineStageFrames {
    std::uint32_t menu = 0u;
    std::uint32_t down = 0u;
    std::uint32_t mission = 0u;
};

struct PrototypePlayablePipelineResult {
    std::uint32_t menu_s7 = 0u;
    std::uint32_t menu_s7_after_menu_budget = 0u;
    bool dispatch_destination_stated = false;
    bool dispatch_tail_ran = false;
    std::uint32_t dispatch_destination = 0u;
    std::uint32_t dispatch_word_address = 0u;
    std::uint32_t mission_path_gpr = 0u;
    MissionMovementStartState movement_final_state{};
    PrototypePlayablePipelineStageFrames frames{};
};

// Menu and Down stages call pad_get_state (Idle s2=2 in synthetic tests).
// Mission frames use the fixed MissionPadScript from task 8, not pad_get_state.
// See docs/research/re/prototype-task-9.md.
PrototypePlayablePipelineResult run_prototype_playable_pipeline(
    const PrototypePlayablePipelineConfig& config,
    std::uint32_t (*pad_get_state)(std::uint32_t port));

MissionPadScript prototype_playable_default_mission_script(std::uint32_t frame_budget);

}  // namespace am3d::exe