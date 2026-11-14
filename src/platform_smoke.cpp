// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_clear.hpp"
#include "front_tim.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char** argv) {
    try {
        int frames = 120;
        bool hidden = false, capture = false;
        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--hidden") hidden = true;
            else if (arg == "--capture") capture = true;
            else if (arg == "--frames" && i + 1 < argc) frames = std::stoi(argv[++i]);
            else throw std::invalid_argument("use --frames NUMBER, --hidden, or --capture");
        }
        if (frames < 1 || frames > 36000) throw std::invalid_argument("frames must be 1 through 36000");
        am3d::platform::SdlPlatform host("Army Men 3D platform test", 640, 480, hidden);
        am3d::platform::FillVram vram;
        am3d::exe::DisplayBufferState display;
        display.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
        display.width = display.right = 512;
        display.height = display.bottom = 240;
        display.mode = 2;
        display.buffer_count = 2;
        am3d::exe::clear_display_buffers(0, display, host, vram);
        int x = 240, y = 112;
        int completed = 0;
        const std::filesystem::path front_path = "build/disc/DATA/FRONT.TIM";
        std::vector<std::uint8_t> front_bytes;
        if (std::filesystem::is_regular_file(front_path)) {
            std::ifstream in(front_path, std::ios::binary);
            front_bytes.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
            if (!in) throw std::runtime_error("could not read build/disc/DATA/FRONT.TIM");
        }
        for (int frame = 0; frame < frames; ++frame) {
            const auto pad = host.poll();
            if (pad.quit || !(pad.buttons & (1u << 3))) break;
            if (!(pad.buttons & (1u << 4)) && y > 0) --y;
            if (!(pad.buttons & (1u << 6)) && y < 224) ++y;
            if (!(pad.buttons & (1u << 7)) && x > 0) --x;
            if (!(pad.buttons & (1u << 5)) && x < 496) ++x;
            const auto drawing = am3d::exe::drawing_fill_state(display);
            if (front_bytes.empty()) {
                for (unsigned stripe = 0; stripe < 8; ++stripe) {
                    const auto color = (stripe & 1 ? 0x0000ffu : 0u) |
                        (stripe & 2 ? 0x00ff00u : 0u) | (stripe & 4 ? 0xff0000u : 0u);
                    am3d::exe::fill_display(color,
                        {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(stripe * 64), 0,
                         static_cast<std::uint16_t>((stripe + 1) * 64), 240}, vram);
                }
            } else {
                am3d::exe::fill_display(0,
                    {drawing.origin_x, drawing.origin_y, 0, 0, 512, 240}, vram);
                if (!am3d::platform::paint_front_tim(front_bytes.data(), front_bytes.size(),
                        drawing.origin_x + 234, drawing.origin_y + 56, vram, nullptr)) {
                    throw std::runtime_error("DATA/FRONT.TIM is not the measured 4-bit picture");
                }
            }
            am3d::exe::fill_display((pad.buttons & (1u << 14)) ? 0xffffffu : 0x0000ffu,
                {drawing.origin_x, drawing.origin_y, static_cast<std::uint16_t>(x), static_cast<std::uint16_t>(y),
                 static_cast<std::uint16_t>(x + 16), static_cast<std::uint16_t>(y + 16)}, vram);
            am3d::exe::advance_display_buffers(display, host);
            host.present(vram);
            ++completed;
            if (capture && frame == 0) {
                std::filesystem::create_directories("build/platform");
                host.save_frame("build/platform/smoke.bmp");
            }
            host.wait_next_frame(std::chrono::nanoseconds(16666667));
        }
        std::cout << "Platform test presented " << completed
                  << (front_bytes.empty() ? " synthetic frames.\n" : " frames from DATA/FRONT.TIM.\n");
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
