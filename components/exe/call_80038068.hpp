// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
namespace am3d::exe {
struct Call80038068Result {
    std::uint32_t counts[32];
    std::uint32_t at_800aa294;
    std::uint32_t at_800abe98;
    std::uint32_t at_800abe9c;
    std::uint32_t at_800d68b8;
};
Call80038068Result call_80038068();
}
