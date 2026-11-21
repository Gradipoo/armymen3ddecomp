// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_movement_slice.hpp"

namespace am3d::exe {

namespace {

constexpr std::int32_t kCrossForwardStep = 16;

}  // namespace

MissionMovementRunResult run_mission_movement_frames(const MissionPadScript& script,
                                                       MissionMovementStartState start,
                                                       MissionMovementStartState& state) {
    state = start;
    MissionMovementRunResult result{};
  // gap: per-frame camera, collision, and retail physics hooks
    const std::size_t frames =
        script.length > MissionPadScript::kMaxFrames ? MissionPadScript::kMaxFrames : script.length;
    for (std::size_t i = 0u; i < frames; ++i) {
        const std::uint32_t pad_s2 = script.s2[i];
        if (pad_s2 == MissionPadScript::kPadCrossS2) {
            state.z += kCrossForwardStep;
        }
        result.frames_run += 1u;
    }
    result.final_state = state;
    return result;
}

}  // namespace am3d::exe