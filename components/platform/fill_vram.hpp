// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "display_fill.hpp"
#include <cstdint>
#include <vector>

namespace am3d::platform {

// The known display-fill packet sink. Other GPU commands fail explicitly.
class FillVram final : public exe::DisplayFillGpu {
public:
    static constexpr unsigned width = 1024;
    static constexpr unsigned height = 512;
    FillVram();
    void draw_sync(int mode) override;
    void draw_prim(const exe::FillPacket& packet) override;
    std::uint16_t pixel(unsigned x, unsigned y) const;
    std::uint32_t argb(unsigned x, unsigned y) const;
    void write_pixel(unsigned x, unsigned y, std::uint16_t rgb555);

private:
    std::vector<std::uint16_t> pixels_;
};

}
