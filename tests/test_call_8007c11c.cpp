// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007c11c.hpp"

#include <cstdint>
#include <vector>

namespace {
struct Gpu final : am3d::exe::SubmitOrderingTableGpu {
    std::vector<int> events;
    std::uint32_t flag = 0;
    std::uint32_t mode = 99;
    std::uint32_t callback = 0;
    std::uint32_t address = 0;
    void draw_sync(std::uint32_t value) override {
        mode = value; events.push_back(1); flag = 7;
    }
    void draw_sync_callback(std::uint32_t value) override {
        callback = value; events.push_back(3);
    }
    std::uint32_t draw_otag(std::uint32_t table) override {
        address = table; events.push_back(4); return 0x12345678u;
    }
};
}

int main() {
    Gpu gpu;
    auto flag = [&] { gpu.events.push_back(2); return gpu.flag; };
    const auto first = am3d::exe::call_8007c11c(0x800c8518u, 0x900u, flag, gpu);
    if (first != 0x12345678u || gpu.mode != 0 || gpu.callback != 0x8007c00cu ||
        gpu.events != std::vector<int>{1, 2, 3, 4} || gpu.address != 0x800ca914u) return 1;

    gpu.events.clear();
    auto zero = [&] { gpu.events.push_back(2); return 0u; };
    const auto second = am3d::exe::call_8007c11c(0x800ca918u, 0x900u, zero, gpu);
    if (second != 0x12345678u || gpu.events != std::vector<int>{1, 2, 4} ||
        gpu.address != 0x800ccd14u) return 2;

    gpu.events.clear();
    const auto wrapped = am3d::exe::call_8007c11c(2u, 0u, zero, gpu);
    if (wrapped != 0x12345678u || gpu.events != std::vector<int>{1, 2, 4} ||
        gpu.address != 0xfffffffeu) return 3;
}
