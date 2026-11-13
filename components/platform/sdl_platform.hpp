// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "fill_vram.hpp"
#include "display_buffers.hpp"
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace am3d::platform {

struct PadState {
    bool quit = false;
    // Standard digital pad bits. A zero bit means the button is held.
    std::uint16_t buttons = 0xffff;
};

class SdlPlatform : public exe::DisplayEnvironmentGpu {
public:
    SdlPlatform(const char* title, int window_width, int window_height, bool hidden = false);
    ~SdlPlatform();
    SdlPlatform(const SdlPlatform&) = delete;
    SdlPlatform& operator=(const SdlPlatform&) = delete;

    PadState poll();
    void apply_display(const exe::DisplayEnvironment& environment) override;
    void apply_draw(const exe::DrawEnvironment& environment) override;
    const exe::DrawEnvironment& drawing_environment() const;
    void present(const FillVram& vram);
    void present(const FillVram& vram, unsigned x, unsigned y, unsigned width, unsigned height);
    void wait_next_frame(std::chrono::nanoseconds period);
    std::vector<std::uint32_t> readback(int& width, int& height) const;
    void save_frame(const std::string& path) const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}
