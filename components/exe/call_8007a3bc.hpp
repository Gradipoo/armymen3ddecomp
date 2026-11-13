// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

using Call8007a3bcFn = std::uint32_t (*)();

std::uint32_t call_8007a3bc(std::uint32_t v0, std::uint32_t s0, Call8007a3bcFn nonzero);

}
