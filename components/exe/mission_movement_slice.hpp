// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <array>
#include <cstdint>
#include <cstddef>

namespace am3d::exe {

// Disc-relative paths for owner ALP1 assets under build/disc/. Not read here.
struct MissionSliceDeclaration {
    static constexpr const char kMissionId[] = "Alp1";
    static constexpr const char kTxtPath[] = "DATA/ALP1.TXT";
    static constexpr const char kMapPath[] = "DATA/ALP1.MAP";
    static constexpr const char kPadPath[] = "DATA/ALP1.PAD";
    static constexpr const char kMdlPath[] = "DATA/ALP1.MDL";
};

// Host movement start. Retail spawn may be filled from alp1_pad_spawn (pad index 1).
struct MissionMovementStartState {
    std::int32_t x = 0;
    std::int32_t z = 0;
    std::int32_t heading = 0;
};

// Synthetic PadGetState return values per menu-scan-pad-sdl.md (s2 below seven).
struct MissionPadScript {
    static constexpr std::size_t kMaxFrames = 64u;
    static constexpr std::uint32_t kPadIdleS2 = 2u;
    static constexpr std::uint32_t kPadCrossS2 = 6u;
    std::array<std::uint32_t, kMaxFrames> s2{};
    std::size_t length = 0u;
};

struct MissionMovementRunResult {
    std::uint32_t frames_run = 0u;
    MissionMovementStartState final_state{};
};

// Applies each script frame. Cross (s2=6) advances the forward (z) axis.
// // gap: collision, camera, GTE, and ALP1 geometry are not modeled.
MissionMovementRunResult run_mission_movement_frames(const MissionPadScript& script,
                                                       MissionMovementStartState start,
                                                       MissionMovementStartState& state);

}  // namespace am3d::exe