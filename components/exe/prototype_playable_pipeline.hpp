// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "mission_movement_slice.hpp"

#include <cstdint>
#include <filesystem>

namespace am3d::exe {

// Frame budgets match prototype_task_7 / prototype_task_8 synthetic defaults.
struct PrototypePlayablePipelineConfig {
    std::uint32_t menu_frame_budget = 4u;
    std::uint32_t down_frame_budget = 1u;
    std::uint32_t mission_frame_budget = 8u;
    // Disc-free default is the ALP1.PAD index 1 fixture (50/1252/50).
    // The mission stage uses run_prototype_task_8_mission_slice(disc_root).
    // An empty disc_root keeps the fixture. A non-empty root loads pad index 1.
    MissionMovementStartState movement_start{};
    std::filesystem::path disc_root{};
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
    bool spawn_from_pad = false;
};

// Composes run_prototype_task_7_menu_transition (4 scan frames, 1 Down frame)
// then run_prototype_task_8_mission_slice (8 movement frames).
// pad_get_state must be non-null. The scan uses prototype_task_7_pad_get_state
// so Down still dispatches when the caller passes idle s2=2.
// See docs/research/re/prototype-task-9.md.
PrototypePlayablePipelineResult run_prototype_playable_pipeline(
    const PrototypePlayablePipelineConfig& config,
    std::uint32_t (*pad_get_state)(std::uint32_t port));

}  // namespace am3d::exe
