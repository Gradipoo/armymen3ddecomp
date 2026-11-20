// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_task8_checkpoint.hpp"

#include <iomanip>
#include <sstream>

namespace am3d::exe {

std::string format_mission_task8_checkpoint(const PrototypeTask8MissionResult& result) {
    std::ostringstream out;
    out << MissionSliceDeclaration::kMissionId << ' ' << result.spawn_x << ' ' << result.spawn_z
        << ' ' << result.spawn_heading << ' ' << result.final_state.x << ' '
        << result.final_state.z << ' ' << result.final_state.heading << ' ' << result.frames_run
        << ' ' << (result.spawn_from_pad ? 1 : 0) << ' ' << std::hex << std::showbase
        << result.mission_path_gpr << '\n';
    return out.str();
}

}  // namespace am3d::exe
