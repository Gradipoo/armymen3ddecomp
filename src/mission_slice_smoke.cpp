// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_buffers.hpp"
#include "display_clear.hpp"
#include "display_fill.hpp"
#include "mission_task8_checkpoint.hpp"
#include "prototype_task_8_mission.hpp"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

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

        const am3d::exe::PrototypeTask8MissionResult mission =
            am3d::exe::run_prototype_task_8_mission_slice(resolve_disc_root());
        if (mission.mission_path_gpr != 0x800bfdbcu) {
            throw std::runtime_error("mission_path_gpr does not cite 0x800bfdbc");
        }
        if (mission.frames_run != 8u) {
            throw std::runtime_error("expected 8 movement frames");
        }

        const std::uint32_t marker_x =
            200u + static_cast<std::uint32_t>(mission.final_state.z - mission.spawn_z);

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
            out << am3d::exe::format_mission_task8_checkpoint(mission);
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

        std::cout << "Mission slice presented 1 diagnostic frame (Alp1 z="
                  << mission.final_state.z << ", marker_x=" << marker_x << ").\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}