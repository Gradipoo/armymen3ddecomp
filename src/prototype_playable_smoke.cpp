// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_buffers.hpp"
#include "display_clear.hpp"
#include "display_fill.hpp"
#include "alp1_pad_spawn.hpp"
#include "menu_submit_frame.hpp"
#include "prototype_playable_checkpoint.hpp"
#include "disc_front_tim_load.hpp"
#include "prototype_playable_pipeline.hpp"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::uint32_t pad_get_state_idle(std::uint32_t port) {
    (void)port;
    return 2u;
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

void draw_playable_diagnostic(am3d::exe::DisplayBufferState& display,
                              am3d::platform::FillVram& vram, std::uint32_t menu_marker_x,
                              std::uint32_t mission_marker_x) {
    const auto drawing = am3d::exe::drawing_fill_state(display);
    am3d::exe::fill_display(0x202040u,
        {drawing.origin_x, drawing.origin_y, 0, 0, 512, 240}, vram);
    am3d::exe::fill_display(0x00ff00u,
        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(menu_marker_x), 96u,
         static_cast<std::uint16_t>(menu_marker_x + 16u), 112u},
        vram);
    am3d::exe::fill_display(0x0080ffu,
        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(mission_marker_x), 128u,
         static_cast<std::uint16_t>(mission_marker_x + 16u), 144u},
        vram);
}

void present_menu_submit(am3d::exe::DisplayBufferState& display, am3d::platform::SdlPlatform& window,
                         am3d::platform::FillVram& vram,
                         const std::vector<std::uint8_t>& front_bytes,
                         std::uint32_t marker_x, std::uint32_t selection_index) {
    const auto drawing = am3d::exe::drawing_fill_state(display);
    am3d::platform::MenuSubmitFrameRequest request{};
    request.origin_x = drawing.origin_x;
    request.origin_y = drawing.origin_y;
    request.marker_x = marker_x;
    request.marker_y = 112u;
    request.marker_color = 0x00ff00u;
    request.selection_highlight_index = selection_index;
    if (!front_bytes.empty()) {
        request.front_bytes = front_bytes.data();
        request.front_size = front_bytes.size();
    }
    (void)am3d::platform::menu_submit_frame(request, vram);
    am3d::exe::advance_display_buffers(display, window);
    window.present(vram);
}

void draw_mission_marker(am3d::exe::DisplayBufferState& display, am3d::platform::FillVram& vram,
                         std::uint32_t mission_marker_x) {
    const auto drawing = am3d::exe::drawing_fill_state(display);
    am3d::exe::fill_display(0x0080ffu,
        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(mission_marker_x), 128u,
         static_cast<std::uint16_t>(mission_marker_x + 16u), 144u},
        vram);
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

        am3d::exe::PrototypePlayablePipelineConfig config{};
        bool spawn_from_pad = false;
        const std::filesystem::path disc_root = resolve_disc_root();
        config.disc_root = disc_root;
        if (!disc_root.empty()) {
            const am3d::exe::Alp1PadSpawnParseResult spawn =
                am3d::exe::load_alp1_pad_spawn_from_disc_root(disc_root, 1u);
            if (spawn.ok) {
                config.movement_start.x = spawn.x;
                config.movement_start.z = spawn.z;
                config.movement_start.heading = spawn.heading;
                spawn_from_pad = true;
            }
        }
        const am3d::exe::PrototypePlayablePipelineResult result =
            am3d::exe::run_prototype_playable_pipeline(config, pad_get_state_idle);

        const std::uint32_t mission_marker_x =
            260u + static_cast<std::uint32_t>(result.movement_final_state.z -
                                              config.movement_start.z);

        am3d::platform::SdlPlatform window("Army Men 3D prototype playable test", 640, 480, hidden);
        am3d::platform::FillVram vram;
        am3d::exe::DisplayBufferState display;
        display.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
        display.width = display.right = 512;
        display.height = display.bottom = 240;
        display.mode = 2;
        display.buffer_count = 2;
        am3d::exe::clear_display_buffers(0, display, window, vram);

        const std::vector<std::uint8_t> front_bytes =
            am3d::platform::load_front_tim_disc_bytes(disc_root);
        const bool use_menu_submit = result.has_front && !front_bytes.empty();
        unsigned frames_presented = 0u;

        if (use_menu_submit) {
            present_menu_submit(display, window, vram, front_bytes, result.menu_marker_x_a,
                                result.menu_selection_after_a);
            ++frames_presented;
            if (capture) {
                std::filesystem::create_directories("build/platform");
                window.save_frame("build/platform/prototype_playable_smoke-menu.bmp");
            }

            const auto drawing_b = am3d::exe::drawing_fill_state(display);
            am3d::platform::MenuSubmitFrameRequest request_b{};
            request_b.origin_x = drawing_b.origin_x;
            request_b.origin_y = drawing_b.origin_y;
            request_b.marker_x = result.menu_marker_x_b;
            request_b.marker_y = 112u;
            request_b.marker_color = 0x00ff00u;
            request_b.selection_highlight_index = result.menu_selection_after_b;
            request_b.front_bytes = front_bytes.data();
            request_b.front_size = front_bytes.size();
            (void)am3d::platform::menu_submit_frame(request_b, vram);
            draw_mission_marker(display, vram, mission_marker_x);
            am3d::exe::advance_display_buffers(display, window);
            window.present(vram);
            ++frames_presented;
            if (capture) {
                window.save_frame("build/platform/prototype_playable_smoke.bmp");
            }
        } else {
            const std::uint32_t menu_marker_x = 200u + result.menu_s7 * 12u;
            draw_playable_diagnostic(display, vram, menu_marker_x, mission_marker_x);
            am3d::exe::advance_display_buffers(display, window);
            window.present(vram);
            frames_presented = 1u;
            if (capture) {
                std::filesystem::create_directories("build/platform");
                window.save_frame("build/platform/prototype_playable_smoke.bmp");
            }
        }

        if (checkpoint) {
            const am3d::exe::PrototypePlayableCheckpointLine line =
                am3d::exe::make_prototype_playable_checkpoint_line(
                    result, config.movement_start, spawn_from_pad);
            am3d::exe::write_prototype_playable_checkpoint_file(
                am3d::exe::kPrototypePlayableCheckpointPath, line);
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

        if (use_menu_submit) {
            std::cout << "Prototype playable pipeline presented " << frames_presented
                      << " FRONT menu frames (s7_a=" << result.menu_s7_after_menu_budget
                      << ", s7_b=" << result.menu_s7
                      << ", mission z=" << result.movement_final_state.z << ").\n";
        } else {
            std::cout << "Prototype playable pipeline presented 1 diagnostic frame (menu s7="
                      << result.menu_s7 << ", mission z=" << result.movement_final_state.z
                      << ").\n";
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}