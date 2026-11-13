// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

using Call80010e00Fn = void (*)(std::uint32_t a0, std::uint32_t a1,
                                std::uint32_t a2, std::uint32_t a3);

void call_80010e00(Call80010e00Fn callee);

}
