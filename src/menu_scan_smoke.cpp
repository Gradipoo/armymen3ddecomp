// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_clear.hpp"
#include "front_tim.hpp"
#include "menu_input_scan_loop.hpp"
#include "menu_pad_get_state.hpp"
#include "menu_submit_frame.hpp"
#include "menu_table_sequence.hpp"

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

std::uint16_t g_live_pad_buttons = 0xffffu;

std::uint32_t pad_get_state_from_poll(std::uint32_t port) {
    return am3d::platform::menu_scan_pad_get_state(port, g_live_pad_buttons);
}

void draw_frame(const std::vector<std::uint8_t>& front_bytes,
                am3d::exe::DisplayBufferState& display, am3d::platform::FillVram& vram,
                std::uint32_t marker_x, std::uint32_t marker_y, std::uint32_t marker_color) {
    const auto drawing = am3d::exe::drawing_fill_state(display);
    if (front_bytes.empty()) {
        for (unsigned stripe = 0; stripe < 8; ++stripe) {
            const auto color = (stripe & 1 ? 0x0000ffu : 0u) | (stripe & 2 ? 0x00ff00u : 0u) |
                (stripe & 4 ? 0xff0000u : 0u);
            am3d::exe::fill_display(color,
                {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(stripe * 64), 0,
                 static_cast<std::uint16_t>((stripe + 1) * 64), 240},
                vram);
        }
    } else {
        am3d::exe::fill_display(0,
            {drawing.origin_x, drawing.origin_y, 0, 0, 512, 240}, vram);
        if (!am3d::platform::paint_front_tim(front_bytes.data(), front_bytes.size(),
                drawing.origin_x + 234, drawing.origin_y + 56, vram, nullptr)) {
            throw std::runtime_error("DATA/FRONT.TIM is not the measured 4-bit picture");
        }
    }
    am3d::exe::fill_display(marker_color,
        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(marker_x),
         static_cast<std::uint16_t>(marker_y), static_cast<std::uint16_t>(marker_x + 16),
         static_cast<std::uint16_t>(marker_y + 16)},
        vram);
}

struct ScanHostState {
    static constexpr std::size_t kSlots = 8u;
    std::array<std::uint8_t, kSlots * am3d::exe::kMenuInputScanSlotBytes> table{};
    am3d::exe::MenuTableSequencer table_sequencer{};
    std::array<std::uint8_t, 0x400u> record_bytes{};
    std::uint8_t* record = record_bytes.data();
    am3d::exe::MenuInputScanState scan{};
    am3d::exe::MenuInputScanIndices indices{};
    std::uint32_t sp20 = 0u;
    std::uint32_t stack_word_1c = 4u;
};

ScanHostState make_scan_host() {
    ScanHostState host{};
    am3d::exe::menu_table_fill_released_slots(host.table.data(), ScanHostState::kSlots);
    host.indices.menu_table_bytes = static_cast<std::uint32_t>(host.table.size());
    // stack_word_18 0: retail PadGetState a0=0 per call-80064e58.md.
    host.indices.stack_word_18 = 0u;
    host.indices.stack_word_28 = 0u;
    return host;
}

}  // namespace

int main(int argc, char** argv) {
    try {
        int frames = 4;
        bool hidden = false;
        bool capture = false;
        bool batch = false;
        bool submit = false;
        bool scripted = false;
        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--hidden") {
                hidden = true;
            } else if (arg == "--capture") {
                capture = true;
            } else if (arg == "--batch") {
                batch = true;
            } else if (arg == "--submit") {
                submit = true;
            } else if (arg == "--scripted") {
                scripted = true;
            } else if (arg == "--frames" && i + 1 < argc) {
                frames = std::stoi(argv[++i]);
            } else {
                throw std::invalid_argument(
                    "use --frames NUMBER, --hidden, --capture, --batch, --submit, or --scripted");
            }
        }
        if (frames < 1 || frames > 36000) {
            throw std::invalid_argument("frames must be 1 through 36000");
        }

        am3d::platform::SdlPlatform window("Army Men 3D menu scan test", 640, 480, hidden);
        am3d::platform::FillVram vram;
        am3d::exe::DisplayBufferState display;
        display.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
        display.width = display.right = 512;
        display.height = display.bottom = 240;
        display.mode = 2;
        display.buffer_count = 2;
        am3d::exe::clear_display_buffers(0, display, window, vram);

        const std::filesystem::path front_path = "build/disc/DATA/FRONT.TIM";
        std::vector<std::uint8_t> front_bytes;
        if (std::filesystem::is_regular_file(front_path)) {
            std::ifstream in(front_path, std::ios::binary);
            front_bytes.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
            if (!in) {
                throw std::runtime_error("could not read build/disc/DATA/FRONT.TIM");
            }
        }

        ScanHostState scan_host = make_scan_host();
        const bool use_table_sequencer = scripted || frames > 1;
        am3d::exe::MenuTableSequencer* const table_sequencer =
            use_table_sequencer ? &scan_host.table_sequencer : nullptr;
        int completed = 0;

        auto present_scan_marker = [&](std::uint32_t marker_x, std::uint32_t marker_color) {
            if (submit) {
                const auto drawing = am3d::exe::drawing_fill_state(display);
                am3d::platform::MenuSubmitFrameRequest request{};
                request.origin_x = drawing.origin_x;
                request.origin_y = drawing.origin_y;
                request.marker_x = marker_x;
                request.marker_y = 112u;
                request.marker_color = marker_color;
                if (!front_bytes.empty()) {
                    request.front_bytes = front_bytes.data();
                    request.front_size = front_bytes.size();
                }
                (void)am3d::platform::menu_submit_frame(request, vram);
            } else {
                draw_frame(front_bytes, display, vram, marker_x, 112u, marker_color);
            }
            am3d::exe::advance_display_buffers(display, window);
            window.present(vram);
        };

        if (batch) {
            g_live_pad_buttons = window.poll().buttons;
            const am3d::exe::MenuInputScanLoopResult result = am3d::exe::run_menu_input_scan_frames(
                static_cast<std::uint32_t>(frames), pad_get_state_from_poll, scan_host.table.data(),
                scan_host.indices, scan_host.sp20, 0u, 0u, scan_host.record, scan_host.scan,
                scan_host.stack_word_1c, table_sequencer,
                &scan_host.indices.stack_word_28);
            const std::uint32_t marker_x = 200u + scan_host.scan.s7 * 12u;
            present_scan_marker(marker_x, 0x00ff00u);
            completed = 1;
            if (capture) {
                std::filesystem::create_directories("build/platform");
                window.save_frame("build/platform/menu_scan_smoke.bmp");
            }
            std::cout << "Menu scan batch ran " << result.frames_run << " scan frames; presented 1 "
                      << (submit ? "submission" : (front_bytes.empty() ? "synthetic" : "FRONT.TIM"))
                      << " diagnostic frame (s7=" << scan_host.scan.s7 << ").\n";
            return 0;
        }

        for (int frame = 0; frame < frames; ++frame) {
            const auto pad = window.poll();
            g_live_pad_buttons = pad.buttons;
            if (pad.quit || !(pad.buttons & (1u << 3))) {
                break;
            }
            const am3d::exe::MenuInputScanLoopResult step =
                am3d::exe::run_menu_input_scan_frames(
                    1u, pad_get_state_from_poll, scan_host.table.data(), scan_host.indices,
                    scan_host.sp20,
                    0u, 0u, scan_host.record, scan_host.scan, scan_host.stack_word_1c,
                    table_sequencer, &scan_host.indices.stack_word_28);
            const std::uint32_t marker_x = 200u + scan_host.scan.s7 * 12u;
            const std::uint32_t marker_color =
                (pad.buttons & (1u << 14)) ? 0xffffffu : 0x0000ffu;
            present_scan_marker(marker_x, marker_color);
            ++completed;
            if (capture && frame == 0) {
                std::filesystem::create_directories("build/platform");
                window.save_frame("build/platform/menu_scan_smoke.bmp");
            }
            window.wait_next_frame(std::chrono::nanoseconds(16666667));
            if (!step.last_step.loop_again) {
                break;
            }
        }

        std::cout << "Menu scan test presented " << completed << " frame"
                  << (completed == 1 ? "" : "s") << " with scan s7=" << scan_host.scan.s7
                  << (submit ? " (call_8007c11c submit path).\n"
                           : (front_bytes.empty() ? " (synthetic background).\n" : " (FRONT.TIM).\n"));
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}