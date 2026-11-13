// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

using Call8007a3b0Fn = void (*)(std::uint32_t a0, std::uint32_t* slot10,
                                std::uint32_t a2, std::uint32_t a3);

void call_8007a3b0(std::uint32_t s1, std::uint32_t* slot10, std::uint32_t a2,
                   std::uint32_t a3, Call8007a3b0Fn callee);

}
