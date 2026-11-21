// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_playable_checkpoint.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace am3d::exe {

PrototypePlayableCheckpointLine make_prototype_playable_checkpoint_line(
    const PrototypePlayablePipelineResult& result,
    const MissionMovementStartState& movement_start, bool spawn_from_pad) {
    PrototypePlayableCheckpointLine line{};
    line.menu_s7_after_menu_budget = result.menu_s7_after_menu_budget;
    line.menu_s7 = result.menu_s7;
    line.mission_z = result.movement_final_state.z;
    line.frames = result.frames;
    line.mission_path_gpr = result.mission_path_gpr;
    line.movement_start = movement_start;
    line.spawn_from_pad = spawn_from_pad;
    return line;
}

std::string format_prototype_playable_checkpoint_line(
    const PrototypePlayableCheckpointLine& line) {
    std::ostringstream out;
    out << line.menu_s7_after_menu_budget << ' ' << line.menu_s7 << ' ' << line.mission_z << ' '
        << line.frames.menu << ' ' << line.frames.down << ' ' << line.frames.mission << ' '
        << std::hex << std::nouppercase << "0x" << line.mission_path_gpr << std::dec << ' '
        << line.movement_start.x << ' ' << line.movement_start.z << ' '
        << line.movement_start.heading << ' ' << (line.spawn_from_pad ? 1 : 0) << '\n';
    return out.str();
}

void write_prototype_playable_checkpoint_file(const std::filesystem::path& path,
                                              const PrototypePlayableCheckpointLine& line) {
    if (path.has_parent_path()) {
        std::filesystem::create_directories(path.parent_path());
    }
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        throw std::runtime_error("could not write playable checkpoint");
    }
    out << format_prototype_playable_checkpoint_line(line);
}

}  // namespace am3d::exe
