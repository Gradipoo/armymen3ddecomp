// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"
#include "alp1_pad_spawn_fixture.hpp"
#include "mission_movement_slice.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

constexpr int kSkipNoDisc = 77;

std::filesystem::path resolve_disc_data(const char* name) {
    const std::filesystem::path from_build = std::filesystem::path("disc/DATA") / name;
    if (std::filesystem::is_regular_file(from_build)) {
        return from_build;
    }
    const std::filesystem::path from_root = std::filesystem::path("build/disc/DATA") / name;
    if (std::filesystem::is_regular_file(from_root)) {
        return from_root;
    }
    return {};
}

bool regular_file_nonzero(const std::filesystem::path& path) {
    if (path.empty()) {
        return false;
    }
    std::error_code ec;
    const auto size = std::filesystem::file_size(path, ec);
    return !ec && size > 0u;
}

std::filesystem::path resolve_disc_root() {
    if (std::filesystem::is_directory("build/disc")) {
        return "build/disc";
    }
    if (std::filesystem::is_directory("disc")) {
        return "disc";
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

int run_movement_slice(const am3d::exe::MissionMovementStartState& start) {
    am3d::exe::MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadCrossS2;
    }

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
    const std::filesystem::path txt_path = resolve_disc_data("ALP1.TXT");
    if (txt_path.empty()) {
        return kSkipNoDisc;
    }
    if (!first_line_contains_alpine1(txt_path)) {
        return 5;
    }
    if (!regular_file_nonzero(resolve_disc_data("ALP1.MAP"))) {
        return 6;
    }
    if (!regular_file_nonzero(resolve_disc_data("ALP1.PAD"))) {
        return 7;
    }
    if (!regular_file_nonzero(resolve_disc_data("ALP1.MDL"))) {
        return 8;
    }
    am3d::exe::MissionMovementStartState start = am3d::exe::mission_start_from_alp1_pad_fixture();
    const std::filesystem::path disc_root = resolve_disc_root();
    if (!disc_root.empty()) {
        const am3d::exe::Alp1PadSpawnParseResult spawn =
            am3d::exe::load_alp1_pad_spawn_from_disc_root(disc_root, 1u);
        if (spawn.ok) {
            start.x = spawn.x;
            start.z = spawn.z;
            start.heading = spawn.heading;
        }
    }
    return run_movement_slice(start);
}