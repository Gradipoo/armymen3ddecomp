// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
std::uint32_t call_80073fb0(std::uint32_t a0, std::uint32_t flag, std::uint32_t hi, std::uint32_t lo,
    std::uint32_t base);
std::uint32_t call_800741b8(std::uint32_t a0, std::uint32_t link);
std::uint32_t call_8007466c();
}
