// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_task8_checkpoint.hpp"
#include "prototype_task_8_mission.hpp"

#include <filesystem>
#include <string>

namespace {

constexpr int kSkipNoDisc = 77;

std::filesystem::path resolve_disc_root() {
    if (std::filesystem::is_directory("build/disc") &&
        std::filesystem::is_regular_file("build/disc/DATA/ALP1.TXT") &&
        std::filesystem::is_regular_file("build/disc/DATA/ALP1.PAD")) {
        return "build/disc";
    }
    if (std::filesystem::is_directory("disc") &&
        std::filesystem::is_regular_file("disc/DATA/ALP1.TXT") &&
        std::filesystem::is_regular_file("disc/DATA/ALP1.PAD")) {
        return "disc";
    }
    return {};
}

}  // namespace

// Same slice as the disc-free checkpoint, with owner ALP1.TXT and ALP1.PAD.
int main() {
    const std::filesystem::path disc_root = resolve_disc_root();
    if (disc_root.empty()) {
        return kSkipNoDisc;
    }
    const am3d::exe::PrototypeTask8MissionResult mission =
        am3d::exe::run_prototype_task_8_mission_slice(disc_root);
    if (!mission.spawn_from_pad || mission.frames_run != 8u) {
        return 1;
    }
    if (mission.spawn_x != 50 || mission.spawn_z != 1252 || mission.spawn_heading != 50) {
        return 2;
    }
    if (mission.final_state.z != 1316 || mission.mission_path_gpr != 0x800bfdbcu) {
        return 3;
    }
    const std::string line = am3d::exe::format_mission_task8_checkpoint(mission);
    if (line != "Alp1 50 1252 50 50 1316 50 8 1 0x800bfdbc\n") {
        return 4;
    }
    return 0;
}
