// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"
#include "prototype_playable_pipeline.hpp"

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

std::uint32_t pad_get_state_idle(std::uint32_t port) {
    (void)port;
    return 2u;
}

}  // namespace

// Requires owner ALP1.TXT; runs full menu-to-mission pipeline (no retail gameplay).
int main() {
    const std::filesystem::path txt_path = resolve_disc_data("ALP1.TXT");
    if (txt_path.empty()) {
        return kSkipNoDisc;
    }
    if (!first_line_contains_alpine1(txt_path)) {
        return 5;
    }

    am3d::exe::PrototypePlayablePipelineConfig config{};
    const std::filesystem::path disc_root = resolve_disc_root();
    config.disc_root = disc_root;
    if (!disc_root.empty()) {
        const am3d::exe::Alp1PadSpawnParseResult spawn =
            am3d::exe::load_alp1_pad_spawn_from_disc_root(disc_root, 1u);
        if (spawn.ok) {
            config.movement_start.x = spawn.x;
            config.movement_start.z = spawn.z;
            config.movement_start.heading = spawn.heading;
        }
    }
    const am3d::exe::PrototypePlayablePipelineResult result =
        am3d::exe::run_prototype_playable_pipeline(config, pad_get_state_idle);

    if (result.menu_s7_after_menu_budget != 8u) {
        return 1;
    }
    if (result.mission_path_gpr != 0x800bfdbcu) {
        return 2;
    }
    if (result.movement_final_state.z <= config.movement_start.z) {
        return 3;
    }
  // Down dispatch cites match synthetic task 7 phase B.
    if (!result.dispatch_destination_stated || result.dispatch_destination != 0x80064f14u) {
        return 4;
    }
    return 0;
}