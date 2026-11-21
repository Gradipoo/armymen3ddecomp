// SPDX-License-Identifier: GPL-3.0-or-later
#include "prototype_task_8_mission.hpp"

#include "alp1_pad_spawn.hpp"
#include "alp1_pad_spawn_fixture.hpp"
#include "disc_data_file_read.hpp"
#include "mission_menu_handoff.hpp"

#include <array>
#include <string>

namespace am3d::exe {
namespace {

constexpr std::size_t kAlp1TxtProbeBytes = 256u;

bool alp1_txt_header_in_probe(const std::uint8_t* data, std::size_t nbytes) {
    std::string line;
    for (std::size_t i = 0u; i < nbytes; ++i) {
        const char ch = static_cast<char>(data[i]);
        if (ch == '\n' || ch == '\r') {
            break;
        }
        line.push_back(ch);
    }
    return line.find("Alpine1") != std::string::npos;
}

}  // namespace

MissionMovementStartState mission_movement_start_disc_free() {
    return mission_start_from_alp1_pad_fixture();
}

MissionPadScript prototype_task_8_default_pad_script() {
    MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = MissionPadScript::kPadCrossS2;
    }
    return script;
}

PrototypeTask8MissionResult run_prototype_task_8_mission_slice(
    const std::filesystem::path& disc_root) {
    PrototypeTask8MissionResult result{};
    const MissionLoadIntent intent = record_mission_load_intent();
    result.mission_path_gpr = intent.mission_path_gpr;

    MissionMovementStartState start = mission_movement_start_disc_free();
    if (!disc_root.empty()) {
        std::array<std::uint8_t, kAlp1TxtProbeBytes> txt_probe{};
        const platform::DiscDataFileReadResult txt_read = platform::read_disc_data_file(
            disc_root / MissionSliceDeclaration::kTxtPath, txt_probe.size(), txt_probe.data());
        if (txt_read.ok && txt_read.bytes_read > 0u) {
            result.alp1_txt_header =
                alp1_txt_header_in_probe(txt_probe.data(), txt_read.bytes_read);
        }
        const Alp1PadSpawnParseResult spawn = load_alp1_pad_spawn_from_disc_root(disc_root, 1u);
        if (spawn.ok) {
            start.x = spawn.x;
            start.z = spawn.z;
            start.heading = spawn.heading;
            result.spawn_from_pad = true;
        }
    }

    result.spawn_x = start.x;
    result.spawn_z = start.z;
    result.spawn_heading = start.heading;

    MissionMovementStartState state{};
    const MissionMovementRunResult run =
        run_mission_movement_frames(prototype_task_8_default_pad_script(), start, state);
    result.frames_run = run.frames_run;
    result.final_state = run.final_state;
    return result;
}

}  // namespace am3d::exe
