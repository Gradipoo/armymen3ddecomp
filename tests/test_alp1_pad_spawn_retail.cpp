// SPDX-License-Identifier: GPL-3.0-or-later
#include "alp1_pad_spawn.hpp"

#include <cstdint>
#include <filesystem>

namespace {

constexpr int kSkipNoDisc = 77;

constexpr std::int32_t kGoldenX = 50;
constexpr std::int32_t kGoldenZ = 1252;
constexpr std::int32_t kGoldenHeading = 50;

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

int main() {
    const std::filesystem::path root = resolve_disc_root();
    if (root.empty()) {
        return kSkipNoDisc;
    }
    const std::filesystem::path pad = root / "DATA" / "ALP1.PAD";
    if (!std::filesystem::is_regular_file(pad)) {
        return kSkipNoDisc;
    }
    const am3d::exe::Alp1PadSpawnParseResult result =
        am3d::exe::load_alp1_pad_spawn_from_disc_root(root, 1u);
    if (!result.ok) {
        return 1;
    }
    if (result.x != kGoldenX || result.z != kGoldenZ || result.heading != kGoldenHeading) {
        return 2;
    }
    return 0;
}