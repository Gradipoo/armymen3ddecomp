// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_80063b34.hpp"

#include <cstdint>

namespace am3d::exe {

// Cites mission path pointer returned by call_80063b34 (mission.ini loop).
// Does not load ALP1 files. See docs/research/re/mission-ini-loop.md.
struct MissionLoadIntent {
    std::uint32_t mission_path_gpr = 0u;
};

inline MissionLoadIntent record_mission_load_intent() {
    MissionLoadIntent intent{};
    intent.mission_path_gpr = call_80063b34();
    return intent;
}

}  // namespace am3d::exe