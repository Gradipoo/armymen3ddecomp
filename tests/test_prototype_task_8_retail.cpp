// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_task_8_mission.hpp"

#include <cstdint>
#include <filesystem>
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

}  // namespace

// PROTOTYPE.md row 8 disc-backed check when build/disc/DATA/ALP1.TXT exists.
int main() {
    const std::filesystem::path txt_path = resolve_disc_data("ALP1.TXT");
    if (txt_path.empty()) {
        return kSkipNoDisc;
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
    const std::filesystem::path disc_root = resolve_disc_root();
    if (disc_root.empty()) {
        return kSkipNoDisc;
    }
    const am3d::exe::PrototypeTask8MissionResult result =
        am3d::exe::run_prototype_task_8_mission_slice(disc_root);
    if (!result.alp1_txt_header) {
        return 5;
    }
    if (!result.spawn_from_pad) {
        return 9;
    }
    if (result.frames_run != 8u) {
        return 1;
    }
    if (result.final_state.x != result.spawn_x ||
        result.final_state.heading != result.spawn_heading) {
        return 2;
    }
    if (result.final_state.z <= result.spawn_z) {
        return 3;
    }
    if (result.mission_path_gpr != 0x800bfdbcu) {
        return 10;
    }
    return 0;
}
