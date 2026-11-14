// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

std::uint32_t call_800751d8(std::uint32_t a0, std::uint32_t a1, std::uint32_t& stack_word,
    std::uint32_t& saved_word);

}
