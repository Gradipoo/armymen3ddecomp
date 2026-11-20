// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "prototype_task_8_mission.hpp"

#include <string>

namespace am3d::exe {

// One line, space-separated, trailing newline:
// Alp1 x z h x2 z2 h2 frames spawn_from_pad mission_path_gpr
// x z h are the spawn. x2 z2 h2 are final_state. frames is frames_run.
// spawn_from_pad is 0 or 1. mission_path_gpr is hexadecimal with a 0x prefix.
std::string format_mission_task8_checkpoint(const PrototypeTask8MissionResult& result);

}  // namespace am3d::exe
