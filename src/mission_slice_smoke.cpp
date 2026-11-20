// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_buffers.hpp"
#include "display_clear.hpp"
#include "display_fill.hpp"
#include "mission_menu_handoff.hpp"
#include "alp1_pad_spawn.hpp"
#include "mission_movement_slice.hpp"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

am3d::exe::MissionPadScript default_eight_frame_script() {
    am3d::exe::MissionPadScript script{};
    script.length = 8u;
    for (std::size_t i = 0u; i < 4u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadIdleS2;
    }
    for (std::size_t i = 4u; i < 8u; ++i) {
        script.s2[i] = am3d::exe::MissionPadScript::kPadCrossS2;
    }
    return script;
}

void draw_mission_diagnostic(am3d::exe::DisplayBufferState& display, am3d::platform::FillVram& vram,
                             std::uint32_t marker_x) {
    const auto drawing = am3d::exe::drawing_fill_state(display);
    am3d::exe::fill_display(0x202040u,
        {drawing.origin_x, drawing.origin_y, 0, 0, 512, 240}, vram);
    am3d::exe::fill_display(0x00ff00u,
        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(marker_x), 112u,
         static_cast<std::uint16_t>(marker_x + 16u), 128u},
        vram);
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

int main(int argc, char** argv) {
    try {
        bool hidden = false;
        bool capture = false;
        bool checkpoint = false;
        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--hidden") {
                hidden = true;
            } else if (arg == "--capture") {
                capture = true;
            } else if (arg == "--checkpoint") {
                checkpoint = true;
            } else {
                throw std::invalid_argument("use --hidden, --capture, or --checkpoint");
            }
        }

        const am3d::exe::MissionLoadIntent intent = am3d::exe::record_mission_load_intent();
        if (intent.mission_path_gpr != 0x800bfdbcu) {
            throw std::runtime_error("mission_path_gpr does not cite 0x800bfdbc");
        }

        const am3d::exe::MissionPadScript script = default_eight_frame_script();
        am3d::exe::MissionMovementStartState start{100, 200, 0};
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
        am3d::exe::MissionMovementStartState state{};
        const am3d::exe::MissionMovementRunResult result =
            am3d::exe::run_mission_movement_frames(script, start, state);
        if (result.frames_run != 8u) {
            throw std::runtime_error("expected 8 movement frames");
        }

        const std::uint32_t marker_x =
            200u + static_cast<std::uint32_t>(state.z - start.z);

        am3d::platform::SdlPlatform window("Army Men 3D mission slice test", 640, 480, hidden);
        am3d::platform::FillVram vram;
        am3d::exe::DisplayBufferState display;
        display.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
        display.width = display.right = 512;
        display.height = display.bottom = 240;
        display.mode = 2;
        display.buffer_count = 2;
        am3d::exe::clear_display_buffers(0, display, window, vram);

        draw_mission_diagnostic(display, vram, marker_x);
        am3d::exe::advance_display_buffers(display, window);
        window.present(vram);

        if (capture) {
            std::filesystem::create_directories("build/platform");
            window.save_frame("build/platform/mission_slice_smoke.bmp");
        }
        if (checkpoint) {
            std::filesystem::create_directories("build/platform");
            std::ofstream out("build/platform/task8-checkpoint.txt", std::ios::trunc);
            out << am3d::exe::MissionSliceDeclaration::kMissionId << ' ' << state.x << ' '
                << state.z << ' ' << state.heading << ' ' << result.frames_run << '\n';
        }

        if (!hidden) {
            const auto pad = window.poll();
            while (!pad.quit && (pad.buttons & (1u << 3))) {
                window.wait_next_frame(std::chrono::nanoseconds(16666667));
                const auto next = window.poll();
                if (next.quit || !(next.buttons & (1u << 3))) {
                    break;
                }
            }
        }

        std::cout << "Mission slice presented 1 diagnostic frame (Alp1 z=" << state.z
                  << ", marker_x=" << marker_x << ").\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}