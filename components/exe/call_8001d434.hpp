// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

using Call8001d434Tolower = std::uint32_t (*)(std::uint32_t a0);

// Walks the bytes at text until a zero byte. Each nonzero byte is
// sign-extended and passed to tolower. The low 8 bits of the result
// replace that byte. The retail tolower body stays open.
void call_8001d434(std::uint8_t* text, Call8001d434Tolower tolower);

}
