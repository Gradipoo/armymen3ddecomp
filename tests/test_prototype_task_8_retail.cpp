// SPDX-License-Identifier: GPL-3.0-or-later
#include "mission_movement_slice.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

constexpr int kSkipNoDisc = 77;

std::filesystem::path resolve_alp1_txt() {
    const std::filesystem::path from_build = "disc/DATA/ALP1.TXT";
    if (std::filesystem::is_regular_file(from_build)) {
        return from_build;
    }
    const std::filesystem::path from_root = "build/disc/DATA/ALP1.TXT";
    if (std::filesystem::is_regular_file(from_root)) {
        return from_root;
    }
    return {};
}

bool first_line_contains_alpine1(const std::filesystem::path& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    std::string line;
    if (!std::getline(in, line)) {
        return false;
    }
    return line.find("Alpine1") != std::string::npos;
}

int run_movement_slice() {
    am3d::exe::MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadCrossS2;
    }

    am3d::exe::MissionMovementStartState start{};
    start.x = 100;
    start.z = 200;
    start.heading = 0;
    am3d::exe::MissionMovementStartState state{};

    const am3d::exe::MissionMovementRunResult result =
        am3d::exe::run_mission_movement_frames(script, start, state);
    if (result.frames_run != 8u) {
        return 1;
    }
    if (state.x != start.x || state.heading != start.heading) {
        return 2;
    }
    if (state.z <= start.z) {
        return 3;
    }
    if (result.final_state.z != state.z) {
        return 4;
    }
    return 0;
}

}  // namespace

// PROTOTYPE.md row 8 disc-backed check when build/disc/DATA/ALP1.TXT exists.
int main() {
    const std::filesystem::path txt_path = resolve_alp1_txt();
    if (txt_path.empty()) {
        return kSkipNoDisc;
    }
    if (!first_line_contains_alpine1(txt_path)) {
        return 5;
    }
    return run_movement_slice();
}